#pragma once

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
