#include "ComponentC.h"

ComponentC::ComponentC() : parent(nullptr)
{
}

ComponentC::~ComponentC()
{
	parent = nullptr;
}

bool ComponentC::OnCreate(GameObject* parent_)
{
	return true;
}

void ComponentC::Update(float deltaTime_)
{
	std::cout << "Updating ComponentC\n";
}
