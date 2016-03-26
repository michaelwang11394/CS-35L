//
//  main.c
//  tr2u
//
//  Created by Michael Wang on 2/20/16.
//  Copyright © 2016 Michael Wang. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    //we have to check to make sure lengths are the same
    const char* fromStr = argv[1];
    const char* toStr = argv[2];
    
    int length1 = strlen(fromStr);
    int length2 = strlen(toStr);
    
    if (length1 != length2)
        exit(1);
    
    //check to see if we have duplicates
    int i;
    int j;
    for(int i=0; i<length1; i++){
        for(int j=0; j<length1; i++)
            if (fromStr[i]==fromStr[j]) {
                exit(1);
                
            }
        
    }
    
    int size = 2048;
    int counter = 0;
    char* from = (char*)malloc(sizeof(char)*size);

   
    if(from == NULL)
        exit(1);
    
    
    int character;
    
    
    do {
        character = read(0, from+counter, 1);
        
        if(character == 0)
            break;
        
        counter++;
        
        if(counter == size)
        {
            from = (char*)realloc(from, size*2);
        
            if(from == NULL)
            
                exit(1);
            
            size = size*2;
        }
    } while(character != EOF);
   
    int one;
    
    for(one = 0; one < length1; one++) {
        char inputOne = fromStr[one];
        char inputTwo = toStr[one];
        
        if(inputOne == inputTwo)
            continue;
        
        int two;
        
        for(two = 0; two < counter; two++)
            if(from[two] == inputOne)
                from[two] = inputTwo;
    }
    
    for(i = 0; i < counter; i++)
        write(1, from+i, 1);
    
    free(from);
    
    return 0;
}
