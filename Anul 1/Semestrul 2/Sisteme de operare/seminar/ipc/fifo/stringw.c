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

  char *myfifo = argv[1];

  char arr2[80];
  
  if (mkfifo (myfifo, 0600) < 0)
    {
      perror ("Error creating fifo.\n");
      exit (1);    }

  fd = open (myfifo, O_WRONLY);

  if (fd < 0)
    {
      perror ("Error opening fifo.\n");
      exit (2);
    }
    
  printf("Give a string: ");

  fgets (arr2, 80, stdin);

  l = strlen (arr2);

  if (write (fd, &l, sizeof (int)) < sizeof (int))
    {
      perror ("Error sending string length.\n");
      exit (3);
    }

  if (write (fd, arr2, (l + 1) * sizeof (char)) < l + 1)
      {
        perror ("Error sending string.\n"); exit (4);
        exit(4);
      }

  close (fd); 
  
  return 0;

}
