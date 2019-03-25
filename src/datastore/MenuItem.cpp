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

//! MenuItem default constructor
//!
//! \author edt (3/25/19)
MenuItem::~MenuItem()
{
}

//! MenuItem::GetNumber
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return int - number of this item
int MenuItem::GetNumber(void) const
{
    return m_nNumber;
}
//! MenuItem::GetPrice
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return float - price of item
float MenuItem::GetPrice(void) const
{
    return (m_fMenuItemPrice);
}

//! MenuItem::UpdatePrice
//!
//! \author edt (3/25/19)
//!
//! \param NewPrice - updated orice of item
void MenuItem::UpdatePrice(const float NewPrice)
{
    m_fMenuItemPrice = NewPrice;
}

//! MenuItem::GetName
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return const string&amp; Name of Item
const string &MenuItem::GetName(void) const
{
    return m_MenuItemName;
}

//! MenuItem::UpdateName
//!
//! \author edt (3/25/19)
//!
//! \param NewName - new name for item
void MenuItem::UpdateName(const string &NewName)
{
    m_MenuItemName = NewName;
}

//! MenuItem::IsDeleted
//!
//! \author edt (3/25/19)
//!
//! \param void 
//!
//! \return bool - 
bool MenuItem::IsDeleted(void) const
{
    return m_bDeleted;
}

//! MenuItem::MarkDeleted
//!
//! \author edt (3/25/19)
//!
//! \param Delete - true to mark item deleted
//!
//! \return bool - true if item is deleted and should not be used for new trips
bool MenuItem::MarkDeleted(bool Delete)
{
    m_bDeleted = Delete;
    return m_bDeleted;
}
 
//! MenuItem::MenuItem - used by TripDataStore only for loading datastore
//!
//! \author edt (3/25/19)
//!
//! \param Number - trip number
//! \param Deleted - true if item is deleted
//! \param Name - item name
//! \param Price - item price
MenuItem::MenuItem(const int Number, const bool Deleted, const string &Name, const float &Price)
    :m_nNumber(Number), m_bDeleted(Deleted), m_MenuItemName(Name), m_fMenuItemPrice(Price)
{
    m_bInitialized = true;
}

//! MenuItem::MenuItem - copy constructor
//!
//! \author edt (3/25/19)
//!
//! \param src - item to copy
MenuItem::MenuItem(const MenuItem& src)
    :m_nNumber(src.m_nNumber), m_bDeleted(src.m_bDeleted),
    m_MenuItemName(src.m_MenuItemName), m_fMenuItemPrice(src.m_fMenuItemPrice)
{
}

//! MenuItem::operator=
//!
//! \author edt (3/25/19)
//!
//! \param rhs - item to copy
//!
//! \return MenuItem&amp; 
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
