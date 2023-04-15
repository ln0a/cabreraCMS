#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "macro.h"
#include "main.h"
#include "projects.h"
#include "template.h"


int main(int argc, char *argv[])
{
	int opt;
	char *indexTemplateFile = defaultIndexTemplateFile;
	char *projectTemplateFile = defaultProjectTemplateFile;
	char *indexOutputFile = defaultIndexOutputFile;
	char *help =
		"CabreraCMS Version 0.2\n"
		"\n"
		"Usage: cabreraCMS [option1] [file1] [option2] [file2] [options...]\n"
		"\n"
		"Options:\n"
		"-i <file> define index template path (defaults to templates/index_template.html)\n"
		"-p <file> define project template path (defaults to templates/project_template.html)\n"
		"-o <file> define output path (defaults to index.html)\n"
		"\n"
		"-s        generate site into a single file (default)\n"
		"-m        generate site into multiple files (1 per project)\n"
		"\n"
		"-v        view verbose output\n"
		"-h        see this help page again\n";


	// Go through program arguments
	while ((opt = getopt(argc, argv, "i:p:o:s:m:vh")) != -1) {
		switch(opt) {
		case 'i':
			indexTemplateFile = optarg;
			break;
		case 'p':
			projectTemplateFile = optarg;
			break;
		case 'o':
			indexOutputFile = optarg;
			break;
		case 's':
			outputMode = 0;
			break;
		case 'm':
			outputMode = 1;
			break;
		case 'v':
			verboseMode = 1;
			break;
		case 'h':
		default:
			printf("%s", help);
			break;
		}
	}


	// Check what template tags are available
	index_template_tags(indexTemplateFile);

	// Generate projects structures and fill with content
	gen_projects();



	// Generate html file(s) from template file(s)
	if (outputMode == 0) {
		// Single file mode
		gen_html_from_template(strlen(indexTemplateFile), indexTemplateFile,
							   strlen(indexOutputFile), indexOutputFile, 0);
	}
	else {
		// Multi file mode
		gen_html_from_template(strlen(indexTemplateFile), indexTemplateFile,
							   strlen(indexOutputFile), indexOutputFile, 0);

		for (int i = 0; i < projectsCount; i++) {
			char projectPath[PATH_LENGTH + 1];
			strcpy(projectPath, ProjectsArr[i].path);

			char *projectOutputFile = strcat(projectPath, "index.html");
			gen_html_from_template(strlen(projectTemplateFile), projectTemplateFile,
								   strlen(projectOutputFile), projectOutputFile,
								   i);
		}
	}

	return 0;
}
