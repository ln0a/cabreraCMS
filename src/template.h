#ifndef TEMPLATE_H
#define TEMPLATE_H


#include "macro.h"


char templateTags[][BUFFER_SIZE] = {
	"projects_index",
	"projects_tags",
	"projects_gallery",
	"project",
	"project_tags",
	"project_text",
	"project_gallery",
};
int templateTagsIndex[LEN(templateTags)];

int gen_html_from_template(int m, char indexTemplatePath[m],
						   int n, char outputPath[n],
						   int projectIndex);
int gen_html_project_item(int index, int m, int tagsIndex[m],
						  int buffer, char output[buffer]);
int gen_html_gallery_item (int index, int buffer, char output[buffer]);
void index_template_tags(char *template);


#endif
