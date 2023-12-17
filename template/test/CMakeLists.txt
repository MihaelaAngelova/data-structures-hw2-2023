# Executable target for the unit tests
add_executable(unit-tests
        test-StudentLinkedList.cpp)

target_link_libraries(
	unit-tests
	PRIVATE
		simulator-lib
		Catch2::Catch2WithMain
)

target_sources(
	unit-tests
	PRIVATE
		"test-simulation.cpp"
		"test-StudentLinkedList.cpp"
)

# Automatically register all tests
catch_discover_tests(unit-tests)
