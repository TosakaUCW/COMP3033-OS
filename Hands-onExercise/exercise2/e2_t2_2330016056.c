/*
 * @Author: Bohan YANG
 * @Student ID: 2330016056
 * @Date: 2025-03-06 14:40:48
 * @FilePath: /tosaka/COMP3033-OS/Lab2/e2_t2_2330016056.c
 */
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define SIZE 1024
int main(void) {
    char prompt[] = "Type a command: ";
    char buf[SIZE];

    // Ask the user to type a command:
    // printf(prompt);
    write(1, prompt, strlen(prompt));

    // Read from the standard input the command typed by the user (note
    // that fgets also puts into the array buf the '\n' character typed
    // by the user when the user presses the Enter key on the keyboard):
    // fgets(buf, SIZE, stdin);
    read(0, buf, SIZE);

    // Replace the Enter key typed by the user with '\0':
    for (int i = 0; i < SIZE; i++) {
        if (buf[i] == '\n' || buf[i] == '\r') {
            buf[i] = '\0';
            break;
        }
    }

    // Execute the command typed by the user (only prints it for now):

    // Create child process
    pid_t pid = fork();

    if (pid == -1) {
        write(1, "Error: Failed to create child process\n", 38);
        return 1;
    } else if (pid == 0) {
        write(1, "Child: now running the same program as parent, doing exec\n",
              58);
        execlp(buf, buf, (char *)NULL);
        write(1, "Child: exec failed, die\n", 24);
        return 1;
    } else {
        wait(NULL);
    }

    return 0;
}