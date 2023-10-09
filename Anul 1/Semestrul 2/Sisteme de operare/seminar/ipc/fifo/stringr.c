#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
  int fd, l;

  char arr2[80];

  char *myfifo = argv[1];

  fd = open (myfifo, O_RDONLY);

  if (fd < 0)
    {
      perror ("Error opening fifo.\n");
      exit (2);
    }

  if (read (fd, &l, sizeof (int)) < sizeof (int))
    {
      perror ("Error reading length.\n");
      exit (3);
    }
    
  if (read (fd, arr2, (l + 1) * sizeof (char)) < l + 1)
      {
        perror ("Error reading string.\n"); exit (4);
        exit(4);
      }

  close (fd); 
  
  unlink(argv[1]);
  
  printf("String: %s\n", arr2);
  
  return 0;

}
