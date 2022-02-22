#include <iostream>
using std::cout;
using std::exit;

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
    if (count < 16)
    {
        mySize = count;
        for (int n = 0; n < count; n++)
            bx.buf[n] = ptr[n];
        bx.buf[count] = '\0';
    }
    else
    {
        mySize = count;
        
        while (myRes < count)//undone
            myRes += 16;
        
        bx.ptr = new value_type[myRes]();
        for (int n = 0; n < count; n++)
            bx.ptr[n] = ptr[n];
        if (count != myRes)
            bx.ptr[count] = '\0';
    }
}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    if (count < 16)
    {
        mySize = count;
        for (int n = 0; n < count; n++)
            bx.buf[n] = ch;
        bx.buf[count] = '\0';
    }
    else
    {
        mySize = count;
        while (myRes < count)//undone
            myRes += 16;
        
        bx.ptr = new value_type[myRes]();
        for (int n = 0; n < count; n++)
            bx.ptr[n] = ch;
        if (count != myRes)
            bx.ptr[count] = '\0';
    }
}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    if (right.size() < 16)
    {
        mySize = right.size();
        for (int n = 0; n < right.size(); n++)
            bx.buf[n] = right.at(n);
        bx.buf[right.size()] = '\0';
    }
    else
    {
        mySize = right.size();
        while (myRes < right.size())
            myRes += 16;        
        
        bx.ptr = new value_type[myRes]();
        for (int n = 0; n < right.size(); n++)
            bx.ptr[n] = right.at(n);
        if(right.size() != myRes)
            bx.ptr[right.size()] = '\0';
    }
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

string& string::assign( const string &right )
{
   if( this != &right )
   {
       if (right.size() < 16)
       {
           for (int n = 0; n < right.size(); n++)
               bx.buf[n] = right.myPtr()[n];
           bx.buf[right.size()] = '\0';
           mySize = right.size();
       }
       else
       {
//           bx.ptr = new value_type[];
           mySize = right.size();

       }

   }

   return *this;
}

bool string::equal( const string &right )
{
    return true;
}

string& string::erase( const size_type off, size_type count )
{
   if( off < mySize )
   {
           
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

string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::at( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::at( const size_type off ) const
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
    if (capacity() < 16)
    {
        if (newSize > capacity())
        {
            while (myRes < newSize)
            {
                if (myRes + 16 > myRes * 3 / 2)
                    myRes += 16;
                else
                    myRes * 3 / 2;
            }
            bx.ptr = new value_type[myRes]();
            for (int n = 0; n < mySize; n++)
                bx.ptr[n] = bx.buf[n];
            for (int n = mySize; n < newSize; n++)
                bx.ptr[n] = ch;
            bx.ptr[newSize] = '\0';
        }
        else
            bx.buf[newSize] = '\0';
        
        mySize = newSize;
    }
    else
    {
        if (newSize > capacity())
        {
            while (myRes < newSize)
            {
                if (myRes + 16 > myRes * 3 / 2)
                    myRes += 16;
                else
                    myRes * 3 / 2;
            }
            value_type* tempPtr = bx.ptr;
            bx.ptr = new value_type[myRes]();
            for (int n = 0; n < mySize; n++)
                bx.ptr[n] = tempPtr[n];
            for (int n = mySize; n < newSize; n++)
                bx.ptr[n] = ch;
            bx.ptr[newSize] = '\0';
            delete[] tempPtr;
        }
        else
            bx.buf[newSize] = '\0';

        mySize = newSize;
    }
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}