#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
       

int
main (int argc, char **argv)
{

  int p[2],a;
  
  if ( pipe(p) < 0 )
  {
    perror("Error creating the pipe.\n");
    exit(1);
  }

  printf("Give a integer: ");
  
  scanf("%d", &a);
  
  if ( write(p[1], &a, sizeof(int)) < sizeof(int))
  {
    perror("Error sending number.\n");
    exit(2);
  }

  close(p[1]);

  if (!fork())
  {
    int n;
    
    if ( read (p[0], &n, sizeof(int)) < sizeof(int))
    {
      perror("Error recieving number.\n");
      exit(1);
    }
    
    printf("%d\n", n);
    
    close(p[0]);
    
    exit(0);
  }
  
  wait(0);
  
  close(p[0]);
  
  return 0;
}
