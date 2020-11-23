#include <stdio.h>
#include "macro.h"
#include "template.h"
#include "template.c"
#include "directory.h"
#include "directory.c"
#include "projects.h"
#include "projects.c"


int main(void)
{
	char inFile[] = "templates/index_template.html";
	char outFile[] = "projects/test_project_3/out.txt";

	char template_tags[][BUFFER_SIZE] = {
		"<ul id=\"projects_container\">",
		"<ul id=\"projects_tags\">",
		"<li id=\"NAME_OF_PROJECT\" class=\"project\">",
		"<ul id=\"project_tags\">",
		"<ul id=\"project_gallery\">",
	};

	printf("\n%d tags available.\n\n", LEN(template_tags));


	// Read each line in a file individually until EOF
	printf("Matched tags:\n");
	compareTagsInFile(inFile, LEN(template_tags), BUFFER_SIZE, template_tags);
	printf("\n");


	generateProjects();

	return 0;
}
