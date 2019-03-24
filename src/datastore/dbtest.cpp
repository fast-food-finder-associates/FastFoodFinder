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
    Restaurants.load("./");
    Restaurants.save("./");

    Trips.load("./");
    Trips.save("./");

    Users.load("./");
    Users.save("./");

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

    cout << "Print Imported Restaurants ================================" << endl;
    //Restaurants.printAsDebug(true, true);

    //cout << "Print Imported Trips ======================================" << endl;
    //Trips.printAsDebug(true, true);

    cout << "Adding a New User -------------------------------------------" << endl;
    User new1("Bill Smith","Nopass");
    Users.list.push_back(new1);

    cout << "Name from id test " << Restaurants.FindbyNumber(2).GetName() << endl;

    cout << "Add a menu item test" << endl;
    Restaurant &myrest = Restaurants.FindbyNumber(2);
    myrest.PrintAsDebug(true);
    myrest.AddMenuItem("Test Item", 9.89);
    myrest.PrintAsDebug(true);

    cout << endl << endl;
    cout << "Test Trip findByNum" << endl;
    Trip &myTrip = Trips.FindbyNumber(10);
    myTrip.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #3 - start at Saddleback, visit 10 Restaurants" << endl;
    int myTrip3x = Trips.StoreTripNumRest("Trip Test Req3", 0, 10, Restaurants, Users.list.front());
    Trip &myTrip3 = Trips.FindbyNumber(myTrip3x);
    myTrip3.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #4 - start at Dominos, visit N (5) Restaurants" << endl;
    int myTrip4x = Trips.StoreTripNumRest("Trip Test Req4", 3, 5, Restaurants, Users.list.front());
    Trip &myTrip4 = Trips.FindbyNumber(myTrip4x);
    myTrip4.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #5a - start at Saddleback, visit selected Restaurants" << endl;
    vector<int> myrests5a = { 2, 6, 3, 1, 8 };
    int myTrip5ax = Trips.StoreTrip("Trip Test Req5a", myrests5a, Restaurants, Users.list.front(), true);
    Trip &myTrip5a = Trips.FindbyNumber(myTrip5ax);
    myTrip5a.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;

    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #5b - visit selected Restaurants" << endl;
    vector<int> myrests5b = { 2, 9, 3, 1, 4, 8 };
    int myTrip5bx = Trips.StoreTrip("Trip Test Req5b", myrests5b, Restaurants, Users.list.front(), false);
    Trip &myTrip5b = Trips.FindbyNumber(myTrip5bx);
    myTrip5b.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;
#if 0
   >> Add  2 more restaurants to Resturants list
    cout << endl << endl;
    cout << "Test Plan a Trip - requirement #6 - start at Saddleback, visit 12 Restaurants" << endl;
    int myTrip = StoreTripNumRest("Trip Test Req3", 0, 10, &Restaurants, Users.list.front());
    myTrip.PrintAsDebug(true);
    cout << "--------------------" << endl << endl;
#endif

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

