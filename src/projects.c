#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projects.h"
#include "macro.h"
#include "strings.h"
#include "directory.h"
#include "tags.h"
#include "content.h"


// Turn directory into project structure using the global project structure array
int create_project(int n, int index, char dirName[n])
{
	int dateComponentLength;


	// Convert project directory name into title string and date component integers
	get_title_from_dirname(n, index, dirName);
	dateComponentLength = get_date_from_dirname(n, index, dirName);
	split_date(index, dateComponentLength, LEN(projectsArr[index].date.dateStr),
			  projectsArr[index].date.dateStr);


	// Create project path
	set_project_path(index, n, dirName);


	// Create project tags
	gen_project_tags(index);


	// Generate description
	gen_description(index);


	// Print path, title, date and tags from project structure
	printf("Path: %s\n", projectsArr[index].path);
	printf("Title: %s\n", projectsArr[index].title);
	printf("Date: %d %d %d\n",
		   projectsArr[index].date.y,
		   projectsArr[index].date.m,
		   projectsArr[index].date.d);
	for (int i = 0; i < 3; i++)
		printf("%s\n", projectsArr[index].tags[i]);
	printf("\n");


	return 0;
}


// Create project file path and returns path string
int set_project_path(int index, int n, char dirName[n])
{
	char fullPath[PATH_LENGTH + 1];
	char prefix[WORD_LENGTH + 1];
	char suffix[WORD_LENGTH + 1];

	strcpy(prefix, "projects/");
	strcpy(suffix, "/");

	strcat(fullPath, prefix);
	strcat(fullPath, dirName);
	strcat(fullPath, suffix);

	strcpy(projectsArr[index].path, fullPath);

	return 0;
}


// Separate title from project directory string
int get_title_from_dirname(int n, int index, char dirName[n])
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
int get_date_from_dirname(int n, int index, char dirName[n])
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
int split_date(int index, int components, int n, char dateString[n])
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
        for (int i = 0; *(tokens + i); i++) {
            /* printf("date=[%s]\n", *(tokens + i)); */

			// Copy strings into year, month and day
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
int gen_projects(void)
{
	int quanity = 0;

	char projects[BUFFER_SIZE][WORD_LENGTH];
	char blank[LEN(projects)];
	char path[PATH_LENGTH];

	// Creates array of directory name strings in the projects directory
	strcpy(path, "projects/");
	gen_clean_dir(path, WORD_LENGTH, LEN(projects), projects);

	// Find quatity of projects
	while (strcmp(projects[quanity], blank) != 0) {
		quanity++;
	}

	// Generate each project structure with parsed data
	for (int i = 0; i < quanity; i++) {
		create_project(LEN(projects), i, projects[i]);
	}

	return quanity;
}
