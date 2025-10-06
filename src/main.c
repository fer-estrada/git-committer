#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char commit_message[256];
    char files_to_add[256];
    char choice;

    printf("which files to add: ");
    fgets(files_to_add, 255, stdin);
    git_add(files_to_add);

    printf("commit message: ");
    fgets(commit_message, 255, stdin);
    git_commit(commit_message);

    printf("push to repo ? (y/n): ");

    while(1) {
        fgets(&choice, 2, stdin);

        if(choice == 'y') {
            git_push();
            break;
        } else if(choice == 'n') {
            printf("commits were not pushed\n");
            break;
        } else {
            printf("invalid input try again\n");
            printf("push to repo ? (y/n): ");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        };
    };

    printf("thanks for using git committer :D\n");

    return 0;
}
