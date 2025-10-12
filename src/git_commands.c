#include "git_commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static int run_command(const char *cmd) {
    int status = system(cmd);
    if(status == -1) {
        perror("system");
        return 1;
    };

    if(WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if(code != 0) {
            fprintf(stderr, "command failed\n%s\n(exit code: %d)\n", cmd, code);
        }
    } else {
        fprintf(stderr, "failure to terminanate command properly\n%s\n", cmd);
        return 1;
    }

    return 0;
}

int git_add(const char *files) {
    char cmd[256];
    int res;

    if(files == NULL || strlen(files) == 0) {
        fprintf(stderr, "no files added for git add\n");
        return 1;
    };

    snprintf(cmd, sizeof(cmd), "git add %s", files);

    res = run_command(cmd);
    if(res == 0) {
        printf("git files added\n");
    };

    return res;
}

int git_commit(const char *message) {
    char cmd[512];
    char escaped[512];
    int res;
    int j = 0;

    if(message == NULL || strlen(message) == 0) {
        fprintf(stderr, "empty commit message\n");
        return 1;
    };

    for(int i = 0; message[i] != '\0' && j < (int)sizeof(escaped) - 2; i++) {
        if(message[i] == '"') {
            if(j < (int)sizeof(escaped) - 2) {
                escaped[j++] = '\\';
                escaped[j++] = '\"';
            };
        } else if(message[i] == '\n') {
            break;
        } else {
            escaped[j++] = message[i];
        };
    };
    escaped[j] = '\0';

    snprintf(cmd, sizeof(cmd), "git commit -m \"%s\"", message);

    res = run_command(cmd);
    if(res == 0) {
        printf("git committed\n");
    };

    return res;
}

int git_merge_to_main(char **branch_name) {
    char merge_call[256];
    FILE *merge;

    if(system("git checkout main && git pull") != 0) {
        fprintf(stderr, "failed to pull from repo\n");
        return 1;
    };

    sprintf(merge_call, "git merge %s", *branch_name);
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

    *branch_name = "main";
    return 0;
}

int git_push() {
    int push = system("git push");

    if(push != 0) {
        fprintf(stderr, "failed to push\n%d\n", push);
        return 1;
    };

    return 0;
}
