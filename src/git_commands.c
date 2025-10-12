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
    char cmd[256];
    int res;

    if(branch_name == NULL || strlen(*branch_name) == 0) {
        fprintf(stderr, "sum wrong with dat branch name\n");
        return 1;
    };

    if((res = run_command("git checkout main")) == 0) {
        *branch_name = "main";
    } else {
        return res;
    };

    if((res = run_command("git pull")) != 0) return res;

    snprintf(cmd, sizeof(cmd), "git merge %s", *branch_name);

    res = run_command(cmd);
    if(res != 0) {
        printf("hey there's a merge conflict i'm gonna open the merge tool\n");
        sleep(3);

        if(run_command("git mergetool") != 0) {
            fprintf(stderr, "failed to open merge tool");
            return 1;
        };

        char choice[16];
        while(1) {
            printf("were conflicts resolved ? (y/n): ");
            if(!fgets(choice, sizeof(choice), stdin)) {
                fprintf(stderr, "input error\n");
                return 1;
            };

            if(choice[0] == 'y') {
                res = run_command("git_commit --no-edit");
                break;
            } else if(choice[0] == 'n') {
                res = run_command("git merge --abort");
                break;
            } else {
                printf("invalid input try again (y/n): ");
            };
        };
    } else {
        printf("merge completed succesfully\n");
    };

    return res;
}

int git_push() {
    int res = run_command("git push");
    if(res == 0) {
        printf("pushed to sourese\n");
    };

    return res;
}
