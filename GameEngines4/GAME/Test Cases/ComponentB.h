#ifndef COMPONENTB_H
#define COMPONENTB_H

#include "../../Engine/Rendering/3D/Component.h"
#include <iostream>

class ComponentB : public Component
{
public:
	ComponentB();
	virtual ~ComponentB();
	virtual bool OnCreate(GameObject* parent_);
	virtual void Update(float deltaTime_);

protected:
	GameObject* parent;
};

#endif // !COMPONENTB_H
