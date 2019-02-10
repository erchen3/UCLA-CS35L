#!/bin/bash                                                                                                                                                                                  

arguments=("$@")



for argument in "${arguments[@]}"
do
    if [[ -f $argument ]]; then  #if its a file                                                                                                                                              
        if LC_ALL=C grep -q '[ -~]' $argument && grep -qe "-*- coding: utf-8 -*-" $argument ; then # if its an ascii and has the coding                                                      
            if LC_ALL=C grep -q '[^ -~]' $argument; then # not ascii                                                                                                                         
                continue
            else
                echo $argument  #We're at an ascii file                                                                                                                                      
            fi
        fi
    elif [[ -d $argument ]]; then #if directory                                                                                                                                              
        for file in $argument/*
        do
            if LC_ALL=C grep -q '[ -~]' $file && grep -qe "-*- coding: utf-8 -*-" $file ; then
                if LC_ALL=C grep -q '[^ -~]' $file; then #Not ascii                                                                                                                          
                  continue
                else
                  grep -rle '-*- coding: utf-8 -*-' $argument     #recursively traverse directory & subdirectory searching for pattern                                                       
                fi
            fi
            break
        done

    else
        echo "weird stuff"
    fi
done



