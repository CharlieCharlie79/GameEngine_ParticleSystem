#include "ComponentB.h"

ComponentB::ComponentB() : parent(nullptr)
{
}

ComponentB::~ComponentB()
{
	parent = nullptr;
}

bool ComponentB::OnCreate(GameObject* parent_)
{
	return true;
}

void ComponentB::Update(float deltaTime_)
{
	std::cout << "Updating ComponentB\n";
}
