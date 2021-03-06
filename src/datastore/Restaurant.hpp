/**
 * CS1D - Fast Food Associates
 *
 * Definition of the Restaurant class that provides a means for
 * validating restaurants, string menu items and distances to
 * other restaurants
 *
 * @author   edt
 */

 #pragma once

#include <vector>
#include <string>

#include "Trip.hpp"
#include "MenuItem.hpp"

using namespace std;

//! RestaurantDistance - container for restaurant numbers and their related distances
//!  from the containing Restaurant
//!
//! \author edt (3/25/19)
struct RestaurantDistance
{
    int m_nRestaurantNumber;
    float m_fDistanceMiles;
};
/**
 * Internal datastore for Restaurant Objects
 * 
 * @author   edt
 */
class Restaurant
{
friend class RestaurantDataStore;

public:
    // overload << operator to display internal form of Employee object
    friend ostream& operator<<(ostream& os, const Restaurant& restaurant);

    // No arg constructor
    Restaurant() { m_nNumber = -1; m_bInitialized = false; };

    // Constructor - New User
    Restaurant(const string &Name, const float &Distance);

    // Destructor
    virtual ~Restaurant();

    // Copy constructor
    Restaurant(const Restaurant& src);

    // Assignment operator
    Restaurant& operator=(const Restaurant& rhs);

    const string &GetName(void) const;
    void SetName(const string &NewName);
    int GetNumber(void) const;
    const vector<MenuItem> &GetMenu(void) const;
    const vector<RestaurantDistance> &GetDistances(void) const;
    float GetPurchaseAmount(void) const;
    bool MarkDeleted(bool Delete);
    bool IsDeleted(void) const;
    bool AddTrip(int TripNumber);
    int AddCustCount(void);
    float AddPurchasePrice(float PurchaseAmount);
    float GetDistSaddleback(void) const;
    void AddMenuItem(const string &Name, const float &Price);
    MenuItem&FindMenuItembyNumber(int Number);

    bool PrintAsDebug(bool print_endl) const;

private:
    bool                m_bInitialized;
    int                 m_nNumber;
    string              m_Name;
    float               m_fDistToSaddleback;
    float               m_fTotalPurchases;
    int                 m_nTotalCustomers;
    int                 m_nUsedByCount;
    bool                m_bDeleted;  // if true, do not display on general GUI (maybe in admin GUI)
    vector<RestaurantDistance> m_Distances;
    vector<MenuItem>    m_Menu;
    vector<int>         m_ReferencedByTrips;

    static int  sm_NextNumber;

    // private members to prevent use

    // Constructor - used by RestaurantrDataSttore class as a freiend to  create
    // restaurant objects from input file
    Restaurant(
         int        nNumber,
         string     &Name,
         float      &fDistToSaddleback,
         float      &fTotalPurchases,
         int        nTotalCustomers,
         int        nUsedByCount,
         bool       bDeleted,
         vector<RestaurantDistance> &Distances,
         vector<MenuItem>           &MenuItems,
         vector<int>                &ReferencedByTrips);
};

struct Cmp_by_name {
    bool operator()(const Restaurant* s1, const Restaurant* s2) const
    {
        // dereference pointer, compare ids
        return (s1->GetName() < s2->GetName());
    }
};

struct Cmp_by_distance {
    bool operator()(const Restaurant* s1, const Restaurant* s2) const
    {
        // dereference pointer, compare ids
        return (s1->GetDistSaddleback() < s2->GetDistSaddleback());
    } } ;
