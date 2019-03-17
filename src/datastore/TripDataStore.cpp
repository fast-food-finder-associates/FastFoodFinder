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
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace nsMyDblLinkList;

static const int nMaxUserInputLine = 200;

// Constructor implementation
TripDataStore::TripDataStore()
{
    std::ifstream infile("TripData.csv", ios::in);
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
};

void TripDataStore::printAsDebug(bool printeol, bool printcontent) const
{
    list.printAsDebug(printeol,printcontent);
}

// Destructor implementation
TripDataStore::~TripDataStore()
{

};
