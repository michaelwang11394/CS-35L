//
//  main.c
//  srot13
//
//  Created by Michael Wang on 2/6/16.
//  Copyright © 2016 Michael Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const *a, char const *b){
    const char *one = *(const char **)a;
    const char *two = *(const char **)b;
    while (1){
        
        int newcaseone=(int)*one;
        int newcasetwo=(int)*two;
       
        if((newcaseone^42) > (newcasetwo^42))
            return 1;
        else if((newcaseone^42)<(newcasetwo^42))
            return -1;
        else {
            one++;
            two++;
            
        if(newcaseone==32 && newcasetwo==32)
            return 0;
        else if(newcaseone==32)
            return -1;
        else if(newcasetwo==32)
            return 1;
        }
    }
}
int around(const void *a, const void *b){
    return frobcmp(a,b);
}

int main(){
    int size = 2048;
    int counter=0;
    char *data = (char*)malloc(size);
    int submit;
    
        if(counter==NULL)
        exit(0);
    
    if(data[counter-1]!=' '){
        if(counter==size){
            data=(char*)realloc(data, 2*size);
            if(data==NULL){
                fprintf(stderr,"Problem allocating data");
                exit(1);
            }
            size = size*2;
        }
        counter++;
        data[counter-1]=' ';
        while (1){
            submit=getchar();
            if(submit == EOF)
                break;
            data[counter]=(char)submit;
            counter++;
            if(counter!=size)
                continue;
            else{
                data=(char*)realloc(data,2*size);
                if(data==NULL){
                    fprintf(stderr,"Problem with data");
                    exit(1);
                }
                size=size*2;
            }
        }
    }
    int wordcounter=0;
    int a;
    for(a=0; a<counter;a++){
        if(data[a]==' ')
            wordcounter++;
    }
    
    char **word = (char **)malloc(sizeof(char*)*wordcounter);
    if(word==NULL){
        fprintf(stderr, "Problem allocating data");
        exit(1);
    }
    
    char *pointer=data;
    int index=0;
    int b;
    for(b=0;b<wordcounter;b++){
        word[index]=pointer;
        index++;
        while(*pointer != ' ')
            pointer++;
        pointer++;  
    }
    free(data);
    free(word);
    
    qsort(word, index, sizeof(char*), around);
    int c;
    for(c=0;c<wordcounter;c++){
        char *w=word[c];
        while(*w!=' '){
            printf("%c",*w);
            w++;
        }
        printf("%c",*w);
    }
    exit(0);
}