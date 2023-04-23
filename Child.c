#include <unistd.h>
#include <signal.h>	
#include <stdlib.h>
#include <stdio.h>
void signal_processing(int signum) {
	switch(signum) {
		case SIGINT:
		    printf("Child: Child-process completed.\n");
		    exit(0);
		case SIGHUP:
			printf("Child: Child-process is frozen...\n");
			exit(1);
			break;
		default:
			return;
	}
}

int main()
{
	signal(SIGHUP, signal_processing);
	signal(SIGINT, signal_processing);
	int program_pid = getpid();
	printf("Child: launch Child-process. PID=%d.\n",program_pid);
	if (program_pid % 10 == 1 || program_pid % 10 == 2 || program_pid % 10 == 3)
		raise(SIGHUP);
	printf("Child: Press Enter to complete.\n");
	getchar();
	kill(getpid(),SIGINT); 
	return 0;
}

