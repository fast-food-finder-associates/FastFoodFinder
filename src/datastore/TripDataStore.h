/**
 * CS1D - Fast Food Associates
 *
 * Implements a data storage mechanism for User objects. These
 * objects are contained in a doublly linked list that supports
 * iterators and a comperable interfacen
 *
 * @author   edt
 */

#ifndef __TRIPATASTORE_H_INCL__
#define __TRIPATASTORE_H_INCL__

#include <list>
#include "MyDblLinkList.h"
#include "Trip.h"

using namespace std;
using namespace nsMyDblLinkList;

class TripDataStore
{
public:
    // Constructor
    TripDataStore();

    // Destructor
    virtual ~TripDataStore();

    void printAsDebug(bool printeol, bool printcontent) const;

    //std::list<Trip> list;
    MyDblLinkList<Trip> list;

private:

    // Copy constructor
    TripDataStore(const TripDataStore& src);

    // Assignment operator
    TripDataStore& operator=(const TripDataStore& src);
};

#endif // __TRIPATASTORE_H_INCL__
