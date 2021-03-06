#include <stdio.h>
#include <stdlib.h>



char translateChar(char a, char* arr1, char* arr2);

int main(int argc, char** argv){

  // Check Arguments
  if(argc > 3){
    fprintf(stderr, "Error: Extra operand '%s'\n", argv[3]);
    exit(1);
  }else if(argc < 3){
    fprintf(stderr, "Error: Missing operand after '%s'\n", argv[1]);
    printf("Two strings must be given when translating\n");
    exit(1);
  }

  int arrLen1, arrLen2;
  arrLen1 = arrLen2 = 0;
  // Check if 'from' has duplicate bytes
  int i,j;
  for(i=0; argv[1][i] != '\0'; i++){
    arrLen1++;
    for(j=0; argv[1][j] != '\0'; j++){
      if(j==i) continue;
      if(argv[1][i] == argv[1][j]){
	fprintf(stderr, "Error: 'from' string has repeating characters...\n");
	exit(1);
      }
    }
  }

  for(i=0; argv[2][i] |= '\0'; i++) arrLen2++;

  if(arrLen1 != arrLen2){
    fprintf(stderr, "Error: 'from' and 'to' strings of different lengths...\n");
    exit(1);
  }
  
  /*
  _Bool eof = feof(stdin);
  while(!eof){

    // Get character
    char ch = translateChar(getchar(), argv[1], argv[2]);
    eof = feof(stdin);

    // Print translated character
    if(!eof)
      putchar(ch);
  }
  */

  int ch;
  while( (ch = getchar()) != EOF ){
    char c = (char) ch;
    putchar(translateChar(c, argv[1], argv[2]));
  }

}

char translateChar(char a, char* arr1, char* arr2){

  int i;
  for(i=0; arr1[i] != '\0'; i++){
    if(arr1[i] == a){
      a = arr2[i];
      break;
    }
  }
  
  return a;
}
