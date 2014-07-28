CC=gcc
CFLAGS=-I.
DEPS = RDMA_defs.h RDMA_types.h 
OBJ = rdma_example.o rdma_defs.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm *.o *.exe
