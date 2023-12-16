# Target for the expression processing library
add_library(simulator-lib STATIC
        Student.cpp
        Student.h
        StudentLinkedList.cpp
        StudentLinkedList.h)

target_sources(
	simulator-lib
	PRIVATE
		"bar-simulator.cpp"
		"bar-simulator.h"
		"Student.h"
		"Student.cpp"
)
