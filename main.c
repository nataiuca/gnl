#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int main()
{
   int fd = 0;
   char *line;

   fd = open("43_no_nl.txt", O_RDONLY);
   while ((line = get_next_line(fd)) != NULL)
   {
    printf("%s", line);
    free(line);
   }
   close(fd);
   return (0);
}
