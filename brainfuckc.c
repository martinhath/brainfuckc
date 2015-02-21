#include <stdio.h>
#include <ctype.h>

#define MEMORY_SIZE 30000
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
  /**
   * memory er minnet
   * i  er indexen til cellen
   * j  er indexen til input
   */
  int memory[MEMORY_SIZE], i, j, count;
  char c, input[BUFFER_SIZE];
  FILE *f;

  for (i = 0; i<MEMORY_SIZE; i++){
    memory[i] = 0;
  }

  if(argc<2) printf("%s\n", "Usage: brainfuckc <input file>");

  f = fopen(argv[1], "r");

  i = 0;
  while(i < BUFFER_SIZE-1 && (c=getc(f)) != EOF){
    if(isspace(c)) continue;
    input[i++] = c;
  }
  input[i] = '\0';

  i = 0;
  j = 0;
  fclose(f);

  
  while(j < BUFFER_SIZE && input[j] != '\0'){
    switch(input[j]){
      case '+': memory[i]++;  
                break;
      case '-': memory[i]--;  
                break;
      case '>': i++;          
                break;
      case '<': i--;          
                break;
      case '.': fprintf(stdout, "%d", memory[i]);   
                break;
      case ',': memory[i] = getchar(); 
                break;
      case '[': if(memory[i] == 0){
                  count  = 0;
                  while(input[j++] != '\0'){
                    if(input[j] == ']' && count-- == 0) 
                      break;
                    if(input [j] == '[') count++;
                  }
                } 
                break;
      case ']': if(memory[i] != 0){
                  count  = 0;
                  while(j-- > 0){
                    if(input[j] == '[' && count-- == 0) 
                      break;
                    if(input [j] == ']') count++;
                  }
                } 
                break;
      default:  fprintf(stderr, "%s %x\n", "Error! Illegal input", input[j]);
                return -1;
    }
    j++;
  }
  printf("\n");
}
