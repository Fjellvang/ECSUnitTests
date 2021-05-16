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

        //TODO: Seperate into own method?
        auto manager = getComponentManager<ComponentType>();
        //ComponentManager<ComponentType>* manager = this->getComponentManager<ComponentType>();

        manager->addComponent(e, c);
    }

    //// Remove a component from an entity
    //template<typename ComponentType>
    //void removeComponent(Entity& e);

    template<typename ComponentType>
    ComponentType * getComponent(Entity e) {

        auto manager = getComponentManager<ComponentType>();
        //auto manager = this->getComponentManager<ComponentType>();

        return manager->getComponent(e);
    }
//private:
	std::unique_ptr<EntityManager> entityManager;
    std::vector<std::unique_ptr<BaseComponentManager>> componentManagers;

    template<typename ComponentType>
    ComponentManager<ComponentType> * getComponentManager() {
        int index = GetComponentFamily<ComponentType>();
        if (index >= componentManagers.size())
        {
            componentManagers.resize(index + 1);
        }
        if (!componentManagers.at(index))
        {
            componentManagers.at(index) = std::make_unique<ComponentManager<ComponentType>>();
        }
        ComponentManager<ComponentType>* manager = static_cast<ComponentManager<ComponentType> *>(componentManagers.at(index).get());
        return manager;
    }
};
