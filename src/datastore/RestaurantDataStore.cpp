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

using namespace std;
using namespace nsMyDblLinkList;

static const int nMaxRestaurantInputLine = 500;

// Constructor implementation
RestaurantDataStore::RestaurantDataStore()
{
    std::ifstream infile("RestaurantData.csv", ios::in);
    if (infile.is_open())
    {
        std::string inputline;
        while (infile.good())
        {
            std::getline(infile, inputline);
            if (!infile.eof())
            {
                //cout << inputline << endl;
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
                // 8,Big Mac,3.99,French Fries,2.95,Hamburger,1.79,Double Cheeseburger,4.29,Cheeseburger,2.29,Quarter Pounder with Cheese,4.99,Filet-O-Fish,3.33,McRib,4.97
                // 0
                int nNumber = std::stoi(commaSeparated[0]);
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
                    while(it < (8 + 2*nDistances))
                    {
                        RestaurantDistance tmp;
                        tmp.m_nRestaurantNumber = std::stoi(commaSeparated[it]);
                        tmp.m_fDistanceMiles = std::stof(commaSeparated[it+1]);
                        Distances.push_back(tmp);
                        it += 2;
                    }
                }

                // Parse the list of Menu Items
                std::vector<MenuItem> MenuItems;
                int it2 = it + 1;
                int nMenuItems = std::stoi(commaSeparated[it]);
                if (nMenuItems > 0)
                {
                    while (it2 < (it + 1 + (2*nMenuItems)))
                    {
                        MenuItem tmp;
                        tmp.m_MenuItemName = commaSeparated[it2];
                        tmp.m_MenuItemPrice = std::stof(commaSeparated[it2+1]);
                        MenuItems.push_back(tmp);
                        it2 += 2;
                    }
                }

                // Parse the Used by Trips List
                std::vector<int> ReferencedByTrips;
                while (it2 < commaSeparated.size())
                {
                    ReferencedByTrips.push_back(std::stoi(commaSeparated[it2++]));
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
};

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

void RestaurantDataStore::printAsDebug(bool printeol, bool printcontent) const
{
//    list.printAsDebug(printeol,printcontent);
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

