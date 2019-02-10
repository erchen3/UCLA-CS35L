#!/bin/bash                                                                                                                                                 


arguments=("$@")


#Program checks if file or directory.                                                                                                                       
#Then it checks if non-ascii(utf-8)                                                                                                                         
#If UTF-8 and does not having the special coding, print file                                                                                                


for argument in "${arguments[@]}"
do
    if [[ -f $argument ]]; then
        if LC_ALL=C grep -Pq '[^ \x00-\x7F]' $argument; then  #must be utf-8                                                                                
            if grep -vqe "-*- coding: utf-8 -*-" $argument ; then  #Does not have  -*- coding: utf-8 -*- in line 1  and utf-8                               
                echo $argument
            else #has utf-8 header and  is utf-8                                                                                                            
                echo "Has the special coding"
            fi
        fi
    elif [[ -d $argument ]]; then
        for file in $argument/*
        do
            if LC_ALL=C grep -Prq '[^ \x00-\x7F]' $file; then #must be utf-8                                                                                
                if grep -vqre "-*- coding: utf-8 -*-" $file | head -n1; then  #Does not have  -*- coding: utf-8 -*- in line 1 and utf-8                    
                    echo $file
                else #has utf-8 header but is non-ascii                                                                                                     
                    echo "has special coding"
                fi
            fi
        done

    else
        echo "weird result"
    fi
done





