#include "processreader.h"

//#define DEBUG

static const char* logError = "\x1b[31m";
static const char* logEnd = "\x1b[0m";
static const char* logWarn = "\x1b[33m";
static const char* logDebug = "\x1b[32m";


bool printProcess(const char* procDir)
{
    struct Queue* q = createQueue();
    readProcessIntoQueue(q, procDir);
    bool returnFlag = printQueue(q);
    deleteQueue(q);
	return returnFlag;
}

bool checkIsDigit(char input[])
{
    int i;
    for (i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
#ifdef DEBUG
            printf("%sDEBUG: checkIsDigit(): char[%d]: is invalid\n%s", logWarn, i, logEnd);
#endif
            return false;
        }
    }
#ifdef DEBUG
    printf("%sDEBUG: checkIsDigit(): valid\n%s", logDebug, logEnd);
#endif
    return true;
}

void readProcessIntoQueue(struct Queue* q, const char* procDir)
{
    char *dirname_buf, *curr_path = malloc(sizeof(char) * 100);
    DIR* directory;
    directory = opendir(procDir);

    if (directory == NULL) {
        printf("%s\nERROR: unable to open %s for read\n\n%s", logError, procDir, logEnd);
        free(curr_path);
        return;
    }
#ifdef DEBUG
    printf("%sDEBUG: opened %s for read:\n%s", logDebug, procDir, logEnd);
#endif
    struct dirent* dir;
	char* name = malloc(sizeof(char) * 100);
    while ((dir = readdir(directory)) != NULL) {
        dirname_buf = dir->d_name;
        if (!checkIsDigit(dirname_buf)) {
            continue;
        }
        snprintf(curr_path, 100, "%s%s%s", "/proc/", dirname_buf, "/status");
        int pid = strtol(dirname_buf, NULL, 10);
        getPid(name, curr_path);
        push_back(q, pid, name);
    }
    free(directory);
    free(dir);
    free(curr_path);
    free(name);
    return;
}

void getPid(char* name, char* path)
{
#ifdef DEBUG
    printf("%sDEBUG: getPid(%s)\n%s", logDebug, path, logEnd);
#endif
    char null[BUF_LEN];

    FILE* file = fopen(path, "r");
    if (!file) {
        printf("%sERROR: cannot open %s for read\n%s", logError, path, logEnd);
        snprintf(name, 100, "%s", "not_readed");
        return;
    }
    fscanf(file, "%s ", null);
    fscanf(file, "%s ", name);
    fclose(file);
    return;
}

bool showName(char* pid, const char* procDir)
{
#ifdef DEBUG
    printf("%sDEBUG: showName(%s)\n%s", logDebug, pid, logEnd);
#endif

    if (checkIsDigit(pid) == 0) {
        return false;
    }
    int pidInt = strtol(pid, NULL, 10);

    struct Queue* q = createQueue();
    readProcessIntoQueue(q, procDir);

	struct Queue* findQ = findPidInQueue(q, pidInt);

	bool returnFlag = printNameFromQueue(findQ);

	deleteQueue(findQ);
    deleteQueue(q);
    return returnFlag;
}

bool showPid(char* name, const char* procDir)
{
#ifdef DEBUG
    printf("%sDEBUG: showPid(%s)\n%s", logDebug, name, logEnd);
#endif
    struct Queue* q = createQueue();
    readProcessIntoQueue(q, procDir);


	struct Queue* findQ = findNameInQueue(q, name);

	bool returnFlag = printPidFromQueue(findQ);
    
	deleteQueue(findQ);
    deleteQueue(q);
    return returnFlag;
}
