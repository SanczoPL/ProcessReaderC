#include "processreader.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

//#define DEBUG

static const char* logError = "\x1b[31m";
static const char* logEnd = "\x1b[0m";
static const char* logWarn = "\x1b[33m";
static const char* logDebug = "\x1b[32m";
static const char* procDir = "/proc";

int outputFile;
int save_outputFile;

void usage(char* progName);

void getOpt(int* argc,
    char* argv[],
    char* state,
    char* input_param[],
    char* file_name[]);

void redirectStdout(char* name);

void stopRedirectStdout();

void showUsageAndExit(char* name);

int main(int argc, char* argv[])
{
    char* input_param = NULL;
    char* file_name = NULL;
    char state = -1;
    if (argc < 2) {
        showUsageAndExit(argv[0]);
    }
    getOpt(&argc, argv, &state, &input_param, &file_name);

#ifdef DEBUG
    printf("%sDEBUG: state:%d\n%s", logDebug, state, logEnd);
    printf("%sDEBUG: input_param:%s\n%s", logDebug, input_param, logEnd);
#endif

    if (!state) {
        showUsageAndExit(argv[0]);
    }
    switch (state) {
    case 1:
        printProcess(procDir);
        break;
    case 2:
        showName(input_param, procDir);
        break;
    case 3:
        showPid(input_param, procDir);
        break;
    }

    if (file_name != NULL) {
        stopRedirectStdout();
    }

    return 0;
}

void usage(char* progName)
{
    printf("%s [Options] [Optional]\n", progName);
    printf("Options:\n");
    printf("\t-a        | show all process\n");
    printf("\t-u <pid>  | show <pid> process name\n");
    printf("\t-n <name> | show pid of process <name>\n");
    printf("Optional:\n");
    printf("\t-f <file> | save output to <file> \n");
}

void getOpt(int* argc,
    char* argv[],
    char* state,
    char* input_param[],
    char* file_name[])
{
    int opt = 0;
    while ((opt = getopt(*argc, argv, "au:n:f:")) != -1) {
#ifdef DEBUG
        printf("%sDEBUG: opt:%d args:%s\n%s", logDebug, opt, optarg, logEnd);
        printf("%sDEBUG: state:%d\n%s", logDebug, *state, logEnd);
#endif
        switch (opt) {
        case 'a':
            if (*state > 0) {
                showUsageAndExit(argv[0]);
            }
            *state = 1;
            break;
        case 'u':
            if (*state > 0) {
                showUsageAndExit(argv[0]);
            }
            *input_param = optarg;
            *state = 2;
            break;
        case 'n':
            if (*state > 0) {
                showUsageAndExit(argv[0]);
            }
            *input_param = optarg;
            *state = 3;
            break;
        case 'f':
            *file_name = optarg;
            redirectStdout(optarg);
            break;
        default:
            showUsageAndExit(argv[0]);
            break;
        }
    }
}

void redirectStdout(char* name)
{
#ifdef DEBUG
    printf("%sDEBUG: redirectStdout()\n%s", logDebug, logEnd);
#endif
    outputFile = open(name, O_RDWR | O_CREAT | O_APPEND, 0600);
    save_outputFile = dup(fileno(stdout));
    if (-1 == dup2(outputFile, fileno(stdout))) {
        perror("cannot redirect stdout");
        exit(-55);
    }
}

void stopRedirectStdout()
{
#ifdef DEBUG
    printf("%sDEBUG: stopRedirectStdout()\n%s", logDebug, logEnd);
#endif
    fflush(stdout);
    close(outputFile);
    dup2(save_outputFile, fileno(stdout));
    close(save_outputFile);
}

void showUsageAndExit(char* name)
{
#ifdef DEBUG
    printf("%sDEBUG: showUsageAndExit()\n%s", logDebug, logEnd);
#endif
    usage(name);
    exit(-1);
}
