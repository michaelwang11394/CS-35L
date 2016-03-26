#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int comparisons = 0;

int frobcmp(const char* a, const char* b) {
    comparisons++;
    
    int z = 0;
    
    while(z >= 0) {
        int one  = a[z];
        int two = b[z];
        
        if((one  ^ 42) > (two ^ 42))
            return 1;
        else if((one  ^ 42) < (two ^ 42))
            return -1;
        
        z++;
        }

    
    return 0;
}

int wrap(const void* a, const void* b) {
    // From Piazza
    char const* aa = *(const char **) a;
    char const* bb = *(const char **) b;
    
    return frobcmp(aa,bb);
}

int main(void) {
    int size = 2048;
    char* memory;
    char readNow;
    
    struct stat file;
    fstat(0, &file);
    
    int fileSize = file.st_size;
    

    if(S_ISREG(file.st_mode)) {
        memory = (char*)malloc(fileSize);
        
        if(memory == NULL) {
            fprintf(stderr, "Memory allocation error.");
            exit(1);
        }
    }
    else {
        memory = (char*)malloc(sizeof(char)*size);
        
        if(memory == NULL) {
            fprintf(stderr, "Memory allocation error.");
            exit(1);
        }
    }
    
    int counter = 0;
    char pointer;
    
    
    while(read(0, &pointer, 1) > 0) {
        memory[counter] = (char)pointer;
        counter++;
        
        if(counter == fileSize) {
            memory = (char*)realloc(memory,fileSize*2);
            
            if(memory == NULL) {
                fprintf(stderr, "Memory allocation error.");
                exit(1);
            }
            
            fileSize = fileSize*2;
        }
    }
    

    if(memory[counter-1] != ' ') {
        if(counter >= fileSize) {
            memory = (char*)realloc(memory, fileSize*2);
            
            if(memory == NULL) {
                fprintf(stderr, "Memory allocation error.");
                exit(1);
            }
        }
        
        memory[counter] = ' ';
        counter++;
    }
    
    
    char** words = NULL;
    int wordNumber = 0;
    int i;
    
    for(i = 0; i < counter; i++) {
        if(i == 0 || memory[i-1] == ' ') {
            words = realloc(words, sizeof(char*)*(wordNumber+1));
            
            if(words == NULL) {
                fprintf(stderr, "Memory allocation error.");
                exit(1);
            }
            words[wordNumber++] = &memory[i];
        }
    }
    
    qsort(words, wordNumber, sizeof(char*), wrap);
    
    int *number=(int*)malloc(sizeof(int)*wordNumber);
    int first=0;
    int second=1;
    for(int q=0;q<wordNumber;q++){
        char *w=words[q];
        while(*w!=' '){
            w++;
            second++;
        }
        number[first++]=second;
        second=1;
    }
    int x;
    for(x=0; x<wordNumber;x++){
        char *p = words[x];
        int t;
        for(t=0; t<number[x]; t++){
            write(1, &(*p),1);
            p++;
        }
    }

    free(memory);
    free(words);
    fprintf(stderr, "Comparisons: %d\n", comparisons);
    exit(0);
}