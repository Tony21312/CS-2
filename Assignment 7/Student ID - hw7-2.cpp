#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstring>
using std::strlen;

// list standard header
#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
   using nodePtr = ListNode *;

   nodePtr next; // successor node, or first element if head
   nodePtr prev; // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
      mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   explicit list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      if( count > 0 )
         for( size_type i = 0; i < count; ++i )
            //            insert( cend(), Ty() );
            push_back( Ty() );
   }

   list( const list &right )
      : myData()
   {
       myData.myHead = new node;
       myData.myHead->myVal = Ty();
       myData.myHead->prev = myData.myHead->next = myData.myHead;

       iterator it = right.myData.myHead->next;
       for (; it != right.myData.myHead; it = it->next)
           push_back(it->myVal);
   }

   ~list()
   {
      clear();
      delete myData.myHead;
   }

   list& operator=( const list &right )
   {
       if (this != &right)
       {
           while (myData.mySize > right.myData.mySize)
               pop_back();
           while (myData.mySize < right.myData.mySize)
               push_back(Ty());

           iterator it1 = myData.myHead->next;
           iterator it2 = right.myData.myHead->next;

           for (; it1 != myData.myHead; it1 = it1->next, it2 = it2->next)
               it1->myVal = it2->myVal;
       }


      return *this;
   }

   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   iterator end()
   {
      return iterator( myData.myHead );
   }

   void resize( size_type newSize )
   {
      if( myData.mySize < newSize ) // pad to make larger
      {
         size_type difference = newSize - myData.mySize;
         for( size_type i = 0; i < difference; i++ ) // create newSize - myData.mySize elements
            push_back( Ty() );
      }
      else
      {
         while( newSize < myData.mySize )
            pop_back();
      }
   }

   size_type size() const
   {
      return myData.mySize;
   }

   bool empty() const
   {
      return myData.mySize == 0;
   }

   reference front()
   {
      return myData.myHead->next->myVal;
   }

   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   void push_back( const Ty &val )
   {
       nodePtr temp = new node;
       temp->myVal = val;
       temp->next = myData.myHead;
       temp->prev = myData.myHead->prev;
       myData.myHead->prev->next = temp;
       myData.myHead->prev = temp;
       myData.mySize++;
   }

   void pop_back()
   {
      if( myData.mySize > 0 )
      {
          nodePtr temp = myData.myHead->prev;
          myData.myHead->prev = temp->prev;
          temp->prev->next = myData.myHead;
          myData.mySize--;
          delete temp;
      }
   }

   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
          while (myData.mySize > 0)
              pop_back();  
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( list< Ty > &left, list< Ty > &right )
{
    if (left.size() != right.size())
        return false;

    ListNode< Ty >* it1 = left.end()->prev;
    ListNode< Ty >* it2 = right.end()->prev;
    for (; it1 != left.end(); it1 = it1->prev, it2 = it2->prev)
        if (it1->myVal != it2->myVal)
            return false;
    
    return true;
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( list< Ty > &left, list< Ty > &right )
{
   return !( left == right );
}

#endif // LIST


// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type; 

   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   // constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const T &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   bool operator==( HugeInteger &right ); // less than or equal to

   bool operator<( HugeInteger &right );  // less than

   bool operator<=( HugeInteger &right ); // less than or equal to

   HugeInteger square( value_type powerTwo ); // the square of HugeInteger
   HugeInteger squareRoot( value_type powerTwo ); // the square root of HugeInteger

   bool isZero();           // return true if and only if all digits are zero
private:
   T integer;
}; // end class HugeInteger

#endif

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const T &integerToCopy )
   : integer( integerToCopy )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger &right )
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger &right )
{
    if (integer.size() != right.integer.size())
        return integer.size() < right.integer.size();
    
    typename T::iterator it1 = integer.end()->prev;
    typename T::iterator it2 = right.integer.end()->prev;

    for (; it1 != integer.end(); it1 = it1->prev, it2 = it2->prev)
        if (it1->myVal != it2->myVal)
            return it1->myVal < it2->myVal;
    return false;
} // end function operator<

// function that tests if one HugeInteger is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger &right )
{
   return ( *this == right || *this < right );
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_t squareSize = 2 * integer.size();
   HugeInteger square( squareSize );

   int integerSize = integer.size();

   typename T::iterator it1 = square.integer.begin();
   typename T::iterator it2 = integer.begin();
   typename T::iterator it3 = integer.begin();
   typename T::value_type* temp = new value_type[squareSize]();

   for (int i = 0; i < integerSize; i++, it2 = it2->next)
   {
       it3 = integer.begin();
       for (int j = 0; j < integerSize; j++, it3 = it3->next)
           temp[i + j] += it2->myVal * it3->myVal;
   }
   for (int n = 0; n < squareSize; n++)
       if (temp[n] >= powerTwo)
       {
           temp[n + 1] += temp[n] / powerTwo;
           temp[n] %= powerTwo;
       }
   
   for (int n = 0; n < squareSize; n++, it1 = it1->next)
       it1->myVal = temp[n];

   delete[] temp;

   it1 = square.integer.end()->prev;
   while (it1->myVal == 0)
   {
       it1 = it1->prev;
       square.integer.pop_back();
   }

   return square;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_type sqrtSize = ( integer.size() + 1 ) / 2;
   HugeInteger sqrt( sqrtSize );

   typename T::iterator it = sqrt.integer.end()->prev;

   for (int n = sqrtSize - 1; n >= 0; n--, it = it->prev)
   {
       int max = powerTwo - 1;
       int min = 0;

       int mid = (max + min) / 2;
       it->myVal = mid;

       while (min <= max)
       {
           mid = (max + min) / 2;
           it->myVal = mid;

           HugeInteger temp( sqrt.square (powerTwo) );
           
           if (temp == *this)
               return sqrt;
           if (*this < temp)
               max = mid - 1;
           else
               min = mid + 1;
       }
       it->myVal = min - 1;
   }
   return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   typename T::iterator it = integer.begin();
   for( ; it != integer.end(); it = it->next )
      if( it->myVal != 0 )
         return false;

   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::value_type numDigits = sizeof( typename T::value_type ) - 1;
   typename T::iterator it = hugeInteger.integer.end()->prev;
   output << it->myVal;
   for( it = it->prev; it != hugeInteger.integer.begin()->prev; it = it->prev )
      output << setw( numDigits ) << setfill( '0' ) << it->myVal;

   return output; // enables cout << x << y;
}

template< typename T >
void solution()
{
   char buf[ 1002 ];
   int numCases;
   cin >> numCases;
   for( int i = 1; i <= numCases; ++i )
   {
      cin >> buf;

      T digits[ 1001 ] = {};
      size_t last = strlen( buf ) - 1;
      for( size_t i = 0; i <= last; ++i )
         digits[ i ] = static_cast< T >( buf[ last - i ] ) - '0';

      list< T > integer;
      T powerTwo;
      size_t numDigits = sizeof( T ) - 1;
      for( size_t i = 0; i <= last; i += numDigits )
      {
         powerTwo = 1;
         T bigDigit = 0;
         for( size_t j = i; j < i + numDigits; ++j, powerTwo *= 10 )
            bigDigit += digits[ j ] * powerTwo;

         integer.push_back( bigDigit );
      }

      HugeInteger< list< T > > hugeInteger( integer );

      cout << hugeInteger.squareRoot( powerTwo ) << endl;

      if( i < numCases )
         cout << endl;
   }
}

int main()
{
   int choice = 1;
   switch( choice )
   {
   case 1:
      solution< long int >();
      break;
   case 2:
      solution< unsigned long int >();
      break;
   case 3:
      solution< long long int >();
      break;
   case 4:
      solution< unsigned long long int >();
      break;
   default:
      cout << "Program should never get here!";
   }

   system( "pause" );
}