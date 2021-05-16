#pragma once
#include <type_traits>

struct ComponentCounter {
	static int counter;
};
int ComponentCounter::counter = 0;
template<typename ComponentType>
struct ComponentBase {
	static inline int familyId() {
		static unsigned int id = ComponentCounter::counter++;
		return id;
	}
};

template <typename C>
static int GetComponentFamily() {
	return ComponentBase<typename std::remove_const<C>::type>::familyId();
}
