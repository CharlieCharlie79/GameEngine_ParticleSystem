#include "ComponentA.h"


ComponentA::ComponentA() : parent(nullptr)
{
}

ComponentA::~ComponentA()
{
	parent = nullptr;
}

bool ComponentA::OnCreate(GameObject* parent_)
{
	return true;
}

void ComponentA::Update(float deltaTime_)
{
	std::cout << "Updating ComponentA\n";
}
