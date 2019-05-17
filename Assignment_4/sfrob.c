#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

int frobcmp(char const* a, char const* b);
int cmp(const void* a, const void* b);
void printWord(char const* a);

int main(void){
  
  char* buf = (char*) malloc(BUFFER_SIZE);
  if(buf == NULL){
    fprintf(stderr, "Error: Unable to allocate memory");
    exit(1);
  }
  
  _Bool eof = feof(stdin);
  int numChars = 0;
  int numWords = 0;
  int bufSize  = BUFFER_SIZE;

  
  while(!eof){
    char ch = getchar();
    eof = feof(stdin);

    // Buffer change
    if(numChars >= bufSize - 1){
      bufSize *= 2;
      buf = (char*) realloc(buf, bufSize);
      if(buf == NULL){
	fprintf(stderr, "Error: Unable to allocate memory");
	exit(1);
      }
    }


    if(!eof){
      if(ch == '\n') ch = ' ';
      if(ch == ' ' && numChars > 0 && buf[numChars-1] == ' ')
	continue;
      buf[numChars++] = ch;
    }else{
      if(numChars > 0 && buf[numChars-1] != ' '){
	ch = ' ';
	buf[numChars++] = ch;
      }
    }

    if(ch == ' ')
      numWords++;
    
  }


  char** list;

  list = malloc(sizeof(char*) * numWords);
  if(list == NULL){
    fprintf(stderr, "Error: Unable to allocate memory");
    exit(1);
  }
  
  char *tempStr;
  int temp;

  tempStr = buf;
  temp = 0;

  int i;
  for(i=0; i<=numChars; i++){
    if(buf[i] == ' '){
      list[temp++] = tempStr;
      tempStr = buf+i+1;
    }
  }


  qsort(list, numWords, sizeof(char**), cmp);


  for(i=0; i<numWords; i++){
    printWord(list[i]);
  }

  
  free(list);
  free(buf);
  return 0;
}

int cmp(const void* a, const void* b){
  char* x = (char*) *((const char**)a);
  char* y = (char*) *((const char**)b);

  return frobcmp(x,y);
}

int frobcmp(char const* a, char const* b){
  while( *a != ' ' && *b != ' '){
    char x,y;
    x = (*a) ^ 0x2a;
    y = (*b) ^ 0x2a;

    if(x < y) return -1;
    if(x > y) return  1;

    if(*(a+1) == ' ' && *(b+1) != ' ') return -1;
    if(*(b+1) == ' ' && *(a+1) != ' ') return  1;
    
    a++; b++;
  }
  return 0;
}

void printWord(const char* a){
  while(*a != ' '){
    printf("%c", *a);
    a++;
  }
  printf(" ");
}
