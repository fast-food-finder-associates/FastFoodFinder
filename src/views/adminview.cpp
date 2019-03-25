#include "adminview.hpp"
#include "ui_adminview.h"
#include <QFileDialog>

/**
 * @brief Constructor
 *
 * Constructs a view for admin tools.
 * Instantiates all the UI for the view and connects signals to slots.
 *
 * @param parent The parent widget this view will show up in
 * @param dataStore The datastore that this view can edit
 */
AdminView::AdminView(QWidget* parent, RestaurantDataStore* dataStore)
    : QWidget(parent), m_ui(new Ui::AdminView), m_store(dataStore), m_currentMenu(-1)
{
    m_ui->setupUi(this);

    /* Available restaurant list */
    m_restListAvailable = new RestaurantList(m_ui->widget_restListAvailable);
    m_restListAvailable->setDragDropMode(QAbstractItemView::DragDrop);
    m_restListAvailable->setAcceptDrops(true);

    /* Deleted restaurant list */
    m_restListDeleted = new RestaurantList(m_ui->widget_restListHidden);
    m_restListDeleted->setDragDropMode(QAbstractItemView::DragDrop);
    m_restListDeleted->setAcceptDrops(true);
    m_restListDeleted->allowDeleted(true);

    /*
     * These connections will unselect items of the other list.
     * This will be used for selecting what restaurant will be chosen
     * when editing a menu.
     */
    connect(m_restListAvailable, &RestaurantList::currentRestaurantChanged,
            [this](RestaurantID id)
            {
                m_restListDeleted->setCurrentRow(-1);
                fillRestaurantEditFields(id);
            });

    connect(m_restListDeleted, &RestaurantList::currentRestaurantChanged,
            [this](RestaurantID id)
            {
                m_restListDeleted->setCurrentRow(-1);
                fillRestaurantEditFields(id);
            });

    /* Menu lists */
    m_menuListAvailable = new MenuList(m_ui->widget_menuAvailable);
    m_menuListDeleted = new MenuList(m_ui->widget_menuDeleted);
    m_menuListDeleted->allowDeleted(true);

    /*
     * These connections are similar as the connections
     * for the restaurant lists above. In addition,
     * edit fields are filled when a menu item is selected
     */
    connect(m_menuListAvailable, &MenuList::currentMenuItemChanged,
            [this](IDs id)
            {
                m_menuListDeleted->setCurrentRow(-1);
                fillMenuItemEditFields(id);
            });

    connect(m_menuListDeleted, &MenuList::currentMenuItemChanged,
            [this](IDs id)
            {
                m_menuListAvailable->setCurrentRow(-1);
                fillMenuItemEditFields(id);
            });

    resetView();
}

/**
 * @brief Destructor
 *
 * Delete dynamically allocated objects.
 */
AdminView::~AdminView()
{
    delete m_ui;
    delete m_restListAvailable;
    delete m_restListDeleted;
    delete m_menuListAvailable;
    delete m_menuListDeleted;
}

/**
 * @brief Reset view as if it was just created
 *
 * The current index of the stacked widget will be set to the first page (index 0).
 * The current menu will be set to an invalid restaurant ID (-1).
 * Reset the UI.
 */
void AdminView::resetView()
{
    //Reset stack widget
    m_ui->stackedWidget->setCurrentIndex(0);

    m_currentMenu = -1;

    resetUi();
}

/**
 * @brief Reset lists, buttons, and fields to their original state
 *
 * Reload the restaurant lists.
 * Reload the menu lists
 * Redo push button stylesheets.
 * Clear line edits.
 * Set double spinboxes to zero.
 */
void AdminView::resetUi()
{
    /* Reset available restaurant list */
    m_restListAvailable->clear();
    m_restListAvailable->addItems(m_store->list.begin(), m_store->list.end());

    /* Reset deleted restaurant list */
    m_restListDeleted->clear();
    for(Restaurant& rest : m_store->list)
    {
        if(rest.IsDeleted())
            m_restListDeleted->addItem(rest);
    }

    /* Menu lists */
    loadMenuList(m_currentMenu);

    /* Push buttons */
    QString pushbuttonReset = "QPushButton { color: black; }";
    m_ui->pushButton_restEdit->setStyleSheet(pushbuttonReset);
    m_ui->pushButton_editMenuView->setStyleSheet(pushbuttonReset);
    m_ui->pushButton_menuAdd->setStyleSheet(pushbuttonReset);
    m_ui->pushButton_menuEdit->setStyleSheet(pushbuttonReset);
    m_ui->pushButton_hideMenuItem->setStyleSheet(pushbuttonReset);
    m_ui->pushButton_restoreMenuItem->setStyleSheet(pushbuttonReset);

    /* Line edits */
    m_ui->lineEdit_nameAdd->clear();
    m_ui->lineEdit_nameEdit->clear();

    /* Double spinboxes */
    m_ui->doubleSpinBox_priceAdd->setValue(0);
    m_ui->doubleSpinBox_priceEdit->setValue(0);
}

/**
 * @brief Load menu lists
 *
 * If the ID isn't invalid (-1), clear the menu lists and load them back.
 * Load the available menu list with all the items (already handles hidden items).
 * Load the hidden menu list with all the menu items only if they're hidden.
 *
 * @param id The restaurant ID to load the menu lists with
 */
void AdminView::loadMenuList(RestaurantID id)
{
    if(id == -1)
        return;

    m_menuListAvailable->clear();
    m_menuListDeleted->clear();

    Restaurant rest = m_store->FindbyNumber(id);

    /* Available menu list */
    m_menuListAvailable->addAllItems(rest);

    /* Deleted menu list */
    const std::vector<MenuItem> items = rest.GetMenu();
    for(MenuItem item : items)
    {
        if(item.IsDeleted())
            m_menuListDeleted->addItem(id, item);
    }
}

/**
 * @brief Mark all the restaurants in the available and hidden list available and hidden respectively
 *
 * Get all the restaurant IDs in the available restaurant list and mark them available.
 * Do the same for hidden restaurant list but make them hidden.
 */
void AdminView::on_pushButton_confirmRestChanges_clicked()
{
    /* Get all the IDs in the list and mark them as available */
    std::vector<RestaurantID> available;
    m_restListAvailable->getRestaurantIDs(available);
    for(RestaurantID id : available)
    {
        if(id != -1)
            m_store->FindbyNumber(id).MarkDeleted(false);
    }

    /* Get all the IDs in the list and mark them as deleted */
    std::vector<RestaurantID> deleted;
    m_restListDeleted->getRestaurantIDs(deleted);
    for(RestaurantID id : deleted)
    {
        if(id != -1)
            m_store->FindbyNumber(id).MarkDeleted(true);
    }

    resetUi();
}


/**
 * @brief Fill restaurant edit fields
 *
 * Find the restaurant and load the edit fields with its data.
 *
 * @param id The restaurant ID to fill the fields
 */
void AdminView::fillRestaurantEditFields(RestaurantID id)
{
    Restaurant rest = m_store->FindbyNumber(id);

    m_ui->lineEdit_restEdit->setText(QString::fromStdString(rest.GetName()));
}

/**
 * @brief Edit restaurant properties
 *
 * Get the selected available restaurant ID and input fields.
 * If the available restaurant ID is invalid, get the
 * hidden restaurant ID.
 * If the hidden restaurant ID is invalid or the input fields are empty,
 * turn the edit button color to red.
 * If they're valid, get the corresponding restaurant object change
 * the inputted properties.
 */
void AdminView::on_pushButton_restEdit_clicked()
{
    RestaurantID id = m_restListAvailable->getSelected();
    QString name = m_ui->lineEdit_restEdit->text();

    /* If the available list isn't selected */
    if(id == -1)
        id = m_restListDeleted->getSelected();

    /* Check if the hidden list isn't selected and if the input fields are invalid */
    if(id == -1 || name.isEmpty())
    {
        m_ui->pushButton_restEdit->setStyleSheet("QPushButton { color: red; } ");
        return;
    }

    /* Edit the menu item */
    Restaurant& rest = m_store->FindbyNumber(id);
    rest.SetName(name.toStdString());

    resetUi();
}

/**
 * @brief Add restaurants to the database
 *
 * Prompts a QFileDialog for a file path.
 * If a valid path was returned, attempt to load that file into the database.
 */
void AdminView::on_pushButton_addFromFile_clicked()
{
    QString folder = QFileDialog::getOpenFileName(this, "Add restaurants", QDir::homePath(), "Restaurants file (*.csv)");

    if(!folder.isEmpty())
        m_store->load(folder.toStdString());

    resetUi();
}

/**
 * @brief Switch to menu view
 *
 * Look for a valid restaurant ID from either list (only 1 restaurant is selected at a time).
 * If a valid ID is found, set the current restaurant menu and change the stacked widget view.
 * If a valid ID isn't found, the push button for changing views is set to color red.
 */
void AdminView::on_pushButton_editMenuView_clicked()
{
    RestaurantID id = m_restListAvailable->getSelected();

    /* If the available list isn't selected */
    if(id == -1)
        id = m_restListDeleted->getSelected();

    /* If the deleted list isn't selected, then none of them are */
    if(id == -1)
    {
        m_ui->pushButton_editMenuView->setStyleSheet("QPushButton { color: red; } ");
        return;
    }

    m_currentMenu = id;

    resetUi();

    m_ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief Fill menu item edit fields
 *
 * Find the correct menu item using the IDs given.
 * Set the values of the fields with their respective data.
 *
 * @param id The IDs of the restaurant and menu item to fill the edit fields with
 */
void AdminView::fillMenuItemEditFields(IDs id)
{
    Restaurant rest = m_store->FindbyNumber(id.first);
    MenuItem item = rest.FindMenuItembyNumber(id.second);

    m_ui->lineEdit_nameEdit->setText(QString::fromStdString(item.GetName()));
    m_ui->doubleSpinBox_priceEdit->setValue(static_cast<double>(item.GetPrice()));
}

/**
 * @brief Switch to restaurant view
 */
void AdminView::on_pushButton_selectRestView_clicked()
{
    resetView();
}

/**
 * @brief Hide selected menu item
 *
 * Get the selected menu item from the available menu list.
 * If one is selected, mark the corresponding menu item as hidden.
 * If one isn't selected, set the hide button color to red.
 */
void AdminView::on_pushButton_hideMenuItem_clicked()
{
    IDs id = m_menuListAvailable->getSelected();

    if(id.second == -1)
    {
        m_ui->pushButton_hideMenuItem->setStyleSheet("QPushButton { color: red; }");
        return;
    }

    /* Hide the menu item */
    Restaurant& rest = m_store->FindbyNumber(id.first);
    rest.FindMenuItembyNumber(id.second).MarkDeleted(true);

    resetUi();
}

/**
 * @brief Restore selected menu item
 *
 * Get the selected menu item from the hidden menu list.
 * If one is selected, mark the corresponding menu item as available.
 * If one isn't selected, set the hide button color to red.
 */
void AdminView::on_pushButton_restoreMenuItem_clicked()
{
    IDs id = m_menuListDeleted->getSelected();

    if(id.second == -1)
    {
        m_ui->pushButton_restoreMenuItem->setStyleSheet("QPushButton { color: red; }");
        return;
    }

    /* Restore the menu item */
    Restaurant& rest = m_store->FindbyNumber(id.first);
    rest.FindMenuItembyNumber(id.second).MarkDeleted(false);

    resetUi();
}

/**
 * @brief Create new menu item through input fields
 *
 * Get the data from input fields.
 * If fields are valid, create a new menu item on the current restaurant ID's menu (m_currentMenu)
 * If either of the fields are empty, set the add button color to red.
 */
void AdminView::on_pushButton_menuAdd_clicked()
{
    QString name = m_ui->lineEdit_nameAdd->text();
    double price = m_ui->doubleSpinBox_priceAdd->value();

    if(name.isEmpty() || price == 0.0)
    {
        m_ui->pushButton_menuAdd->setStyleSheet("QPushButton { color: red; } ");
        return;
    }

    /* Create a new menu item */
    Restaurant& rest = m_store->FindbyNumber(m_currentMenu);
    rest.AddMenuItem(name.toStdString(), static_cast<float>(price));

    resetUi();
}

/**
 * @brief Edit menu item through input fields
 *
 * Look for valid selected IDs from either menu list.
 * If no valid IDs were found, set the edit button color to red.
 * If valid IDs were found and input fields are valid,
 * set the menu item's data using the corresponding input fields.
 */
void AdminView::on_pushButton_menuEdit_clicked()
{
    IDs id = m_menuListAvailable->getSelected();
    QString name = m_ui->lineEdit_nameEdit->text();
    double price = m_ui->doubleSpinBox_priceEdit->value();

    /* If the available list isn't selected */
    if(id.second == -1)
        id = m_menuListDeleted->getSelected();

    /* Check if the hidden list isn't selected and if the input fields are invalid */
    if(id.second == -1 || name.isEmpty() || price == 0.0)
    {
        m_ui->pushButton_menuEdit->setStyleSheet("QPushButton { color: red; } ");
        return;
    }

    /* Edit the menu item */
    MenuItem& item = m_store->FindbyNumber(id.first).FindMenuItembyNumber(id.second);
    item.UpdateName(name.toStdString());
    item.UpdatePrice(static_cast<float>(price));

    resetUi();
}
