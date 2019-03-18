/**
 * CS1D - Fast Food Associates
 *
 * Definitionn of the Restaurant class that provides a means for
 * validating restaurants, string menu items and distances to
 * other restaurants
 *
 * @author   edt
 */

#pragma once

#include <vector>
#include <string>

using namespace std;

class MenuItem
{
friend class Restaurant;
friend class RestaurantDataStore;

public:
    MenuItem(const string &Name, const float &Price);

    virtual ~MenuItem();

    // Copy constructor
    MenuItem(const MenuItem& src);

    // Assignment operator
    MenuItem& operator=(const MenuItem& rhs);

    float GetPrice(void) const;
    void UpdatePrice(const float NewPrice);
    const string &GetName(void) const;
    void UpdateName(const string &NewName);
    bool IsDeleted(void) const;
    bool MarkDeleted(bool Delete);

    const MenuItem&FindbyNumber(int Number) const;

private:
    bool        m_bInitialized;
    int         m_nNumber;
    bool        m_bDeleted;
    string      m_MenuItemName;
    float       m_fMenuItemPrice;

    static int  sm_NextNumber;

    // private to prevent usage

    // Noarg constructor
    MenuItem();

    // used by database load only
    MenuItem(const int Number, const bool Deleted, const string &Name, const float &Price);

};
