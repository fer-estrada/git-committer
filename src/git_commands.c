#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int git_add(char files[]) {
    char add[256];
    sprintf(add, "git add %s", files);

    int add_files = system(add);
    if(add_files == 0)
        printf("files added succesfully\n");
    else
        fprintf(stderr, "failed to add files\n%d", add_files);

    return 0;
}

int git_commit(char message[]) {
    char commit[512];
    
    for (int i = 0; message[i] != '\0'; i++) {
        if(message[i] == '\n') {
            message [i] = '\0';
            break;
        }
    };

    sprintf(commit, "git commit -m \"%s\"", message);

    int commit_changes = system(commit);
    if(commit_changes == 0)
        printf("git committed\n");
    else
        fprintf(stderr, "failed to perform commit\n%d", commit_changes);

    return 0;
}

int git_merge_to_main(char branch_name[]) {
    char merge_call[256];
    char output[256];
    FILE *merge;

    if(system("git checkout main && git pull") != 0) {
        fprintf(stderr, "failed to pull from repo\n");
        return 1;
    };

    sprintf(merge_call, "git merge %s", branch_name);
    merge = popen(merge_call, "r");
    if(merge == NULL) {
        fprintf(stderr, "failed to merge\n");
        return 1;
    };

    while(fgets(output, sizeof(output), merge) != NULL)
        printf("%s", output);

    int status = pclose(merge);
    return (status == 0) ? 0 : 1;
}

int git_push() {
    int push = system("git push");

    if(push != 0)
        fprintf(stderr, "failed to push\n%d", push);

    return 0;
}
