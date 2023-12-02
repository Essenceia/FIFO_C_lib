DOC_DIR=doc
RELEASE=release
INC=inc
LIB_NAME=libeth.a

ifndef debug
debug:=
endif

FLAGS = -std=gnu99 -Wall -Wextra -Wconversion -Wshadow -Wundef -fno-common  -Wno-unused-parameter -Wno-type-limits -fpic
CC = cc $(if $(debug),-DDEBUG -g)
LD = cc
DEPS=tb_fifo.c tb_fifo.h tb_all.h tb_list.h tb_types.h tb_util.h 

test : test.o fifo.o
	$(LD) -o test -g $^

test.o : test.c
	$(CC) -c test.c $(FLAGS)

fifo.o: $(DEPS)
	$(CC) -c tb_fifo.c $(FLAGS)

lib: fifo.o 
	ar rcs $(LIB_NAME) $^ 

valgrind: test
	valgrind --leak-check=full --track-origins=yes ./test	

release: lib
	mkdir -p $(RELEASE)/$(INC)
	cp $(LIB_NAME) $(RELEASE)/.
	cp *.h $(RELEASE)/$(INC)

clean:
	-rm -f *.o	
	-rm -f *.a	
	-rm -f vgcore.*	
	-rm -f test
	-rm -fr $(RELEASE)
