#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int frobcmp (char const *a, char const *b,int flag){
  if(flag){// no -f                                                                                                                                       
    for(;; a++, b++){//traverse                                                                                                                           
      if (*a == ' ' && *b == ' '){ /*mpty case*/
        return 0;
      }
      else if (*a == ' '|| ((*a^42) < (*b^42)) ) {
        return -1;
      }
      else if (*b == ' ' || ((*a^42) >  (*b^42))){
        return 1;// a bigger                                                                                                                              
      }
    }
  }
  else {//-f                                                                                                                                              
    for(;; a++, b++){
      if (*a == ' ' && *b == ' '){ //empty case                                                                                                           
        return 0;
      }
      else if (*a == ' '|| (toupper(*a^42) < toupper(*b^42)) ) {
        return -1; //a shorter                                                                                                                            
      }
      else if (*b == ' ' || (toupper(*a^42) >  toupper(*b^42))){
        return 1;// a bigger                                                                                                                              
      }
    }
  }
}

/*Checks error for reading input                                                                                                                          
*/
void findErr(){
  if(ferror(stdin)){ //nonzero value means error on the input stream                                                                                      
    //    fprintf(stderr,"Error with reading file");                                                                                                      
    exit(1);//unsuccesful termination                                                                                                                     
  }
}

/*                                                                                                                                                        
Checks if able to allocate memor                                                                                                                          
*/
void memoryError(void* p){
  if(p == NULL){ //Null, MALLOC couldnt allocate space                                                                                                    
    fprintf(stderr, "Error couldn't allocate the space.");
    exit(1);
  }
}
/*Checks error writing when stdout                                                                                                                        
*/void OutError(){
  if(ferror(stdout)){
    fprintf(stderr,"Error with writing");
    exit(1);
  }
}
//Compare the two characters, without -f                                                                                                                  
int compareReg( const void* first, const void* second){
  char const* uno = *(const char **) first;
  char const* dos = *(const char **) second;
    return frobcmp(uno ,dos,1);
}
//Compare but with -f                                                                                                                                     
int compareF( const void* first, const void* second){
  char const* uno = *(const char **) first;
  char const* dos = *(const char **) second;
  return frobcmp(uno ,dos,0);
}


int main(int argc,char* argv[] ) {
  int flag= 0;// default to no -f                                                                                                                         
  struct stat file;

  if(fstat(0,&file)!=0){// succeeds at zero, wouldnt execute                                                                                              
       exit(1);
  }
  //did we get -f?                                                                                                                                        
  if(argc ==2 && strcmp(argv[1],"-f") == 0)
     flag = 1;

  int letterCount =0, wordCount =0;
  char* aWord;//pointer to a word                                                                                                                         
  aWord = (char*)malloc((file.st_size/2)*(sizeof(char))); // allocate a portion of the file size's memory                                                 
  char** listWords = (char**)malloc(file.st_size*(sizeof(char*)));
  //allocate file size amount of memory as safe
  //upper bound                                                                                                                                           
  memoryError(aWord); //memory allocated?                                                                                                                 
  memoryError(listWords);
  ssize_t val1;
  ssize_t val2;
  char currChar;
  char nextChar;

  char* temp;
  //Is this a regular file?                                                                                                                               
  if(S_ISREG(file.st_mode)){
    //allocate amount of size of file                                                                                                                     
    temp = (char*) malloc(sizeof(char)*file.st_size);
    memoryError(temp);
    read(0,temp, file.st_size);//read all to temp                                                                                                         
    int i;
    currChar = temp[0];//first char
    nextChar = temp[1];// second char
   for(i=0;i<file.st_size-2;i++){//iterate through
      aWord[letterCount] = currChar;
      if(currChar ==' '){//last word case                                                                                                                 
        listWords[wordCount] = aWord;
        aWord = NULL; //resets aWord
        aWord = (char*) malloc((file.st_size/2)*sizeof(char));
        memoryError(aWord);
        letterCount = -1;
        wordCount++;
      }
      if( i>= file.st_size-2 && currChar == ' '){ //beyond size correctly                                                                                 
        break;
      }
      else if(i>= file.st_size-2 && currChar != ' '){
        currChar = ' ';
        letterCount++;
        continue;
      }
      currChar = nextChar;
      nextChar = temp[i+2];
      letterCount++;
    }//listWords filled from file  end loop
  }

  val1 = read(0,&currChar,1);
  val2 = read(0,&nextChar, 1);
  letterCount =0;
  aWord = NULL;
  aWord= (char*) malloc(sizeof(char));
  //  listWords = (char**)malloc(sizeof(char*));                                                                                                          

  while (val1 >0){ //while input hasnt ended                                                                                                              
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
    if (nextChar==EOF  && currChar == ' '){
      break;
    }
    else if(currChar == ' ' && nextChar == ' '){
      while(currChar == ' ') { //keep running as long as we need to                                                                                       
        if (currChar != ' '){ //break from infinite loop if character isnt a space                                                                        
          break;
        }
        val1 = read(0,&currChar,1);
      }//endwhile                                                                                                                                         
      val2= read(0,&nextChar,1);
         letterCount++;
      continue;
      }//end else if                                                                                                                                      
    else if(nextChar ==EOF && currChar != ' ' ){ //we're at the end of the file and needa add a space                                                     
      currChar = ' ';
      letterCount++;
      continue;
    }
      ///  nextChar = getchar();                                                                                                                          
    currChar = nextChar;
    val2 = read(0,&nextChar,1);//unusual behavior//                                                                                                       
    nextChar = getchar();
    findErr();
    letterCount++;
  }
  /*                                                                                                                                                      
                                                                                                                                                          
HANDLE CASE WITH -F LATER LOGIC                                                                                                                           
   */
  if(flag == 1)// -F case                                                                                                                                 
    qsort(listWords,wordCount,sizeof(char*),compareF);//quick sort                                                                                        
  else //not -F, flag was 0                                                                                                                               
    qsort(listWords,wordCount,sizeof(char*),compareReg);//quick sort                                                                                      
  int i,j;
  for (i=0; i< wordCount; i++){ //display                                                                                                                 
    for (j=0;; j++){
      write(1,&listWords[i][j],1);
      if (listWords[i][j] == ' ')
        break;
    }
  }
  for (i=0; i < wordCount; i++){ //deallocation                                                                                                           
    free(listWords[i]);//deallocate memory from list                                                                                                      
  }
  free(listWords);
  free(aWord);
  /*  int me = frobcmp("*{_CIA\030\031 ", "*`_GZY\v ");                                                                                                   
  printf("%d",me);                                                                                                                                        
  */
  return 0;
}
