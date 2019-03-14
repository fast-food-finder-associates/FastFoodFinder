// --------------------------------------------------------------------------
// Copyright Eugene Dale Tyler 2018 under the BSD license. All rights Reserved
//
// --------------------------------------------------------------------------

#pragma once

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ostream>


using namespace std;

namespace nsMyDblLinkList
{

template<typename NT>
struct Node
{
    NT data;
    Node * next;
    Node * prev;
    void printAsDebug(bool printeol, bool printcontent) const;
    void print(bool printeol = true) const;
    Node(const NT& v = NT(), Node* p = 0, Node* n = 0) : prev{p}, next{n}, data{v}  { }
};

//! printAsDebug - prints internal information about node
//!
//! \author edt (4/5/18)
//!
//! \param printeol - true=output one line to console, false=print data on separate lines
//! \param printcontent - true= print elememnt data, if any
template <typename NT>
void Node<NT>::printAsDebug(bool printeol, bool printcontent) const
{
    cout << " Node ObjAddr:" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec;
    if (printeol)
    {
        cout << endl;
    }
    cout << " Prev.Node:" << std::hex << std::uppercase << "0x" << (unsigned long long)prev << std::nouppercase << std::dec;
    if (printeol)
    {
        cout << endl;
    }
    cout << " Next.Node:" << std::hex << std::uppercase << "0x" << (unsigned long long)next << std::nouppercase << std::dec;
    if (printeol)
    {
        cout << endl;
    }
    if (printcontent)
    {
        cout << " Value:";
        cout << " " << data;
        if (printeol)
        {
            cout << endl;
        }
    }
}

//! print - prints node content
//!
//! \author edt (4/5/18)
//!
//! \param printeol - true=output one line to console, false=print data on separate lines
//! \param printcontent - true= print elememnt data, if any
template <typename NT>
void Node<NT>::print(bool printeol) const
{
    cout << " " << data;
    if (printeol)
    {
        cout << endl;
    }
}

template<typename Elem>
class MyDblLinkList
{
public:
    enum ErrorType
    {
        INVALID_POSITION = 100,
        LIST_EMPTY = 200,
        LINKS_INVALID = 300,
    };
    class iterator;         // forward declaration of member type: class iterator
    class const_iterator;   // forward declaration of member type: class const_iterator

private:
    unsigned long m_nElements;
    Node<Elem> *m_pFirstElement;
    Node<Elem> *m_pLastElement;

public:
    // Constructor
    MyDblLinkList();

    // Destructor
    virtual ~MyDblLinkList();

    // Copy constructor
    MyDblLinkList(const MyDblLinkList& src);

    // Assignment operator
    MyDblLinkList& operator=(const MyDblLinkList& src);

    void push_back (const Elem& val);
    Elem &front(void) const;
    void pop_front(void);
    Elem &back(void) const;
    void pop_back(void);
    unsigned long size(void) const;
    bool isEmpty(void) const;

    void insert(const Elem &data, int position);
    void erase(int position);
    void addSorted(const Elem data);

    Elem& operator[] (int position);
    const Elem& operator[] (int position) const;

    void printAsDebug(bool printeol = true, bool printcontent = false) const;
    void print(bool printeol = true) const;
    bool validate(void) const;

    iterator begin();   // iterator to first element
    iterator end();     // iterator to one beyond last element

    // add missing const iterators begin, end here
    const_iterator begin() const;   // iterator to first element - elements cannot be modified
    const_iterator end() const;     // iterator to one beyond last element - elements cannot be modified
};

// Constructor implementation
template<typename Elem>
MyDblLinkList<Elem>::MyDblLinkList()
{
    m_nElements = 0;
    m_pFirstElement = m_pLastElement = nullptr;
}

// Destructor implementation
template <typename Elem>
MyDblLinkList<Elem>::~MyDblLinkList()
{
    Node<Elem> *np = m_pFirstElement;
    
    while (np != nullptr)
    {
        Node<Elem> *temp = np->next;
        delete np;
        np = temp;
    }
}

//! Copy Contructor
//!
//! \author edt (4/5/18)
//!
//! \param src - list being copied from
template <typename Elem>
MyDblLinkList<Elem>::MyDblLinkList(const MyDblLinkList<Elem>& src)
{
    m_nElements = 0;
    m_pFirstElement = m_pLastElement = nullptr;

    Node<Elem> *np = src.m_pFirstElement;
    
    while (np != nullptr)
    {
        m_nElements++;
        Node<Elem> *pp;
        Node<Elem> *pNewNode = new Node<Elem>;
        pNewNode->data = np->data;  // copy the payload using copy constructor if needed
        pNewNode->next = nullptr;
        if (m_pFirstElement == nullptr)
        {
            m_pFirstElement = pNewNode;
            pp = m_pFirstElement;
            pNewNode->prev = nullptr;
        }
        else
        {
            pp->next = pNewNode;
            pNewNode->prev = pp;
            m_pLastElement = pNewNode;
            pp = m_pLastElement;
        }
        np = np->next;
    }
}

//! Copy Assignment Operator= - copies the lesser of source queue elements or destination size of queue
//!
//! \author edt (4/5/18)
//!
//! \param rhs - queue being assigned from
//!
//! \return MyDblLinkList&amp; 
template <typename Elem>
MyDblLinkList<Elem>& MyDblLinkList<Elem>::operator=(const MyDblLinkList<Elem>& rhs)
{
   if (this == &rhs) {
      return *this;
   }

   // delete all nodes associated with the destination of the copy
   Node<Elem> *np = m_pFirstElement;

   while (np != nullptr)
   {
       Node<Elem> *temp = np->next;
       delete np;
       np = temp;
   }

   m_nElements = 0;
   m_pFirstElement = m_pLastElement = nullptr;

   np = rhs.m_pFirstElement;

   while (np != nullptr)
   {
       m_nElements++;
       Node<Elem> *pp;
       Node<Elem> * pNewNode = new Node<Elem>;
       pNewNode->data = np->data;  // copy the payload using copy constructor if needed
       pNewNode->next = nullptr;
       if (m_pFirstElement == nullptr)
       {
           m_pFirstElement = m_pLastElement = pNewNode;
           pp = m_pFirstElement;
           pNewNode->prev = nullptr;
       }
       else
       {
           pp->next = pNewNode;
           pNewNode->prev = pp;
           m_pLastElement = pNewNode;
           pp = m_pLastElement;
       }
       np = np->next;
   }

   return *this;
}

//! add an element at end, if space available
//!
//! \author edt (4/5/18)
//!
//! \param data - element content to add
//!
//! \return void
template <typename Elem>
void MyDblLinkList<Elem>::push_back(const Elem &data)
{
    Node<Elem> * pNewNode = new Node<Elem>;
    pNewNode->data = data;  // copy the payload using copy constructor if needed
    pNewNode->next = nullptr;

    m_nElements++;
    if (m_pFirstElement == nullptr)
    {
        m_pFirstElement = m_pLastElement = pNewNode;
        pNewNode->prev = nullptr;
    }
    else
    {
        m_pLastElement->next = pNewNode;
        pNewNode->prev = m_pLastElement;
        m_pLastElement = pNewNode;
    }
}

//! front - returns content of first element in queue, if any
//!
//! \author edt (4/5/18)
//!
//! \return refernce to first list elememnt or throws exception if empty
template <typename Elem>
Elem &MyDblLinkList<Elem>::front(void) const
{
    if (isEmpty())
    {
        throw LIST_EMPTY;
    }

    return m_pFirstElement->data;
}

//! pop_front - remove the first element on the queue, if any
//!
//! \author edt (4/5/18)
//!
//! \param void 
//!
//! \return void
template <typename Elem>
void MyDblLinkList<Elem>::pop_front(void)
{
    if (isEmpty())
    {
        throw LIST_EMPTY;
    }

    Node<Elem> *np = m_pFirstElement;

    if (np->next == nullptr)
    {
        // list has only one element
        delete np;
        m_nElements = 0;
        m_pFirstElement = m_pLastElement = nullptr;
    }
    else
    {
        // make the second element the first element
        m_pFirstElement = np->next;
        m_pFirstElement->prev = nullptr;
        delete np;
        m_nElements--;
    }
}

//! back - returns content of last element in queue, if any
//!
//! \author edt (4/5/18)
//!
//! \return refernce to last list elememnt or throws exception if empty
template <typename Elem>
Elem &MyDblLinkList<Elem>::back(void) const
{
    if (isEmpty())
    {
        throw LIST_EMPTY;
    }

    return *m_pLastElement;
}

//! pop_back - remove the lst element on the queue, if any
//!
//! \author edt (4/5/18)
//!
//! \param void 
//!
//! \return void
template <typename Elem>
void MyDblLinkList<Elem>::pop_back(void)
{
    if (isEmpty())
    {
        throw LIST_EMPTY;
    }

    Node<Elem> *np = m_pLastElement;

    if (np->prev == nullptr)
    {
        // list has only one element
        delete np;
        m_nElements = 0;
        m_pFirstElement = m_pLastElement = nullptr;
    }
    else
    {
        // make the second to last element the last element
        m_pLastElement = np->prev;
        m_pLastElement->next = nullptr;
        delete np;
        m_nElements--;
    }
}

//! overload subscript operator - returns data at position soecified
//!
//! \author edt (4/26/18)
//!
//! \param position - node number to return content
//!
//! \return reference to data at specified postion
template <typename Elem>
Elem& MyDblLinkList<Elem>::operator[] (int position)
{
    if ( (position < 0) || (position >= (int)m_nElements) )
    {
        throw INVALID_POSITION;
    }

    if (position == 0)
    {
        return m_pFirstElement->data;
    }
    else if (position == (int)m_nElements)
    {
        return m_pLastElement->data;
    }
    else
    {
        unsigned long curelem = position;
        Node<Elem> *np = m_pFirstElement;
        while (curelem-- != 0)
        {
            // scan list until desired element found
            np = np->next;
        }
        return np->data;
    }
}


//! overload subscript operator - returns data at position soecified
//!
//! \author edt (4/26/18)
//!
//! \param position - node number to return content
//!
//! \return const reference to data at specified postion
template <typename Elem>
const Elem& MyDblLinkList<Elem>::operator[] (int position) const
{
    if ( (position < 0) || (position >= m_nElements) )
    {
        throw INVALID_POSITION;
    }

    if (position == 0)
    {
        return m_pFirstElement->data;
    }
    else if (position == m_nElements)
    {
        return m_pLastElement->data;
    }
    else
    {
        unsigned long curelem = position;
        Node<Elem> *np = m_pFirstElement;
        while (curelem-- != 0)
        {
            // scan list until desired element found
            np = np->next;
        }
        return np->data;
    }
}

//! size - return maximum number of elements in queue
//!
//! \author edt (4/5/18)
//!
//! \param void 
//!
//! \return unsigned long
template <typename Elem>
unsigned long MyDblLinkList<Elem>::size(void) const
{
    return m_nElements;
}

//! isEmpty - return true if queue empty
//!
//! \author edt (4/5/18)
//!
//! \param void 
//!
//! \return bool - true if queue empty, else false
template <typename Elem>
bool MyDblLinkList<Elem>::isEmpty(void) const
{
    return ( m_pFirstElement == nullptr );
}

//! insert element in list before specified element
//!
//! \author edt (4/25/18)
//!
//! \param data 
//! \param position 
//!
//! \return void
template <typename Elem>
void MyDblLinkList<Elem>::insert(const Elem &data, int position)
{
    if ( (position < 0) || (position > ((int)m_nElements + 1)) )
    {
        throw INVALID_POSITION;
    }

    m_nElements++;

    Node<Elem> * pNewNode = new Node<Elem>;
    pNewNode->data = data;  // copy the payload using copy constructor if needed
    Node<Elem> *np = m_pFirstElement;

    if (position == 0)
    {
        // insert at head of list
        pNewNode->next = np;
        pNewNode->prev = nullptr;
        np->prev = pNewNode;
    }
    else if (position == ((int)m_nElements + 1))
    {
        // insert at end of list (before imaginary element past end of list
        pNewNode->next = nullptr;
        pNewNode->prev = m_pLastElement;
        m_pLastElement->next = pNewNode;
    }
    else
    {
        unsigned long curelem = position;
        if ( (position < 0) || (position >= (int)m_nElements) )
        {
            throw INVALID_POSITION;
        }
        while (curelem-- != 0)
        {
            // scan list until desired element found
            np = np->next;
        }
        // insert before specified element
        pNewNode->next = np;
        pNewNode->prev = np->prev;
        np->prev->next = pNewNode;
        np->prev = pNewNode;
    }
}

//! erases list element at position specified
//!
//! \author edt (4/25/18)
//!
//! \param position - element number to erase
//!
//! \return void
template <typename Elem>
void MyDblLinkList<Elem>::erase(int position)
{
    if ( (position < 0) || (position >= (int)m_nElements) )
    {
        throw INVALID_POSITION;
    }

    m_nElements--;

    if (position == 0)
    {
        pop_front();
    }
    else if (position == (int)m_nElements)
    {
        Node<Elem> *temp = m_pLastElement->prev;
        delete m_pLastElement;
        m_pLastElement = temp;
    }
    else
    {
        unsigned long curelem = position;
        Node<Elem> *np = m_pFirstElement;
        while (curelem-- != 0)
        {
            // scan list until desired element found
            np = np->next;
        }
        np->next->prev = np->prev;
        np->prev->next = np->next;
        delete np;
    }
}

//! addSorted - adds element to a sorted list
//!
//! \author edt (4/26/18)
//!
//! \param data 
template <typename Elem>
void MyDblLinkList<Elem>::addSorted(const Elem data)
{
    m_nElements++;

    Node<Elem> * pNewNode = new Node<Elem>;
    pNewNode->data = data;  // copy the payload using copy constructor if needed
    Node<Elem> *np = m_pFirstElement;

    if (np == nullptr)
    {
        // insert at head of list
        pNewNode->next = nullptr;
        pNewNode->prev = nullptr;
        m_pFirstElement = pNewNode;
        m_pLastElement = pNewNode;

    }
    else
    {
        while (np != nullptr)
        {
            // scan list until desired element found
            if (np->data >= data)
            {
                break; // add the new element here
            }
            np = np->next;
        }
        if (np != nullptr)
        {
            // insert before specified element
            pNewNode->next = np;
            pNewNode->prev = np->prev;
            if (np == m_pFirstElement)
            {
                // place this element at first position
                m_pFirstElement = pNewNode;
            }
            else
            {
                np->prev->next = pNewNode;
            }
            np->prev = pNewNode;
        }
        else
        {
            // insert at end of list
            pNewNode->next = nullptr;
            pNewNode->prev = m_pLastElement;
            m_pLastElement->next = pNewNode;
            m_pLastElement = pNewNode;
        }
    }
}


//! printAsDebug - prints internal information about list and nodes
//!
//! \author edt (4/5/18)
//!
//! \param printeol - true=output one line to console, false=print data on separate lines
//! \param printcontent - true= print elememnt data, if any
template <typename Elem>
void MyDblLinkList<Elem>::printAsDebug(bool printeol, bool printcontent) const
{
    cout << "ObjAddr:" << std::hex << std::uppercase << "0x" << (unsigned long long)this << std::nouppercase << std::dec;
    if (printeol)
    {
        cout << endl;
    }
    cout << " First Element:" << std::hex << std::uppercase << "0x" << (unsigned long long)m_pFirstElement << std::nouppercase << std::dec;
    if (printeol)
    {
        cout << endl;
    }
    cout << " Last Element:" << std::hex << std::uppercase << "0x" << (unsigned long long)m_pLastElement << std::nouppercase << std::dec;
    if (printeol)
    {
        cout << endl;
    }
    cout << " Empty:" << isEmpty();
    if (printeol)
    {
        cout << endl;
    }
    cout << " MaxSize:" << size();
    if (printeol)
    {
        cout << endl;
    }
    if (printcontent)
    {
        cout << " Data:";
        if (isEmpty())
        {
            cout << "None";
            return;
        }
        Node<Elem> *np = m_pFirstElement;
        while (np != nullptr)
        {
            np->printAsDebug(printeol, printcontent);
            np = np->next;
        }
    }
}


//! print - prints list and nodes
//!
//! \author edt (4/5/18)
//!
//! \param printeol - true=output one line to console, false=print data on separate lines
template <typename Elem>
void MyDblLinkList<Elem>::print(bool printeol) const
{
    cout << " Data:";
    if (isEmpty())
    {
        cout << "None";
        return;
    }
    Node<Elem> *np = m_pFirstElement;
    while (np != nullptr)
    {
        np->print(printeol);
        np = np->next;
    }
}

//! validate - checks forward and backward links, node count and first/last pointers
//!
//! \author edt (4/26/18)
//!
//! \param void 
//!
//! \return bool - trtue if all links consistant, false if an error exists 
template <typename Elem>
bool MyDblLinkList<Elem>::validate(void) const
{
    if ( ( (m_pFirstElement == nullptr) && (m_pLastElement != nullptr) ) ||
         ( (m_pFirstElement != nullptr) && (m_pLastElement == nullptr) ) ||
         ( (m_pFirstElement == nullptr) && (m_pLastElement != nullptr) && (m_nElements != 0) ) ||
         ( (m_pFirstElement != nullptr) && (m_pFirstElement->prev != nullptr) ) ||
         ( (m_pLastElement != nullptr) && (m_pLastElement->next != nullptr) ) )
    {
        return false;
    }

    int nodecnt = 0;

    Node<Elem> *np = m_pFirstElement;
    if (np != nullptr)
    {
        np = np->next; // start at second element, if any
        nodecnt++;
        while (np != nullptr)
        {
            if ( (np->prev->next != np) || ( (np != m_pLastElement) && (np->next->prev != np) ) )
            {
                return false;
            }
            np = np->next;
            nodecnt++;
        }
    }

    if (nodecnt != (int)m_nElements)
    {
        return false;
    }
    return true;
}

//-------------------------------------------------------------------
template<typename Elem>
class MyDblLinkList<Elem>::iterator // definition for class iterator
{
    Node<Elem>* curr;   // current node
public:
    iterator(Node<Elem>* p) : curr{p} { }
    iterator& operator++() // forward - NOTE: Preincrement operator
    {
        curr = curr->next;
        return *this;
    }
    iterator& operator--() // backwards - NOTE: Preincrement operator
    {
        curr = curr->prev;
        return *this;
    }
    iterator operator++(int)  // Post increment
    {
        iterator tmp(*this);
        this->operator++(); // Call pre-increment on this.
        return tmp;
    }
    Elem& operator*() // get value (dereference)
    {
        return curr->data;
    }

    bool operator==(const iterator& rhs) const // lhs, rhs iterators point to the same node (equal)
    {
        return (curr == rhs.curr);
    }
    bool operator!=(const iterator& rhs) const // lhs, rhs iterators do not point to the same node (not equal)
    {
        return(curr != rhs.curr);
    }
};

//---------------------------------------------------------------------------
//-- Iteratators ------------------------------------------------------------
//---------------------------------------------------------------------------

template<typename Elem>
class MyDblLinkList<Elem>::const_iterator // definition for class const_iterator
{
    const Node<Elem>* curr;   // current node
                              // node pointed to by curr is immutable (i.e. can't be changed)
                              // fine to modify curr pointer itself (i.e. pointer value stored in curr)
                              // refer to const correctness reading
public:
;
    // add missing constructor, overloaded ++, --, *, ==, != operators here
    const_iterator(Node<Elem>* p) : curr{p} { }
    iterator& operator++() // forward - NOTE: Preincrement operator
    {
        curr = curr->next;
    }
    const_iterator& operator--() // backwards - NOTE: Preincrement operator
    {
        curr = curr->prev;
        return *this;
    }
    const Elem& operator*() // get value (dereference)
    {
        return (*curr);
    }

    bool operator==(const iterator& rhs) const // lhs, rhs iterators point to the same node (equal)
    {
        return (curr == rhs.curr);
    }

    bool operator!=(const iterator& rhs) const // lhs, rhs iterators do not point to the same node (not equal)
    {
        return(curr != rhs.curr);
    }
};

//------------------------------------------------------------------------------

template<typename Elem>
typename MyDblLinkList<Elem>::iterator MyDblLinkList<Elem>::begin()  // iterator to first element
{
    return iterator(m_pFirstElement);
}

template<typename Elem>
typename MyDblLinkList<Elem>::const_iterator MyDblLinkList<Elem>::begin() const // iterator to first element
{
    return iterator(m_pFirstElement);
}

//------------------------------------------------------------------------------

template<typename Elem>
typename MyDblLinkList<Elem>::iterator MyDblLinkList<Elem>::end() // iterator to one beyond last element
{
    return iterator(m_pLastElement->next);
}

// constant iterator to last element
template<typename Elem>
typename MyDblLinkList<Elem>::const_iterator MyDblLinkList<Elem>::end() const // iterator to one beyond last element
{
    return iterator(m_pLastElement->next);
}


//
// low algorithms adapted from Chapter 20.1, 20.4
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//


// implement templated low algorithm heretemplate<typename Elem>
template<typename iterator>
iterator low(iterator first, iterator last)
{
    if (first == last)
    {
        // empty list - must not defererence any iterator
        return last;
    }
    iterator lowest = first;
    while (first != last)
    {
        if (*first < *lowest)
        {
            lowest = first;
        }
        ++first;
    }
    return lowest;
}

template<typename InputIterator, typename Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
    // find the first element in [first,last) that satisfies predicate
{
    while ( (first != last) && !(pred(*first)) )
    {
        ++first;
    }
    // ...        // temp, replace when defining function
    return first;
}

} /* namespace */
