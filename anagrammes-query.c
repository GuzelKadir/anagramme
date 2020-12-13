#include "anagrammes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#define BUFSIZE 512


int main(int argc, char *argv[]) {
	struct word_array w,res1,res2;
	word_array_create(&w);
	
	word_array_read_file(&w,"dictionnaire.txt");

    struct word_dict d;
	word_dict_create(&d);
	word_dict_fill_with_array(&d,&w);
	struct timeval start,end;
	//struct timezone tz;
	
  	char buf[BUFSIZE];
  	for (;;) {
  		

    	printf(">");
    	fgets(buf, BUFSIZE, stdin);
    	clean_newline(buf, BUFSIZE);
    	size_t count=0,size=strlen(buf);
    	bool incorrect=false;
    	for (int i = 0; i <size ; ++i){
    		if (buf[i]!='*' && (buf[i]<'a'||buf[i]>'z')){
    			incorrect=true;
    		}
			if (buf[i]=='*')
				count++;
    	}
    	if (incorrect){
    		printf("Usage: [a-z]or'*'\n");
    		continue;
    	}
    	if(count>4)
    		continue;
    	if (strcmp(buf,"")==0){
    		break;
    	}
    	word_array_create(&res1);
    	gettimeofday(&start,NULL);
    	word_array_search_anagrams_wildcard(&w,buf,&res1);
    	gettimeofday(&end,NULL);
    	word_array_sort(&res1);
    	printf("Array of word:\n");
    	printf("Number of anagram found: %ld\n",res1.size);
    	word_array_print(&res1);
    	printf("Search finish in %ld µsecs\n",((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
    	printf("\n");
    	
    	word_array_create(&res2);
    	printf("dict of word:\n");
    	gettimeofday(&start,NULL);
    	word_dict_search_anagrams_wildcard(&d,buf,&res2);
    	gettimeofday(&end,NULL);
    	word_array_sort(&res2);
    	printf("Number of anagram found: %ld\n",res2.size);
    	word_array_print(&res2);
    	printf("Search finish in %ld µsecs\n",((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
    	printf("\n");
    	word_array_destroy(&res2);
    	word_array_destroy(&res1);	
  	}
  word_array_destroy(&w);
  word_dict_destroy(&d);
  return 0;
}
