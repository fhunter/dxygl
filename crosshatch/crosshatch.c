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

long x=0,y=0;

int in_image(long width,long height){
  if((x>=0)&&(y>=0)&&(x<width)&&(y<width)){
    return 1;
  }else{
    return 0;
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

int main( int argc, char **argv )
{
  Imlib_Image image;
  long x, y;
  long width, height;

  int pen_state = PEN_UP;

  if( argc != 2 )
    exit( 1 );

  image = imlib_load_image( argv[1] );  //Загрузка изображения

  if( image ) {
    imlib_context_set_image( image );   //Считывание изображения
    width = imlib_image_get_width(  );  //Читаем ширину
    height = imlib_image_get_height(  );        //Читаем высоту
    printf( START_CMD );
    printf( UP_CMD "0,0" ENDER );
    pen_state = PEN_UP;

    printf( PS_CMD "1" ENDER );
    x = y = 0;
    for( y = 0; y < height; y++ ) {
      if(pen_state != PEN_UP) {
        printf( UP_CMD "%ld,%ld" ENDER, 0, y * A4_HEIGHT / height );
        pen_state = PEN_UP;
      };
      x=0;
      while(x<width){
        if( get_light( x, y, image ) < 127 ) {
          //This is dark
          printf( DN_CMD "%ld,%ld" ENDER, x * A4_WIDTH / width,
                  y * A4_HEIGHT / height );
          pen_state = PEN_DOWN;
          while( ( x < width ) && ( get_light( x, y, image ) < 127 ) ) {
            x++;
          };
          printf( UP_CMD "%ld,%ld" ENDER, x * A4_WIDTH / width,
                  y * A4_HEIGHT / height );
          pen_state = PEN_UP;
        };
	x++;
      };
      if(pen_state !=PEN_UP){
        printf(UP_CMD "%ld,%ld" ENDER, x*A4_WIDTH/width, y*A4_HEIGHT/height);
        pen_state = PEN_UP;
      };
    };
    printf( UP_CMD "0,0" ENDER );
    pen_state = PEN_UP;
  };

  return 0;
};
