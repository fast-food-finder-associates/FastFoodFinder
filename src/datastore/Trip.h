#ifndef __TRIP_H_INCL__
#define __TRIP_H_INCL__

/**
 * TODO: Add class description
 * 
 * @author   edt
 */

#include <vector>
#include <string>

using namespace std;


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

    const string &GetName(void) const;
    int  GetCreatingUser(void) const;
    const vector<int> &GetResturants(void) const;
    float GetTotalDistance(void) const;
    bool MarkDeleted(bool Delete);
    bool AddRestaurant(int Resturaurant);
    bool PrintAsDebug(bool print_endl) const;

private:
    bool        m_bInitialized;
    int         m_nNumber;
    string      m_Name;
    int         m_nCreatingUser;
    vector<int> m_Restraurants;
    bool        m_bDeleted; // if true, do not display on general GUI (maybe in admin GUI)
    float       m_fTotalDistance;

    static int  sm_NextNumber;
};

#endif // __TRIP_H_INCL__
