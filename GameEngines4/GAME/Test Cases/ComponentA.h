#ifndef COMPONENTA_H
#define COMPONENTA_H
#include "../../Engine/Rendering/3D/Component.h"
#include <iostream>

class ComponentA : public Component
{
public:
	ComponentA();
	virtual ~ComponentA();
	virtual bool OnCreate(GameObject* parent_);
	virtual void Update(float deltaTime_);

protected:
	GameObject* parent;
	
};

#endif // !COMPONENTA_H