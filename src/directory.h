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
	".ccls-cache"
};

int exploreDirectory(char path[], int buffer, int n, char arr[buffer][n]);
int cleanDirList(int m, int n, int o, int buffer,
				 char arr1[m][buffer], char arr2[n][buffer], char arrOut[o][buffer]);
int createCleanDirectory(char path[], int buffer, int n, char arrOut[buffer][n]);


#endif
