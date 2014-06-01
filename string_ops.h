#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <sys/types.h>
#include <stdbool.h>

size_t strlcat(char *dst, const char *src, size_t siz);
size_t strlcpy(char *dst, const char *src, size_t siz);
char *rand_str(char *dst, int size);
int char_type_counter(char *string,char type);
void chomp(char * str);
char *payload_injector(char * ptr,char * payload,int counter);
int strstr_regex(char *string, char *expression);
char *StrRep(char *st,char *orig,char *repl,const int mim);
int split_request(char *header,char *data,char *method,char *NameFile);

