# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.19.2)

set(This Example) # Variable set from youyube vid

#project ("CMakeECS")
project (${This})

# Include sub-projects.
add_subdirectory ("CMakeECS")
#add_subdirectory (${This})

set(CMAKE_C_STANDARD 99) # set c standard
set(CMAKE_CXX_STANDARD 17) # set c++
set(CMAKE_POSITION_INDEPENDENT_CODE ON) #nice to have siger tuben

enable_testing()

add_subdirectory("googletest")
add_subdirectory("ECS")
add_subdirectory(test)

set(Headers
	Example.hpp
	"ECS/Entity.hpp" "ECS/EntityManager.hpp")

set(Sources
	Example.cpp
	"ECS/Entity.cpp")

add_library(${This} STATIC ${Sources} ${Headers} "ECS/EntityMap.hpp" "ECS/ComponentData.hpp" "ECS/ComponentManager.hpp" "ECS/Statics.hpp")


