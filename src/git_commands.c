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
    else {
        fprintf(stderr, "failed to add files\n%d\n", add_files);
        return 1;
    };

    return 0;
}

int git_commit(char message[]) {
    char commit[512];
    char escaped[512];
    int j = 0;

    for(int i = 0; message[i] != '\0' && j < 510; i++) {
        if(message[i] == '"') {
            escaped[j++] = '\\';
            escaped[j++] = '\"';
        } else if(message[i] == '\n')
            break;
        else {
            escaped[j++] = message[i];
        };
    };
    escaped[j] = '\0';

    sprintf(commit, "git commit -m \"%s\"", escaped);

    int commit_changes = system(commit);
    if(commit_changes == 0)
        printf("git committed\n");
    else {
        fprintf(stderr, "failed to perform commit\n%d\n", commit_changes);
        return 1;
    }

    return 0;
}

int git_merge_to_main(char branch_name[]) {
    char merge_call[256];
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

    int status = pclose(merge);
    if(status != 0) {
        int mergetool = system("git mergetool");
        if (mergetool != 0) {
            fprintf(stderr, "failure to open merge editor tool\n");
            return 1;
        };

        printf("were conflicts resolved ? (y/n): ");
        while(1) {
            int c;
            while((c = getchar()) != '\n' && c != EOF);

            char choice[64];
            fgets(choice, sizeof(choice), stdin);

            if(choice[0] == 'y') {
                system("git commit --no-edit");
                break;
            } else if(choice[0] == 'n') {
                system("git merge --abort");
                break;
            } else {
                printf("invalid input try again\n");
                printf("(y/n): ");
            };
        };
    };

    return 0;
}

int git_push() {
    int push = system("git push");

    if(push != 0) {
        fprintf(stderr, "failed to push\n%d", push);
        return 1;
    };

    return 0;
}
