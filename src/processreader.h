#ifndef PROCESS_READER_H
#define PROCESS_READER_H

#include "queue.h"

#include <stdbool.h>
#include <dirent.h>
#include <ctype.h>
#include <fcntl.h>

int printProcess(const char * procDir);

bool checkIsDigit(char input[]);

void readProcessIntoQueue(struct Queue* q, const char * procDir);

void getPid(char* name, char* path);

bool showName(char* pid, const char * procDir);

bool showPid(char* name, const char * procDir);

#endif // PROCESS_READER_H