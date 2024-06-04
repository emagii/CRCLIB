CC = gcc

all:	testcrc

testcrc:	components
	cc -o $@ main.o crc32.o crc64.o reflect.o digest_tab.o

components: main.o crc32.o crc64.o reflect.o digest_tab.o

# lddigest.o lddigest_tab.o
crc.h:	reflect.h

crc32.o:	crc32.c crc.h
	$(CC) -c -g -o $@ $<

crc64.o:	crc64.c crc.h
	$(CC) -c -g -o $@ $<

digest_tab.o:	digest_tab.c crc.h
	$(CC) -c -g -o $@ $<

reflect.o:	reflect.c reflect.h
	$(CC) -c -g -o $@ $<

main.o:	main.c crc.h
	$(CC) -c -g -o $@ $<

clean:
	rm -fr *.o testcrc
