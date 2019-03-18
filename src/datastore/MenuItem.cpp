/**
 * CS1D - Fast Food Associates
 *
 * Implemention of the MeniItem class that provides a means for
 * validating menu items, string menu items and prices
 *
 * @author   edt
 */


#include "MenuItem.hpp"
#include <string>
#include <ostream>
#include <iostream>

int MenuItem::sm_NextNumber = 1;

MenuItem::MenuItem(const string &Name, const float &Price)
    :m_MenuItemName(Name), m_fMenuItemPrice(Price)
{
    m_bDeleted = false;

    m_nNumber =  sm_NextNumber++;

    m_bInitialized = true;
}

MenuItem::~MenuItem()
{
}

float MenuItem::GetPrice(void) const
{
    return (m_fMenuItemPrice);
}

void MenuItem::UpdatePrice(const float NewPrice)
{
    m_fMenuItemPrice = NewPrice;
}

const string &MenuItem::GetName(void) const
{
    return m_MenuItemName;
}

void MenuItem::UpdateName(const string &NewName)
{
    m_MenuItemName = NewName;
}

bool MenuItem::IsDeleted(void) const
{
    return m_bDeleted;
}

bool MenuItem::MarkDeleted(bool Delete)
{
    m_bDeleted = Delete;
    return m_bDeleted;
}

const MenuItem&MenuItem::FindbyNumber(int Number) const
{
}

    // used by database load only
MenuItem::MenuItem(const int Number, const bool Deleted, const string &Name, const float &Price)
    :m_nNumber(Number), m_bDeleted(Deleted), m_MenuItemName(Name), m_fMenuItemPrice(Price)
{
    m_bInitialized = true;
}

MenuItem::MenuItem(const MenuItem& src)
    :m_nNumber(src.m_nNumber), m_bDeleted(src.m_bDeleted),
    m_MenuItemName(src.m_MenuItemName), m_fMenuItemPrice(src.m_fMenuItemPrice)
{
}

MenuItem& MenuItem::operator=(const MenuItem& rhs)
{
   if (this == &rhs)
   {
      return *this;
   }

   m_nNumber = rhs.m_nNumber;
   m_bDeleted = rhs.m_bDeleted;
   m_MenuItemName = rhs.m_MenuItemName;
   m_fMenuItemPrice = rhs.m_fMenuItemPrice;

   return *this;
}
