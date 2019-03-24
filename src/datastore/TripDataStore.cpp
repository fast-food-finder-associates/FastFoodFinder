/**
 * CS1D - Fast Food Associates
 *
 * Implements a data storage mechanism for Trip objects. These
 * objects are contained in a doublly linked list that supports
 * iterators and a comperable interfacen
 *
 * @author   edt
 */

#include "TripDataStore.hpp"
#include "RestaurantDataStore.hpp"
#include "Restaurant.hpp"
#include "User.hpp"
#include <stdio.h>
#include <fstream>
#include <stdexcept>

using namespace std;
using namespace nsMyDblLinkList;

static const int nMaxUserInputLine = 200;

// Constructor implementation
TripDataStore::TripDataStore()
{
}

void TripDataStore::load(const string path)
{
    string fullpath = path + "TripData.csv";
    std::ifstream infile(fullpath, ios::in);
    int line_count = 0;
    if (infile.is_open())
    {
        std::string inputline;
        while (infile.good())
        {
            std::getline(infile, inputline);
            if (!infile.eof())
            {
                line_count++;
                std::vector<std::string> commaSeparated(1);
                int commaCounter = 0;
                for (int i=0; i < inputline.size(); i++)
                {
                    if (inputline[i] == ',')
                    {
                        commaSeparated.push_back("");
                        commaCounter++;
                    } else
                    {
                        commaSeparated.at(commaCounter) += inputline[i];
                    }
                }
                // We now have a vector of strings that represent the data members
                // of our object
                // The serialized data looks like:
                // 10,PizzaBinge,10,21.65,0,3,1,8,9
                int nNumber = std::stoi(commaSeparated[0]);
                int nCreator = std::stoi(commaSeparated[2]);
                float fTotalDistance = std::stof(commaSeparated[3]);
                int nDeleted = std::stoi(commaSeparated[4]);

                // Parse the Restaurants List
                std::vector<int> Restaurants;
                int nNumRestaurants = std::stoi(commaSeparated[5]);
                int it = 6;
                while (it < (6 + nNumRestaurants))
                {
                    Restaurants.push_back(std::stoi(commaSeparated[it++]));
                }
                Trip *pTrip = new Trip(nNumber,
                                 nCreator,
                                 Restaurants,
                                 fTotalDistance,
                                 commaSeparated[1],
                                 nDeleted);
                list.push_back(*pTrip);
            }
        }
    }
    else
    {
        throw std::invalid_argument("Trip File name invalid");
    }
    if (line_count == 0)
    {
        throw std::invalid_argument("Trip File Empty");
    }
}

void TripDataStore::save(const string path)
{
    string fullpath = path + "TripData.csv.tmp";
    string outline;
    int line_count = 0;

    std::ofstream outfile(fullpath, ios::trunc);
    if (outfile.is_open())
    {
        for (MyDblLinkList<Trip>::iterator it = list.begin(); it != list.end(); it++)
        {
            line_count++;

            outfile << (*it).m_nNumber << ",";
            outfile << (*it).m_Name << ",";
            outfile << (*it).m_nCreatingUser << ",";
            outfile << (*it).m_fTotalDistance << ",";
            outfile << (*it).m_bDeleted << ",";

            int num_rests = (*it).m_Restaurants.size();
            outfile << num_rests << ",";
            if (num_rests > 0)
            {
                for (std::vector<int>::const_iterator itt = (*it).m_Restaurants.begin();
                                                           itt != (*it).m_Restaurants.end(); itt++)
                {
                    outfile << (*itt) << ",";
            }
        }

            outfile << endl;
        }

    }
    else
    {
        throw std::invalid_argument("Trip Save File name invalid");
    }
    if (line_count == 0)
    {
        throw std::invalid_argument("Trip Save File Empty");
    }

}

Trip &TripDataStore::FindbyNumber(int Number)
{
    for (MyDblLinkList<Trip>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if ( (*it).m_nNumber == Number)
        {
            return *it;
        }
    }
    return *(list.end());  // never reached  - should throw exception
}

int TripDataStore::StoreTrip(const string &TripName, const vector<int> RestaurantsSelectedbyUser, RestaurantDataStore &RestSt, User &User, bool StartatSaddleback)
{
    int current_restaurant;
    int closest_restnum;
    vector<int> sVec;
    float shortest_distance = 999.9;
    float cumulative_distance = 0;
    Restaurant *pRest;
    vector<int> selected_restaurants(RestaurantsSelectedbyUser.begin(), RestaurantsSelectedbyUser.end());
    if (StartatSaddleback)
    {
        for (vector<int>::const_iterator it = selected_restaurants.begin(); it != selected_restaurants.end(); it++)
        {
            pRest = &RestSt.FindbyNumber(*it);
            float restdist = pRest->GetDistSaddleback();
            if (restdist < shortest_distance) 
            {
                shortest_distance = restdist;
                closest_restnum = pRest->GetNumber();
            }
        }
        current_restaurant = closest_restnum;
        cumulative_distance = shortest_distance;
        sVec.push_back(current_restaurant);
        for (vector<int>::iterator delete_restaurant = selected_restaurants.begin(); delete_restaurant != selected_restaurants.end(); delete_restaurant++)
        {
            if ((*delete_restaurant) == current_restaurant)
            {
                selected_restaurants.erase(delete_restaurant);
                break;
            }
        }
    }
    else
    {
        // save starting restaurant if not starting at Saddleback
        // then delete it from the list
        current_restaurant = selected_restaurants.front();
        sVec.push_back(current_restaurant);
        selected_restaurants.erase(selected_restaurants.begin());
    }

    while (selected_restaurants.size() > 0)
    {
        shortest_distance = 999.9;
        pRest = &RestSt.FindbyNumber(current_restaurant);
        
        for (vector<int>::iterator next_restaurant = selected_restaurants.begin(); next_restaurant != selected_restaurants.end(); next_restaurant++)
        {
            // search Restaurant Distances list for an item in the selected restaurants list
            for (vector<RestaurantDistance>::const_iterator itrd = pRest->GetDistances().begin(); itrd != pRest->GetDistances().end(); itrd++)
            {
                if ((*itrd).m_nRestaurantNumber != (*next_restaurant))
                {
                    // not the restaurant number we are looking for
                    continue;
                }

                // found the restaurant, check if shorter distance than any others so far
                if ((*itrd).m_fDistanceMiles < shortest_distance)
                {
                    shortest_distance = (*itrd).m_fDistanceMiles;
                    closest_restnum = (*itrd).m_nRestaurantNumber;
                }
                break;
            }
        }

        // we now have the closest restaurant remaining in the selected list 
        current_restaurant = closest_restnum;
        cumulative_distance += shortest_distance;
        sVec.push_back(current_restaurant);

        // delete the restaurant selected as closest from the user's selection
        // to prevent loops and duplicate selections
        for (vector<int>::iterator delete_restaurant = selected_restaurants.begin(); delete_restaurant != selected_restaurants.end(); delete_restaurant++)
        {
            if ((*delete_restaurant) == current_restaurant)
            {
                selected_restaurants.erase(delete_restaurant);
                break;
            }
        }
    }

    // sVec contains a list of restaurants to visit - each successive restaurant
    // is closest to its predecessor
    // Construct a Trip containing this list
    Trip tmp(User.GetNumber(), sVec, cumulative_distance, TripName);
    list.push_back(tmp);

    // Update all of the restaurants referenced by this trip
    for (vector<int>::iterator it = sVec.begin(); it != sVec.end(); it++)
    {
        pRest = &RestSt.FindbyNumber(*it);
        pRest->AddTrip(tmp.GetNumber());
    }

    // also update the creating user's list
    User.AddTrip(tmp.GetNumber());

    return(tmp.GetNumber());
}

int TripDataStore::StoreTripNumRest(const string &TripName, int StartingRestNum, int NumtoVisit, RestaurantDataStore &RestSt, User &User)
{
    int current_restaurant = StartingRestNum;
    int closest_restnum;
    vector<int> sVec;
    float shortest_distance = 999.9;
    float cumulative_distance = 0;
    Restaurant *pRest;
    if (StartingRestNum == 0)
    {
        // If start number is zero, starting point is Saddleback
        for (MyDblLinkList<Restaurant>::iterator it = RestSt.list.begin(); it != RestSt.list.end(); ++it)
        {
            float restdist = (*it).GetDistSaddleback();
            if (restdist < shortest_distance) 
            {
                shortest_distance = restdist;
                closest_restnum = (*it).GetNumber();
            }
        }
        current_restaurant = closest_restnum;
        cumulative_distance = shortest_distance;
        sVec.push_back(current_restaurant);
    }

    while (--NumtoVisit > 0)
    {
        shortest_distance = 999.9;
        pRest = &RestSt.FindbyNumber(current_restaurant);
        
        for (vector<RestaurantDistance>::const_iterator itrd = pRest->GetDistances().begin(); itrd != pRest->GetDistances().end(); itrd++)
        {
            if ((*itrd).m_fDistanceMiles < shortest_distance)
            {
                bool dupe_found = false;
                for (vector<int>::const_iterator itrs = sVec.begin(); itrs != sVec.end(); itrs++)
                {
                    if ((*itrd).m_nRestaurantNumber == (*itrs))
                    {
                        dupe_found = true;
                    }
                }
                if (!dupe_found)
                {
                    shortest_distance = (*itrd).m_fDistanceMiles;
                    closest_restnum = (*itrd).m_nRestaurantNumber;
                }
            }
        }
        if (shortest_distance != 999.9)
        {
            current_restaurant = closest_restnum;
            cumulative_distance += shortest_distance;
            sVec.push_back(current_restaurant);
        }
    }

    // sVec contains a list of restaurants to visit - each successive restaurant
    // is closest to its predecessor
    // Construct a Trip containing this list
    Trip tmp(User.GetNumber(), sVec, cumulative_distance, TripName);
    list.push_back(tmp);

    // Update all of the restaurants referenced by this trip
    for (vector<int>::iterator it = sVec.begin(); it != sVec.end(); it++)
    {
        pRest = &RestSt.FindbyNumber(*it);
        pRest->AddTrip(tmp.GetNumber());
    }

    // also update the creating user's list
    User.AddTrip(tmp.GetNumber());

    return(tmp.GetNumber());
}

void TripDataStore::printAsDebug(bool printeol, bool printcontent) const
{
    list.printAsDebug(printeol,printcontent);
}

// Destructor implementation
TripDataStore::~TripDataStore()
{

};
