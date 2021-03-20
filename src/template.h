#ifndef TEMPLATE_H
#define TEMPLATE_H


#include "macro.h"


char templateTags[][BUFFER_SIZE] = {
	"projects_container",
	"projects_tags",
	"project",
	"project_tags",
	"project_text",
	"project_gallery",
};
int templateTagsIndex[LEN(templateTags)];

int gen_html_from_template(int m, char templatePath[m], int n, char outputPath[n],
						   int o, int buffer, char templateTags[o][buffer]);
int gen_html_project_item(int index, int m, int tagsIndex[m],
						  int buffer, char output[buffer]);
void index_template_tags(char template[]);


#endif
