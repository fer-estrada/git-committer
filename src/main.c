#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char commit_message[256];
    char files_to_add[256];
    char choice;
    FILE *branch;
    char output[256];
    char *branch_name;

    printf("which files to add: ");
    fgets(files_to_add, 255, stdin);
    git_add(files_to_add);

    printf("commit message: ");
    fgets(commit_message, 255, stdin);
    git_commit(commit_message);

    branch = popen("git rev-parse --abbrev-ref HEAD", "r");
    if (branch == NULL)
        fprintf(stderr, "failed to read branch name\n");
    if(fgets(output, sizeof(output), branch) != NULL) {
        output[strcspn(output, "\n")] = 0;

        if(strcmp(output, "HEAD") || strcmp(output, "main") == 0)
            return 0;
        else {
            branch_name = output;
            printf("you are in a branch [%s], do you want to merge to main ? (y/n): ", branch_name);
            while(1) {
                fgets(&choice, 2, stdin);

                if(choice == 'y') {
                    git_merge_to_main(branch_name);
                    break;
                } else if(choice == 'n') {
                    printf("remained in branch\n");
                    break;
                } else {
                    printf("invalid input try again\n");
                    printf("you are in a branch [%s], do you want to merge to main ? (y/n): ", branch_name);

                    int c;
                    while((c = getchar()) != '\n' && c != EOF);
                }
            }
        }
    }

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
