#include <stdio.h>
#include "projects.h"
#include "macro.h"
#include "directory.h"


// Create struct of projects
int generateProjects(void)
{
	char projectList[BUFFER_SIZE][WORD_LENGTH];

	cleanDirectory("projects", WORD_LENGTH, LEN(projectList), projectList);

	for (int i = 0; i < 4; i++) {
		printf("%s\n", projectList[i]);
	}


	return 1;
}
