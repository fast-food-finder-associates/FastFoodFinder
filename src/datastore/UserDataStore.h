/**
 * CS1D - Fast Food Associates
 *
 * Implements a data storage mechanism for User objects. These
 * objects are contained in a doublly linked list that supports
 * iterators and a comperable interfacen
 * 
 * @author   edt
 */

#ifndef __USERDATASTORE_H_INCL__
#define __USERDATASTORE_H_INCL__

#include <list>
#include "MyDblLinkList.h"
#include "User.h"

using namespace std;
using namespace nsMyDblLinkList;

class UserDataStore
{
public:
    // Constructor
    UserDataStore();

    // Destructor
    virtual ~UserDataStore();

    void printAsDebug(bool printeol, bool printcontent) const;

    //std::list<User> list;
    MyDblLinkList<User> list;
private:

    // Copy constructor
    UserDataStore(const UserDataStore& src);

    // Assignment operator
    UserDataStore& operator=(const UserDataStore& src);

};

#endif // __USERDATASTORE_H_INCL__
