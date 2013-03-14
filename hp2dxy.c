#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define HPGL_RES 0.025
#define PL_RES	0.1
enum
{ PEN_DOWN = 0, PEN_UP };

float xscale = HPGL_RES / PL_RES;
float yscale = HPGL_RES / PL_RES;
int pen_state = PEN_UP;

void read_to_eoln(  )
{
  //This is temporary and wrong
  int ch;
  ch = getchar(  );
  if( ch < 0 )
    return;
  while( ( ch != '\n' ) && ( ch != '\r' ) && ( ch != ';' ) ) {
    ch = getchar(  );
    if( ch < 0 )
      return;
  };
};

int read_pen_color(  )
{
  int color = 0;
  int ch;
  ch = getchar(  );
  while( ( ch >= 0 ) && isdigit( ch ) ) {
    color *= 10;
    color = color + ( ch - '0' );
    ch = getchar(  );
  };
  ungetc( ch, stdin );
  return color;
};

int read_and_convert_coordinates(  )
{
  float x = 0, y = 0;
  int ch;
  int count = 0;
  count = scanf( "%f , %f", &x, &y );
  x = x * xscale;
  y = y * yscale;
  x = nearbyintf( x );
  y = nearbyintf( y );
  if( count == 0 )
    return 0;
  printf( "%d,%d", ( int ) ( x ), ( int ) ( y ) );
  ch = getchar(  );
  if( ch < 0 )
    return 0;
  while( isblank( ch ) ) {
    ch = getchar(  );
    if( ch < 0 )
      return 0;
  };
  if( ch == ',' ) {
    printf( "," );
    return 1;
  }
  else
    ungetc( ch, stdin );
  return 0;
};

void analise_i(  )
{
  int ch;
  ch = getchar(  );
  switch ( ch ) {
    case 'n':
    case 'N':{
        printf( "H\n" );
        read_to_eoln(  );
        break;
      };
    default:{
        read_to_eoln(  );
        printf( "Unrecognised token\n" );
        break;
      };
  };
};

void analise_p(  )
{
  int ch;
  ch = getchar(  );
  switch ( ch ) {
    case 'u':
    case 'U':{
        printf( "M" );
        pen_state = PEN_UP;
        while( read_and_convert_coordinates(  ) ) {
        };
        read_to_eoln(  );
        printf( "\n" );
        break;
      };
    case 'd':
    case 'D':{
        printf( "D" );
        pen_state = PEN_DOWN;
        while( read_and_convert_coordinates(  ) ) {
        };
        read_to_eoln(  );
        printf( "\n" );
        break;
      };
    case 'A':
    case 'a':{
        switch ( pen_state ) {
          case PEN_UP:
            printf( "M" );
            break;
          case PEN_DOWN:
            printf( "D" );
            break;
        };
        while( read_and_convert_coordinates(  ) ) {
        };
        read_to_eoln(  );
        printf( "\n" );
        break;
      };
    default:{
        printf( "Unrecognised token\n" );
        read_to_eoln(  );
        break;
      }
  };
};

void analise_l(  )
{
  int ch;
  ch = getchar(  );
  switch ( ch ) {
    case 'B':
    case 'b':{
//FIXME: TBD
        printf( "LB command\n" );
        read_to_eoln(  );
        break;
      };
    default:{
        printf( "Unrecognised token\n" );
        read_to_eoln(  );
        break;
      };
  };
};

void analise_d(  )
{
  int ch;
  ch = getchar(  );
  switch ( ch ) {
    case 'I':
    case 'i':{
//FIXME: TBD
        printf( "DI command\n" );
        read_to_eoln(  );
        break;
      };
    default:{
        printf( "Unrecognised token\n" );
        read_to_eoln(  );
        break;
      };
  };
};

void analise_s(  )
{
  int ch;
  ch = getchar(  );
  switch ( ch ) {
    case 'P':
    case 'p':{
        printf( "J%d\n", read_pen_color(  ) );
        read_to_eoln(  );
        break;
      };
    case 'C':
    case 'c':{
//FIXME: TBD
        printf( "SC command\n" );
        read_to_eoln(  );
        break;
      };
    case 'R':
    case 'r':{
//FIXME: TBD
        printf( "SR command\n" );
        read_to_eoln(  );
        break;
      };
    default:{
        read_to_eoln(  );
        printf( "Unrecognised token\n" );
      };
  }
};

int main( void )
{
  int ch;
  while( ( ch = getchar(  ) ) >= 0 ) {
    switch ( ch ) {
      case 'I':
      case 'i':{
          analise_i(  );
          break;
        };
      case 'P':
      case 'p':{
          analise_p(  );
          break;
        };
      case 'S':
      case 's':{
          analise_s(  );
          break;
        };
      case 'D':
      case 'd':{
          analise_d(  );
          break;
        };
      case 'L':
      case 'l':{
          analise_l(  );
          break;
        };
      case ';':
      case '\n':
      case '\r':
      case ' ':
      case '\t':
        continue;
      default:{
          fprintf( stderr, "Unrecognised token\n" );
          read_to_eoln(  );
        }

    };
  };
  return 0;
};
