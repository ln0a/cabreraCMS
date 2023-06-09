#ifndef PROJECTS_H
#define PROJECTS_H


#include "macro.h"


// Date structure
struct Date {
	char dateStr[10];
	int y;
	int m;
	int d;
};

// Visual Content structure
struct VisualContent {
	char filename[PATH_LENGTH]; // full filename with format
	char file[PATH_LENGTH]; // just name
	char format[WORD_LENGTH]; // just extension
};

// Project structure
struct Project {
	// Content
	char title[WORD_LENGTH + 1];
	char hyphenatedTitle[WORD_LENGTH + 1];
	char unhyphenatedTitle[WORD_LENGTH + 1];

	char *text;
	char *textHTML;
	char *data;
	char *dataHTML;
	char textSplit[BUFFER_SIZE][WORD_LENGTH + 1];

	struct VisualContent VisualContentArr[VISUAL_BUFFER];
	int visualContentCount;

	char tags[BUFFER_SIZE][WORD_LENGTH + 1];
	char tagsHyphenated[BUFFER_SIZE][WORD_LENGTH + 1];
	int tagsCount;

	// Meta-data
	struct Date date;
	char location[WORD_LENGTH + 1];

	// Accessibility
	char path[PATH_LENGTH + 1];
};

struct Project ProjectsArr[BUFFER_SIZE]; // Array of projects
int projectsCount = 0;


int create_project(int n, int index, char dirName[n]);
int set_project_path(int index, int n, char dirName[n]);
int get_title_from_dirname(int n, int index, char dirName[n]);
void hyphenate_title(char *title);
void unhyphenate_title(char *title);
int get_date_from_dirname(int n, int index, char dirName[n]);
int split_date(int index, int components, int n, char longString[n]);
void print_project_data(int index);
int gen_projects(void);


#endif
