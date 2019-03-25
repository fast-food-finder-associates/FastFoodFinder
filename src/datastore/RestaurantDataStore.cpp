/**
 * CS1D - Fast Food Associates
 *
 * Implements a data storage mechanism for User objects. These
 * objects are contained in a doublly linked list that supports
 * iterators and a comperable interfacen
 *
 * @author   edt
 */

#include "RestaurantDataStore.hpp"
#include "Restaurant.hpp"
#include <stdio.h>
#include <fstream>
#include <stdexcept>

using namespace std;
using namespace nsMyDblLinkList;

// Constructor implementation
RestaurantDataStore::RestaurantDataStore()
{
};

void RestaurantDataStore::load(const string path, bool ItemsAreAdditional)
{
    //string fullpath = path + "RestaurantData.csv";
    std::ifstream infile(path, ios::in);
    int line_count = 0;
    if (infile.is_open())
    {
        std::string inputline;
        while (infile.good())
        {
            std::getline(infile, inputline);
            if (!infile.eof())
            {
                if (inputline[0] == '#')
                {
                    continue;  // ignore comment lines
                }
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
                // 1,MacDonalds,8.1,100.00,19,0,0,
                // 10,1,0.0,2,13.2,3,15.4,4,11.5,5,13.3,6,15.2,7,5.8,8,6.9,9,8.56,10,3.5,
                // 1,0,8,Big Mac,3.99,2,0,French Fries,2.95,3.0,Hamburger,1.79,4,0,Double Cheeseburger,4.29,5,0,Cheeseburger,2.29,6,0,Quarter Pounder with Cheese,4.99,7,0,Filet-O-Fish,3.33,8,0,McRib,4.97
                // 0
                int nNumber = std::stoi(commaSeparated[0]);
                // prevent loading of duplicate numbers by silently rejecting the load for this record
                if (DuplicateNumPresent(nNumber))
                {
                    continue;
                }

                float fDistToSaddleback = std::stof(commaSeparated[2]);
                float fTotalPurchases = std::stof(commaSeparated[3]);
                int nTotalCustomers = std::stoi(commaSeparated[4]);
                int nUsedByCount = std::stoi(commaSeparated[5]);
                int nDeleted = std::stoi(commaSeparated[6]);

                // parse the list of Restaurant Distances
                std::vector<RestaurantDistance> Distances;
                int nDistances = std::stoi(commaSeparated[7]);
                int it = 8;
                if (nDistances > 0)
                {
                    RestaurantDistance tmp;
                    while(it < (8 + 2*nDistances))
                    {
                        tmp.m_nRestaurantNumber = std::stoi(commaSeparated[it]);
                        tmp.m_fDistanceMiles = std::stof(commaSeparated[it+1]);
                        Distances.push_back(tmp);
                        if (ItemsAreAdditional)
                        {
                            Restaurant *pRest = &this->FindbyNumber(tmp.m_nRestaurantNumber);
                            tmp.m_nRestaurantNumber = nNumber;
                            // Add the new restaurant's distance grouping to every existing Restaurant
                            if (pRest != nullptr)  
                            {
                                // if nullptr, then this is a forward reference to an not yet created restaurant
                                // this test also prevents updating the restaurant we are currently adding
                                bool distance_already_present = false;
                                for (vector<RestaurantDistance>::iterator itc = pRest->m_Distances.begin(); itc != pRest->m_Distances.end(); itc++)
                                {
                                    if ((*itc).m_nRestaurantNumber == nNumber)
                                    {
                                        distance_already_present = true;
                                    }
                                }
                                if (!distance_already_present)
                                {
                                    pRest->m_Distances.push_back(tmp);
                                }
                            }
                        }
                        it += 2;
                    }
                }

                // Parse the list of Menu Items
                std::vector<MenuItem> MenuItems;
                int it2 = it + 1;
                int nMenuItems = std::stoi(commaSeparated[it]);
                if (nMenuItems > 0)
                {
                    while (it2 < (it + 1 + (4*nMenuItems)))
                    {
                        int x = std::stoi(commaSeparated[it2++]);
                        int y = std::stoi(commaSeparated[it2++]);
                        string z = commaSeparated[it2++];
                        float w = std::stof(commaSeparated[it2++]);
                        MenuItem tmp(x,y,z,w);
                        MenuItems.push_back(tmp);
                    }
                }

                // Parse the Used by Trips List
                std::vector<int> ReferencedByTrips;
                int nTripRef = std::stoi(commaSeparated[it2++]);

                if (nTripRef > 0)
                {
                    while (it2 < commaSeparated.size())
                {
                    ReferencedByTrips.push_back(std::stoi(commaSeparated[it2++]));
                    }
                }
                Restaurant *pRestaurant = new Restaurant(nNumber,
                                 commaSeparated[1],
                                 fDistToSaddleback,
                                 fTotalPurchases,
                                 nTotalCustomers,
                                 nUsedByCount,
                                 nDeleted,
                                 Distances,
                                 MenuItems,
                                 ReferencedByTrips);
                list.push_back(*pRestaurant);
            }
        }
    }
    else
    {
        throw std::invalid_argument("Restaurant File name invalid");
    }
    if (line_count == 0)
    {
        throw std::invalid_argument("Restaurant File Empty");
    }
}

void RestaurantDataStore::save(const string path)
{
    //string fullpath = path + "RestaurantData.csv.tmp";
    string outline;
    int line_count = 0;

    std::ofstream outfile(path, ios::trunc);
    if (outfile.is_open())
    {
        for (std::list<Restaurant>::iterator it = list.begin(); it != list.end(); it++)
        {
            line_count++;

            outfile << (*it).m_nNumber << ",";
            outfile << (*it).m_Name << ",";
            outfile << (*it).m_fDistToSaddleback << ",";
            outfile << (*it).m_fTotalPurchases << ",";
            outfile << (*it).m_nTotalCustomers << ",";
            outfile << (*it).m_nUsedByCount << ",";
            outfile << (*it).m_bDeleted << ",";
            int num_dists = (*it).m_Distances.size();
            outfile << num_dists << ",";
            if (num_dists > 0)
            {
                for (std::vector<RestaurantDistance>::const_iterator itd = (*it).m_Distances.begin();
                                                                     itd != (*it).m_Distances.end(); itd++)
                {
                    outfile << (*itd).m_nRestaurantNumber << ",";
                    outfile << (*itd).m_fDistanceMiles << ",";
                }
            }

            int num_menuitems = (*it).m_Menu.size();
            outfile << num_menuitems << ",";
            if (num_menuitems > 0)
            {
                for (std::vector<MenuItem>::const_iterator itm = (*it).m_Menu.begin();
                                                           itm != (*it).m_Menu.end(); itm++)
                {
                    outfile << (*itm).m_nNumber << ",";
                    outfile << (*itm).m_bDeleted << ",";
                    outfile << (*itm).m_MenuItemName << ",";
                    outfile << (*itm).m_fMenuItemPrice << ",";
                }
            }

            int num_tripref = (*it).m_ReferencedByTrips.size();
            outfile << num_tripref << ",";
            if (num_tripref > 0)
            {
                for (std::vector<int>::const_iterator itt = (*it).m_ReferencedByTrips.begin();
                                                           itt != (*it).m_ReferencedByTrips.end(); itt++)
                {
                    outfile << (*itt) << ",";
                }
        }

            outfile << endl;
        }

    }
    else
    {
        throw std::invalid_argument("Restaurant Save File name invalid");
    }
    if (line_count == 0)
    {
        throw std::invalid_argument("Restaurant Save File Empty");
    }
}

void RestaurantDataStore::load_additional(const string path)
{
    load(path, true);
}

Restaurant &RestaurantDataStore::FindbyNumber(int Number)
{
    for (std::list<Restaurant>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if ( (*it).m_nNumber == Number)
        {
            return *it;
        }
    }
    return *(list.end());  // never reached  - should throw exception
}

bool RestaurantDataStore::DuplicateNumPresent(int Number)
{
    bool dupe_found = false;
    for (std::list<Restaurant>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if ( (*it).m_nNumber == Number)
        {
            dupe_found = true;
            break;
        }
    }
    return dupe_found;
}

void RestaurantDataStore::printAsDebug(bool printeol, bool printcontent) const
{
    // std::list has no printAsDebug() method - MyDblLinkList does
    //list.printAsDebug(printeol,printcontent);
}

// Destructor implementation
RestaurantDataStore::~RestaurantDataStore()
{

};

// TODO: Uncomment the copy constructor when you need it.
//inline RestaurantDataStore::RestaurantDataStore(const RestaurantDataStore& src)
//{
//   // TODO: copy
//}

// TODO: Uncomment the assignment operator when you need it.
//inline RestaurantDataStore& RestaurantDataStore::operator=(const RestaurantDataStore& rhs)
//{
//   if (this == &rhs) {
//      return *this;
//   }
//
//   // TODO: assignment
//
//   return *this;
//}
// TODO: your implementation here

