#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>

int git_add(char files[]) {
    char add[256];
    sprintf(add, "git add %s", files);

    int add_files = system(add);

    if (add_files == 0)
        printf("files added succesfully\n");
    else
        fprintf(stderr, "failed to add files\n%d", add_files);

    return 0;
}

int git_commit(char message[]) {
    char commit[512];
    
    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] == '\n') {
            message [i] = '\0';
            break;
        }
    };

    sprintf(commit, "git commit -m \"%s\"", message);

    int commit_changes = system(commit);

    if (commit_changes == 0)
        printf("git committed\n");
    else
        fprintf(stderr, "failed to perform commit\n%d", commit_changes);

    return 0;
}

int git_merge_to_main(char branch_name[]) {
    char return_command[128];

    int checkout_and_pull = system("git checkout main && git pull");
    if(checkout_and_pull != 0) {
        fprintf(stderr, "failed to pull from repo/n");
        return 1;
    };

    sprintf(return_command, "git checkout \"%s\"", branch_name);
    int return_to_branch = system(return_command);
    if(return_to_branch != 0) {
        fprintf(stderr, "failed to return to branch");
        return 1;
    }

    return 0;
}

int git_push() {
    int push = system("git push");

    if(push != 0)
        fprintf(stderr, "failed to push\n%d", push);

    return 0;
}
