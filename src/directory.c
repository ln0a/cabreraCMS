#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "directory.h"
#include "macro.h"

/*********************************************\

  DIRECTORY STRUCTURE (2 LEVELS):

  projects               >  project1  >  .txt
  self-defined:             project2     .img
  about                     project3     .png
  contact                                .mp4
  etc.
  { ignore following: }
  src
  templates
  cabreraCMS

\********************************************/

char dirList[BUFFER_SIZE][WORD_LENGTH];
char dirListFull[BUFFER_SIZE][WORD_LENGTH];
char dirListIgnored[][WORD_LENGTH] = {
	".",
	"..",
	"src",
	"templates",
	"cabreraCMS",
	".git",
	".ccls-cache"
};


// Explore directory structure and add to arrays
int exploreDirectory(char path[])
{
	struct dirent *item;

	DIR *dir = opendir(path);

	if (dir == NULL) {
		printf("Could not open the current directory.");
		return 0;
	}

	int i = 0;
	while ((item = readdir(dir)) != NULL) {
		// Add directories to dirList array
		strcpy(dirListFull[i], item->d_name);
		i++;
	}

	closedir(dir);
	return 1;
}


// Remove ignored items from directory list
int cleanDirList(void)
{
	int index, k = 0;

	for (int i=0; i < LEN(dirListFull); i++) {
		index = 0;
		for (int j=0; j < LEN(dirListIgnored); j++) {
			if (strcmp(dirListFull[i], dirListIgnored[j]) != 0) {
				// Strings are not the same
				index++;
			}
		}

		// No match has been found
		if (index == LEN(dirListIgnored)) {
			strcpy(dirList[k], dirListFull[i]);
			k++;
		}
	}

	return 0;
}
