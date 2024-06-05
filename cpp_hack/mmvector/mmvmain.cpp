/*
Feladat: egy olyan vector implement�l�sa, ami addig elt�rolja minim�lis, ill. maxim�lis �rt�ket, am�g a kont�ner elemeit nem v�ltoztatjuk meg.
Ha a kont�ner elemei megv�ltoz(hat)nak, az elt�rolt minim�lis, ill. maxim�lis �rt�kek �rv�nytelenn� v�lnak, �s sz�ks�g eset�n �jrasz�m�tand�ak.
*/
#include <iostream>
#include "mmvec.h"
#include <algorithm>
#include <string>
#include "mmvec.h"

struct Limited
{

  int val;

public:

  static int cnt;

  Limited( int i = 0 ) : val( i ) { }

  int get() const
  {
    return val;
  }
  //bool operator<(const Limited &a, const Limited &b);
};

int Limited::cnt = 0;

bool operator<( const Limited& a, const Limited& b )
{
  ++Limited::cnt;
  return a.get() < b.get();
}

const int max = 1024;

int main()
{
  int yourMark = 1;
  //2-es
  MinMaxVector<char> mc;
  mc.push_back( 'h' ).push_back( 'e' ).push_back( 'l' ).push_back( 'l' ).push_back( 'o' );
  mc.push_back( 'w' ).push_back( 'o' ).push_back( 'r' ).push_back( 'l' ).push_back( 'd' );
  const MinMaxVector<char> cmc = mc;

  MinMaxVector<int> v;
  for( int i = 0; i < max; ++i )
  {
    v.push_back( i );
  }
  MinMaxVector<Limited> ml;
  ml.push_back( Limited( 2 ) );
  ml.push_back( Limited( 1 ) );
  ml.push_back( Limited( 4 ) );
  ml.push_back( Limited( 5 ) );


  if ( 'd' == mc.min() && 0 == v.min() && 1 == ml.min().get() )
  {
    int tmp = Limited::cnt;
    --v.at( 0 );

    if ( 4 == ml.size() && 
         -1 == v.min() && 
         1 == ml.min().get() &&
         tmp == Limited::cnt )
    {
      yourMark = cmc.size() / ml.max().get();
    }

  }

  // 3-as
  mc.at( 1 ) = 'a';
  if ( max - 1 == v.max() )
  {
    for( int i = 0; i < max; ++i )
    {
      if ( i % 2 == 0 )
      {
        --v[ i ];
      }
      else
      {
        ++v[ i ];
      }
    }
  }
  int tmp = Limited::cnt;
  if ( -2 == v.min() &&
      'a' == mc.min() &&
      'h' == cmc.at( 0 ) &&
      'w' == cmc.max() &&
       5 == ml.max().get() &&
       tmp == Limited::cnt )
  {
    yourMark = v[ ml.size() ];
  }
  
  // 4-es
  MinMaxVector<int>::iterator it = std::find( v.begin(), v.end(), 15 );
  if ( it != v.end() )
  {
    yourMark = std::count( mc.begin(), mc.end(), 'o' ) - v.min();
  }
  
  // 5-os
  for( MinMaxVector<int>::iterator i = v.begin(); i != v.end(); ++i )
  {
    *i = ml.max().get();
  }

  if ( ml.begin() != ml.end() &&
       ml.max().get() == v.max() &&
       tmp == Limited::cnt &&
       v.min() == v.max() )
  {
    yourMark = v.min();
  }
  //std::cout<<tmp<<" "<<Limited::cnt<<std::endl;
  /*
  */
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
