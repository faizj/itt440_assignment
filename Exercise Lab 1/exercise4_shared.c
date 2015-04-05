#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024 /* make it a 1K shared memory segment */
int main(void)
{
	pid_t pid;
	char rv[20];

	key_t key;
	int shmid;
	char *data;
	int mode;


	/* make the key : */
	if ((key = ftok("shmdemo.c", 'R')) == -1)
	{
		perror("ftok");
		exit(1);
	}

	/* connect to (and possibly create) the segment: */
	if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1)
	{
		perror("shmget");
		exit(1);
	}

	/* attach to the segment to get a pointer to it: */
	data = shmat(shmid, (void *)0, 0);
	if (data == (char *) (-1))
	{
		perror("shmat");
		exit(1);
	}

/*
	switch(pid=fork())
	{
	case -1:
		perror("fork"); //something went wrong
		exit(1); //parent exits

	case 0:
		printf(" CHILD: This is the child process!\n");
		printf(" CHILD: Enter my String: \n");
		scanf(" %s", rv);
		strncpy(data, rv, SHM_SIZE);
		printf(" CHILD: I'm outta here!\n");

	default:
		printf("PARENT: This is the parent process!\n");
		printf("PARENT: I'm now waiting for my child to exit...\n");
		wait(NULL);
		printf("PARENT: Result from child: %s\n", data);
		printf("PARENT: I'm outta here!\n");
	}
*/
	if(pid=fork())
	{
                printf("PARENT: This is the parent process!\n");
                printf("PARENT: I'm now waiting for my child to exit...\n");
                wait(NULL);
                printf("PARENT: Result from child: %s\n", data);
                printf("PARENT: I'm outta here!\n");
	}
	else
	{
                printf(" CHILD: This is the child process!\n");
                printf(" CHILD: Enter my String:");
                scanf(" %s", rv);
                strncpy(data, rv, SHM_SIZE);
                printf(" CHILD: I'm outta here!\n");


	}
	return 0;
}
