randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) -fPIC -c -o randlibhw.o randlibhw.c
	$(CC) $(CFLAGS) -shared -o randlibhw.so randlibhw.o
randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) -fPIC -c -o randlibsw.o randlibsw.c
	$(CC) $(CFLAGS) -shared -o randlibsw.so randlibsw.o
randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) randmain.o randcpuid.o -ldl -Wl,-rpath=$(PWD) -o randmain
