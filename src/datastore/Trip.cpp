/**
 * CS1D - Fast Food Associates
 *
 * Implemention of the User class that provides a means for
 * validating users, collecting their trips and defines their
 * access rights
 *
 * @author   edt
 */


#include "Trip.h"
#include <string>
#include <ostream>
#include <iostream>

int Trip::sm_NextNumber = 1;

// Constructor - New Trip
Trip::Trip(int User,
           const vector<int> &Restaurants,
           float TotalDistance,
           const string &Name)
        : m_nCreatingUser(User),
          m_Name(Name),
          m_Restraurants(Restaurants),
          m_fTotalDistance(TotalDistance)
{
    m_bDeleted = false;

    m_nNumber =  sm_NextNumber++;

    m_bInitialized = true;
};

// Constructor implementation
Trip::Trip(int TripNum,
           int User,
           const vector<int> &Restaurants,
           float TotalDistance,
           const string &Name,
           bool bTripDeleted)
        : m_nNumber(TripNum),
          m_nCreatingUser(User),
          m_Name(Name),
          m_Restraurants(Restaurants),
          m_fTotalDistance(TotalDistance),
          m_bDeleted(bTripDeleted)
{
    if (m_nNumber >= sm_NextNumber)
    {
        sm_NextNumber = m_nNumber + 1;
    }
    m_bInitialized = true;
};

// Destructor implementation
Trip::~Trip()
{
}

    bool        m_bInitialized;
    int         m_nNumber;
    string      m_Name;
    int         m_nCreatingUser;
    vector<int> m_Restraurants;
    bool        m_bDeleted; // if true, do not display on general GUI (maybe in admin GUI)
    float       m_fTotalDistance;

Trip::Trip(const Trip& src)
: m_nNumber(src.m_nNumber), m_Name(src.m_Name),
  m_nCreatingUser(src.m_nCreatingUser), m_Restraurants(src.m_Restraurants),
  m_bDeleted(src.m_bDeleted), m_fTotalDistance(src.m_fTotalDistance)
{
    m_bInitialized      = true;
}

Trip& Trip::operator=(const Trip& rhs)
{
   if (this == &rhs) {
      return *this;
   }

    m_nNumber           = rhs.m_nNumber;
    m_Name              = rhs.m_Name;
    m_nCreatingUser     = rhs.m_nCreatingUser;
    m_Restraurants      = rhs.m_Restraurants;
    m_bDeleted          = rhs.m_bDeleted;
    m_fTotalDistance    = rhs.m_fTotalDistance;

    m_bInitialized      = true;

   return *this;
}


const string &Trip::GetName(void) const
{
    return m_Name;
}

int  Trip::GetCreatingUser(void) const
{
    return m_nCreatingUser;
}

const vector<int> &Trip::GetResturants(void) const
{
    return m_Restraurants;
}

float Trip::GetTotalDistance(void) const
{
    return m_fTotalDistance;
}

bool Trip::MarkDeleted(bool Delete)
{
    m_bDeleted = Delete;
    return m_bDeleted;
}

bool Trip::AddRestaurant(int Resturaurant)
{
    // prevent dupes
    m_Restraurants.push_back(Resturaurant);
    return true;
}

//! print the value of the object for external display
//!
//! \author edt (2/7/18)
//!
//! \param print_endl
//!
//! \return bool
bool Trip::PrintAsDebug(bool print_endl) const
{
    if (print_endl)
    {
        cout << "ObjAddr    :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec << endl
             << " Number     :" << m_nNumber << endl
             << " Name       :" << m_Name << endl
             << " Creator    :" << m_nCreatingUser << endl
             << " Total Dist :" << m_fTotalDistance << endl
             << " Deleted    :" << m_bDeleted << endl
             << " Restaurants  :";
        for (std::vector<int>::const_iterator it = m_Restraurants.begin(); it != m_Restraurants.end(); it++)
        {
            cout << " " << *it;
        }
        if (m_Restraurants.size() == 0)
        {
            cout << "None";
        }
        cout << endl;
    }
    else
    {
        cout << "ObjAddr    :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec
             << " Number     :" << m_nNumber
             << " Name       :" << m_Name
             << " Creator    :" << m_nCreatingUser
             << " Total Dist :" << m_fTotalDistance << endl
             << " Deleted    :" << m_bDeleted
             << " Restaurants  :";
        for (std::vector<int>::const_iterator it = m_Restraurants.begin(); it != m_Restraurants.end(); it++)
        {
            cout << " " << *it;
        }
        if (m_Restraurants.size() == 0)
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
//! \param user
//!
//! \return ostream&amp;
ostream& operator<<(ostream& os, const Trip& trip)
{
    os << trip.PrintAsDebug(true);
    return(os);
}


