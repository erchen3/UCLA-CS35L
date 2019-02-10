#!/usr/bin/python
import random, sys, string                                                                                                                                                               
from argparse import ArgumentParser                                                                                                                                                      
 """
Implementation of shuf.py
that replicates GNU shuf's 3 commands
-n
-r
-i

 """                                                                                                                                                                                        
class shuf:                                                                                                                                                                              
     def __init__(self, filename=""):                                                                                                                                                    
        if filename == "-" or filename == "": #can take multiple lines until user ends if we pass these cases                                                                            
            self.lines = sys.stdin.readlines()                                                                                                                                           
        else:                                                                                                                                                                            
            f = open(filename, 'r') #create file handle                                                                                                                                  
            self.lines = f.readlines() #reads the file to list of string                                                                                                                 
            f.close() #close file                                                                                                                                                        
                                                                                                                                                                                         
     def chooseline(self): #returns random line                                                                                                                                          
        ret = random.choice(self.lines)                                                                                                                                                  
                                                                                                                                                                                         
                                                                                                                                                                                         
def main():                                                                                                                                                                              
    usage_msg= """%shuf []...[FILE]                                                                                                                                                
    OR: shuf -r [OPTION]... [FILE]                                                                                                                                                       
    output lines can repeat                                                                                                                                                              
    OR: shuf -i LO-HI [OPTION] ...                                                                                                                                                       
    Outputs range Lo-hi                                                                                                                                                                  
    OR: shuf -n COUNT [OPTION] ..... [FILE]                                                                                                                                              
    FILE Output randomly selected lines from FILE."""   

    numline = sys.maxsize                                                                                                                                                                                     
    parser = ArgumentParser(usage=usage_msg) #create object                                                                                                                              
                                                                                                                                                                                         
    parser.add_argument("FILE", nargs='?', action="store", default="") #positional argument                                                                                              
    parser.add_argument("-n","--head-count", action="store", dest="count", help="Output at most COUNT lines") #head                                                                      
    parser.add_argument("-r","--repeat", action="store_true", dest="repeat", help="Output lines can be repeated")# repeat                                                                
    parser.add_argument("-i","--input-range",dest='inrange', help="treat each number LO-HI as input line") #input range                                                                  
                                                                                                                                                                                         
    args = parser.parse_args()  #where I can traverse my arguments                                                                                                                       



    choseCount = False
    if args.count: #we've selected count to check errors                                                                                                                                 
         choseCount = True
         try:
              headCount = int(args.count) #get the int value                                                                                                                             
              assert(headCount >0) #dont want to store the number of lines if its not even right                                                                                         
              numline = headCount
         except: #theres an error                                                                                                                                                        
              parser.error("invalid line count: '{0}'".format(args.count)) #display the COUNT that was invalid

    choseRange = False
    if args.inrange: # we've selected input range  will check for the errors                                                                                                                                      
        choseRange = True
        try:
              inrange =args.inrange.split('-') #generate list                                                                                                                            
              #print(len(inrange)) 
              assert(len(inrange) == 2) #list has something like 1-10-20, break and go to error                                                                                          
              LO = int(inrange[0])
              HI = int(inrange[1])
              assert(HI > LO) #Wont get error when case is -i 10-1
        except:
              parser.error("invalid input range: '{0}'".format(args.inrange)) #display the entire range for the error
    choseRepeat = False
    if args.repeat:  
         choseRepeat = True

    inputFile = args.FILE #store the FILE from command line to inputFile


    try:
         if choseRange:
              output = list(range(LO,HI+1)) #generates a list of numbers 
              for i in range(len(output)):
                   output[i] = str(output[i]) + '\n' #make the elements string
         else:
              generator = shuf(inputFile) #create an instance of shuf
              output = generator.lines
            #if its inRange function, the number of lines corresponds to the list of integers length
            #if its head count or repeat, we want to access the list of strings
         if not choseCount and not choseRepeat: # only command(in Range ) that would have numline store an integer
              numline = len(output)
         i =0
         while( i < numline) and (len(output) > 0):  #validate output length but also iterates so we can write the random lines                                                                                                   
              display = random.choice(output)
              if not choseRepeat:
                   output.remove(display)
              sys.stdout.write(display)  #On the first run, sometimes it doesnt display, but if I make the call again in terminal I get the correct input                                
              i+=1
    except IOError as err:
         errno, strerror = err.args
         parser.error("I/O errors({0}): {1}".format(errno,strerror))

if __name__ == "__main__":
    main()




                                                                        

