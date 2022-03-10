#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "SpellCheck.h"

SpellCheck::SpellCheck()
   : result()
{
}

void SpellCheck::equalLength( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size();
   vector words;

   findWords( words, dictionary, length );

   string buffer1;//same length with words
   string buffer2;//the words that from dictionary
   
   buffer2 = wordToCheck;
   
   for (size_t i = 0; i < words.size(); i++)//i is the place of words
   {
       buffer1 = words[i];
      for( size_t j = 0; j < length; j++ )
      {
          int counter = 0;
          for (size_t n = 0; n < length; n++)
          {
              if (n == j)
                  continue;
              if (buffer1[n] == buffer2[n])
                      counter++;
          }
          if (counter == length - 1)
              result.push_back(buffer1);
      }
   }
}

void SpellCheck::shorter( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() + 1;
   vector words;

   findWords( words, dictionary, length );

   string buffer;
   for (size_t i = 0; i < words.size(); i++)
   {
       buffer = words[i];
      for( size_t j = 0; j < length; j++ )
      {
          int counter = 0;
          for (size_t n = 0; n < length; n++)
          {
              if (n == j)
                  continue;
              if (n < j)
                  if (buffer[n] == wordToCheck[n])
                      counter++;
              if (n > j)
                  if (buffer[n] == wordToCheck[n - 1])
                      counter++;
          }
          if (counter == length - 1)
              result.push_back(buffer);
      }
   }
}

void SpellCheck::longer( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() - 1;
   vector words;

   findWords( words, dictionary, length );

   string buffer;

   for (size_t i = 0; i < words.size(); i++)
   {
       buffer = words[i];
      for( size_t j = 0; j < wordToCheck.size(); j++ )
      {
          int counter = 0;
          for (size_t n = 0; n < length + 1; n++)
          {
              if (n == j)
                  continue;
              if(n < j)
                  if (buffer[n] == wordToCheck[n])
                      counter++;
              if(n > j)
                  if (buffer[n] == wordToCheck[n - 1])
                      counter++;
          }
          if (counter == length)
              result.push_back(buffer);

      }

   }
}

void SpellCheck::findWords( vector &words, const vector &dictionary, size_t length )
{
   for( size_t i = 0; i < dictionary.size(); i++ )
       if (dictionary[i].size() == length) 
         words.push_back( dictionary[ i ] );
}

void SpellCheck::output()
{
   cout << "Similar legal words: ";
   cout << result[ 0 ].c_str();
   for( size_t i = 1; i < result.size(); i++ )
      cout << ", " << result[ i ].c_str();
   cout << endl << endl;
}

void SpellCheck::clear()
{
   result.clear();
}