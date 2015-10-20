CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2


target_file  := main
prog_name    := complex
object_files := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: $(target_file)

$(target_file): $(object_files)
	$(CXX) $(object_files) -o $(prog_name)

strip:
	strip -s $(prog_name)*

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(prog_name) $(object_files)
