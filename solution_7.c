#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int fd[2]; 	//defined fd for pipe

void signal_handler(int sig) {
	pid_t pid;
	int n, i;

	if (pipe(fd) == -1) {
		perror("Pipe failed");
		exit(1);
	}

	pid = fork();

	if (pid < 0) {				//failed child process
		perror("Fork failed");
		exit(1);
	}

	if (pid == 0) {			//in the child process
		close(fd[0]);		//closes read end of the pipe
		
		// Send the child's PID to pipe
		pid_t child_pid = getpid();
		write(fd[1], &child_pid, sizeof(child_pid));
		
		printf("\nEnter the number of terms for Fibonacci series: ");
		scanf("%d", &n);
		
		// Send the number of terms to the parent process
		write(fd[1], &n, sizeof(n));
		
		int a = 0, b = 1, next;
		for (i = 0; i < n; i++) {
			// Send Fibonacci number
			write(fd[1], &a, sizeof(a)); 
			next = a + b;
			a = b;
			b = next;
		}

		// Send the SIGINT signal
		int signal_id = SIGINT;
		write(fd[1], &signal_id, sizeof(signal_id));

		close(fd[1]);
		exit(0);
	} else { 
		// Parent Process
		close(fd[1]); 
		
		// Read the child's PID
		pid_t received_pid;
		read(fd[0], &received_pid, sizeof(received_pid));
		printf("\nReceived Child Process ID: %d\n", received_pid);
		
		// Read the Fibonacci count N
		read(fd[0], &n, sizeof(n));

		printf("Fibonacci Series: ");
		for (i = 0; i < n; i++) {
			int fib;
			read(fd[0], &fib, sizeof(fib));
			printf("%d ", fib);
		}
		printf("\n");
		
		// Read the received signal
		int received_signal;
		read(fd[0], &received_signal, sizeof(received_signal));
		printf("Received Signal ID: %d\n", received_signal);

		close(fd[0]); 
		wait(NULL);
	}
}

int main() {
	signal(SIGINT, signal_handler);
	
	printf("Press Ctrl+C to generate Fibonacci series.\n");
	
	while (1) {
		pause(); 
	}

	return 0;
}
