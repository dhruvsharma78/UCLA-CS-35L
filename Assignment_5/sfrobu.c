#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define INIT_BUFFER_SIZE 32
int cnt=0;
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

  int numChars = 1;
  buf[0] = ' ';
  char ch;

  if( usingRegularFile ){
    numChars = fileStats.st_size;
    read(0, buf+1, numChars++);
    lseek(0, 0, SEEK_CUR);
  }
  
  while( read(0, &ch, 1) ){

    if(numChars >= bufSize - 1){
      bufSize *= 2;
      buf = (char*) realloc(buf, bufSize);
      if(buf == NULL)
	memoryError();
    }
    
    buf[numChars++] = ch;
    
  }

  buf[numChars++] = ' ';

  list = (char**) malloc(sizeof(char**));
  if(list == NULL) memoryError();

  tempStr = buf;
  temp = 0;

  for(i=1; i<numChars; i++){
    if(/*buf[i] != ' ' &&*/ buf[i-1] == ' '){
      list = (char**) realloc(list, sizeof(char*) * ++temp);
      tempStr = buf + i;
      list[temp-1] = tempStr;
    }
  }

  qsort(list, temp, sizeof(char**), cmp);

  for(i=0; i<temp; i++){
    printWord(list[i]);
  }

  /*
  printf("\n\nCount: %d\n\n",cnt);
  //*/

  
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
  cnt++;
  while( *a != ' ' && *b != ' '){
    char x,y;
    x = decrypt(*a);
    y = decrypt(*b);

    if(fOption){
      if((x==EOF) || (x >= 0 && x <= UCHAR_MAX)){
	x = toupper(x);
      }
      if((y==EOF) || (y >= 0 && y <= UCHAR_MAX)){
	y = toupper(y);
      }
    }

    
    if(x < y) return -1;
    if(x > y) return  1;

    if(*(a+1) == ' ' && *(b+1) != ' ') return -1;
    if(*(b+1) == ' ' && *(a+1) != ' ') return  1;
    
    a++; b++;
  }
  if( *a == ' ' || *b == ' ' ){
    char x,y;
    x = decrypt(*a);
    y = decrypt(*b);

    if(fOption){
      if((x==EOF) || (x >= 0 && x <= UCHAR_MAX)){
	x = toupper(x);
      }
      if((y==EOF) || (y >= 0 && y <= UCHAR_MAX)){
	y = toupper(y);
      }
    }
    
    if(x < y) return -1;
    if(x > y) return  1;
  }
  return 0;
}

void printWord(const char* a){
  while(*a != ' '){
    write(1, a, 1);
    a++;
  }
  write(1, " ", 1);
}

void memoryError(void){
  fprintf(stderr, "Error: Memory allocation failiure");
  exit(1);
}

char decrypt(char a){
  return (a ^ 0x2a);
}
