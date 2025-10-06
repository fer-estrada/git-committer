#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>

int git_add(char files[]) {
    char add[256];
    sprintf(add, "git add %s", files);

    int call = system(add);

    if (call == 0)
        printf("files added succesfully\n");
    else
        fprintf(stderr, "failed to add files\n%d", call);

    return 0;
}

int git_commit(char message[]) {
    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] == '\n') {
            message [i] = '\0';
            break;
        }
    };

    char commit[512];
    sprintf(commit, "git commit -m \"%s\"", message);

    int call = system(commit);

    if (call == 0)
        printf("git committed\n");
    else
        fprintf(stderr, "failed to perform commit\n%d", call);

    return 0;
}

int git_push() {
    int push = system("git push");

    if (push == 0)
        printf("pushed to source\n");
    else
        fprintf(stderr, "failed to push\n%d", push);

    return 0;
}
