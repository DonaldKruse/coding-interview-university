CFLAGS  = -g -Wall -pedantic

default: hash

hash:  hashtable_driver.o hashtable.o
	$(CC) $(CFLAGS) -o hash hashtable_driver.o hashtable.o

hash_driver.o: hashtable_driver.c hash_table.h
	$(CC) $(CFLAGS) -c hashtable_driver.c

hashtable.o:  hashtable.c hashtable.h
	$(CC) $(CFLAGS) -c hashtable.c

# To create 
# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
	$(RM) hash *.o *~
