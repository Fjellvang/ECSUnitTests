#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP
#include <unordered_map>
//#include <map>
#include <memory>
#include "ECS/Entity.hpp"


struct ComponentBase {
	//Entity * entity; //TODO: not sure we want to keep this. Evauluate
};


struct TestComponent {
	int id;
};

#endif // !ExampleH
