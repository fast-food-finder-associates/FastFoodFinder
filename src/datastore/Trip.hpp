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

/**
 * Information and methods about Trips taken by Foodies
 * 
 * @author   edt
 */

#include <vector>
#include <string>

using namespace std;

//! Trip - store information about Trips planned or taken
//!
//! \author edt (3/25/19)
class Trip
{
friend class TripDataStore;

public:
    // overload << operator to display internal form of Employee object
    friend ostream& operator<<(ostream& os, const Trip& trip);

    // No arg constructor
    Trip() { m_nNumber = -1; m_bInitialized = false; };

    // Destructor
    virtual ~Trip();

    Trip(int User,
         const vector<int> &Restaurants,
         float TotalDistance,
         const string &Name);

    Trip(int TripNum,
         int User,
         const vector<int> &Restaurants,
         float TotalDistance,
         const string &Name,
         bool bTripDeleted);

    // Copy constructor
    Trip(const Trip& src);

    // Assignment operator
    Trip& operator=(const Trip& rhs);

    int GetNumber(void) const;
    const string &GetName(void) const;
    int  GetCreatingUser(void) const;
    vector<int> &GetRestaurants(void);
    float GetTotalDistance(void) const;
    bool MarkDeleted(bool Delete);
    bool IsDeleted(void) const;
    bool AddRestaurant(int Restaurant);
    bool PrintAsDebug(bool print_endl) const;

private:
    bool        m_bInitialized;
    int         m_nNumber;
    string      m_Name;
    int         m_nCreatingUser;
    vector<int> m_Restaurants;
    bool        m_bDeleted; // if true, do not display on general GUI (maybe in admin GUI)
    float       m_fTotalDistance;

    static int  sm_NextNumber;
};
