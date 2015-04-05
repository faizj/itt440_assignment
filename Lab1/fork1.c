#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pids[2];
	int rv[2];
	int x;

	for (x=0;x<2;x++)
	{
		if((pids[x] = fork())<0)
		{
			perror("fork");
			abort();
		}
		else if (pids[x] == 0)
		{
			printf(" CHILD: This is the child no %d process!\n", x+1);
                        printf(" CHILD: My PID is %d\n", getpid());
                        printf(" CHILD: My parent's PID is %d\n", getppid());
                        printf(" CHILD: Enter my exit status (make it small): ");

                        scanf(" %d", &rv[x]);
                        printf(" CHILD: I'm outta here!\n\n");
		}
	}

	pid_t pid;	

	printf("PARENT: This is the parent process!\n");
        printf("PARENT: My PID is %d\n", getpid());
        printf("PARENT: My child's PID is %d\n", pid);
        printf("PARENT: I'm now waiting for my both child to exit()...\n");
        wait(&rv[0]);
        printf("PARENT: My First child's exit status is: %d\n", WEXITSTATUS(rv[0]));
        wait(&rv[1]);
        printf("PARENT: My Second child's exit status is: %d\n", WEXITSTATUS(rv[1]));
        printf("PARENT: I'm outta here! DONE\n\n\n");

	/*
	switch(pid = fork())
	{

		case -1:
			perror("fork");
			exit(1);

		case  0
			printf(" CHILD: This is the child no %d process!\n", x);
			printf(" CHILD: My PID is %d\n", getpid());
			printf(" CHILD: My parent's PID is %d\n", getppid());
			printf(" CHILD: Enter my exit status (make it small): ");

			if(x==1)scanf(" %d", &rv1);
			if(x==2)scanf(" %d", &rv2);
			printf(" CHILD: I'm outta here!\n\n");
			}

		default:
			printf("PARENT: This is the parent process!\n");
			printf("PARENT: My PID is %d\n", getpid());
			printf("PARENT: My child's PID is %d\n", pid);
			printf("PARENT: I'm now waiting for my both child to exit()...\n");
			wait(&rv1);
			printf("PARENT: My First child's exit status is: %d\n", WEXITSTATUS(rv1));
			wait(&rv2);
			printf("PARENT: My Second child's exit status is: %d\n", WEXITSTATUS(rv2));
			printf("PARENT: I'm outta here! DONE\n\n\n");
	}*/
}
