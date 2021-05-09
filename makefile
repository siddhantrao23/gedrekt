CXXFLAGS=--std=c++2a
EXEC:=$(wildcard test_*)

binaries=test_string test_vector test_deque_list test_nucleotide test_map
all: test_string test_vector test_deque_list test_nucleotide test_map

test_string.o: test_string.cpp edit_distance.h
	@echo $(CXX)
	$(CXX) $(CXXFLAGS) -c test_string.cpp

test_string: test_string.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_vector.o: test_vector.cpp edit_distance.h
	$(CXX) $(CXXFLAGS) -c test_vector.cpp

test_vector: test_vector.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_deque_list.o: test_deque_list.cpp edit_distance.h
	$(CXX) $(CXXFLAGS) -c test_deque_list.cpp

test_deque_list: test_deque_list.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_nucleotide.o: test_nucleotide.cpp edit_distance.h
	$(CXX) $(CXXFLAGS) -c test_nucleotide.cpp

test_nucleotide: test_nucleotide.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_map.o: test_map.cpp edit_distance.h
	$(CXX) $(CXXFLAGS) -c test_map.cpp

test_map: test_map.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(binaries) *.o
