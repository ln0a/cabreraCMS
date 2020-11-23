#include <stdio.h>
#include <string.h>
#include "projects.h"
#include "macro.h"
#include "directory.h"


// Turn directory into project structure using the global project structure array
int createProject(int n, int index, char project[n])
{
	strcpy(projectsArr[index].title, project);
	printf("%s\n", projectsArr[index].title);

	return 0;
}


// Create array of projects
int generateProjects(void)
{
	int quanity = 0;

	char projects[BUFFER_SIZE][WORD_LENGTH];
	char blank[LEN(projects)];
	char path[PATH_LENGTH];

	// Creates array of project title strings
	strcpy(path, "projects/");
	createCleanDirectory(path, WORD_LENGTH, LEN(projects), projects);

	// Find quatity of projects
	while (strcmp(projects[quanity], blank) != 0) {
		quanity++;
	}

	for (int i = 0; i < quanity; i++) {
		createProject(LEN(projects), i, projects[i]);
	}

	return quanity;
}
