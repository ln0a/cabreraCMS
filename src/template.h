#ifndef TEMPLATE_H
#define TEMPLATE_H

char *readLine(char filePath[], int lineNumber);
void trimwhitespace(char *str);
int compareLineToTags(char line[], int tagsLength, int buffer, char tags[tagsLength][buffer]);
void compareTagsInFile(char file[], int tagsLength, int buffer, char tags[tagsLength][buffer]);

#endif
