MPICXX = mpic++
MPIFLAGS = -std=c++17

TARGET = heat_transfer

OBJS = \
parameters.o \
communicator.o \
domain.o \
main.o

$(TARGET):$(OBJS)
	$(MPICXX) $(MPIFLAGS) $^ -o $@

%.o:%.cpp
	$(MPICXX) -c $(MPIFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm *.o $(TARGET)