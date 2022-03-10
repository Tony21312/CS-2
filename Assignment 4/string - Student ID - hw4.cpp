#include <iostream>
using std::cout;
using std::exit;

#include <algorithm>
using std::max;

#include "string.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = count;
   myRes = ( mySize / 16 ) * 16 + 15;

   if (myRes > 15)
       bx.ptr = new value_type[myRes + 1]();
   for (int n = 0; n < count; n++)
       myPtr()[n] = ptr[n];
   myPtr()[count] = '\0';
}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   mySize = count;
   if( count > 15 )
   {
      myRes = ( mySize / 16 ) * 16 + 15;

      if (myRes > 15)
          bx.ptr = new value_type[myRes + 1]();
   }
   for (int n = 0; n < count; n++)
       myPtr()[n] = ch;
   myPtr()[count] = '\0';
}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = right.mySize;
   myRes = ( mySize / 16 ) * 16 + 15;

   if (myRes > 15)
       bx.ptr = new value_type[myRes + 1]();
   
   for (int n = 0; n < right.mySize; n++)
       myPtr()[n] = right.myPtr()[n];
   myPtr()[right.mySize] = '\0';
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

//string& string::assign( const string &right )
string& string::operator=( const string &right )
{
   if( this != &right )
   {
      if( right.mySize > myRes )
      {
          
         delete[] bx.ptr;

         myRes = myRes * 3 / 2;
         if( myRes < ( right.mySize / 16 ) * 16 + 15 )
            myRes = ( right.mySize / 16 ) * 16 + 15;

         bx.ptr = new value_type[myRes + 1]();
      }
      for (int n = 0; n < right.mySize; n++)
          myPtr()[n] = right.myPtr()[n];
      myPtr()[right.mySize] = '\0';
      mySize = right.mySize;
   }

   return *this;
}

bool string::operator==( const string &right )
{
    if (capacity() != right.capacity())
        return 0;
    if (size() != right.size())
        return 0;
    for (int n = 0; n < mySize; n++)
        if (myPtr()[n] != right.myPtr()[n])
            return 0;
    return 1;
}

string& string::erase( const size_type off, size_type count )
{
   if( off < mySize )
   {
       int i = 0;
       for (int n = off; n + count < mySize; n++)
       {
           i++;
           myPtr()[n] = myPtr()[n + count];
       }
       mySize = off + i;
   }

   return *this;
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}
/*
string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}
*/
// Returns a reference to the character at position pos in the string.
string::reference string::operator[]( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

// Returns a reference to the character at position pos in the string.
string::const_reference string::operator[]( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

void string::push_back( char ch )
{
   resize( mySize + 1 );
   myPtr()[ mySize - 1 ] = ch;
}

void string::pop_back()
{
   if( mySize > 0 )
      --mySize;
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

void string::resize( const size_type newSize, const char ch )
{
   // determine new length, padding with ch elements as needed
   if( newSize > mySize )
   {
      if( newSize > myRes )
      {
         size_type newMyRes = myRes * 3 / 2;
         if( newMyRes < ( newSize / 16 ) * 16 + 15 )
            newMyRes = ( newSize / 16 ) * 16 + 15;

         pointer temp = new value_type[mySize]();
         for (int n = 0; n < mySize; n++)
             temp[n] = myPtr()[n];

         if (myRes > 15)
             delete[] bx.ptr;

         bx.ptr = new value_type[newMyRes + 1]();
         for (int n = 0; n < mySize; n++)
             bx.ptr[n] = temp[n];
         delete[] temp;
         myRes = newMyRes;
      }
      for (int n = mySize; n < newSize; n++)
          myPtr()[n] = ch;

   }
   myPtr()[newSize] = '\0';

   mySize = newSize;

}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}