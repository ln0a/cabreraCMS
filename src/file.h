#ifndef FILE_H
#define FILE_H


char *read_line(char filePath[], int lineNumber);
void trim_whitespace(char *str);
void trim_quotes(char *str);
int cmp_str_to_arr(char line[], int tagsLength, int buffer, char tags[tagsLength][buffer]);
void cmp_arr_in_file(char file[], int tagsLength, int buffer, char tags[tagsLength][buffer]);


#endif
