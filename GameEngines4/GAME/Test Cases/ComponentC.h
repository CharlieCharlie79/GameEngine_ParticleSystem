#ifndef COMPONENTC_H
#define COMPONENTC_H

#include "../../Engine/Rendering/3D/Component.h"
#include <iostream>

class ComponentC : public Component
{
public:
	ComponentC();
	virtual ~ComponentC();
	virtual bool OnCreate(GameObject* parent_);
	virtual void Update(float deltaTime_);

protected:
	GameObject* parent;

};

#endif // !COMPONENTC_H
