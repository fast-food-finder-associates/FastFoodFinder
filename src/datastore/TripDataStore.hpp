/**
 * CS1D - Fast Food Associates
 *
 * Defines a data storage mechanism for User objects. These
 * objects are contained in a doublly linked list that supports
 * iterators and a comperable interfacen
 *
 * @author   edt
 */

#pragma once
#include <list>
<<<<<<< HEAD
#include <string>
=======
>>>>>>> master
#include "MyDblLinkList.hpp"
#include "Trip.hpp"

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

<<<<<<< HEAD
    void load(const string path);
    void save(const string path);

=======
>>>>>>> master
    //std::list<Trip> list;
    MyDblLinkList<Trip> list;

private:

    // Copy constructor
    TripDataStore(const TripDataStore& src);

    // Assignment operator
    TripDataStore& operator=(const TripDataStore& src);
};
