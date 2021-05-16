#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP
#include <unordered_map>
//#include <map>
#include <memory>
#include "ECS/ComponentManager.hpp"
#include "ECS/Entity.hpp"
#include "ECS/EntityManager.hpp"


struct ComponentBase {
	//Entity * entity; //TODO: not sure we want to keep this. Evauluate
};


struct TestComponent {
	int id;
};

#endif // !ExampleH
