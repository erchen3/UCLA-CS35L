#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  //argc counts the number of arguments in argv                                          
  //argv holds the arguments --- say tr from to ,, {tr, from, to}                        

  if(argc !=3){ // needs the convention tr from to                                       
    fprintf(stderr, "Error: Incorrect # of arguments");
    exit(1);
  }

  char* from =argv[1];
  char* to = argv[2];

  if(strlen(from)!= strlen(to)){ //enforce same length                                   
    fprintf(stderr, "Error: Not the same length");
    exit(1);
  }
  int i,j;
  //from has duplicate bytes or nah                                                      
  for(i=0; i < strlen(from); i++){
    for(j=i+1; j<strlen(from); j++){
      if(from[i] ==from[j]){
        fprintf(stderr, "Error: duplicate byte in from");
        exit(1);
       }
     }
   }
  int flip;
  ssize_t val;
  char c[1];
  for(val = read(0,c,1); val>0; val=read(0,c,1)){
    if(ferror(stdin)!= 0){//at each iteration check validity                             
      write(2,"trouble reading from stdin",0);
      exit(1);
    }
   for(i =0; i< strlen(from); i++){
    if(ferror(stdin)!= 0){//at each iteration check validity                             
      write(2,"trouble reading from stdin",0);
      exit(1);
    }
   for(i =0; i< strlen(from); i++){
      if(*c == from[i]){
        write(1,to+i,1);
        flip = 1;
        break;
      }
      else{
        flip =0;
      }
    }//endfor                                                                            
    if(!flip){
      write(1,c,1);
    }
  }

}


