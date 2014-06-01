#include "string_ops.h"

// functions strlcat.c,strlcpy from OpenBSD 
/*
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
size_t strlcat(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;

	while (n-- != 0 && *d != '\0')
		d++;

	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return(dlen + strlen(s));

	while (*s != '\0') 
	{
		if (n != 1) 
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));	
}

size_t strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

/* Copy as many bytes as will fit */
	if (n != 0) 
	{
		while (--n != 0) 
		{
			if ((*d++ = *s++) == '\0')
				break;
		}
	}
/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) 
	{
		if (siz != 0)
			*d = '\0';	/* NUL-terminate dst */
		while (*s++)
		;
	}

	return(s - src - 1);	/* count does not include NUL */
}


// 0d1n's strings functions...
char *rand_str(char *dst, int size)
{
	static const char text[] =	"abcdefghijklmnopqrstuvwxyz"
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i, len = rand() % (size - 1);
  
	if(!len) 
		len=8;
 
	for(i=0; i<len; ++i)
		dst[i] = text[rand() % (sizeof text - 1)];
   
	dst[i] = '\0';

	return dst;
}

int char_type_counter(char *string,char type)
{
	int counter=0;
 
	while(*string != '\0')
	{
		if(*string==type) 
			counter++;
		string++;
	}
  
	return counter;
}


void chomp(char * str)
{
 
	while (*str) 
	{
		if (*str == '\n' || *str == '\r') 
		{
			*str = 0;
			return;
		}
		str++;
	}
  
}

char *payload_injector(char * ptr,char * payload,int counter)
{
	char *new=(char *)malloc((strlen(ptr)+strlen(payload)+2)*sizeof(char));
	short i=0,x=1;

	memset(new, 0,sizeof(char)*(strlen(ptr)+strlen(payload)+1));

	while(*ptr != '\0')
	{
		if(*ptr == '!')
		{
			if(counter==x)
			{
				strlcat(new,payload, strlen(new)+strlen(payload)+1 );
				i+=strlen(payload);
			}
			x++;
		} else {
 			*(new+i)=*ptr;
			i++;
		}
 		ptr++;
 	}

	return new;
}


int strstr_regex(char *string, char *expression)
{

	regex_t regex;
	int reti;

// Compile regular expression
	reti = regcomp(&regex, expression, 0);

	if(reti) 
		fprintf(stdout, "Could not compile regex\n at match_regex() function \n");

	reti = regexec(&regex, string, 0, NULL, 0);

	regfree(&regex);
  
	if(!reti)
		return 1;
	else 
		return 0;

}


//string replace
char *StrRep(char *st,char *orig,char *repl,const int mim) 
{
	char bufer[mim];
	char *ch;

	if(!(ch = strstr(st, orig)))
		return st;

	strncpy(bufer, st, ch-st);  
	bufer[ch-st] = 0;
	sprintf(bufer+(ch-st),"%s%s",repl,ch+strlen(orig));

	char *out=bufer;

	return out;
}

// return lines from file, example:  const char *buff=readLine("log.txt"),printf("%s",buff);
int split_request(char *header,char *data,char *method,char *NameFile)
{
	FILE * file;
	bool sinal=false,first=true;

	file = fopen(NameFile, "r");
	if(!file)
	{
		puts("error in file"); 	 
		return 0;
	}


	char line[256];
	char *header2=(char *)malloc(sizeof(char)*1024);
	char *data2=(char *)malloc(sizeof(char)*1024);
	char *method2=(char *)malloc(256*sizeof(char));

	while(fgets(line,sizeof line-1,file))  
	{
  
		if(strlen(line)< 5)
		{
			sinal=true;
		}
		if(first==true)
		{
			strncat(method2,line,255);
			first=false;
		} else {
			if(sinal==false)
			{ 
//    header=realloc(header,strlen(header)+strlen(line)+1);
				strncat(header2,line,1023);
			} else {
//    header=realloc(data,strlen(data)+strlen(line)+1);
				strncat(data2,line,1023);
			}
		}
 
	}
	strncpy(data,data2,1023);
	strncpy(header,header2, 1023);
	method2=strtok(method2,"\r\n"); 
	strncpy(method,method2,255);

	free(data2);
	free(header2);
	free(method2);

	fclose(file); 
 
	return 1;
}





