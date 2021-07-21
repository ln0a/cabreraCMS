#ifndef HTML_H
#define HTML_H


#include "macro.h"


// HTML tag structure
struct HTML_Tag {
	char string[WORD_LENGTH];
	char cleanString[WORD_LENGTH];
	char htmlTag[WORD_LENGTH];

	char *tagString; // template tag string

	char attributes[BUFFER_SIZE][WORD_LENGTH];
	int attributeCount;
};

// Empty HTML tag
static const struct HTML_Tag EmptyTag;


const char tagDelim[2] = {'<', '>'};
const char tagClose = '/';


int parse_html_tag(char* element, char **cmsTagString);
int clean_html_tag(int buffer, char string[buffer], char cleanString[buffer]);
int parse_html_components(int buffer, int x,
						  char input[buffer],
						  char id[buffer],char components[x][buffer]);
int parse_html_tag_attribute(char *attr, char **tagString);


#endif
