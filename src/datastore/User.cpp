/**
 * CS1D - Fast Food Associates
 *
 * Implemention of the User class that provides a means for
 * validating users, collecting their trips and defines their
 * access rights
 *
 * @author   edt
 */


#include "User.hpp"
#include <string>
#include <ostream>
#include <iostream>

int User::sm_NextNumber = 1;

// Constructor - New User
User::User(const string &Name, const string &Password)
        : m_UserName(Name), m_HashedPassword(Password)
{

    m_fTotalPurchases = 0.0f;
    m_bIsAdministrator = false;
    m_bDeleted = false;
    m_bBlocked = false;

    m_nUserNumber =  sm_NextNumber++;

    m_bInitialized = true;
};

// Constructor implementation
User::User(int nUserNumber,
           string &Name,
           float &fTotalPurchases,
           bool  bUserAdmin,
           string &HashedPw,
           bool bUserDeleted,
           bool bUserBlocked,
           vector<int> &UserTrips)
: m_nUserNumber(nUserNumber), m_UserName(Name),
  m_fTotalPurchases(fTotalPurchases), m_bIsAdministrator(bUserAdmin),
  m_HashedPassword(HashedPw), m_bDeleted(bUserDeleted),
  m_bBlocked(bUserBlocked), m_Trips(UserTrips)
{
    if (m_nUserNumber >= sm_NextNumber)
    {
        sm_NextNumber = m_nUserNumber + 1;
    }
    m_bInitialized = true;
}

// Destructor implementation
User::~User()
{
}

User::User(const User& src)
: m_nUserNumber(src.m_nUserNumber), m_UserName(src.m_UserName),
  m_fTotalPurchases(src.m_fTotalPurchases), m_bIsAdministrator(src.m_bIsAdministrator),
  m_HashedPassword(src.m_HashedPassword), m_bDeleted(src.m_bDeleted),
  m_bBlocked(src.m_bBlocked), m_Trips(src.m_Trips)
{
    m_bInitialized      = true;
}

User& User::operator=(const User& rhs)
{
   if (this == &rhs) {
      return *this;
   }

    m_nUserNumber       = rhs.m_nUserNumber;
    m_UserName          = rhs.m_UserName;
    m_fTotalPurchases   = rhs.m_fTotalPurchases;
    m_bIsAdministrator  = rhs.m_bIsAdministrator;
    m_HashedPassword    = rhs.m_HashedPassword;
    m_bDeleted          = rhs.m_bDeleted;
    m_bBlocked          = rhs.m_bBlocked;
    m_Trips             = rhs.m_Trips;

    m_bInitialized      = true;

   return *this;
}

bool User::operator<(User &rhs)
{
    return (this->m_UserName < rhs.m_UserName);
}

const int User::GetNumber(void) const
{
    return (m_nUserNumber);
}

const string &User::GetName(void) const
{
    return m_UserName;
}

const string & User::GetHashedPasswd(void) const
{
    return m_HashedPassword;
}

bool User::MarkDeleted(bool Delete)
{
    m_bDeleted = Delete;
    return m_bDeleted;
}
bool User::IsDeleted(void) const
{
    return m_bDeleted;
}
bool User::MarkAdmin(bool Admin)
{
    m_bIsAdministrator = Admin;
    return m_bIsAdministrator;

}

bool User::IsAdmin(void) const
{
    return m_bIsAdministrator;
}
bool User::MarkBlocked(bool Block)
{
    m_bBlocked = Block;
    return m_bBlocked;
}

bool User::IsBlocked(void) const
{
    return m_bBlocked;
}

float User::Purchase(float PurchaseAmount)
{
    m_fTotalPurchases += PurchaseAmount;
    return m_fTotalPurchases;
}

void User::AddTrip(int Trip)
{
    // should avoid adding duplicates
    m_Trips.push_back(Trip);
}

const vector<int> &User::GetTrips(void) const
{
    return m_Trips;
}

float User::GetTotalPurchase(void) const
{
    return m_fTotalPurchases;
}

//! print the value of the object for external display
//!
//! \author edt (2/7/18)
//!
//! \param print_endl
//!
//! \return bool
bool User::PrintAsDebug(bool print_endl) const
{
    if (print_endl)
    {
        cout << "ObjAddr    :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec << endl
             << " Number     :" << m_nUserNumber << endl
             << " Name       :" << m_UserName << endl
             << " Purchases  :" << m_fTotalPurchases << endl
             << " Admin      :" << m_bIsAdministrator << endl
             << " Hash PW    :" << m_HashedPassword << endl
             << " Deleted    :" << m_bDeleted << endl
             << " Blocked    :" << m_bBlocked << endl
             << " Trips      :";
        for (std::vector<int>::const_iterator it = m_Trips.begin(); it != m_Trips.end(); it++)
        {
            cout << " " << *it;
        }
        if (m_Trips.size() == 0)
        {
            cout << "None";
        }
        cout << endl;
    }
    else
    {
        cout << "ObjAddr    :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec
             << " Number     :" << m_nUserNumber
             << " Name       :" << m_UserName
            << " Purchases  :" << m_fTotalPurchases
            << " Admin      :" << m_bIsAdministrator
            << " Hash PW    :" << m_HashedPassword
            << " Deleted    :" << m_bDeleted
            << " Blocked    :" << m_bBlocked
            << " Trips      :";
        for (std::vector<int>::const_iterator it = m_Trips.begin(); it != m_Trips.end(); it++)
        {
            cout << " " << *it;
        }
        if (m_Trips.size() == 0)
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
ostream& operator<<(ostream& os, const User& user)
{
    os << user.PrintAsDebug(true);
    return(os);
}
