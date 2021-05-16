#pragma once
#include <memory>
#include "EntityManager.hpp"

class World {
public:
	void init() {
		entityManager = std::make_unique<EntityManager>();
	}


    //Inspiration:  
    //// Create a new entity
    //EntityHandle createEntity();

    //// Add a new system (should happen before init)
    //void addSystem(System* system);

    //// Destroy an entity and all its components
    //void destroyEntity(Entity e);

    //// Get components for an entity
    //template<typename ComponentType, typename ... Args>
    //void unpack(Entity e, ComponentHandle<ComponentType>& a, ComponentHandle<Args> & ... args);

    //// Add a component to an entity
    //template<typename ComponentType>
    //void addComponent(Entity& e, ComponentType&& c);

    //// Remove a component from an entity
    //template<typename ComponentType>
    //void removeComponent(Entity& e);
private:
	std::unique_ptr<EntityManager> entityManager;
};
