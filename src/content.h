#ifndef CONTENT_H
#define CONTENT_H


#include "macro.h"


int gen_description(int index);
int gen_data(int index);
int gen_visual_content(int index);
int split_filename(int index, int j, int m, char filename[m],
				   int n, int buffer, char outArr[n][buffer]);


#endif
