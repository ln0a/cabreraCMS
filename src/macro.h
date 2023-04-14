#ifndef MACRO_H
#define MACRO_H


#define BUFFER_SIZE 512
#define LINE_SIZE 2048

#define WORD_LENGTH 256 // single word buffer
#define PATH_LENGTH 512 // path buffer
#define TEXT_LENGTH 1000000 // long text buffer
#define VISUAL_BUFFER 2048 // max count of images

#define DIR_LEVELS 2

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))


extern char *optarg;

char *defaultIndexTemplateFile = "templates/index_template.html";
char *defaultProjectTemplateFile = "templates/project_template.html";
char *defaultIndexOutputFile = "index.html";

int verboseMode = 0;

// 0 = Single file mode
// 1 = Multi file mode
int outputMode = 0;

#endif
