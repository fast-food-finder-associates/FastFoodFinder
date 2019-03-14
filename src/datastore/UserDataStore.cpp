/**
 * CS1D - Fast Food Associates
 *
 * Implements a data storage mechanism for User objects. These
 * objects are contained in a doublly linked list that supports
 * iterators and a comperable interfacen
 *
 * @author   edt
 */

#include "UserDataStore.hpp"
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace nsMyDblLinkList;

static const int nMaxUserInputLine = 200;

// Constructor implementation
UserDataStore::UserDataStore()
{
    std::ifstream infile("UserData.csv", ios::in);
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
                // 10,Dale,123.45,1,nopass,0,0,#,
                int nUserNumber = std::stoi(commaSeparated[0]);
                float fTotalPurchases = std::stof(commaSeparated[2]);
                int nUserAdmin = std::stoi(commaSeparated[3]);
                int nUserDeleted = std::stoi(commaSeparated[5]);
                int nUseBlocked = std::stoi(commaSeparated[6]);

                std::vector<int> UserTrips;
                if (commaSeparated[7] != "#")
                {
                    for ( int it = 7; it < commaSeparated.size(); it++)
                    {
                        UserTrips.push_back(stoi(commaSeparated[it]));
                    }
                }
                User *pUser = new User(nUserNumber,
                                 commaSeparated[1],
                                 fTotalPurchases,
                                 nUserAdmin,
                                 commaSeparated[4],
                                 nUserDeleted,
                                 nUseBlocked,
                                 UserTrips);
                list.push_back(*pUser);
            }
        }
    }
};

void UserDataStore::printAsDebug(bool printeol, bool printcontent) const
{
    list.printAsDebug(printeol,printcontent);
}

// Destructor implementation
UserDataStore::~UserDataStore()
{

};
