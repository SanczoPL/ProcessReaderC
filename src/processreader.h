#ifndef PROCESS_READER_H
#define PROCESS_READER_H

#include "queue.h"

#include <stdbool.h>
#include <dirent.h>
#include <ctype.h>
#include <fcntl.h>

bool printProcess(const char* procDirInput);

bool checkIsDigit(char input[]);

void readProcessIntoQueue(struct Queue* q, const char * procDirInput);

void getPid(char* name, char* path);

bool showName(char* pid, const char * procDirInput);

bool showPid(char* name, const char * procDirInput);

#endif // PROCESS_READER_H