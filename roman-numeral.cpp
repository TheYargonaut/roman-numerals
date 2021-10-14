#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

constexpr char symbol[] = "IVXLCDM";
constexpr int len = strlen( symbol );
constexpr int maxVal = 3999;
constexpr char usage[] =
   "usage: roman NATURAL_NUMBER\n\tNATURAL_NUMBER less than 4000";

unsigned int intPow( unsigned int base, unsigned int p ) {
   if( !p ) { return 1; }
   unsigned int r = intPow( base * base, p / 2 );
   if( p % 2 ) {
      return base * r;
   } else {
      return r;
   }
}

string romanNumeral( unsigned int raw ) {
   ostringstream result;
   unsigned int value, under, quotient;
   char s;
   for( int i = len - 1; raw && i >= 0; i-- ) {
      value = under = intPow( 10, i/2 );
      s = symbol[ i ];
      if( i % 2 ) { value *= 5; } else { under /= 10; }
      quotient = raw / value;
      if( quotient ) {
         result << string( quotient, s );
         raw %= value;
      }
      if( raw && raw + under >= value ) {
         result << symbol[ ( i + i % 2 ) - 2 ] << s;
         raw -= value - under;
      }
   }
   return result.str();
}

bool argRangeCheck( const string arg ) {
   return arg.find_first_not_of( "0123456789" ) == string::npos &&
          arg.find_first_of( "123456789" ) != string::npos &&
          stoi( arg ) <= maxVal ;
}

int main( int argc, char ** argv ) {
   if( argc == 2 && argRangeCheck( argv[ 1 ] ) ) {
      cout << romanNumeral( stoi( argv[ 1 ] ) ) << endl;
   } else {
      cout << usage << endl;
   }
}
