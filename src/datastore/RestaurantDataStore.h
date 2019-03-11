/**
 * CS1D - Fast Food Associates
 *
 * Implements a data storage mechanism for Restaurant objects.
 * These objects are contained in a doublly linked list that
 * supports iterators and a comperable interfacen
 *
 * @author   edt
 */

#ifndef __RESTURANTDATASTORE_H_INCL__
#define __RESTURANTDATASTORE_H_INCL__

#include "MyDblLinkList.h"
#include "Restaurant.h"
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

    //std::list<Restaurant> list;
    MyDblLinkList<Restaurant> list;

private:

    // Copy constructor
    RestaurantDataStore(const RestaurantDataStore& src);

    // Assignment operator
    RestaurantDataStore& operator=(const RestaurantDataStore& src);
};

#endif // __RESTURANTDATASTORE_H_INCL__
