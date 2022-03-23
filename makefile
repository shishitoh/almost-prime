CXX = g++

CFLAGS = -fdiagnostics-color=always -O2 -std=c++20 -Wall

TARGET = almprm

SRCS = main.cpp
SRCS += sieve.cpp
SRCS += merge.cpp
SRCS += almprm1.cpp
SRCS += almprm2_1.cpp
SRCS += almprm2_2.cpp
SRCS += almprm2_3.cpp
SRCS += almprm3_1.cpp
SRCS += almprm3_2.cpp
SRCS += almprm3_3.cpp

OBJS = $(SRCS:.cpp=.o)

LIBDIR =

LIBS =

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBDIR) $(LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $(INCDIR) -c $<

main:
	$(CXX) $(CLAFG) $(INCDIR) -c main.cpp
	$(CXX) -o $(TARGET) $(OBJS) $(LIBDIR) $(LIBS)

clean:
	del -f *.o