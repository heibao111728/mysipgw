CC=g++
S = $(wildcard *.h)
C_SRCS = $(wildcard *.c)
CPP_SRCS = $(wildcard *.cpp)
CXX_SRCS = $(wildcard *.cxx)
OBJS = $(patsubst %.cpp, %.o, $(CPP_SRCS)) $(patsubst %.c, %.o, $(C_SRCS)) $(patsubst %.cxx, %.o, $(CXX_SRCS))

CFLAGS := -g -c -D_POSIX_THREADS

INCLUDE_DIR = -I. \
	-I../sipgw \
	-I..
#	-I/usr/local/gsoap \
	-I/usr/local/gsoap/share/gsoap/ \

%.o:%.cxx
	$(CC) $(CFLAGS)  $(INCLUDE_DIR) $< -o $@
	$(if $(wildcard $(BIN_DIR)), mv $@ $(BIN_DIR), )
%.o:%.cpp
	$(CC) $(CFLAGS)  $(INCLUDE_DIR) $< -o $@
	$(if $(wildcard $(BIN_DIR)), mv $@ $(BIN_DIR), )

all:$(OBJS)

clean:
	rm -rf *.o 
