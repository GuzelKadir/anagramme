#include "anagrammes.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Part 1
static size_t get_size(const char *str){
  assert(str!=NULL);
  size_t taille=0;
  while(str[taille]!='\0'){//through the list until the end
    taille++;
  }
  return taille;
}

bool string_are_anagrams(const char *str1, const char *str2) {//tell if 2 string are anagramme
  size_t size1=get_size(str1),size2=get_size(str2);
  if(size2!=size1)
    return false;
  int mem[26]={0};
  for (int i = 0; i < size1; ++i)
  {
    mem[str1[i]-'a']++;
  }
  for (int i = 0; i <size1; ++i)
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
  char *copy=malloc((size+1)*sizeof(char));
  for (int i = 0; i < size; ++i){
    copy[i]=str[i];//create a copy of str
  }
  copy[size]='\0';
  return copy;
}

void string_sort_letters(char *str) {
  assert(str!=NULL);
  size_t size=get_size(str);
  char ch;
  int j;
  for (int i = 0; i < size; ++i){// sort letters
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
  size=strlen(buf)+1;
  for (int i = 0; i < size; ++i)
  {
    if (buf[i]=='\n'){
      buf[i]='\0';
      return;
    }
  }
}

// Part 2

void word_array_create(struct word_array *self) {//create a word array struct
  self->capacity=10;
  self->size=0;
  self->data=calloc(self->capacity, sizeof(char*));
}

void word_array_destroy(struct word_array *self) {
   for (int i = 0; i < self->size; ++i)
   {
     free(self->data[i]);// destroy a word array structure
   }
   self->size=0;
   self->capacity=0;
   free(self->data);
}

static void grow(struct word_array *self){
  self->capacity = self->capacity*2;// increase the capacity of the array
  char **new=calloc(self->capacity,sizeof(char*));
  memcpy(new,self->data,self->size*sizeof(char*));
  free(self->data);
  self->data=new;
}


void word_array_add(struct word_array *self, const char *word) {
  if(self->size >= self->capacity)
    grow(self);
  size_t size=get_size(word);
  char *w = string_duplicate(word);
  self->data[self->size]=calloc(size+1,sizeof(char*));
  for (int i = 0; i < size; ++i)
  {
    self->data[self->size][i]=w[i];//add a word to array word struct
  }
  //self->data[self->size][size+1]='\0';
  self->size++;
  free(w);
}

void word_array_search_anagrams(const struct word_array *self, const char *word, struct word_array *result) {
  for (int i = 0; i < self->size; ++i){
    if (string_are_anagrams(self->data[i],word))//test if word and data[i] are anagrams
      word_array_add(result,self->data[i]);
  }
}

static void array_merge(struct word_array *self, size_t i, size_t m, size_t j , struct word_array *tmp){
  size_t a=i;
  size_t b=m;
  bool test=false;
  for (int k =i ; k < j; ++k){
    if(a<m && (b==j || strncmp(self->data[a],self->data[b],4)<0))
      test=true;
    if(a<m && (b==j || test)){
      tmp->data[k]=self->data[a];
      a++;
    }else{
      tmp->data[k]=self->data[b];
      b++;
    }
  }
}
static void array_merge_sort_partial(struct word_array *self, size_t i, size_t j, struct word_array *tmp){
  if (j-i<2)
    return;
  size_t m =(i+j)/2;
  array_merge_sort_partial(self,i,m,tmp);
  array_merge_sort_partial(self,m,j,tmp);
  array_merge(self,i,m,j,tmp);
  memcpy((self->data)+i,(tmp->data)+i,(j-i)*sizeof(char*));
}
static void array_merge_sort(struct word_array *self, size_t n){
  struct word_array tmp;
  tmp.capacity=n;
  tmp.data=calloc(n,sizeof(char *));
  array_merge_sort_partial(self,0,n,&tmp);
  //word_array_destroy(&tmp);
  free(tmp.data);
}

void word_array_sort(struct word_array *self) {
  array_merge_sort(self,self->size);//sort the array with an efficace sort
}

void word_array_print(const struct word_array *self) {
  for (int i = 0; i < self->size; ++i){
    printf("%s\n",self->data[i]);//print contents of self's array
  }
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
  struct word_dict_bucket *current;
  while(bucket!=NULL){//destroy a bucket
    current=bucket;
    bucket=bucket->next;
    free(current);
  }
}

struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *bucket, const char *word) {
  struct word_dict_bucket *new= malloc(sizeof(struct word_dict_bucket));//create a new bucket
  new->word = word;//add a bucket
  new->next = bucket;
  return new;
}

void word_dict_create(struct word_dict *self) {
  self->count=0;//size
  self->size=10;//capacity
  self->buckets=calloc(self->size, sizeof(struct word_dict_bucket*));
  for (int i = 0; i < self->size; ++i){
    self->buckets[i]=NULL;//initialize the bucket for NULL
  }
}
void word_dict_destroy(struct word_dict *self) {
  for (int i = 0; i < self->size; ++i){
    word_dict_bucket_destroy(self->buckets[i]);//destroy and word dict bucket
  }
  free(self->buckets);
}

size_t fnv_hash(const char *key) {//hash an string 
  char *cpy=malloc((strlen(key)+1)*sizeof(char));
  memcpy(cpy,key,(strlen(key)+1)*sizeof(char));
  string_sort_letters(cpy);
  size_t hash=0,size = strlen(cpy);
  char c;
  int a;
  for (int i = 0; i < size; ++i){
    c=cpy[i];
    a = c - '0';
    hash=(hash * 10)+a;
  }
  free(cpy);
  return hash;
}

void word_dict_rehash(struct word_dict *self) {//reash all the word in an word dict , grow this one and put the word inside
  size_t newsize=self->size*2;
  struct word_dict_bucket **new = calloc(newsize, sizeof(struct word_dict_bucket*));
  for (int i = 0; i < newsize; ++i){
    new[i]=NULL;
  }
  struct word_dict_bucket *current;
  size_t index;
  for (int i = 0; i < self->size; ++i){
    current=self->buckets[i];
    while(current!=NULL){
      index = fnv_hash(current->word)%newsize;
      new[index]=word_dict_bucket_add(new[index],current->word);
      current=current->next;
    }
  }
  word_dict_destroy(self);
  self->size=newsize;
  self->buckets=new;
}

void word_dict_add(struct word_dict *self, const char *word) {
  if(((double)self->count/self->size)>=0.5){// if the quotient is > 0.5 then we rehash
    word_dict_rehash(self);
  }
  size_t indice = fnv_hash(word)%self->size;
  self->buckets[indice]=word_dict_bucket_add(self->buckets[indice],word);
  self->count++;
}

void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array) {
  for (int i = 0; i < array->size; ++i){
    word_dict_add(self,array->data[i]);//add in the word dict from an array
  }
}

void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result) {
  size_t index = fnv_hash(word)%self->size;
  struct word_dict_bucket *current=self->buckets[index];
  while(current!=NULL){
    if (string_are_anagrams(word,current->word))//compare if these word are anagrame
    {
      word_array_add(result,current->word);//if they are anagram add the word into result
    }
    current=current->next;
  }
}

// Part 4

void wildcard_create(struct wildcard *self) {//create an empty wildcard
  self->count=0;
  /*
  for (int i = 0; i < 4; ++i){
    self->index[i]=0;
  }
  */
}

void wildcard_search(struct wildcard *self, const char *word) {//search for joker in a string 
  size_t size = strlen(word);
  for (int i = 0; i < size; ++i){
    if (word[i]=='*'){
      self->count++;
      self->index[self->count-1]=i;
    }
  }
}

static bool empty_int_array(int *data){//tell if an array of int is empty
  for (int i = 0; i < 26; ++i){
    if (data[i]!=0){
      return false;
    }
  }
  return true;
}

void word_array_search_anagrams_wildcard(const struct word_array *self, const char *word, struct word_array *result) {
  struct wildcard *w=malloc(sizeof(struct wildcard));
  wildcard_create(w);
  wildcard_search(w,word);
  if (w->count==0){//if there is 0 joker
    word_array_search_anagrams(self,word,result);
    free(w);
    return;
  }
  for (int i = 0; i < self->size; ++i){
    size_t sizedata = strlen(self->data[i]);
    if (strlen(word)!=sizedata){
      continue;
    }
    int mem[26]={0};
    size_t sizeword= strlen(word);
    for (int j = 0; j < sizeword; ++j){
      if (word[j]!='*'){
        mem[word[j]-'a']++;
      } 
    }
    for (int k = 0; k < sizedata; ++k){
      if (mem[self->data[i][k]-'a']>0){
        mem[self->data[i][k]-'a']--;
      }
    }
    if (empty_int_array(mem)){//if mem is empty then add the word into result
      word_array_add(result,self->data[i]);
    }
  }
  free(w);
}

static bool exist_int_array(int val,int *data,struct wildcard *j){//tell us if and value already exist inside an array
  size_t size = 26*j->count;
  for (int i = 0; i < size; ++i){
    if (val==data[i])
    {
      return true;
    }
  }
  return false;
}


static void word_rec(char *word, struct wildcard *j,int pos,int *data,int count){//replace recursivly all the jokers into letter from a to z
  if (pos==-1){
    for (int i = 0; i < j->count; ++i){
      word[j->index[i]]='a';
    }
    pos=0;
    count=0;
  }
  if(word[j->index[pos]]!='z'){
    int hash =fnv_hash(word);
    if (!exist_int_array(hash,data,j)){
      data[count]=fnv_hash(word);
      count++;
    }
    word[j->index[pos]]=word[j->index[pos]]+1;
    word_rec(word,j,pos,data,count);
  }else {
    if(pos+1<j->count){
      word[j->index[pos]]='a';
      word_rec(word,j,pos+1,data,count);
  }
  }
}






void word_dict_search_anagrams_wildcard(const struct word_dict *self, const char *word, struct word_array *result) {
  struct wildcard *w=malloc(sizeof(struct wildcard));
  wildcard_create(w);
  wildcard_search(w,word);
  if (w->count==0){// if there is 0 joker
    word_dict_search_anagrams(self,word,result);
    free(w);
    return;
  }
  int *data=malloc((26*w->count)*sizeof(int));
  for (int i = 0; i < (26*w->count); ++i){
    data[i]=0;
  }
  size_t size = strlen(word);
  char *tmp;//malloc(strlen(word)*sizeof(char));
  tmp=string_duplicate(word);
  word_rec(tmp,w,-1,data,0);
  free(tmp);
  size_t indice;
  struct word_dict_bucket *current;
  for (int i = 0; i < (26*w->count); ++i){
    indice=data[i]%self->size;
    current=self->buckets[indice];
    while(current!=NULL){//get all the word inside the bucket
      size_t s = strlen(current->word);
      if (s==size)
      {
        word_array_add(result,current->word);//add it into reesult
      }
      current=current->next;
    }
  }
  printf("(This result isn't correct!)\n");
  free(w);
  free(data);
}
