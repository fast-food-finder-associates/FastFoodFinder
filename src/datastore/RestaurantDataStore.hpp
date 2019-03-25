/**
 * CS1D - Fast Food Associates
 *
 * Defines a data storage mechanism for Restaurant objects.
 * These objects are contained in a doublly linked list that
 * supports iterators and a comperable interfacen
 *
 * @author   edt
 */

#pragma once

#include "MyDblLinkList.hpp"
#include "Restaurant.hpp"
#include <list>

using namespace std;
using namespace nsMyDblLinkList;

class RestaurantDataStore
{
public:
    // Constructor
    RestaurantDataStore();

    // Destructor
    virtual ~RestaurantDataStore();

    void printAsDebug(bool printeol, bool printcontent) const;
    Restaurant &FindbyNumber(int Number);

    void load(const string path, bool ItemsAreAdditional = false);
    void save(const string path);
    void load_additional(const string path);

    std::list<Restaurant> list;
//    MyDblLinkList<Restaurant> list;

private:
    bool DuplicateNumPresent(int Number);

    // Copy constructor
    RestaurantDataStore(const RestaurantDataStore& src);

    // Assignment operator
    RestaurantDataStore& operator=(const RestaurantDataStore& src); } ;
