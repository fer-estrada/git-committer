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
    while(scanf("%c", &choice) == 1) {
        if (choice == 'y') {
            git_push();
            return 0;
        }
        else if (choice == 'n') {
            printf("commits were not pushed\n");
            return 0;
        } else {
            printf("invalid input try again\n");
            continue;
        }
    }

    printf("thanks for using git committer :D");

    return 0;
}
