#include <Imlib2.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
int get_light( long x, long y, Imlib_Image image )
{
  float hue, lightness, saturation;
  int alpha;
  imlib_image_query_pixel_hlsa( x, y, &hue, &lightness, &saturation,
                                &alpha );
  return ( int ) trunc( lightness * 255 );
};

long x = 0, y = 0;

int in_image( long width, long height )
{
  if( ( x >= 0 ) && ( y >= 0 ) && ( x < width ) && ( y < width ) ) {
    return 1;
  }
  else {
    return 0;
  };
};

void get_next_point( long width, long height )
{
  static int direction = 1;
  x += direction;
  if( x >= width ) {
    x -= direction;
    direction = -direction;
    y++;
  };
  if( x < 0 ) {
    x -= direction;
    direction = -direction;
    y++;
  };
  if( y >= height ) {
    x = -1;
    y = -1;
  };
};

#define PEN_UP	0
#define PEN_DOWN	1

#if defined(HPGL)
#define UP_CMD "PU"
#define DN_CMD "PD"
#define PS_CMD "SP"
#define ENDER	";\n"
#define START_CMD "IN"ENDER"IP"ENDER

#define A4_WIDTH	8400
#define A4_HEIGHT	11880
#else
#define UP_CMD "M"
#define DN_CMD "D"
#define PS_CMD "J"
#define ENDER	"\n"
#define START_CMD "H"ENDER"M0,0"ENDER

#define A4_WIDTH	950
#define A4_HEIGHT	1485
#endif

void pen_update( int pen_state, long width, long height )
{
  if( pen_state == PEN_DOWN ) {
    printf( DN_CMD "%ld,%ld" ENDER, x * A4_WIDTH / width,
            y * A4_HEIGHT / height );
  }
  else {
    printf( UP_CMD "%ld,%ld" ENDER, x * A4_WIDTH / width,
            y * A4_HEIGHT / height );
  };
};

int main( int argc, char **argv )
{
  Imlib_Image image;
  long width, height;

  int pen_state = PEN_UP;
  int light, old_light;

  if( argc != 2 )
    exit( 1 );

  image = imlib_load_image( argv[1] );  //Load image

  if( image ) {
    imlib_context_set_image( image );
    width = imlib_image_get_width(  );
    height = imlib_image_get_height(  );
    printf( START_CMD );
    printf( PS_CMD "1" ENDER );

    pen_state = PEN_UP;
    pen_update( pen_state, width, height );

    x = y = 0;
    light = old_light = ( get_light( 0, 0, image ) < 127 );
    while( ( x >= 0 ) && ( y >= 0 ) ) {
      light = ( get_light( x, y, image ) < 127 );
      if( old_light == light ) {
        if( light ) {
          pen_state = PEN_DOWN;
          pen_update( pen_state, width, height );
        }
        else {
          pen_state = PEN_UP;
          pen_update( pen_state, width, height );
        };
      };
      get_next_point( width, height );
      old_light = light;
    };
    x = y = 0;
    pen_state = PEN_UP;
    pen_update( pen_state, width, height );
  };

  return 0;
};
