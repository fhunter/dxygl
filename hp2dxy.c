#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HPGL_RES 0.025
#define PL_RES	0.1

float xscale = HPGL_RES/PL_RES;
float yscale = HPGL_RES/PL_RES;

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

int read_and_convert_coordinates(){
  float x=0,y=0;
  int ch;
  scanf("%f , %f",&x,&y);
  x=x*xscale;y=y*yscale;
  x=nearbyintf(x);y=nearbyintf(y);
  printf("%d,%d",(int)(x),(int)(y));
  ch=getchar();if(ch<0) return;
  while(isblank(ch)){
	 ch=getchar();
	if(ch<0) return;
  };
  if(ch==',') {
	printf(",");
	return 1;
  }else ungetc(ch, stdin);
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
	while(read_and_convert_coordinates()){
	};
        read_to_eoln(  );
        printf( "\n" );
        break;
      };
    case 'd':
    case 'D':{
        printf( "D" );
	while(read_and_convert_coordinates()){
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
