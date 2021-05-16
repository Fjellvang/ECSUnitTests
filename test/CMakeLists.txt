
cmake_minimum_required (VERSION 3.19.2)
set(This ExampleTests) # Variable set from youyube vid


set(Sources
	ExampleTests.cpp
 "EntityManagerTests.cpp" "ComponentTests.cpp")

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC 
	gtest_main	
	Example
)

add_test(
	NAME ${This}
	COMMAND ${This}
)
