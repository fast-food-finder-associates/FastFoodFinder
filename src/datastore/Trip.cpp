/**
 * CS1D - Fast Food Associates
 *
 * Implemention of the User class that provides a means for
 * validating users, collecting their trips and defines their
 * access rights
 *
 * @author   edt
 */


#include "Trip.hpp"
#include <string>
#include <ostream>
#include <iostream>

//! Trip::sm_NextNumber - next number to use for new Trip
//!
//! \author edt (3/25/19)
int Trip::sm_NextNumber = 1;

//! Trip::Trip - constructor used when adding trip manually - depricated
//!
//! \author edt (3/25/19)
//!
//! \param User - User planning trip
//! \param Restaurants - Restaurants on trip
//! \param TotalDistance - length of trip in miles
//! \param Name - Name of Trip
Trip::Trip(int User,
           const vector<int> &Restaurants,
           float TotalDistance,
           const string &Name)
        : m_nCreatingUser(User),
          m_Name(Name),
          m_Restaurants(Restaurants),
          m_fTotalDistance(TotalDistance)
{
    m_bDeleted = false;

    m_nNumber =  sm_NextNumber++;

    m_bInitialized = true;
};

//! Trip::Trip - Constructor used only by TripDataStore to load datastore
//!
//! \author edt (3/25/19)
//!
//! \param TripNum - number
//! \param User - creating user
//! \param Restaurants - restaurants on trip
//! \param TotalDistance - distance in miles
//! \param Name - name of trip
//! \param bTripDeleted - true if deleted - cannot be taken again
Trip::Trip(int TripNum,
           int User,
           const vector<int> &Restaurants,
           float TotalDistance,
           const string &Name,
           bool bTripDeleted)
        : m_nNumber(TripNum),
          m_nCreatingUser(User),
          m_Name(Name),
          m_Restaurants(Restaurants),
          m_fTotalDistance(TotalDistance),
          m_bDeleted(bTripDeleted)
{
    if (m_nNumber >= sm_NextNumber)
    {
        sm_NextNumber = m_nNumber + 1;
    }
    m_bInitialized = true;
};

//! Trip::~Trip - Destructor
//!
//! \author edt (3/25/19)
Trip::~Trip()
{
}

//! Trip::Trip - Copy constructor
//!
//! \author edt (3/25/19)
//!
//! \param src - Item to copy
Trip::Trip(const Trip& src)
: m_nNumber(src.m_nNumber), m_Name(src.m_Name),
  m_nCreatingUser(src.m_nCreatingUser), m_Restaurants(src.m_Restaurants),
  m_bDeleted(src.m_bDeleted), m_fTotalDistance(src.m_fTotalDistance)
{
    m_bInitialized      = true;
}

//! Trip::operator=
//!
//! \author edt (3/25/19)
//!
//! \param rhs - Item to copy
//!
//! \return Trip&amp; 
Trip& Trip::operator=(const Trip& rhs)
{
   if (this == &rhs) {
      return *this;
   }

    m_nNumber           = rhs.m_nNumber;
    m_Name              = rhs.m_Name;
    m_nCreatingUser     = rhs.m_nCreatingUser;
    m_Restaurants      = rhs.m_Restaurants;
    m_bDeleted          = rhs.m_bDeleted;
    m_fTotalDistance    = rhs.m_fTotalDistance;

    m_bInitialized      = true;

   return *this;
}
//! Trip::GetNumber
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return int - name of trip
int Trip::GetNumber(void) const
{
    return m_nNumber;
}

//! Trip::GetName
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return const string&amp; - name of trip
const string &Trip::GetName(void) const
{
    return m_Name;
}

//! Trip::GetCreatingUser
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return int - number of user who planned this trip
int  Trip::GetCreatingUser(void) const
{
    return m_nCreatingUser;
}


//! Trip::GetRestaurants - get list of Restaurants to allow taking the trip
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return const vector&lt;int&gt;&amp; - vector of ints that are restaurant numbers
vector<int> &Trip::GetRestaurants(void)
{
    return m_Restaurants;
}

//! Trip::GetTotalDistance
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return float - distance in miles for entire trip
float Trip::GetTotalDistance(void) const
{
    return m_fTotalDistance;
}

//! Trip::MarkDeleted
//!
//! \author edt (3/25/19)
//!
//! \param Delete - true if trip is deleted
//!
//! \return bool - true if trip is deleted and should not be taken again
bool Trip::MarkDeleted(bool Delete)
{
    m_bDeleted = Delete;
    return m_bDeleted;
}

//! Trip::IsDeleted
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return bool - true if trip is deleted and should not be taken again
bool Trip::IsDeleted(void) const
{
    return m_bDeleted;
}

//! Trip::AddRestaurant - depricated - use StoreTrip
//!
//! \author edt (3/25/19)
//!
//! \param Restaurant - number of restaurant to add
//!
//! \return bool - true if added
bool Trip::AddRestaurant(int Restaurant)
{
    // prevent dupes
    m_Restaurants.push_back(Restaurant);
    return true;
}

//! print the value of the object for external display
//!
//! \author edt (2/7/18)
//!
//! \param print_endl - print end of line between each field
//!
//! \return bool - true if no errors
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
        for (std::vector<int>::const_iterator it = m_Restaurants.begin(); it != m_Restaurants.end(); it++)
        {
            cout << " " << *it;
        }
        if (m_Restaurants.size() == 0)
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
        for (std::vector<int>::const_iterator it = m_Restaurants.begin(); it != m_Restaurants.end(); it++)
        {
            cout << " " << *it;
        }
        if (m_Restaurants.size() == 0)
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

//! Overloaded operator << to print the contents of an Trip object
//!
//! \author edt (2/7/18)
//!
//! \param os - output stream being processed
//! \param trip - object to print
//!
//! \return ostream&amp;- output stream being processed
ostream& operator<<(ostream& os, const Trip& trip)
{
    os << trip.PrintAsDebug(true);
    return(os);
}

