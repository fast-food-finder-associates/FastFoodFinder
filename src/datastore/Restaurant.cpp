/**
 * CS1D - Fast Food Associates
 *
 * Implemention of the Restaurant class that provides a means
 * for validating restaurants, string menu items and distances
 * to other restaurants
 *
 * @author   edt
 */


#include "Restaurant.hpp"
#include <string>
#include <ostream>
#include <iostream>

int Restaurant::sm_NextNumber = 1;

// Constructor - New Restaurant
Restaurant::Restaurant(const string &Name, const float &Distance)
        : m_Name(Name), m_fDistToSaddleback(Distance)
{

    m_fTotalPurchases = 0.0f;
    m_nTotalCustomers = 0;
    m_nUsedByCount = 0;
    m_bDeleted = false;

    m_nNumber =  sm_NextNumber++;

    m_bInitialized = true;
};

// Constructor implementation
Restaurant::Restaurant(
         int        nNumber,
         string     &Name,
         float      &fDistToSaddleback,
         float      &fTotalPurchases,
         int        nTotalCustomers,
         int        nUsedByCount,
         bool       bDeleted,
         vector<RestaurantDistance> &Distances,
         vector<MenuItem>           &MenuItems,
         vector<int>                &RefByTrips)
: m_nNumber(nNumber), m_Name(Name), m_fDistToSaddleback(fDistToSaddleback),
  m_fTotalPurchases(fTotalPurchases), m_nTotalCustomers(nTotalCustomers),
  m_nUsedByCount(nUsedByCount), m_bDeleted(bDeleted),
  m_Distances(Distances), m_Menu(MenuItems), m_ReferencedByTrips(RefByTrips)
{
    if (m_nNumber >= sm_NextNumber)
    {
        sm_NextNumber = m_nNumber + 1;
    }
    m_bInitialized = true;
}

// Destructor implementation
Restaurant::~Restaurant()
{
}

Restaurant::Restaurant(const Restaurant& src)
: m_nNumber(src.m_nNumber), m_Name(src.m_Name), m_fDistToSaddleback(src.m_fDistToSaddleback),
  m_fTotalPurchases(src.m_fTotalPurchases), m_nTotalCustomers(src.m_nTotalCustomers),
  m_nUsedByCount(src.m_nUsedByCount), m_bDeleted(src.m_bDeleted),
  m_Distances(src.m_Distances), m_Menu(src.m_Menu), m_ReferencedByTrips(src.m_ReferencedByTrips)
{
    m_bInitialized      = true;
}

Restaurant& Restaurant::operator=(const Restaurant& rhs)
{
   if (this == &rhs) {
      return *this;
   }

    m_nNumber               = rhs.m_nNumber;
    m_Name                  = rhs.m_Name;
    m_fDistToSaddleback     = rhs.m_fDistToSaddleback;
    m_fTotalPurchases       = rhs.m_fTotalPurchases;
    m_nTotalCustomers       = rhs.m_nTotalCustomers;
    m_nUsedByCount          = rhs.m_nUsedByCount;
    m_bDeleted              = rhs.m_bDeleted;
    m_Distances             = rhs.m_Distances;
    m_Menu                  = rhs.m_Menu;
    m_ReferencedByTrips     = rhs.m_ReferencedByTrips;

    m_bInitialized      = true;

   return *this;
}

const string &Restaurant::GetName(void) const
{
    return m_Name;
}

void Restaurant::SetName(const string &NewName)
{
    m_Name = NewName;
}

int Restaurant::GetNumber(void) const
{
    return m_nNumber;
}

const vector<MenuItem> &Restaurant::GetMenu(void) const
{
    return m_Menu;
}

const vector<RestaurantDistance> &Restaurant::GetDistances(void) const
{
    return m_Distances;
}

float Restaurant::GetPurchaseAmount(void) const
{
    return m_fTotalPurchases;
}

bool Restaurant::MarkDeleted(bool Delete)
{
    m_bDeleted = Delete;
    return m_bDeleted;
}

bool Restaurant::IsDeleted(void) const
{
    return m_bDeleted;
}

bool Restaurant::AddTrip(int TripNumber)
{
    // should avoid adding duplicates
    m_ReferencedByTrips.push_back(TripNumber);
    return true;
}
int Restaurant::AddCustCount(void)
{
    m_nTotalCustomers++;
    return m_nTotalCustomers;
}

float Restaurant::AddPurchasePrice(float PurchaseAmount)
{
    m_fTotalPurchases += PurchaseAmount;
    return m_fTotalPurchases;
}

float Restaurant::GetDistSaddleback(void) const
{
    return m_fDistToSaddleback;
}

void Restaurant::AddMenuItem(const string &Name, const float &Price)
{
    MenuItem tmp(m_Menu.size()+1, false, Name, Price);
    m_Menu.push_back(tmp);
}

MenuItem&Restaurant::FindMenuItembyNumber(int Number)
{
    for (std::vector<MenuItem>::iterator it = m_Menu.begin(); it != m_Menu.end(); ++it)
    {
        if ( (*it).m_nNumber == Number)
        {
            return *it;
        }
    }
    return *(m_Menu.end());  // never reached  - should throw exception
}


//! print the value of the object for external display
//!
//! \author edt (2/7/18)
//!
//! \param print_endl
//!
//! \return bool
bool Restaurant::PrintAsDebug(bool print_endl) const
{
    if (print_endl)
    {
        cout << "ObjAddr     :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec << endl
             << " Number     :" << m_nNumber << endl
             << " Name       :" << m_Name << endl
             << " Dist.Saddl :" << m_fDistToSaddleback << endl
             << " Purchases  :" << m_fTotalPurchases << endl
             << " Used Cnt   :" << m_nUsedByCount << endl
             << " Deleted    :" << m_bDeleted << endl
             << " Distances  :" << endl;
        for (std::vector<RestaurantDistance>::const_iterator it = m_Distances.begin(); it != m_Distances.end(); it++)
        {
            cout << " # " << it->m_nRestaurantNumber;
            cout << " Miles " << it->m_fDistanceMiles << endl;
        }
        if (m_Distances.size() == 0)
        {
            cout << "None";
        }
        cout << endl;

        cout << " Menu Items :";
        for (std::vector<MenuItem>::const_iterator it = m_Menu.begin(); it != m_Menu.end(); it++)
        {
            cout << " " << it->m_nNumber;
            cout << " " << it->IsDeleted();
            cout << " " << it->GetName();
            cout << " Price " << it->GetPrice() << endl;
        }
        if (m_Menu.size() == 0)
        {
            cout << "None";
        }
        cout << endl;

        cout << " Referenced by Trips :";
        for (std::vector<int>::const_iterator it = m_ReferencedByTrips.begin(); it != m_ReferencedByTrips.end(); it++)
        {
            cout << " " << *it << endl;
        }
        if (m_ReferencedByTrips.size() == 0)
        {
            cout << "None";
        }
        cout << endl;
    }
    else
    {
        cout << "ObjAddr     :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec
             << " Number     :" << m_nNumber
             << " Name       :" << m_Name
             << " Dist.Saddl :" << m_fDistToSaddleback
             << " Purchases  :" << m_fTotalPurchases
             << " Used Cnt   :" << m_nUsedByCount
             << " Deleted    :" << m_bDeleted
            << " Distances  :";
        for (std::vector<RestaurantDistance>::const_iterator it = m_Distances.begin(); it != m_Distances.end(); it++)
        {
            cout << " # " << it->m_nRestaurantNumber;
            cout << " Miles " << it->m_fDistanceMiles;
        }
        if (m_Distances.size() == 0)
        {
            cout << "None";
        }

        cout << " Menu Items :";
        for (std::vector<MenuItem>::const_iterator it = m_Menu.begin(); it != m_Menu.end(); it++)
        {
            cout << " " << it->m_MenuItemName;
            cout << " Price " << it->GetPrice();
        }
        if (m_Menu.size() == 0)
        {
            cout << "None";
        }

        cout << " Referenced by Trips :";
        for (std::vector<int>::const_iterator it = m_ReferencedByTrips.begin(); it != m_ReferencedByTrips.end(); it++)
        {
            cout << " " << *it;
        }
        if (m_ReferencedByTrips.size() == 0)
        {
            cout << "None";
        }
    }

    if (!m_bInitialized)
    {
        cout << " Warning: Object not proerly initialized ";
        if (print_endl)
        {
            cout << endl;
        }
    }

    return m_bInitialized;
}

//! Overloaded operator << to print the contents of an User object
//!
//! \author edt (2/7/18)
//!
//! \param os
//! \param Restaurant
//!
//! \return ostream&amp;
ostream& operator<<(ostream& os, const Restaurant& Restaurant)
{
    os << Restaurant.PrintAsDebug(true);
    return(os);
}


