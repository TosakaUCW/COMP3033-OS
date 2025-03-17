/*
 * @Author: Bohan YANG
 * @Student ID: 2330016056
 * @Date: 2025-03-06 15:26:38
 * @FilePath: /tosaka/COMP3033-OS/Lab2/e2_t3_2330016056.c
 */
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define SIZE 1024
int main(void) {
    char prompt[] = "Type a command: ";
    char buf[SIZE];

    while (1) {
        // Ask the user to type a command:
        write(1, prompt, strlen(prompt));
        read(0, buf, SIZE);

        // Replace the Enter key typed by the user with '\0':
        for (int i = 0; i < SIZE; i++) {
            if (buf[i] == '\n' || buf[i] == '\r') {
                buf[i] = '\0';
                break;
            }
        }

        if (strcmp(buf, "exit") == 0) {
            break;
        }

        // Execute the command typed by the user (only prints it for now):

        // Create child process
        pid_t pid = fork();

        if (pid == -1) {
            write(1, "Error: Failed to create child process\n", 38);
            return 1;
        } else if (pid == 0) {
            write(1,
                  "Child: now running the same program as parent, doing exec\n",
                  58);
            execlp(buf, buf, (char *)NULL);
            write(1, "Child: exec failed, die\n", 24);
            return 1;
        } else {
            wait(NULL);
        }
    }

    return 0;
}