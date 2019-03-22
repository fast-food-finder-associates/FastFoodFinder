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

    // setting range on spin box
    m_ui->spinBox->setRange(1,static_cast<int>(m_store->list.size()));

    // set text for checkout button
    m_ui->checkout->setText("\uf218");

    resetPlanTripView();
}

PlanTrip::~PlanTrip()
{
    delete m_ui;
}



void PlanTrip::changeHeaderOptions(StartFrom state)
{
    // Reset items within combobox
    m_ui->startLocation->clear();

    switch (state)
    {
    case Saddleback:

        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_1);
        m_ui->startLocation->addItem(tr("Saddleback"), Saddleback);
        m_planTripListDrop->addItems(m_store->list.begin(), m_store->list.end());

        m_state = Saddleback;
        break;
    case ChosenAndN:

        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_2);
        m_planTripListDrop->addItems(m_store->list.begin(), m_store->list.end());
        m_ui->startLocation_2->addItem(QString::fromUtf8("-- Starting Location --"),-1);

        for(Restaurant e : m_store->list)
            m_ui->startLocation_2->addItem(QString::fromStdString(e.GetName()), e.GetNumber());

        m_state = ChosenAndN;
        break;
    case FirstRestaurant:

        m_ui->planTripStack->setCurrentWidget(m_ui->planTrip);
        m_ui->planTripListDrop_header->setCurrentWidget(m_ui->planTripSubHeader_3);
        m_planTripListDrag->addItems(m_store->list.begin(), m_store->list.end());

        m_state = FirstRestaurant;
        break;
    case None:

        m_state = None;
        break;
    }
}



void PlanTrip::on_pushButton_clicked()
{
    switch (m_ui->tripType->currentData().toInt())
    {
    case 0:
        changeHeaderOptions(Saddleback);
        break;
    case 1:
        changeHeaderOptions(ChosenAndN);
        break;
    case 2:
        changeHeaderOptions(FirstRestaurant);
        break;
    case 3:
        // Do nothing
        break;
    }
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
    m_state = None;
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

