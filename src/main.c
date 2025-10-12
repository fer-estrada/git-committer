#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char files_to_add[256];
    char commit_message[256];
    FILE *branch = NULL;
    char *branch_name = NULL;
    int res = 0;

    printf("which files to add: ");
    fflush(stdout);
    if(fgets(files_to_add, sizeof(files_to_add), stdin) == NULL) {
        fprintf(stderr, "failed to read which files to add\n");
        return 1;
    };
    files_to_add[strcspn(files_to_add, "\n")] = '\0';

    if((res = git_add(files_to_add)) != 0) {
        return res;
    };

    printf("commit message: ");
    fflush(stdout);
    if(fgets(commit_message, sizeof(commit_message), stdin) == NULL) {
        fprintf(stderr, "failed to read commit message\n");
        return 1;
    };

    if((res = git_commit(commit_message)) != 0) {
        return res;
    };

    branch = popen("git rev-parse --abbrev-ref HEAD", "r");
    if(branch == NULL) {
        fprintf(stderr, "failed to open pipe\n");
        return 1;
    } else if(fgets(branch_name, sizeof(branch_name), branch) == NULL) {
        printf("failed to read github output\n");
        pclose(branch);
        return 1;
    };
    branch_name[strcspn(branch_name, "\n")] = 0;
    pclose(branch);

    if(strcmp(branch_name, "HEAD") != 0 && strcmp(branch_name, "main") != 0) {
        printf("you are in a branch [%s], wanna merge to main ? (y/n): ", branch_name);
        
        fflush(stdout);
        char choice[16];
        while(1) {
            if(fgets(choice, sizeof(choice), stdin) == NULL) {
                fprintf(stderr, "failed to read input\n");
                return 1;
            };
            choice[strcspn(choice, "\n")] = '\0';

            if(choice[0] == 'y') {
                if((res = git_merge_to_main(branch_name)) == 0) {
                    strcpy(branch_name, "main");
                }
                break;
            } else if(choice[0] == 'n') {
                printf("commits remained in branch [%s]\n", branch_name);
                break;
            } else {
                printf("invalid input try again (y/n): ");
                fflush(stdout);
            };
        };
    };

    if(branch_name != NULL && strcmp(branch_name, "main") == 0) {
        printf("push to repo ? (y/n): ");

        fflush(stdout);
        char choice[16];
        while(1) {
            if(fgets(choice, sizeof(choice), stdin) == NULL) {
                fprintf(stderr, "failed to read input\n");
                return 1;
            };
            choice[strcspn(choice, "\n")] = '\0';

            if(choice[0] == 'y') {
                res = git_push();
                break;
            } else if(choice[0] == 'n') {
                printf("commits were not pushed\n");
                break;
            } else {
                printf("invalid input try again (y/n): ");
                fflush(stdout);
            };
        };
    };

    printf("thanks for using git committer :D\n");

    return res;
}
