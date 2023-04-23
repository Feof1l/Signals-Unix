#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>	
int status_info;
int pid_child;
void create_new_procc() {
	pid_child = fork();
	if (pid_child > 0) { // если parent процесс 
		wait(&status_info);   // ждем завершение child процесса
		if (WEXITSTATUS(status_info)==0)  //
			printf("Parent: Cild-process has been completed successfully.\n");
		else {
			printf("Parent: Child-process is frozen, rebooting..\n");
			create_new_procc();
		}
	}
	else if(pid_child==0) {  // если child процесс
		printf("Parent: launch child-process. Waiting...\n");
		execlp("./Child.out","Child",NULL);
	}
	else
		printf("Parent: ERROR: failed to start the process.\n");
}
int main() {
	printf("Parent: launch Parent process.\n");
	create_new_procc();
	return 0;
}
