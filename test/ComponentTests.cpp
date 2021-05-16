#include <gtest/gtest.h>
#include <memory>
#include "../Example.hpp"
#include "../ECS/ComponentBase.hpp"

class componentBaseTests : public ::testing::Test {
protected:
	void SetUp() override {
	}
	void TearDown() override
	{
	}

};

struct ComponentTest : public ComponentBase<ComponentTest> {};
struct SecondComponentTest : public ComponentBase<SecondComponentTest> {};

TEST_F(componentBaseTests, componentStartsAtZero) {
	ComponentTest c;
	ASSERT_EQ(0, c.familyId());
}
TEST_F(componentBaseTests, componentFamilyIncrements) {
	ComponentTest c;
	SecondComponentTest c2;
	ASSERT_EQ(c.familyId() + 1, c2.familyId());
}
TEST_F(componentBaseTests, componentStartsAtZeroTemplate) {
	ASSERT_EQ(0, GetComponentFamily<ComponentTest>());
}
TEST_F(componentBaseTests, componentFamilyIncrementsTemplate) {
	ASSERT_EQ(GetComponentFamily<ComponentTest>() + 1, GetComponentFamily<SecondComponentTest>());
}
