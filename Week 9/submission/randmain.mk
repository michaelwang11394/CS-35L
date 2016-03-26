randlibhw.so: randlibhw.c
        $(CC) $(CFLAGS) -shared -fPIC randlibhw.c -o $@

randlibsw.so: randlibsw.c
        $(CC) $(CFLAGS) -shared -fPIC randlibsw.c -o $@

randmain: randcpuid.o randmain.o
	$(CC) $(CFLAGS) -Wl,-rpath=$(PWD) -o randmain randcpuid.o randmain.o -ldl