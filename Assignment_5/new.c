#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define INIT_BUFFER_SIZE 32

int frobcmp(const char* a, const char* b);
int cmp(const void* a, const void* b);
char decrypt(char a);
void printWord(char const* a);
void memoryError(void);

int fOption;

int main(int argc, char** argv){

  // Data
  int numWords, bufSize, temp, i, c;
  // Buffers
  char* buf;
  char* tempStr;
  // List
  char** list;
  // Checks
  int usingRegularFile;
  
  struct stat fileStats;

  fOption = 0;
  while((c = getopt(argc, argv, "f")) != -1){
      switch(c){
      case 'f':
	fOption = 1;
	break;
      case '?':
	exit(1);
      }
  }

  if(fstat(0, &fileStats) < 0){
    fprintf(stderr,"Error: Unable to read file");
    exit(1);
  }

  usingRegularFile = S_ISREG(fileStats.st_mode);

  bufSize = INIT_BUFFER_SIZE * sizeof(char);
  if(usingRegularFile){
    bufSize = fileStats.st_size * sizeof(char) + 2;
  }

  buf = (char*) malloc(bufSize);

  //getText(buf, usingRegularFile, bufSize, &numWords); 
  //printf("%s",buf);

  int numChars = 0;
  char ch;
  while( read(0, &ch, 1) ){

    if(numChars >= bufSize - 1){
      bufSize *= 2;
      buf = (char*) realloc(buf, bufSize);
      if(buf == NULL)
	memoryError();
    }

    if(ch == '\n') ch = ' ';
    if(ch == ' ' && numChars > 0 && buf[numChars-1] == ' ') continue;
    if(ch == ' ' && numChars == 0) continue;
    buf[numChars++] = ch;

    if(ch == ' ') numWords++;
    
  }

  if(numChars > 0 && buf[numChars-1] != ' '){
    buf[numChars++] = ' ';
    buf[numChars++] = '\0';
    numWords++;
  }

  list = (char**) malloc(sizeof(char*) * numWords);
  if(list == NULL) memoryError();

  tempStr = buf;
  temp = 0;

  for(i=0; i<numChars; i++){
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
    x = decrypt(*a);
    y = decrypt(*b);

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

void memoryError(void){
  fprintf(stderr, "Error: Memory allocation failiure");
  exit(1);
}

char decrypt(char a){
  if(fOption){
    if((a==EOF) || (a >= 0 && a <= UCHAR_MAX)){
      a = toupper(a);
    }
  }

  return (a ^ 0x2a);
}
