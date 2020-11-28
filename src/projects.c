#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projects.h"
#include "macro.h"
#include "strings.h"
#include "directory.h"


// Turn directory into project structure using the global project structure array
int createProject(int n, int index, char project[n])
{
	int dateComponentLength;

	separateTitleFromDirName(n, index, project);
	dateComponentLength = separateDateFromDirName(n, index, project);

	splitDate(index, dateComponentLength, LEN(projectsArr[index].date.dateStr),
			  projectsArr[index].date.dateStr);

	// Print date and title separated
	printf("%10s %s\n", projectsArr[index].date.dateStr, projectsArr[index].title);
	printf("%d ", projectsArr[index].date.y);
	printf("%d ", projectsArr[index].date.m);
	printf("%d\n\n", projectsArr[index].date.d);

	return 0;
}


// Separate title from project directory string
int separateTitleFromDirName(int n, int index, char dirName[n])
{
	int start = 0;

	// Find the start of title / end of date
	for (int i = 0; i < n; i++) {
		// Check if end of date is reached
		if (dirName[i] == '_' || dirName[i] == ' ') {
			start = i;
			break;
		}
	}

	// Copy characters after end of date and separator into title structure
	int i, j;
	for (i = start+1, j = 0; i < n; i++, j++) {
		projectsArr[index].title[j] = dirName[i];
	}

	return 0;
}


// Separate date from project directory string, returns count of date component
int separateDateFromDirName(int n, int index, char dirName[n])
{
	int count = 1;
	char separator = '-';

	// Copy date characters into date structure until end of date
	for (int i = 0; i < n; i++) {
		// Check if end of date is reached
		if (dirName[i] == '_' || dirName[i] == ' ') {
			break;
		}

		// Count date components
		if (dirName[i] == separator) {
			count++;
		}

		// Add char to dateStr array in date structure
		projectsArr[index].date.dateStr[i] = dirName[i];
	}

	return count;
}


// Split date by '-' and convert to integer components
int splitDate(int index, int components, int n, char dateString[n])
{
    char** tokens;

	char date[n+1];
	strcpy(date, projectsArr[index].date.dateStr);

	char year[4+1];
	char month[2+1];
	char day[2+1];

	// Split string by -
    tokens = str_split(date, '-');

    if (tokens) {
        int i;

        for (i = 0; *(tokens + i); i++) {
            /* printf("date=[%s]\n", *(tokens + i)); */
			if (i == 0) {
				strcpy(year, *(tokens + i));
			}
			if (i == 1) {
				strcpy(month, *(tokens + i));
			}
			if (i == 2) {
				strcpy(day, *(tokens + i));
			}

            free(*(tokens + i));
        }

        free(tokens);
    }

	// Convert date component string to integer based on length of date components
	switch (components) {
	case 1:
		projectsArr[index].date.y = atoi(year);
		break;
	case 2:
		projectsArr[index].date.y = atoi(year);
		projectsArr[index].date.m = atoi(month);
		break;
	case 3:
		projectsArr[index].date.y = atoi(year);
		projectsArr[index].date.m = atoi(month);
		projectsArr[index].date.d = atoi(day);
		break;
	}

	return 0;
}


// Create array of projects and return quantity of projects
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
