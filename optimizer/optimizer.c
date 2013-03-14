#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct point_2d
{
  float x;
  float y;
};

struct line_2d
{
  struct point_2d begin;
  struct point_2d end;
};

float distance( struct point_2d point1, struct point_2d point2 )
{
  return sqrt( pow( point1.x - point2.x, 2 ) +
               pow( point1.y - point2.y, 2 ) );
};

int main( void )
{
  struct line_2d *lines = NULL;
  int lines_count = 0;
  int i;
  while( !feof( stdin ) ) {
    //read_line();
    //parse_line();
    //if this_is_pen_down() store_next_line_point();
  };
  //Sort lines;
  //Output lines;
  for( i = 0; i < lines_count; i++ ) {
    //Output continuous pen down instruction
    //Output pen_up
  };
  //somehow output everything else :D
  free( lines );
  return 0;
};
