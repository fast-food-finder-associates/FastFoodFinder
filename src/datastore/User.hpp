/**
 * CS1D - Fast Food Associates
 *
 * Definition of the User class that provides a means for
 * validating users, collecting their trips and defines their
 * access rights
 * 
 * @author   edt
 */

#pragma once

#include <vector>
#include <string>

using namespace std;

class User
{
friend class UserDataStore;

public:
    // overload << operator to display internal form of Employee object
    friend ostream& operator<<(ostream& os, const User& user);

    // No arg constructor
    User() { m_nUserNumber = -1; m_bInitialized = false; };

    // Constructor - New User
    User(const string &Name, const string &Password);

    // Destructor
    virtual ~User();

    // Copy constructor
    User(const User& src);

    // Assignment operator
    User& operator=(const User& src);

    const string &GetName(void) const;
    const  string &GetHashedPasswd(void) const;
    bool MarkDeleted(bool Delete);
    bool IsDeleted(void) const;
    bool MarkAdmin(bool Admin);
    bool IsAdmin(void) const;
    bool MarkBlocked(bool Block);
    bool IsBlocked(void) const;
    float Purchase(float PurchaseAmount);
    void AddTrip(int Trip);
    const vector<int> &GetTrips(void) const;
    float GetTotalPurchase(void) const;
    bool operator<(User &rhs);

private:
    bool        m_bInitialized;
    int         m_nUserNumber;
    string      m_UserName;
    float       m_fTotalPurchases;
    bool        m_bIsAdministrator;
    string      m_HashedPassword;
    bool        m_bDeleted; // if true, do not display on general GUI (maybe in admin GUI)
    bool        m_bBlocked; // cannot log in
    vector<int> m_Trips;

    static int  sm_NextNumber;

    // private members to prevent use

    // Constructor - used by UserDataSttore class as a freiend to  create
    // user objects from input file
    User(int nUserNumber,
         string     &Name,
         float      &fTotalPurchases,
         bool       bUserAdmin,
         string     &HashedPw,
         bool       bUserDeleted,
         bool       bUserBlocked,
         vector<int> &UserTrips);

    bool PrintAsDebug(bool print_endl) const;

};
