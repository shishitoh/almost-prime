CXX = g++

CFLAGS = -fdiagnostics-color=always -O2 -std=c++20 -Wall

TARGET = almprm

SRCS = main.cpp sieve.cpp merge.cpp
SRCS += $(wildcard almprm*.cpp)

OBJS = $(SRCS:.cpp=.o)

LIBDIR =

LIBS =

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBDIR) $(LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $(INCDIR) -c $<

clean:
	del -f *.o *.exe

test: test.cpp
	$(CXX) -o $@ $^ $(LIBDIR) $(LIBS)