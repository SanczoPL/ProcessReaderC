#include "processreader.h"

//#define DEBUG

static const char * logError =  "\x1b[31m";
static const char * logEnd = "\x1b[0m";
static const char * logWarn =  "\x1b[33m";
static const char * logDebug =  "\x1b[32m";


int printProcess(const char * procDir)
{
	struct Queue* q = createQueue();
	readProcessIntoQueue(q, procDir);
	struct QNode *temp = q->front;
	if(temp!= NULL)
	{
        printf("%s %d\n", temp->name, temp->pid);
		while(temp->next != NULL)
		{
			
			temp = temp->next;
			if(temp == NULL)
			{
				break;
			}
            printf("%s %d\n", temp->name, temp->pid);
		}
	}
	deleteQueue(q);
}

bool checkIsDigit(char input[])
{
	int i;
	for (i=0;i<strlen(input);i++)
	{
		if(!isdigit(input[i]))
		{
			#ifdef DEBUG
			printf("%sDEBUG: checkIsDigit(): char[%d]: is invalid\n%s",logWarn, i, logEnd);
			#endif
			return 0;
		}
	}
	#ifdef DEBUG
	printf("%sDEBUG: checkIsDigit(): valid\n%s",logDebug, logEnd);
	#endif
	return 1;
}

void readProcessIntoQueue(struct Queue* q, const char * procDir)
{
	char * dirname_buf, * curr_path=malloc(sizeof(char)*100);
	char * name = malloc(sizeof(char)*100);
	
	DIR * directory;
	directory=opendir(procDir);
	
	if(directory==NULL)
	{
		printf("%s\nERROR: unable to open %s for read\n\n%s",logError, procDir, logEnd);
		free(curr_path);
		free(name);
		return;
	}

	#ifdef DEBUG
	printf("%sDEBUG: opened %s for read:\n%s",logDebug, procDir, logEnd);
	#endif

	struct dirent * dir;

	while((dir=readdir(directory))!=NULL)
	{
		dirname_buf=dir->d_name;
		if(!checkIsDigit(dirname_buf))
		{
			continue;
		}
		snprintf(curr_path, 100, "%s%s%s", "/proc/", dirname_buf, "/status");
		int pid = strtol(dirname_buf, NULL, 10);
		getPid( name, curr_path);
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
	printf("%sDEBUG: getPid(%s)\n%s",logDebug, path, logEnd);
	#endif
	char null[BUF_LEN];

	FILE * file=fopen(path,"r");
	if(!file)
	{
		printf("%sERROR: FATAL: cannot open %s for read\n%s",logError, path, logEnd);
		snprintf(name, 100, "%s", "not_readed");
		return;
	}

	fscanf(file, "%s ",null);
	fscanf(file, "%s ",name);
	fclose(file);
	return;
}

bool showName(char* pid, const char * procDir)
{
	#ifdef DEBUG
	printf("%sDEBUG: showName(%s)\n%s",logDebug, pid, logEnd);
	#endif
	
	if(checkIsDigit(pid) == 0)
	{
		return false;
	}
	int pidInt = strtol(pid, NULL, 10);
	
	struct Queue* q = createQueue();
	readProcessIntoQueue(q, procDir);
		
	if(q->front == NULL)
	{
		return false;
	}
	struct QNode *temp = q->front;

	if(temp!= NULL)
	{
		while(temp->next != NULL)
		{
			if(pidInt == temp->pid)
			{
				printf("%s\n", temp->name);
			}
			
			temp = temp->next;
		}
	}
	
	deleteQueue(q);
	return true;
}

bool showPid(char* name, const char * procDir)
{
	bool returnFlag = false;
	#ifdef DEBUG
	printf("%sDEBUG: showPid(%s)\n%s",logDebug, name, logEnd);
	#endif
	struct Queue* q = createQueue();
	readProcessIntoQueue(q, procDir);
		
	struct QNode *temp = q->front;

	while(temp != NULL)
	{
		if(strcmp(name, temp->name)==0)
		{
			printf("%d\n", temp->pid);
			returnFlag = true;
		}
		if(temp->next == NULL)
		{
			break;
		}
		temp = temp->next;
	}
	deleteQueue(q);
	return returnFlag;
}
