#pragma once
#include <memory>
#include <vector>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "ComponentBase.hpp"

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
    template<typename ComponentType>
    void addComponent(Entity& e, ComponentType&& c) {
        unsigned int index = GetComponentFamily<ComponentType>();

        //TODO: Seperate into own method?
        if (index >= componentManagers.size())
        {
            componentManagers.resize(index + 1);
        }
        if (!componentManagers[index])
        {
            componentManagers[index] = std::make_unique<ComponentManager<ComponentType>>();
        }
        ComponentManager<ComponentType>* manager = static_cast<ComponentManager<ComponentType> *>(componentManagers[index].get());

        manager->addComponent(e, c);
    }

    //// Remove a component from an entity
    //template<typename ComponentType>
    //void removeComponent(Entity& e);

    template<typename ComponentType>
    ComponentType GetComponent(Entity e) const {
        int index = GetComponentFamily<ComponentType>();
        auto cmp = componentManagers.at(index);
        return static_cast<ComponentType>(cmp);
    }
private:
	std::unique_ptr<EntityManager> entityManager;
    std::vector<std::unique_ptr<BaseComponentManager>> componentManagers;
};
