CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2


target_file  := main
prog_name    := complex
object_files := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
dep_files    := $(patsubst %.o, %.dep, $(object_files))

all: $(target_file)

$(target_file): $(object_files)
	$(CXX) $(object_files) -o $(prog_name)

strip:
	strip -s $(prog_name)

-include $(dep_files)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	$(CXX) -MM $(CXXFLAGS) $< -o $*.dep

clean:
	-$(RM) $(prog_name) $(object_files) $(dep_files)

