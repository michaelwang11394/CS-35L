

#include "randcpuid.h"
#include <dlfcn.h>
#include <cpuid.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
    /* Check arguments.  */
    bool valid = false;
    long long nbytes;
    if (argc == 2)
    {
        char *endptr;
        errno = 0;
        nbytes = strtoll (argv[1], &endptr, 10);
        if (errno)
            perror (argv[1]);
        else
            valid = !*endptr && 0 <= nbytes;
    }
    if (!valid)
    {
        fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        return 1;
    }
    
    /* If there's no work to do, don't worry about which library to use.  */
    if (nbytes == 0)
        return 0;
    
    /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
    void (*initialize) (void);
    unsigned long long (*rand64) (void);
    void (*finalize) (void);
    
    void* hardware = NULL;
    void* software = NULL;
    
    if (rdrand_supported ())
    {
        hardware = dlopen("randlibhw.so", RTLD_NOW);
        if(!hardware) {
            fprintf(stderr, "Library Error");
            exit(1);
        }
        
        initialize = dlsym(hardware, "hardware_rand64_init");
        if(!initialize) {
            fprintf(stderr, "hardware intialize error");
            exit(1);
        }
        
        rand64 = dlsym(hardware, "hardware_rand64");
        if(!rand64) {
            fprintf(stderr, "hardware rand error");
            exit(1);
        }
        
        finalize = dlsym(hardware, "hardware_rand64_fini");
        if(!finalize) {
            fprintf(stderr, "hardware finalize error");
            exit(1);
        }
    }
    else
    {
        software = dlopen("randlibsw.so", RTLD_NOW);
        if(!software) {
            fprintf(stderr, "library error");
            exit(1);
        }
        
        initialize = dlsym(software, "software_rand64_init");
        if(!initialize) {
            fprintf(stderr, "software error");
            exit(1);
        }
        
        rand64 = dlsym(software, "software_rand64");
        if(!rand64) {
            fprintf(stderr, "software error");
            exit(1);
        }
        
        finalize = dlsym(software, "software_rand64_fini");
        if(!finalize) {
            fprintf(stderr, "software error");
            exit(1);
        }
    }
    
    initialize ();
    int wordsize = sizeof rand64 ();
    int output_errno = 0;
    
    do
    {
        unsigned long long x = rand64 ();
        size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (fwrite (&x, 1, outbytes, stdout) != outbytes)
        {
            output_errno = errno;
            break;
        }
        nbytes -= outbytes;
    }
    while (0 < nbytes);
    
    
    if (fclose (stdout) != 0)
        output_errno = errno;
    
    if (output_errno)
    {
        errno = output_errno;
        perror ("output");
        finalize ();
        return 1;
    }
    
    finalize ();
    
    dlclose(hardware);
    dlclose(software);
    
    return 0;
}