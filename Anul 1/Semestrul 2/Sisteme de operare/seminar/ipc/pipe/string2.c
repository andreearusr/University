#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
       

int
main (int argc, char **argv)
{

  int p[2];
  
  if ( pipe(p) < 0 )
  {
    perror("Error creating the pipe.\n");
    exit(1);
  }

  char msg[20];

  printf("Give a string: ");
  
  scanf("%s", msg);
  
  int l = strlen(msg);
  
  if ( write(p[1], &l, sizeof(int)) < sizeof(int))
  {
    perror("Error sending string length.\n");
    exit(2);
  }
  
  if ( write(p[1], msg, l * sizeof(char)) < l * sizeof(char))
  {
    perror("Error sending string.\n");
    exit(3);
  }

  close(p[1]);

  if (!fork())
  {
    char *mymsg;

    int n;
    
    if ( read (p[0], &n, sizeof(int)) < sizeof(int))
    {
      perror("Error recieving the string length.\n");
      exit(1);
    }
    
    mymsg = malloc( (n + 1) * sizeof(char));
    
    if ( read (p[0], mymsg, n * sizeof(char)) < n * sizeof(char))
    {
      perror("Error recievenig the string.\n");
      exit(2);
    }
    
    mymsg[n] = '\0';
    
    printf("%s -- %lu\n", mymsg, strlen(mymsg));
    
    free(mymsg);
    
    close(p[0]);
    
    exit(0);
  }
  
  wait(0);
  
  close(p[0]);
  
  return 0;
}
