#ifndef CONTENT_H
#define CONTENT_H


#include "macro.h"


struct VisualContent {
	char filename[PATH_LENGTH]; // full filename with format
	char file[PATH_LENGTH]; // just name
	char format[WORD_LENGTH]; // just extension
};


int gen_description(int index);
int gen_visual_content(int index);
int split_filename(int index, int j, int m, char filename[m],
				   int n, int buffer, char outArr[n][buffer]);


#endif
