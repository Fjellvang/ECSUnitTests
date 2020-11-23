#include <gtest/gtest.h>
#include <memory>
#include "../Example.hpp"

//struct TestComponent{ };

TEST(ExampleTests, AddTwoComponentsIdIncrement) {
	Entity e;
	e.id = 1;
	auto manager = std::make_unique<ComponentManager<TestComponent>>();
	TestComponent component{0};
	ComponentInstance componentInst = manager->addComponent(e, component);
	ASSERT_EQ(componentInst.instanceId, 1); // stopper ved fejl
	ComponentInstance comp2 = manager->addComponent(e, component);
	ASSERT_EQ(comp2.instanceId, 2);
}

TEST(ExampleTests, NonexistentComponentreturnsnull) {
	Entity e{ 1 };
	auto manager = std::make_unique<ComponentManager<TestComponent>>();
	auto cmp = manager->getComponent(e);
	ASSERT_EQ(nullptr, cmp);
}

TEST(ExampleTests, AddGetSame) {
	Entity e{ 1 };
	auto manager = std::make_unique<ComponentManager<TestComponent>>();
	TestComponent component;
	component.id = 124;
	ComponentInstance componentInst = manager->addComponent(e, component);
	auto cmp = manager->getComponent(e);
	ASSERT_EQ(component.id, cmp->id) << "WHAT";
}
TEST(ExampleTests, RemoveComponent) {
	Entity e{ 1 };
	auto manager = std::make_unique<ComponentManager<TestComponent>>();
	TestComponent component{ 0 };
	manager->addComponent(e, component);
	auto cmp = manager->getComponent(e);
	ASSERT_EQ(0, cmp->id);

	manager->removeComponent(e);

	TestComponent * deletedCmp = manager->getComponent(e);
	ASSERT_EQ(deletedCmp, nullptr);
}
class maptest : public ::testing::Test {
protected:
	void SetUp() override {

	}

	Entity e;
	EntityMap map;
	ComponentInstance inst{ 0 };
};
TEST_F(maptest, EntityMapThrowOnBadGet) {
	ASSERT_ANY_THROW(map.getEntity(inst));
}
TEST_F(maptest, EntityMapThrowOnBadGetInst) {
	ASSERT_ANY_THROW(map.getInstance(e));
}