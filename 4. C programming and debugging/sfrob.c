#include <stdio.h>
#include <stdlib.h>


/*                                                                                                                                                               
This will compare two frobnicated "words'. They end in a space.                                                                                                  
a<b -> negative | a shorter                                                                                                                                      
a= b -> 0 |same                                                                                                                                                  
a >b ->positive | a longer                                                                                                                                       
*/
int frobcmp (char const *a, char const *b){
  for(;; a++, b++){//traverse
    if (*a == ' ' && *b == ' '){ //empty case                                                                                                                    
      return 0;
    }
    else if (*a == ' '|| ((*a^42) < (*b^42)) ) { //42 = hex 0X2A, XOR operation(memcmp)                                                                          
      return -1; //a shorter                                                                                                                                     
    }
    else if (*b == ' ' || ((*a^42) >  (*b^42))){
      return 1;// a bigger                                                                                                                                       
    }
  }
}
/*                                                                                                                                                               
Checks error for reading input                                                                                                                                   
*/
void findErr(){
  if(ferror(stdin)){ //nonzero value means error on the input stream                                                                                             
    fprintf(stderr,"Error with reading file bro");
    exit(1);//unsuccesful termination                                                                                                                            
  }
}

/*                                                                                                                                                               
Checks if able to allocate memory                                                                                                                                
*/
void memoryError(void* p){
  if(p == NULL){ //Null, MALLOC couldnt allocate space                                                                                                           
    fprintf(stderr, "Error couldn't allocate the space bro.");
    exit(1);
  }
}
/*                                                                                                                                                               
Checks error writing when stdout                                                                                                                                 
*/
void OutError(){
  if(ferror(stdout)){
    fprintf(stderr,"Error with writing broski");
    exit(1);
  }
}
//Compare the two characters                                                                                                                                     
int compare( const void* first, const void* second){
  char const* uno = *(const char **) first;
  char const* dos = *(const char **) second;
  return frobcmp(uno ,dos);
}


int main() {
  int letterCount =0, wordCount =0;
  char* aWord;//pointer to a word                                                                                                                                
  char** listWords; //pointer to a list of words                                                                                                                 
  aWord = (char*)malloc(sizeof(char)); // allocate char amount of memory                                                                                         
  listWords = (char**)malloc(sizeof(char*)); //allocate char* amount of memory                                                                                   
  memoryError(aWord); //memory allocated?
  memoryError(listWords);

  char currChar = getchar();
  findErr();
  char nextChar = getchar();
  findErr();
  //printf("%d",3);                                                                                                                                              
  while (currChar != EOF){//while input hasnt ended                                                                                                              
    aWord[letterCount] = currChar;
    char *temp = realloc(aWord, sizeof(char) * (letterCount + 5)); //reallocate memory of aWord                                                                  
    memoryError(temp); //able to allocate?                                                                                                                       
    aWord = temp;

    if (currChar == ' '){//reached terminating char -space                                                                                                       
      listWords[wordCount] = aWord;
      char **additional = realloc(listWords, sizeof(char*)*(wordCount+5));//more words to come                                                                   
      memoryError(additional); //check if abble to allocate, if past this then ya                                                                                
      listWords = additional;
      letterCount = -1;
      wordCount++;
      aWord = NULL;//reset the word                                                                                                                              
      aWord = (char*)malloc(sizeof(char));
    }
    if (nextChar == EOF && currChar == ' '){
      break;
    }
    else if(currChar == ' ' && nextChar == ' '){
      while(1) { //keep running as long as we need to                                                                                                            
        if (currChar != ' '){ //break from infinite loop if character isnt a space                                                                               
          break;
        }
        else {
          currChar = getchar(); //gets the char                                                                                                                  
          findErr(); //everytime we read from stdin make sure we dont have errors                                                                                
        }
      }//endwhile                                                                                                                                                
      nextChar = getchar();
      findErr();
      letterCount++;
      continue;
    }//end else if                                                                                                                                               
    else if(nextChar == EOF){ //we're at the end of the file and needa add a space   
      currChar = ' ';
      letterCount++;
      continue;
    }
    currChar = nextChar;
    nextChar = getchar();
    findErr();
    letterCount++;
  }
  qsort(listWords,wordCount,sizeof(char*),compare);//quick sort
  int i,j;
  for (i=0; i< wordCount; i++){ //display
    for (j=0;; j++){
      //printf("%d",5);                                                                                                                                          
      putchar(listWords[i][j]);
      OutError();
      if (listWords[i][j] == ' ')
        break;
    }
  }
  for (i=0; i < wordCount; i++){ //deallocation                                                                                                                  
    free(listWords[i]);//deallocate memory from list                                                                                                             
  }
  free(listWords);//free up the memory
  free(aWord);
  /*                                                                                                                                                             
  int me = frobcmp("*{_CIA\030\031 ", "*`_GZY\v ");  
  printf("%d",me);                                                                                                                                               
  */

  return 0;
}



