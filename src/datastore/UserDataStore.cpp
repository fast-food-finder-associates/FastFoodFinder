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
#include <string>
#include <stdexcept>

using namespace std;
using namespace nsMyDblLinkList;

static const int nMaxUserInputLine = 200;

// Constructor implementation
UserDataStore::UserDataStore()
{
}

void UserDataStore::load(const string path)
{
    string fullpath = path + "UserData.csv";
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
                // 10,Dale,123.45,1,nopass,0,0,0,
                int nUserNumber = std::stoi(commaSeparated[0]);
                float fTotalPurchases = std::stof(commaSeparated[2]);
                int nUserAdmin = std::stoi(commaSeparated[3]);
                int nUserDeleted = std::stoi(commaSeparated[5]);
                int nUseBlocked = std::stoi(commaSeparated[6]);

                // Parse list of Trips
                std::vector<int> UserTrips;
                int nNumTrips = std::stoi(commaSeparated[7]);
                int it = 8;
                while (it < (8 + nNumTrips))
                {
                        UserTrips.push_back(stoi(commaSeparated[it++]));
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
    else
    {
        throw std::invalid_argument("User File name invalid");
    }
    if (line_count == 0)
    {
        throw std::invalid_argument("User File Empty");
    }
};

void UserDataStore::save(const string path)
{
    string fullpath = path + "UserData.csv.tmp";
    string outline;
    int line_count = 0;

    std::ofstream outfile(fullpath, ios::trunc);
    if (outfile.is_open())
    {
        for (std::list<User>::iterator it = list.begin(); it != list.end(); it++)
        {
            line_count++;

            outfile << (*it).m_nUserNumber << ",";
            outfile << (*it).m_UserName << ",";
            outfile << (*it).m_fTotalPurchases << ",";
            outfile << (*it).m_bIsAdministrator << ",";
            outfile << (*it).m_HashedPassword << ",";
            outfile << (*it).m_bDeleted << ",";
            outfile << (*it).m_bBlocked << ",";

            int num_trips = (*it).m_Trips.size();
            outfile << num_trips << ",";
            if (num_trips > 0)
            {
                for (std::vector<int>::const_iterator itt = (*it).m_Trips.begin();
                                                           itt != (*it).m_Trips.end(); itt++)
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

void UserDataStore::printAsDebug(bool printeol, bool printcontent) const
{
//    list.printAsDebug(printeol,printcontent);
}

// Destructor implementation
UserDataStore::~UserDataStore()
{

};
