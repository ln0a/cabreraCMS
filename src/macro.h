#ifndef MACRO_H
#define MACRO_H


#define BUFFER_SIZE 512
#define LINE_SIZE 2048

#define WORD_LENGTH 256 // single word buffer
#define PATH_LENGTH 512 // path buffer
#define TEXT_LENGTH 32768 // long text buffer

#define DIR_LEVELS 2

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))


extern char *optarg;

char *defaultInputFile = "templates/index_template.html";
char *defaultOutputFile = "templates/index_template.html";

int verboseMode = 0;


#endif
