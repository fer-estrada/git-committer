#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char commit_message[256];
    char choice;

    int git_add = system("git add .");
    if (git_add != 0) {
        printf("failed to add files lol idiot\n");
    } else {
        printf("git added .\n");
    }

    printf("commit message: ");
    scanf("%255s", commit_message);
    git_commit(commit_message);

    printf("push to repo ? (y/n): ");
    scanf("%c", &choice);
    while (choice) {
        switch(choice) {
            case 'y':
                git_push();
                break;
            case 'n':
                printf("commits were not pushed\n");
                break;
            default:
                printf("invalid input try again\n");
                printf("push to repo ? (y/n): ");
                continue;
        }
        break;
    }

    printf("thanks for using git committer :D");

    return 0;
}
