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

//! User::sm_NextNumber - holds next number that will be assigned to a new User
//!
//! \author edt (3/25/19)
int User::sm_NextNumber = 1;

//! User::User - create a new user
//!
//! \author edt (3/25/19)
//!
//! \param Name - user name
//! \param Password - string representing hashed password
User::User(const string &Name, const string &Password)
        : m_UserName(Name), m_HashedPassword(Password)
{

    m_fTotalPurchases = 0.0f;
    m_bIsAdministrator = false;
    m_bDeleted = false;
    m_bBlocked = false;

    m_nNumber =  sm_NextNumber++;

    m_bInitialized = true;
};

//! User::User - private constructor used to load Users from external file
//!
//! \author edt (3/25/19)
//!
//! \param nUserNumber - user number
//! \param Name - user name
//! \param fTotalPurchases - total purchases made by this user on all trips
//! \param bUserAdmin - true if user is an administrator
//! \param HashedPw - string representing hashed password
//! \param bUserDeleted - true if user id deleted and cannot log on
//! \param bUserBlocked - true if user is temporarily blocked from logging on
//! \param UserTrips - trips this user has planned
User::User(int nUserNumber,
           string &Name,
           float &fTotalPurchases,
           bool  bUserAdmin,
           string &HashedPw,
           bool bUserDeleted,
           bool bUserBlocked,
           vector<int> &UserTrips)
: m_nNumber(nUserNumber), m_UserName(Name),
  m_fTotalPurchases(fTotalPurchases), m_bIsAdministrator(bUserAdmin),
  m_HashedPassword(HashedPw), m_bDeleted(bUserDeleted),
  m_bBlocked(bUserBlocked), m_Trips(UserTrips)
{
    if (m_nNumber >= sm_NextNumber)
    {
        sm_NextNumber = m_nNumber + 1;
    }
    m_bInitialized = true;
}

//! User::~User - Destructor
//!
//! \author edt (3/25/19)
User::~User()
{
}

//! User::User - copy constructor
//!
//! \author edt (3/25/19)
//!
//! \param src - User to copy
User::User(const User& src)
: m_nNumber(src.m_nNumber), m_UserName(src.m_UserName),
  m_fTotalPurchases(src.m_fTotalPurchases), m_bIsAdministrator(src.m_bIsAdministrator),
  m_HashedPassword(src.m_HashedPassword), m_bDeleted(src.m_bDeleted),
  m_bBlocked(src.m_bBlocked), m_Trips(src.m_Trips)
{
    m_bInitialized      = true;
}

//! User::operator= 
//!
//! \author edt (3/25/19)
//!
//! \param rhs - user to copy
//!
//! \return User&amp; 
User& User::operator=(const User& rhs)
{
   if (this == &rhs) {
      return *this;
   }

    m_nNumber       = rhs.m_nNumber;
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

//! User::operator< - comparator for user name
//!
//! \author edt (3/25/19)
//!
//! \param rhs - User to compare
//!
//! \return bool - true if other User object name is less
bool User::operator<(User &rhs)
{
    return (this->m_UserName < rhs.m_UserName);
}

//! User::GetNumber
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return const int - user number
const int User::GetNumber(void) const
{
    return (m_nNumber);
}

//! &User::GetName
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return const string&amp; - user name
const string &User::GetName(void) const
{
    return m_UserName;
}

//! User::GetHashedPasswd
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return const string&amp; - string representing hashed password
const string & User::GetHashedPasswd(void) const
{
    return m_HashedPassword;
}

//! User::MarkDeleted
//!
//! \author edt (3/25/19)
//!
//! \param Delete - true if user is to be marked deleted - cannot plan/take trips
//!
//! \return bool - true if user is deleted - cannot plan/take trips
bool User::MarkDeleted(bool Delete)
{
    m_bDeleted = Delete;
    return m_bDeleted;
}

//! User::IsDeleted
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return bool - true if user is deleted - cannot plan/take trips
bool User::IsDeleted(void) const
{
    return m_bDeleted;
}

//! User::MarkAdmin
//!
//! \author edt (3/25/19)
//!
//! \param Admin - true if user is to be made an Administrator
//!
//! \return bool - true if user is an Administrator
bool User::MarkAdmin(bool Admin)
{
    m_bIsAdministrator = Admin;
    return m_bIsAdministrator;

}

//! User::IsAdmin
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return bool - true if user is an Administrator
bool User::IsAdmin(void) const
{
    return m_bIsAdministrator;
}

//! User::MarkBlocked
//!
//! \author edt (3/25/19)
//!
//! \param Block - true if user should be prevented from logging on
//!
//! \return bool - true if user is prevented from logging on
bool User::MarkBlocked(bool Block)
{
    m_bBlocked = Block;
    return m_bBlocked;
}

//! User::IsBlocked
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return bool - true if user is prevented from logging on
bool User::IsBlocked(void) const
{
    return m_bBlocked;
}

//! User::Purchase - update purchase total while taking trip
//!
//! \author edt (3/25/19)
//!
//! \param PurchaseAmount - amount of new purchase
//!
//! \return float - total amount purchased on all trips
float User::Purchase(float PurchaseAmount)
{
    m_fTotalPurchases += PurchaseAmount;
    return m_fTotalPurchases;
}

//! User::AddTrip - depricated - Use StoreTrip
//!
//! \author edt (3/25/19)
//!
//! \param Trip - trip number planned
void User::AddTrip(int Trip)
{
    // should avoid adding duplicates
    m_Trips.push_back(Trip);
}

//! User::GetTrips - list trips planned by this user
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return const vector&lt;int&gt;&amp; - trips planned by this user
const vector<int> &User::GetTrips(void) const
{
    return m_Trips;
}

//! User::GetTotalPurchase
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return float - total amount purchased on all trips
float User::GetTotalPurchase(void) const
{
    return m_fTotalPurchases;
}

//! print the value of the object for external display
//!
//! \author edt (2/7/18)
//!
//! \param print_endl  print end of lines after each element
//!
//! \return bool
bool User::PrintAsDebug(bool print_endl) const
{
    if (print_endl)
    {
        cout << "ObjAddr     :" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec << endl
             << " Number     :" << m_nNumber << endl
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
             << " Number    :" << m_nNumber
             << " Name      :" << m_UserName
             << " Purchases :" << m_fTotalPurchases
             << " Admin     :" << m_bIsAdministrator
             << " Hash PW   :" << m_HashedPassword
             << " Deleted   :" << m_bDeleted
             << " Blocked   :" << m_bBlocked
             << " Trips     :";
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
//! \param os - output stream being processed
//! \param user - item being printed
//!
//! \return ostream&amp; - output stream being processed
ostream& operator<<(ostream& os, const User& user)
{
    os << user.PrintAsDebug(true);
    return(os);
}
