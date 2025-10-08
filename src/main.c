#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char commit_message[256];
    char files_to_add[256];
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
    if(branch == NULL)
        printf("failed to read branch name\n");
    else if(fgets(output, sizeof(output), branch) == NULL)
        printf("failed to read github output\n");
    else {
        output[strcspn(output, "\n")] = 0;

        if(strcmp(output, "HEAD") != 0 && strcmp(output, "main") != 0) {
            branch_name = output;
            printf("you are in a branch [%s], wanna merge to main ? (y/n): ", branch_name);

            while(1) {
                char choice;
                fgets(&choice, 2, stdin);

                if(choice == 'y') {
                    git_merge_to_main(branch_name);
                    break;
                } else if(choice == 'n') {
                    printf("commits remained in branch [%s]\n", branch_name);
                } else {
                    printf("invalid input try again\n");
                    printf("merge to main ? (y/n): ");

                    char c;
                    while((c = getchar()) != '\n' && c != EOF);
                };
            };
        };
    };
    pclose(branch);

    if(strcmp(branch_name, "main") || strcmp(branch_name, "HEAD")) {
        printf("push to repo ? (y/n): ");

        while(1) {
            char choice;
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
    }

    printf("thanks for using git committer :D\n");

    return 0;
}
