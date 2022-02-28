#include <iostream>
using std::cout;
using std::endl;

#include "Polynomial.h" // include definition of class Polynomial

Polynomial::Polynomial( size_t n )
   : polynomial( n )
{
}

Polynomial::Polynomial( size_t n, int coefficient[], int exponent[] )
   : polynomial( n )
{
   for( size_t i = 0; i < n; i++ )
   {
      polynomial.at( i ).coef = coefficient[ i ];
      polynomial.at( i ).expon = exponent[ i ];
   }
}

Polynomial::Polynomial( const Polynomial &right )
   : polynomial( right.polynomial )
{
}

Polynomial::~Polynomial()
{
}

const Polynomial Polynomial::assign( const Polynomial &right )
{
   if( &right != this ) // avoid self-assignment
      polynomial.assign( right.polynomial );

   return *this; // enables x = y = z, for example
}

bool Polynomial::equal( const Polynomial &right )
{
   if( polynomial.size() != right.polynomial.size() )
      return false;

   for( size_t i = 0; i < polynomial.size(); i++ )
      if( polynomial.at( i ).coef != right.polynomial.at( i ).coef ||
          polynomial.at( i ).expon != right.polynomial.at( i ).expon )
         return false;

   return true;
}

void Polynomial::addition( const Polynomial &adder )
{
   Polynomial sum( polynomial.size() + adder.polynomial.size() );
   size_t i = 0;
   size_t j = 0;
   size_t k = 0;
   if (polynomial.size() == 0)
   {
       for (; k < adder.polynomial.size(); k++)
       {
           sum.polynomial.at(k).expon = adder.polynomial.at(k).expon;
           sum.polynomial.at(k).coef = adder.polynomial.at(k).coef;
       }
   }
   else if (adder.polynomial.size() == 0)
   {
       for (; k < polynomial.size(); k++)
       {
           sum.polynomial.at(k).expon = polynomial.at(k).expon;
           sum.polynomial.at(k).coef = polynomial.at(k).coef;
       }
   }
   else
   {
       while (1)
       {
           if (i == polynomial.size() && j == adder.polynomial.size())
               break;

           if (i == polynomial.size())
           {
               for (; j < adder.polynomial.size(); j++)
               {
                   sum.polynomial.at(k).expon = adder.polynomial.at(j).expon;
                   sum.polynomial.at(k).coef = adder.polynomial.at(j).coef;
                   k++;
               }
               break;
           }

           if (j == adder.polynomial.size())
           {
               for (; i < polynomial.size(); i++)
               {
                   sum.polynomial.at(k).expon = polynomial.at(i).expon;
                   sum.polynomial.at(k).coef = polynomial.at(i).coef;
                   k++;
               }
               break;
           }
           if (polynomial.at(i).expon == adder.polynomial.at(j).expon)
           {
               if (polynomial.at(i).coef + adder.polynomial.at(j).coef == 0)
               {
                   i++; j++;
                   continue;
               }
               sum.polynomial.at(k).expon = polynomial.at(i).expon;
               sum.polynomial.at(k).coef = polynomial.at(i).coef + adder.polynomial.at(j).coef;
               i++; j++; k++;
           }
           else if (polynomial.at(i).expon > adder.polynomial.at(j).expon)
           {
               sum.polynomial.at(k).expon = polynomial.at(i).expon;
               sum.polynomial.at(k).coef = polynomial.at(i).coef;
               i++; k++;
           }
           else
           {
               sum.polynomial.at(k).expon = adder.polynomial.at(j).expon;
               sum.polynomial.at(k).coef = adder.polynomial.at(j).coef;
               j++; k++;
           }
       }
   }

/*   for (int n = 0; n < sum.polynomial.size(); n++)
       cout << sum.polynomial.at(n).expon << "  ";
   cout << '\n';
   for (int n = 0; n < sum.polynomial.size(); n++)
       cout << sum.polynomial.at(n).coef << "  ";
   cout << '\n';*/

   if( sum.polynomial.size() != k )
      sum.polynomial.resize( k );

   polynomial.assign( sum.polynomial );

   if( !zero() && leadingCoef() == 0 )
      cout << "addend has leading zeroes!\n";
}

void Polynomial::subtraction( const Polynomial &subtrahend )
{
   Polynomial buffer( subtrahend.minus() );

   addition( buffer ); // minuend = minuend + buffer = minuend - subtrahend

   if( !zero() && leadingCoef() == 0 )
      cout << "minuend has leading zeroes!\n";
}

Polynomial Polynomial::multiplication( const Polynomial &multiplier ) const
{
   Polynomial product;
   Polynomial buffer( polynomial.size() );

   if (polynomial.size() != 0 && multiplier.polynomial.size() != 0)
   {
       for (int i = 0; i < multiplier.polynomial.size(); i++)
       {
            for (int j = 0; j < polynomial.size(); j++)
            {
                buffer.polynomial.at(j).coef = polynomial.at(j).coef * multiplier.polynomial.at(i).coef;
                buffer.polynomial.at(j).expon = polynomial.at(j).expon + multiplier.polynomial.at(i).expon;

            }
            product.addition(buffer);
        }
   }

   if( !product.zero() && product.leadingCoef() == 0 )
      cout << "product has leading zeroes!\n";

   return product;
}

Polynomial Polynomial::division( const Polynomial &divisor )
{
   Polynomial quotient;
   Polynomial remainder( *this );
   Polynomial monomial( 1 );
   
   while (remainder.polynomial.size() != 0 && remainder.polynomial.at(0).expon >= divisor.polynomial.at(0).expon)
   {
       monomial.polynomial.at(0).expon = remainder.polynomial.at(0).expon - divisor.polynomial.at(0).expon;
       monomial.polynomial.at(0).coef = remainder.polynomial.at(0).coef / divisor.polynomial.at(0).coef;

       remainder.subtraction(monomial.multiplication(divisor));
       quotient.addition(monomial);
   }


   if( !quotient.zero() && quotient.leadingCoef() == 0 )
      cout << "quotient has leading zeroes!\n";

   return quotient;
}

Polynomial Polynomial::modulus( const Polynomial &divisor )
{
   Polynomial quotient;
   Polynomial remainder( *this );
   Polynomial monomial( 1 );

   while (remainder.polynomial.size() != 0 && remainder.polynomial.at(0).expon >= divisor.polynomial.at(0).expon)
   {
       monomial.polynomial.at(0).expon = remainder.polynomial.at(0).expon - divisor.polynomial.at(0).expon;
       monomial.polynomial.at(0).coef = remainder.polynomial.at(0).coef / divisor.polynomial.at(0).coef;
       
       remainder.subtraction(monomial.multiplication(divisor));
       quotient.addition(monomial);
   }


   if( !remainder.zero() && remainder.leadingCoef() == 0 )
      cout << "remainder has leading zeroes!\n";

   return remainder;
}

void Polynomial::output()
{
   // the current polynomial is zero polynomial
   if( zero() )
      cout << 0;
   else
   {
      if( leadingCoef() < 0 )
         cout << "-" << -leadingCoef();
      else if( leadingCoef() > 0 )
         cout << leadingCoef();

      if( degree() > 0 )
      {
         if( degree() == 1 )
            cout << "x";
         else
            cout << "x^" << degree();
      }

      for( size_t i = 1; i < polynomial.size(); i++ )
      {
         if( polynomial.at( i ).coef < 0 )
            cout << " - " << -polynomial.at( i ).coef;
         else if( polynomial.at( i ).coef > 0 )
            cout << " + " << polynomial.at( i ).coef;

         if( polynomial.at( i ).expon > 0 )
         {
            if( polynomial.at( i ).expon == 1 )
               cout << "x";
            else
               cout << "x^" << polynomial.at( i ).expon;
         }
      }
   }

   cout << endl;
}

bool Polynomial::hasZeroTerm()
{
   if( !zero() )
      for( size_t i = 0; i < polynomial.size(); i++ )
         if( polynomial.at( i ).coef == 0 )
            return true;

   return false;
}

Polynomial Polynomial::minus() const
{
   Polynomial minus( polynomial.size() );
   for( size_t i = 0; i < minus.polynomial.size(); i++ )
   {
      minus.polynomial.at( i ).coef = -polynomial.at( i ).coef;
      minus.polynomial.at( i ).expon = polynomial.at( i ).expon;
   }

   return minus;
}

bool Polynomial::zero() const
{
   return polynomial.empty();
}

int Polynomial::degree() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().expon;
}

int Polynomial::leadingCoef() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().coef;
}