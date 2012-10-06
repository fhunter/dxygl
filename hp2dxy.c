#include <stdio.h>

int
main (void)
{
  while (!feof (stdin))
    {
      putc (getc (stdin), stdout);
    };
  return 0;
};
