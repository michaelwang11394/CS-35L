Michael Wang
readme.txt 
Assignment 8 

$ make clean check
Without modifications: 

rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o main.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m52.811s
user	0m52.805s
sys	0m0.002s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp
./srt: Multithreading is not supported yet.

real	0m0.002s
user	0m0.000s
sys	0m0.001s
Makefile:36: recipe for target '2-test.ppm' failed
make: *** [2-test.ppm] Error 1

Multi threading is not supported without modifications. To allow it do so, we will do the following: 

Add -lpthread to the MakeFile under CFLAGS

Add #include <pthread.h> to main.c

To allow multithreading add the following globals in main.c: 
-scene_T scene;
-int nthreads;

These global variables will be able to be accessed by all threads

I deleted this loop because it limited the the number of threads we can process:

    if( nthreads != 1 )
    {
      fprintf( stderr, "%s: Multithreading is not supported yet.\n", argv[0] );
      return 1;
    }

    scene_t scene = create_sphereflake_scene( sphereflake_recursion );

    /* Write the image format header */
    /* P3 is an ASCII-formatted, color, PPM file */
    printf( "P3\n%d %d\n%d\n", width, height, max_color );
    printf( "# Rendering scene with %d spheres and %d lights\n",
            scene.sphere_count,
            scene.light_count );

Then I made an array to hold the nethread pointer just made in the form of the float variable picture

Then I made pthread_create which can start new threads. I put create in a function called thereadfunc that starts the whole process. In thereadfunc, I made it so that it couldn't print, and rather have it store colors in the array. 

I then 


I then used pthread_join as recommended in class to join all the edits together, after which all the values are printed.

 

After making the above edits, we run make clean check again and notice the much improved real time results; the times are almost double as fast each time we double the threads:

rm -f *.o *.ppm *.tmp srt srt.tgz
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -lpthread   -c -o main.o main.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -lpthread   -c -o raymath.o raymath.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -lpthread   -c -o shaders.o shaders.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -lpthread -o srt main.o raymath.o shaders.o -lm
time ./srt 1-test.ppm >1-test.ppm.tmp && mv 1-test.ppm.tmp 1-test.ppm

real	0m51.335s
user	0m51.327s
sys	0m0.002s
time ./srt 2-test.ppm >2-test.ppm.tmp && mv 2-test.ppm.tmp 2-test.ppm

real	0m26.192s
user	0m52.266s
sys	0m0.001s
time ./srt 4-test.ppm >4-test.ppm.tmp && mv 4-test.ppm.tmp 4-test.ppm

real	0m13.010s
user	0m51.716s
sys	0m0.000s
time ./srt 8-test.ppm >8-test.ppm.tmp && mv 8-test.ppm.tmp 8-test.ppm

real	0m8.545s
user	1m0.940s
sys	0m0.001s
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u 1-test.ppm $file || exit; \
done



