#ifndef DIRECTORY_H
#define DIRECTORY_H


#include "macro.h"


char ignoredItems[][WORD_LENGTH] = {
	".",
	"..",
	"src",
	"templates",
	"cabreraCMS",
	".git",
	".ccls-cache",
	".DS_Store"
};

int explore_directory(char path[], int buffer, int n, char arr[buffer][n]);
int clean_dir_list(int m, int n, int o, int buffer,
				 char arr1[m][buffer], char arr2[n][buffer], char arrOut[o][buffer]);
int gen_clean_dir(char path[], int buffer, int n, char arrOut[buffer][n]);


#endif
