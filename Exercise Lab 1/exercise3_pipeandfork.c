#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t x,y;
	char rv1[30],rv2[30];

	int pfds1[2];
	int pfds2[2];

	char buf1[30];
	char buf2[30];

	pipe(pfds1);
	pipe(pfds2);

	if(x=fork())
	{
		printf("PARENT: This is the parent process!\n");
		printf("PARENT: My PID is %d\n",getpid());
		printf("PARENT: My 1st child PID is %d\n", x);
		printf("PARENT: I'm now waiting for my 1st child STRING to exit()...\n");
		printf("PARENT: reading from Child 1 pipe\n");
		read(pfds1[0], buf1, 20);
		//printf("PARENT: read from child 1\"%s\"\n", buf1);
		//wait(NULL);
	}
	else
	{
		printf(" CHILD1: This is the child 1 process!\n");
		printf(" CHILD1: Enter my STRING: ");
		scanf(" %s", rv1);
		write(pfds1[1], rv1, 20);
		printf(" CHILD1: I'm outta here!\n");
	}

	//untuk child kedua
        if(y=fork())
        {
                printf("PARENT: I'm now waiting for my 2nd child STRING to exit()...\n");
                printf("PARENT: reading from Child 2 pipe\n");
                read(pfds2[0], buf2, 20);

                printf("\n\n-==RESULT==-\n");
                printf("PARENT: read from child 1 : \"%s\"\n", buf1);
                //wait(NULL);

                printf("PARENT: read from child 2 : \"%s\"\n", buf2);
                //wait(NULL);
                printf("PARENT: I'm outta here !\n");

         }
         else
         {
         	printf(" CHILD2: This is the child 2 process!\n");
                printf(" CHILD2: Enter my STRING: ");
                scanf(" %s", rv2);
                write(pfds2[1], rv2, 20);
                printf(" CHILD2: I'm outta here!\n");
         }
         //end untuk child kedua

	return 0;
}
