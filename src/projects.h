#ifndef PROJECTS_H
#define PROJECTS_H


#include "macro.h"
#include "content.h"


// Date structure
struct date {
	char dateStr[10];
	int y;
	int m;
	int d;
};

// Project structure
struct Project {
	// Content
	char title[WORD_LENGTH + 1];

	char *text;
	char *html;
	char textSplit[BUFFER_SIZE][WORD_LENGTH + 1];

	struct VisualContent VisualContentArr[BUFFER_SIZE];
	int visualContentCount;

	char tags[BUFFER_SIZE][WORD_LENGTH + 1];
	int tagsCount;

	// Meta-data
	struct date date;
	char location[WORD_LENGTH + 1];

	// Accessibility
	char path[PATH_LENGTH + 1];
};

struct Project ProjectsArr[BUFFER_SIZE]; // Array of projects
int projectsCount = 0;


int create_project(int n, int index, char dirName[n]);
int set_project_path(int index, int n, char dirName[n]);
int get_title_from_dirname(int n, int index, char dirName[n]);
int get_date_from_dirname(int n, int index, char dirName[n]);
int split_date(int index, int components, int n, char longString[n]);
void print_project_data(int index);
int gen_projects(void);


#endif
