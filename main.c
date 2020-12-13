
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORD_LETTERS_MAX 32
struct word_array {
  char **data;
  size_t size;
  size_t capacity;
};

#define WILDCARDS_MAX 3
struct word_dict_bucket {
  const char *word;
  struct word_dict_bucket *next;
};
struct word_dict {
  struct word_dict_bucket **buckets;
  size_t count;
  size_t size;
};
struct wildcard {
  size_t count;
  size_t index[WILDCARDS_MAX];
};
// Part 1
static size_t get_size(const char *str){
  assert(str!=NULL);
  size_t taille=0;
  while(str[taille]!='\0'){
    taille++;
  }
  return taille;
}

bool string_are_anagrams(const char *str1, const char *str2) {
  size_t size1=get_size(str1),size2=get_size(str2);
  if(size2!=size1)
    return false;
  int mem[26]={0};
  for (int i = 0; i <= size1; ++i)
  {
    mem[str1[i]-'a']++;
  }
  for (int i = 0; i <=size1; ++i)
  {
    mem[str2[i]-'a']--;
  }
  for (int i = 0; i <26; ++i)
  {
    if(mem[i]!=0)
      return false;
  }
    return true;
}

char *string_duplicate(const char *str) {
  assert(str!=NULL);
  size_t size=get_size(str);
  char *copy = malloc(sizeof(size+1));
  for (int i = 0; i <= size; ++i)
  {
    copy[i]=str[i];
  }
  copy[size+1]='\0';
  return copy;
}

void string_sort_letters(char *str) {
  assert(str!=NULL);
  size_t size=get_size(str);
  char ch;
  int j;
  for (int i = 0; i < size; ++i){
    ch=str[i];
    j=i;
    while( j>0 && str[j-1]>ch ){
      str[j]=str[j-1];
      j--;
    }
    str[j]=ch;
  }

}

void clean_newline(char *buf, size_t size) {
}

// Part 2

void word_array_create(struct word_array *self) {
  self->capacity=10;
  self->size=0;
  self->data=calloc(self->capacity, sizeof(char*));
}

void word_array_destroy(struct word_array *self) {
   for (int i = 0; i < self->size; ++i)
   {
     free(self->data[i]);
   }
   self->size=0;
   self->capacity=0;
}

void word_array_add(struct word_array *self, const char *word) {

}

void word_array_search_anagrams(const struct word_array *self, const char *word, struct word_array *result) {
}

void word_array_sort(struct word_array *self) {
}

void word_array_print(const struct word_array *self) {
}

void word_array_read_file(struct word_array *self, const char *filename) {
  char word[WORD_LETTERS_MAX];

  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "Error when opening file '%s'\n", filename);
    return;
  }

  while (!feof(fp)) {
    fgets(word, WORD_LETTERS_MAX, fp);
    clean_newline(word, WORD_LETTERS_MAX);
    word_array_add(self, word);
  }

  fclose(fp);
}

// Part 3

void word_dict_bucket_destroy(struct word_dict_bucket *bucket) {
}

struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *bucket, const char *word) {
  return NULL;
}


void word_dict_create(struct word_dict *self) {
}

void word_dict_destroy(struct word_dict *self) {
}

size_t fnv_hash(const char *key) {
  return 0;
}

void word_dict_rehash(struct word_dict *self) {
}

void word_dict_add(struct word_dict *self, const char *word) {
}

void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array) {
}

void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result) {
}

// Part 4

void wildcard_create(struct wildcard *self) {
}

void wildcard_search(struct wildcard *self, const char *word) {
}

void word_array_search_anagrams_wildcard(const struct word_array *self, const char *word, struct word_array *result) {
}

void word_dict_search_anagrams_wildcard(const struct word_dict *self, const char *word, struct word_array *result) {
}


int main(int argc, char const *argv[])
{
	
/***** Partie 1 *****/

  const char *chaine1 = "aabbaaccbb"; 
  const char *chaine2 = "aabbaaccbb"; // meme que chaine 1
  const char *chaine3 = "aaaabbbbcc";  // meme que chaine 1 moins 1 lettre 
  const char *chaine4 = "aabbaaccbbff"; // meme que chaine 1 avec derniere lettre diff 
  const char *chaine5 = "";

//----------------------
//----------------------
//----------------------


  bool a = true,b= true,c= true,d= false, e = false;
  bool aa,bb,cc,dd, ee;

printf( "Test egalité de 2 chaines de caracteres \n"); 
printf(" TRUE ; TRUE ; TRUE ; FALSE ; FALSE \n\n") ; 

aa = string_are_anagrams(chaine1,chaine1) ;
bb = string_are_anagrams(chaine1,chaine2) ;
cc = string_are_anagrams(chaine1,chaine3) ;
dd = string_are_anagrams(chaine1,chaine4) ;
ee = string_are_anagrams(chaine1,chaine5) ;

  if (aa){
    printf("string_are_anagrams (chaine1, chaine1) == true\n");
  }else {
    printf("string_are_anagrams (chaine1, chaine1) == false\n");
  }

  if (bb){
    printf("string_are_anagrams (chaine1, chaine2) == true\n");
  }else {
    printf("string_are_anagrams (chaine1, chaine2) == false\n");
  }

    if (cc){
    printf("string_are_anagrams (chaine1, chaine3) == true\n");
  }else {
    printf("string_are_anagrams (chaine1, chaine3) == false\n");
  }

  if (dd){
    printf("string_are_anagrams (chaine1, chaine4) == true\n");
  }else {
    printf("string_are_anagrams (chaine1, chaine4) == false\n");
  }

  if (ee){
    printf("string_are_anagrams (chaine1, chaine5) == true\n");
  }else {
    printf("string_are_anagrams (chaine1, chaine5) == false\n");
  }

  if(a==aa && b == bb && c ==cc && d == dd && e == ee){
    printf("Tous les tests sont passés WOUHOU ");
  }else{
    printf("/!\\ Les test ne passe pas /!\\");
  }
  printf("\n\n");




  //***************************************$
  //***************************************$
  //***************************************$


 const char *chaine1Bis = string_duplicate(chaine1);
 //printf("%s \n",chaine1Bis);
 const char *chaine3Bis = string_duplicate(chaine3);
 // printf("%s \n",chaine3Bis);
 const char *chaine5Bis = string_duplicate(chaine5);
  // printf("%s \n",chaine5Bis);

bool id1 =str_identical(chaine1,chaine1Bis), id3 =str_identical(chaine3,chaine3Bis), id5=str_identical(chaine5,chaine5Bis);

if(id1){
    printf("string_duplicate(chaine 1) est equivalente à chaine1Bis\n");
} else {
    printf("string_duplicate(chaine 1) n'est pas equivalente à chaine1Bis\n");
    printf("Chaine1     = %s\n",chaine1);
    printf("Chaine1 Bis = %s\n",chaine1);
}


if(id3){
    printf("string_duplicate(chaine 3) est equivalente à chaine3Bis\n");
} else {
  printf("string_duplicate(chaine 3) n'est pas equivalente à chaine3Bis\n");
  printf("Chaine1     = %s\n",chaine3);
  printf("Chaine1 Bis = %s\n",chaine3);
}


if(id5){
  printf("string_duplicate(chaine 5) est equivalente à chaine5Bis\n");
} else {
  printf("string_duplicate(chaine 5) n'est pas equivalente à chaine5Bis\n");
  printf("Chaine5    = %s\n",chaine5);
  printf("Chaine Bis = %s\n",chaine5);
}

if(id1 && id3 && id5){
    printf("Tous les tests sont passés WOUHOU ");
  }else{
    printf("/!\\ Les test ne passe pas /!\\");
  }
  printf("\n\n");

  //***************************************$
  //***************************************$
  //***************************************$

  char *chaine1B = string_duplicate(chaine1);
  char *chaine2B = string_duplicate(chaine2);
  char *chaine3B = string_duplicate(chaine3);
  char *chaine4B = string_duplicate(chaine4);
  char *chaine5B = string_duplicate(chaine5);
  char *chaine6B = "aaabbbccc";

  string_sort_letters(chaine1B);
  string_sort_letters(chaine2B);
  string_sort_letters(chaine3B);
  string_sort_letters(chaine4B);
  string_sort_letters(chaine5B);


bool rang1 =string_are_anagrams(chaine1,chaine1B), rang2 =string_are_anagrams(chaine3,chaine2B),rang3 =string_are_anagrams(chaine3,chaine3B), rang4=string_are_anagrams(chaine4,chaine4B), rang5=string_are_anagrams(chaine5,chaine5B);

bool rang6 = string_are_anagrams(chaine1,chaine6B);
if(rang1){
    printf("string_sort_letters(chaine1) sont des anagrammes\n");
} else {
    printf("string_sort_letters(chaine1) ne sont pas des anagrammes\n");
}


if(rang2){
    printf("string_sort_letters(chaine2) sont des anagrammes\n");
} else {
    printf("string_sort_letters(chaine2) ne sont pas des anagrammes\n");
}


if(rang3){
  printf("string_sort_letters(chaine3) sont des anagrammes\n");
} else {
  printf("string_sort_letters(chaine3) ne sont pas des anagrammes\n");
}

if(rang4){
  printf("string_sort_letters(chaine4) sont des anagrammes\n");
} else {
  printf("string_sort_letters(chaine4) ne sont pas des anagrammes\n");
}

if(rang5){
  printf("string_sort_letters(chaine5) sont des anagrammes\n");
} else {
  printf("string_sort_letters(chaine5) ne sont pas des anagrammes\n");
}

if(!rang6){
  printf("string_sort_letters(chaine6) ne sont pas des anagrammes et c'est normal \n");
} else {
  printf("string_sort_letters(chaine6) sont des anagrammes et c'est pas normal \n");
}



if(rang1 && rang2 && rang3 && rang4 && rang5 && !rang6){
    printf("Tous les tests sont passés WOUHOU ");
  }else{
    printf("/!\\ Les test ne passe pas /!\\");
  }
  printf("\n\n");


///////////////////
///////////////////
///////////////////
 /*TEST PARTIE 2 */
///////////////////
///////////////////
///////////////////

struct word_array partie2;
word_array_create(&partie2);
//struct word_array *partie2 = malloc(sizeof(char)*100);

printf("TEST word_array_sort\n "); 

  word_array_add(&partie2, "a");
  word_array_add(&partie2, "b");
  word_array_add(&partie2, "t");
  word_array_add(&partie2, "m");
  word_array_add(&partie2, "e");
  word_array_add(&partie2, "r");
  word_array_add(&partie2, "g");
  word_array_add(&partie2, "d");


    word_array_print(&partie2);
    
    printf("C'est dans l'ordre ? \n");
    word_array_sort(&partie2);    
    word_array_print(&partie2);


  word_array_add(&partie2, "acdbq");
  word_array_add(&partie2, "dbcaw");
  word_array_add(&partie2, "adcqb");
  word_array_add(&partie2, "bcdaq");
  word_array_add(&partie2, "cdabq");
  word_array_add(&partie2, "cadbq");
  word_array_add(&partie2, "cdabq");
  word_array_add(&partie2, "cadbq");
  word_array_add(&partie2, "badcq");
  word_array_add(&partie2, "acdbq");
  word_array_add(&partie2, "dbcaw");
  word_array_add(&partie2, "adcqb");
  word_array_add(&partie2, "bcdaq");
  word_array_add(&partie2, "cdabq");
  word_array_add(&partie2, "cadbq");
  word_array_add(&partie2, "badcq");


printf("\n\n");

printf("\n ====== Test word_array_search_anagrams =======\n\n");

struct word_array result;
word_array_create(&result);

word_array_search_anagrams(&partie2, "abcd", &result);

printf("Il ne doit pas y avoir d'anagramme  : \n \n ");
if(result.size != 0){
  word_array_print(&result);
} else {
  printf("Il n'y a pas d'anagramme\n ");
}




struct word_array result2;
word_array_create(&result2);

word_array_search_anagrams(&partie2, "cdabq", &result2);
printf("\n----\n\nIl doit y avoir d'anagramme  de 'a b c d q': \n\n");

if(result2.size != 0){
  word_array_print(&result2);
} else {
  printf(" Il n'y a pas d'anagramme \n");

}
printf("\n\n");

	return 0;
}