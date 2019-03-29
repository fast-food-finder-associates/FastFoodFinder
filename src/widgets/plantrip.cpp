#include "plantrip.hpp"
#include "ui_plantrip.h"
#include <QDebug>

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
    m_tripFoodCart->showQty(true);

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

    m_receipt = new ReceiptList(m_ui->ReceiptWidget, m_store);

    m_tripStore = new TripDataStore();

    test.load("/Users/RogerChavez/Desktop/Group-docs/FastFoodFinder/src/datastore/UserData.csv");
}

PlanTrip::~PlanTrip()
{
    delete m_ui;
    delete m_tripMenuList;
    delete m_tripFoodCart;
    delete m_planTripListDrag;
    delete m_planTripListDrop;
    delete m_receipt;
    delete m_tripStore;
}



void PlanTrip::changeHeaderOptions(PlanType planType)
{
    // Reset items within combobox
    m_ui->startLocation->clear();

    setPlanType(planType);

    // Get the size of the list and let the user go to as many restaurant as there are in the list
    int maxSize = static_cast<int>(m_store->list.size());

    switch (planType)
    {
    case Saddleback:
        // Set's stack page to plan trip
        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);
        // Different headers will load based on trip type
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_1);
        m_ui->startLocation->addItem(tr("Saddleback"), Saddleback);
        // adds item to drop list instead of drag list
        m_planTripListDrop->addItems(m_store->list.begin(), m_store->list.end());

        break;
    case PlanTrip::ChosenAndN:

        // Set's stack page to plan trip
        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);

        // Different headers will load based on trip type
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_2);
        m_planTripListDrop->addItems(m_store->list.begin(), m_store->list.end());

        // adds item to drop list instead of drag list
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
        // Set's stack page to plan trip
        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);

        // Different headers will load based on trip type
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_3);

        // adds item to drop list instead of drop list
        m_planTripListDrag->addItems(m_store->list.begin(), m_store->list.end());

        break;
    case None:
        // Do Nothing
        break;
    }
}


// When enter is clicked in chooseType view this function is called to load the right options based on the planType chosen
void PlanTrip::on_startPlanning_clicked()
{
    // Set's  up window according to state, the state is attained from the data stored in QComboBox tripType
    changeHeaderOptions(static_cast<PlanType>(m_ui->tripType->currentData().toInt()));
}

/* Button that confirms the users trip list */
void PlanTrip::on_TripButton_clicked()
{
    /* Needs to be cleared before using */
    m_planTripList.clear();
    m_recieptVector.clear();
    vector<int> tempStore;

    /* This list below will be passed into the restaurant list to collect the id's of it's items */
    m_planTripListDrop->getRestaurantIDs(m_planTripList);

    /* check if error messages need to be displayed */
    if (m_planTripList.empty() && m_ui->startLocation_2->currentIndex() == 0)
    {
        // if list is empty and the starting location hasn't been chosen display both error messages
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
        // If the starting location hasn't been chosen just display the starting location error message
        m_ui->activeTrip_warning_noStart->setHidden(false);
        QTimer::singleShot(3000, m_ui->activeTrip_warning_emptyList, [&]()
        {
            m_ui->activeTrip_warning_noStart->setHidden(true);
        });
    }
    else if (m_planTripList.empty())
    {
        // If the list is empty display an error message letting the user know the list is empty
        m_ui->activeTrip_warning_emptyList->setHidden(false);
        QTimer::singleShot(3000, m_ui->activeTrip_warning_emptyList, [&]()
        {
            m_ui->activeTrip_warning_emptyList->setHidden(true);
        });
    }
    else
    {
        /* now input errors - call the right sorter based on the plan type */
        switch(getPlanType())
        {
        case PlanTrip::Saddleback:
            m_tripId = m_tripStore->StoreTrip(QDateTime::currentDateTime().toString().toStdString(),m_planTripList,*m_store,
                                              test.list.front(),true);
            m_sorted.clear();
            tempStore = m_tripStore->FindbyNumber(m_tripId).GetRestaurants();
            foreach(int restaurantId, tempStore)
                m_sorted.push_back(restaurantId);
            break;
        case PlanTrip::ChosenAndN:
            // Trip would do 1 less than the spin box value so made it +1 to whatever value the spinbox gives the function
            m_tripId =  m_tripStore->StoreTripNumRest(QDateTime::currentDateTime().toString().toStdString(), m_ui->startLocation_2->currentData().toInt(),
                                                      m_ui->spinBox->value()+1,*m_store,test.list.front());
            m_sorted.clear();
            tempStore = m_tripStore->FindbyNumber(m_tripId).GetRestaurants();
            foreach(int restaurantId, tempStore)
                m_sorted.push_back(restaurantId);
            break;
        case PlanTrip::FirstRestaurant:
            m_tripId = m_tripStore->StoreTrip(QDateTime::currentDateTime().toString().toStdString(),m_planTripList,*m_store,
                                              test.list.front(),false);
            m_sorted.clear();
            tempStore = m_tripStore->FindbyNumber(m_tripId).GetRestaurants();
            foreach(int restaurantId, tempStore)
                m_sorted.push_back(restaurantId);
            break;
        case PlanTrip::None:
            // Do Nothing
            break;
        }
        /* have an array of sorted id's (int) made it into the trip preping the first item of the trip */
        Restaurant *tempRest;
        tempRest = &m_store->FindbyNumber(m_sorted.front());

        //Hide the navbar so that someone doesn't switch states mid trip
        m_navbar->setHidden(true);

        // Set name of restaurant shown at the top of the view
        m_ui->activeTripRestaurant->setText(QString::fromStdString(tempRest->GetName()));

        // Set current Restaurant
        setCurrentRest(tempRest->GetNumber());

        // add current restaurants menu items to the menu
        m_tripMenuList->addAllItems(m_store->FindbyNumber(m_sorted.front()));

        // Switch viewed page to activeTrip
        m_ui->planTripStack->setCurrentWidget(m_ui->activeTrip);
    }
}

// Resets widgets used for
void PlanTrip::resetPlanTripView()
{
    setPlanType(PlanType::None);
    m_ui->planTripStack->setCurrentWidget(m_ui->chooseType);
    m_ui->tripType->setCurrentIndex(0);
    m_planTripListDrag->clear();
    m_planTripListDrop->clear();
}


void PlanTrip::activeTrip()
{
    bool seen = false;
    m_ui->planTripStack->setCurrentWidget(m_ui->activeTrip);
    m_sorted.pop_front();
    if(!m_sorted.empty())
    {
        Restaurant tempRest = m_store->FindbyNumber(m_sorted.front());
        m_currentRest = tempRest.GetNumber();
        m_ui->activeTripRestaurant->setText(QString::fromStdString(tempRest.GetName()));
        m_tripMenuList->addAllItems(m_store->FindbyNumber(m_sorted.front()));
    }
    else if( m_recieptVector.size() != 0)
    {
        m_receipt->clear();
        m_receipt->grandTotal(m_recieptVector, m_tripStore->FindbyNumber(m_tripId).GetTotalDistance());
        m_ui->planTripStack->setCurrentWidget(m_ui->tripReceipt);
    }
    else if ( m_recieptVector.size() == 0 && m_sorted.empty() && !seen)
    {
        m_ui->TripDistanceLabel_2->setText(QString::number(m_tripStore->FindbyNumber(m_tripId).GetTotalDistance(),'f',1)+" mi.");
        m_ui->planTripStack->setCurrentWidget(m_ui->tripDistance);
        seen = true;
    }
    else
    {
        m_navbar->setHidden(false);
        resetPlanTripView();
    }
}

void PlanTrip::on_next_clicked()
{
    /* Proceed to the next restaurant if the cart is empty */
    if(m_tripFoodCart->count() == 0)
    {
        activeTrip();
    }
    else if (m_tripFoodCart->count() > 0)
    {
        /* If car has items ask the user if they're sure they'd like to proceed */
        if(promptToContinue() == QMessageBox::Yes)
        {
            m_tripFoodCart->resetQty();
            m_tripFoodCart->clear();
            activeTrip();
        }
    }

}

/* set's plan type */
void PlanTrip::setPlanType(const PlanType pickedType)
{
    m_planType = pickedType;
}

/* Returns plan type */
PlanTrip::PlanType PlanTrip::getPlanType() const
{
    return m_planType;
}

/* adds item selected in menu to cart list */
void PlanTrip::on_addToCart_clicked()
{
    // will get restaurant id and menu id from currently selected menu list item
    IDs item = m_tripMenuList->getSelected();

    // get's map of items in the cart list
    IDQtys cartIds(m_tripFoodCart->getIDQty());

    // will indicate if the item is in the list
    bool found = false;

    //Looks to see if the current item is already in the list - sets found to true if so
    for (IDQtys::const_iterator it= cartIds.begin(); it != cartIds.end(); ++it)
    {
        if(it->first.second == item.second)
        {
            // Update Qty - increment by 1
            m_tripFoodCart->setQty(it->first,it->second+1);
            found = true;
        }
    }

    // if no item is found this will add the item to the list and sit the initial qty to 1
    if (!found)
    {
        // as long as the choice isn't -1 add item to the cart
        if(item.second != -1)
            m_tripFoodCart->addItem(getCurrentRest(), m_store->FindbyNumber(getCurrentRest()).FindMenuItembyNumber(item.second));
        // Set Default Qty to 1
        m_tripFoodCart->setQty(item,1);
    }

}

/* set's the current restaurant of the trip */
void PlanTrip::setCurrentRest(const int currentRest)
{
    m_currentRest = currentRest;
}

/* get's the current restaurant of the trip */
int PlanTrip::getCurrentRest() const
{
    return m_currentRest;
}

/* Collect all item data in cart to print receipt */
void PlanTrip::on_checkout_clicked()
{
    if(m_tripFoodCart->getIDQty().size() != 0)
    {
        m_receipt->clear();
        m_recieptVector.push_back(m_tripFoodCart->getIDQty());
        m_receipt->makeReciept(m_tripFoodCart->getIDQty());
        m_ui->planTripStack->setCurrentWidget(m_ui->tripReceipt);
    }
}


/* Prompts user to confirm if the user would like to proceed without buying the items they placed in the cart */
QMessageBox::StandardButton PlanTrip::promptToContinue() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Warning",
                                  "You have items in your cart, are you sure you want to proceed to the next location?",
                                  QMessageBox::Yes|QMessageBox::No);
    return reply;
}

void PlanTrip::on_ContinueToNext_clicked()
{
    if(!m_sorted.empty())
    {
        m_tripFoodCart->resetQty();
        m_tripFoodCart->clear();
        activeTrip();
    }
    else
    {
        m_navbar->setHidden(false);
        resetPlanTripView();
    }
}

void PlanTrip::on_removeItem_clicked()
{
    // will get restaurant id and menu id from currently selected menu list item
    IDs item = m_tripFoodCart->getSelected();

    // Removes selected item from cart when this button is clicked
    m_tripFoodCart->removeItem(item);
}

void PlanTrip::on_ContinueToNext_2_clicked()
{
    m_navbar->setHidden(false);
    resetPlanTripView();
}
