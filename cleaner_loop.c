#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void	 cleaner()
{
	while(1)
		{
			//system syscall is used to execute a system command 
			system("~/Cleaner_42/Cleaner_42.sh");
			sleep(500);
		}
}

int main(int argc, char* argv[])
{
	FILE *fp= NULL;
	pid_t process_id = 0;
	pid_t sid = 0;
	// Create child process
	process_id = fork();
	// Indication of fork() failure
	if (process_id < 0)
		{
			write(2, "!!! Can't create the child proccess !!!", 41);
			// Return failure in exit status
			exit(1);
		}
	// killing the parent process (child process will be an orphan)
	if (process_id > 0)
		{
			printf("process_id of child process %d \n", process_id);
			// return success in exit status
			exit(0);
		}
	//giving the permesions for the process (0 means that any files or directories created in this process will have maximum permissions) 
		umask(0);
	//set new session
		sid = setsid();
		if(sid < 0)
		{
			// Return failure
			exit(1);
		}
	// Change the current working directory to root.
		chdir("/");
	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	//here u can write the code for the deamon  process
	//Dont block context switches, let the process sleep for some time
	cleaner();
	return (0);
}
