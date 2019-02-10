#!/bin/bash                                                                                                                                                                         
                                                                                                                                                                                     

arguments=("$@")



for argument in "${arguments[@]}" #goes through all arguments                                                                                                                        
do
    if [[ -f $argument ]]; then
        if LC_ALL=C grep -q '[ -~]' $argument; then #checks if valid                                                                                                                 
            if LC_ALL=C grep -q '[^ -~]' $argument; then #if utf do nothing                                                                                                          
                continue
            else
                echo $argument  #print if ascii file                                                                                                                                 
            fi
        fi
    elif [[ -d $argument ]]; then
        for file in $argument/*
        do
            if LC_ALL=C grep -q '[ -~]' $file; then #checks if valid                                                                                                                 
                if LC_ALL=C grep -q '[^ -~]' $file; then #if utf do nothing                                                                                                          
                  continue
                else
                    grep -rlP '[ -~]' $argument #prints out all the ascii files and will look through subdirectories recursively                                                     
                fi
            fi
            break;
        done

    else
        echo "weird stuff"
    fi
done



