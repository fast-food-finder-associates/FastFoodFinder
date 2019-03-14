// --------------------------------------------------------------------
//
// main.cpp Test Program for FastFoodAssociates data store
//
// Eugene Tyler -  CS1D - Project 1
//                        02/15/19

#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

#include "MyDblLinkList.hpp"

using namespace std;

#include "User.hpp"
#include "Trip.hpp"
#include "Restaurant.hpp"
#include "UserDataStore.hpp"
#include "RestaurantDataStore.hpp"
#include "TripDataStore.hpp"

void print_state (const std::ios& stream)
{
  std::cout << " good()=" << stream.good();
  std::cout << " eof()=" << stream.eof();
  std::cout << " fail()=" << stream.fail();
  std::cout << " bad()=" << stream.bad();
  cout << endl;
}

UserDataStore Users;
RestaurantDataStore Restaurants;
TripDataStore Trips;

int main (int argc, char *argv[])
{
    for (MyDblLinkList<Restaurant>::iterator it = Restaurants.list.begin(); it != Restaurants.list.end(); ++it)
    {
        cout << "Restaurant name:" << (*it).GetName() << " Distance to Saddleback (miles) " << (*it).GetDistSaddleback() << endl;
    }
    cout << endl << endl;                      // range-for-loop to print Restaurants


    for (MyDblLinkList<User>::iterator it = Users.list.begin(); it != Users.list.end(); ++it)
    {
        cout << "User name:" << (*it).GetName() << " Total Purchases $" << (*it).GetTotalPurchase() << endl;
    }
    cout << endl << endl;                      // range-for-loop to print Restaurants

    cout << "Print Imported Users ======================================" << endl;
    Users.printAsDebug(true, true);

    //cout << "Print Imported Restaurants ================================" << endl;
    //Restaurants.printAsDebug(true, true);

    //cout << "Print Imported Trips ======================================" << endl;
    //Trips.printAsDebug(true, true);

    cout << "Adding a New User -------------------------------------------" << endl;
    User new1("Bill Smith","Nopass");
    Users.list.push_back(new1);

    cout << "Name from id test " << Restaurants.FindbyNumber(2).GetName() << endl;

    for (MyDblLinkList<User>::iterator it = Users.list.begin(); it != Users.list.end(); ++it)
    {
        cout << "User name:" << (*it).GetName() << " Total Purchases $" << (*it).GetTotalPurchase() << endl;
    }
    cout << endl << endl;                      // range-for-loop to print Restaurants


    //Users.printAsDebug(true, true);
    //system("ls -l");
#if 0
    cout << "test list" << endl;
    User ff("XXX","hash");
    User ff1("TTT","hash");
    User ff2("ZZZ","hash");
    std::list<User> xl;
    xl.push_back(ff);
    xl.push_back(ff1);
    xl.push_back(ff2);
    auto ix = xl.begin();
    //cout << *ix << endl;
    sort(xl.begin(),xl.end());
    for (auto id = xl.begin(); id != xl.end(); id++)
    {
        cout << *id;
    }
#endif
}

