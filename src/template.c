#include <stdio.h>
#include <string.h>

#include "macro.h"
#include "file.h"
#include "projects.h"
#include "tags.h"

#include "template.h"



// Generate the output html file from template.html and project structs
int gen_html_from_template(int m, char templatePath[m], int n, char outputPath[n],
						   int o, int buffer, char templateTags[o][buffer])
{
	FILE *output;

	/* char *outputHTML = "test1"; */
	char outputHTML[TEXT_LENGTH] = {0};

	// Open working files
	output = fopen(outputPath, "w");

	// Loop through template file
	int i = 0;
	while (read_line(templatePath, i) != NULL) {
		char line[LINE_SIZE] = {0};
		char linecpy[LINE_SIZE] = {0};
		strcpy(line, read_line(templatePath, i));
		strcpy(linecpy, line);

		// Check if line matches a template tag
		int templateTagIndex;
		trim_whitespace(linecpy);
		templateTagIndex = cmp_str_to_arr(linecpy, o, buffer, templateTags);

		if (templateTagIndex != -1) {
			switch (templateTagIndex) {
				// <ul> projects_container
				case 0:
					// just copy line
					strcat(outputHTML, line);
					break;

				// <ul> projects_tags
				case 1:
					// copy line before tags
					strcat(outputHTML, line);

					// copy global tags into output
					for (int i = 0; i < globalTagNum; i++) {
						strcat(outputHTML, "<li>");
						strcat(outputHTML, globalTags[i]);
						strcat(outputHTML, "</li>\n");
					}

					break;

				// <li> NAME_OF_PROJECT
				case 2:
					// loop through all projects
					for (int i = 0; i < projectsCount; i++) {
						char content[TEXT_LENGTH] = {0};

						strcat(outputHTML, "<li id=\"");
						strcat(outputHTML, ProjectsArr[i].title);
						strcat(outputHTML, "\" class=\"project\">");
						strcat(outputHTML, "\n");

						gen_html_project_item(i, LEN(templateTagsIndex), templateTagsIndex,
											  LEN(content), content);
						strcat(outputHTML, content);

						strcat(outputHTML, "</li>\n");
					}

					break;

				default:
					break;
			}

		}
		else {
			// Concat current line onto outputHTML
			strcat(outputHTML, line);
		}

		i++;
	}

	// Copy outputHTML into output file
	fprintf(output, "%s", outputHTML);

	// Close files
	fclose(output);

	return 0;
}


// Generate html output of project based on available tags
int gen_html_project_item(int index, int n, int tagsIndex[n], int buffer, char output[buffer])
{
	for (int i = 0; i < n; i++) {
		switch (i) {
			// <ul> project_tags
			case 3:
				if (tagsIndex[i] == 1) {
					strcat(output, "<ul id=\"project_tags\">\n");

					for (int j = 0; j < ProjectsArr[index].tagsCount; j++) {
						strcat(output, "<li>");
						strcat(output, ProjectsArr[index].tags[j]);
						strcat(output, "</li>\n");
					}

					strcat(output, "</ul>\n");
				}

				break;

			// <ul> project_text
			case 5:
				if (tagsIndex[i] == 1) {
					strcat(output, "<ul id=\"project_text\">\n");
					strcat(output, ProjectsArr[index].html);
					strcat(output, "</ul>\n");
				}
				break;

			// <ul> project_gallery
			case 4:
				if (tagsIndex[i] == 1) {
					strcat(output, "<ul id=\"project_gallery\">\n");
					for (int j = 0; j < ProjectsArr[index].visualContentCount; j++) {
						strcat(output, "<img src=\"");
						strcat(output, ProjectsArr[index].path);
						strcat(output, ProjectsArr[index].VisualContentArr[j].filename);
						strcat(output, "\">\n");
					}
					strcat(output, "</ul>\n");
				}
				break;
		}
	}

	return 0;
}


// Loop through template file and declare if tag exists with 1 or 0
// in templateTagsIndex global array
void index_template_tags(char template[])
{
	int i = 0;
	int cmp;

	// Loop through template file
	while (read_line(template, i) != NULL) {
		// Empty line on each loop
		char line[LINE_SIZE + 1] = {0};
		strcpy(line, read_line(template, i));
		trim_whitespace(line);

		// Returns index of item in array that matches string
		cmp = cmp_str_to_arr(line, LEN(templateTags), BUFFER_SIZE, templateTags);

		// Loop through template tags
		for (int i = 0; i < LEN(templateTagsIndex); i++) {
			// index matches
			if (cmp == i) {
				templateTagsIndex[i] = 1;
			}
		}

		i++;
	}
}
