#ifndef PROJECTS_H
#define PROJECTS_H


#include "macro.h"


// Date structure
struct date {
	char dateStr[10];
	int y;
	int m;
	int d;
};

// Project structure
struct project {
	// Content
	char title[WORD_LENGTH + 1];
	char text[TEXT_LENGTH + 1];
	char visualContent[BUFFER_SIZE][PATH_LENGTH + 1];
	char tags[BUFFER_SIZE][WORD_LENGTH + 1];

	// Meta-data
	struct date date;
	char location[WORD_LENGTH + 1];

	// Accessibility
	char path[PATH_LENGTH + 1];
};

struct project projectsArr[BUFFER_SIZE]; // Array of projects


int createProject(int n, int index, char project[n]);
int separateTitleFromDirName(int n, int index, char dirName[n]);
int separateDateFromDirName(int n, int index, char dirName[n]);
int splitDate(int index, int components, int n, char longString[n]);
int generateProjects(void);


#endif
