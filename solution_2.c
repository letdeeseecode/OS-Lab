#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>     
#include <utmp.h>
#include <fcntl.h>

void print_logged_in_users() {
    struct utmp user_entry;
    int utmp_fd = open("/var/run/utmp", O_RDONLY);

    if (utmp_fd < 0) {
        perror("Error opening /var/run/utmp");
        exit(1);
    }

    printf("\nLogged-in Users:\n");
    printf("--------------------\n");

    while (read(utmp_fd, &user_entry, sizeof(user_entry)) == sizeof(user_entry)) {
        if (user_entry.ut_type == USER_PROCESS) {
            printf("User: %s\n", user_entry.ut_user);
        }
    }

    close(utmp_fd);
}

int main() {
    pid_t child_pid, grandchild_pid;

    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed for child");
        exit(1);
    }

    if (child_pid == 0) {
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());

        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            perror("Fork failed for grandchild");
            exit(1);
        }

        if (grandchild_pid == 0) {
            printf("Grandchild Process: PID = %d, PPID = %d\n", getpid(), getppid());
            print_logged_in_users(); 
            exit(0);
        } else {
            wait(NULL);
            printf("Child Process (PID %d) exiting...\n", getpid());
            exit(0);
        }
    } else {
        wait(NULL);
        printf("Parent Process: PID = %d (Finished waiting for child)\n", getpid());
    }

    return 0;
}
