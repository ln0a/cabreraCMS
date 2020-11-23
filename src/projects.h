#ifndef PROJECTS_H
#define PROJECTS_H


#include "macro.h"


// Project structure
struct project {
	// Content
	char title[WORD_LENGTH + 1];
	char text[TEXT_LENGTH + 1];
	char visualContent[BUFFER_SIZE][PATH_LENGTH + 1];
	char tags[BUFFER_SIZE][WORD_LENGTH + 1];

	// Meta-data
	int date;
	char location[WORD_LENGTH + 1];

	// Accessibility
	char path[PATH_LENGTH + 1];
};

struct project projectsArr[BUFFER_SIZE]; // Array of projects


int createProject(int n, int index, char project[n]);
int generateProjects(void);


#endif
