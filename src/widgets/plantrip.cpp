#include "plantrip.hpp"
#include "ui_plantrip.h"
#include <QDebug>
#include <QTimer>

PlanTrip::PlanTrip(QWidget *parent,RestaurantDataStore *database, NavBar* bar)
    : QWidget(parent), m_ui(new Ui::PlanTrip), m_store(database), m_navbar(bar)
{
    m_ui->setupUi(this);

    /* Active Trip Menu list */
    m_tripMenuList =  new MenuList(m_ui->activeTripMenuWidget);
    m_tripMenuList->setWrapping(false);
    m_tripMenuList->setFlow(QListView::TopToBottom);

    /* Active Trip Menu list */
    m_tripFoodCart =  new MenuList(m_ui->activeTripCart);
    m_tripFoodCart->setWrapping(false);
    m_tripFoodCart->setFlow(QListView::TopToBottom);


    /* Plan Trip list Drag */
    m_planTripListDrag = new RestaurantList(m_ui->planTripListDrag);
    m_planTripListDrag->setDragDropMode(QAbstractItemView::DragDrop);
    m_planTripListDrag->setAcceptDrops(true);

    /* Plan Trip list Drop */
    m_planTripListDrop = new RestaurantList(m_ui->planTripListDrop);
    m_planTripListDrop->setDragDropMode(QAbstractItemView::DragDrop);
    m_planTripListDrop->setAcceptDrops(true);
    m_planTripListDrop->setWrapping(true);
    m_planTripListDrop->setFlow(QListView::LeftToRight);

    /* Hide warning labels for plan trip view */
    m_ui->activeTrip_warning_emptyList->setHidden(true);
    m_ui->activeTrip_warning_noStart->setHidden(true);

    m_ui->tripType->addItem(tr("--- Trip Type ---"), PlanTrip::None);
    m_ui->tripType->addItem(tr("Saddleback"), PlanTrip::Saddleback);
    m_ui->tripType->addItem(tr("Chosen Restaurant and n number chosen"), PlanTrip::ChosenAndN);
    m_ui->tripType->addItem(tr("First Restaurant"), PlanTrip::FirstRestaurant);

    // set text for checkout button
    m_ui->checkout->setText("\uf218");

    resetPlanTripView();
}

PlanTrip::~PlanTrip()
{
    delete m_ui;
}



void PlanTrip::changeHeaderOptions(PlanState state)
{
    // Reset items within combobox
    m_ui->startLocation->clear();

    setPlanState(state);

    // Get the size of the list and let the user go to as many restaurant as there are in the list
    int maxSize = static_cast<int>(m_store->list.size());

    switch (state)
    {
    case Saddleback:

        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_1);
        m_ui->startLocation->addItem(tr("Saddleback"), Saddleback);
        m_planTripListDrop->addItems(m_store->list.begin(), m_store->list.end());

        break;
    case PlanTrip::ChosenAndN:

        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_2);
        m_planTripListDrop->addItems(m_store->list.begin(), m_store->list.end());
        m_ui->startLocation_2->addItem(QString::fromUtf8("-- Starting Location --"),-1);

        // Print all restaurant in list to the QComboBox as an option and it's id as a data member
        for(Restaurant e : m_store->list)
            m_ui->startLocation_2->addItem(QString::fromStdString(e.GetName()), e.GetNumber());

        // Setting range on spin box
        m_ui->spinBox->setRange(1,static_cast<int>(maxSize));

        // Set default value option to the maximum size
        m_ui->spinBox->setValue(maxSize);

        break;
    case FirstRestaurant:

        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_3);
        m_planTripListDrag->addItems(m_store->list.begin(), m_store->list.end());

        break;
    case None:
        // Do Nothing
        break;
    }
}



void PlanTrip::on_pushButton_clicked()
{
    changeHeaderOptions(static_cast<PlanState>(m_ui->tripType->currentData().toInt()));
}

void PlanTrip::on_TripButton_clicked()
{
    /* Deque to go from list to list make it work with vector so that I can just clear */
    while(!m_planTripVector.empty())
    {
        m_planTripVector.pop();
    }

    m_planTripListDrop->getRestaurantIDs(m_planTripVector);

    if (m_planTripVector.empty() && m_ui->startLocation_2->currentIndex() == 0)
    {
        m_ui->activeTrip_warning_emptyList->setHidden(false);
        m_ui->activeTrip_warning_noStart->setHidden(false);
        QTimer::singleShot(3000, m_ui->activeTrip_warning_emptyList, [&]()
        {
            m_ui->activeTrip_warning_emptyList->setHidden(true);
            m_ui->activeTrip_warning_noStart->setHidden(true);
        });
    }
    else if (m_ui->startLocation_2->currentIndex() == 0 )
    {
        m_ui->activeTrip_warning_noStart->setHidden(false);
        QTimer::singleShot(3000, m_ui->activeTrip_warning_emptyList, [&]()
        {
            m_ui->activeTrip_warning_noStart->setHidden(true);
        });
    }
    else if (m_planTripVector.empty())
    {
        m_ui->activeTrip_warning_emptyList->setHidden(false);
        QTimer::singleShot(3000, m_ui->activeTrip_warning_emptyList, [&]()
        {
            m_ui->activeTrip_warning_emptyList->setHidden(true);
        });
    }
    else
    {
        m_navbar->setHidden(true);
        m_ui->activeTripRestaurant->setText(QString::fromStdString(m_store->FindbyNumber(m_planTripVector.front()).GetName()));
        m_tripMenuList->addAllItems(getRestaurantPointer(m_planTripVector.front()));
        m_ui->planTripStack->setCurrentWidget(m_ui->activeTrip);
    }
}

void PlanTrip::resetPlanTripView()
{
    setPlanState(PlanState::None);
    m_ui->planTripStack->setCurrentWidget(m_ui->chooseType);
    m_ui->tripType->setCurrentIndex(0);
    m_planTripListDrag->clearItems();
    m_planTripListDrop->clearItems();
}

void PlanTrip::activeTrip()
{
    m_planTripVector.pop();
    if(!m_planTripVector.empty())
    {
        m_ui->activeTripRestaurant->setText(QString::fromStdString(m_store->FindbyNumber(m_planTripVector.front()).GetName()));
        m_tripMenuList->addAllItems(getRestaurantPointer(m_planTripVector.front()));
    }
    else
    {
        m_navbar->setHidden(false);
        resetPlanTripView();
    }
}

void PlanTrip::on_next_clicked()
{
    activeTrip();
}

/* add to Eugenes data storage */
Restaurant& PlanTrip::getRestaurantPointer(int id)
{
    for(list<Restaurant>::iterator it = m_store->list.begin() ; it != m_store->list.end(); ++it)
    {
        if(id == (*it).GetNumber())
        {
            return *it;
        }
    }
}

void PlanTrip::setPlanState(const PlanState pickedState)
{
    m_state = pickedState;
}

PlanTrip::PlanState PlanTrip::getPlanState() const
{
    return m_state;
}

void PlanTrip::on_pushButton_2_clicked()
{
    m_tripMenuList->getIDQty();
    m_tripFoodCart;
}
