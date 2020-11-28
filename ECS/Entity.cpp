#include "Entity.hpp"

bool Entity::operator==(const Entity& other) const {
	return (id == other.id);
}
