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
#include "MyDblLinkList.hpp"
#include "User.hpp"

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

    void load(const string path);
    void save(const string path);

    //std::list<User> list;
    MyDblLinkList<User> list;
private:

    // Copy constructor
    UserDataStore(const UserDataStore& src);

    // Assignment operator
    UserDataStore& operator=(const UserDataStore& src);

};
