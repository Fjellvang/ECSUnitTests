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

// For now this is not what we want
//TEST(ExampleTests, NonexistentComponentreturnsnull) {
//	Entity e{ 1 };
//	auto manager = std::make_unique<ComponentManager<TestComponent>>();
//	auto cmp = manager->getComponent(e);
//	ASSERT_EQ(nullptr, cmp);
//}

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
	ASSERT_NE(cmp->id, deletedCmp->id);
}
class maptest : public ::testing::Test {
protected:
	void SetUp() override {

	}

	Entity e;
	EntityMap map;
	ComponentInstance inst{ 1023 };
};
TEST_F(maptest, EntityMapBadGetIdUndefined) {
	Entity x = map.getEntity(inst);
	ASSERT_NE(inst.instanceId, x.id);
}
TEST_F(maptest, EntityMapThrowOnBadGetInst) {
	ASSERT_ANY_THROW(map.getInstance(e));
}
TEST_F(maptest, EntityMapAddInst) {
	map.add(e, inst);
	ASSERT_EQ(map.getEntity(inst).id, e.id);
	ASSERT_EQ(map.getInstance(e).instanceId, inst.instanceId);
}
TEST_F(maptest, EntityMapUpda) {
	map.add(e, inst);
	EXPECT_EQ(map.getEntity(inst).id, e.id);
	EXPECT_EQ(map.getInstance(e).instanceId, inst.instanceId);
	ComponentInstance newInst{ 2 };
	map.update(e, newInst);
	EXPECT_NE(map.getInstance(e).instanceId, inst.instanceId);
	EXPECT_EQ(map.getInstance(e).instanceId, newInst.instanceId);
}
TEST_F(maptest, EntityMapRemove) {
	map.add(e, inst);
	EXPECT_EQ(map.getEntity(inst).id, e.id);
	map.remove(e);
	EXPECT_ANY_THROW(map.getInstance(e));
}
