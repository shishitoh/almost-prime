CC = g++

CFLAGS = -fdiagnostics-color=always -g -O2 -std=c++20 -Wall

TARGET = almprm

SRCS = main.cpp
SRCS += sieve.cpp
SRCS += almprm1.cpp
SRCS += almprm2_1.cpp
SRCS += almprm2_2.cpp

OBJS = $(SRCS:.cpp=.o)

LIBDIR =

LIBS =

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)