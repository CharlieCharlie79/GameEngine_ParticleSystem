#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::vec2 MouseEventListener::mouse = glm::vec2();
glm::vec2 MouseEventListener::prevMouse = glm::vec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)
{
	if (e_.type == SDL_MOUSEBUTTONDOWN) {
		UpdateMousePosition();
		NotifyMousePressed(e_.button.button);
	}

	else if (e_.type == SDL_MOUSEBUTTONUP) {
		UpdateMousePosition();
		NotifyMouseReleased(e_.button.button);
	}

	else if (e_.type == SDL_MOUSEMOTION) {
		UpdateMousePosition();
		NotifyMouseMove();
	}

	else if (e_.type == SDL_MOUSEWHEEL) {
		NotifyMouseScroll(e_.wheel.y);
	}
}

void MouseEventListener::NotifyMousePressed(int buttonType_)
{
	if (engineInstance) {
		engineInstance->NotifyMousePressed(mouse);
	}
}

void MouseEventListener::NotifyMouseReleased(int buttonType_)
{
	if (engineInstance) {
		engineInstance->NotifyMouseReleased(mouse, buttonType_);
	}
}

void MouseEventListener::NotifyMouseMove()
{
	if (engineInstance) {
		engineInstance->NotifyMouseMove(mouse);
	}
}

void MouseEventListener::NotifyMouseScroll(int y_)
{
	if (engineInstance) {
		engineInstance->NotifyMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return prevMouse;
}

glm::vec2 MouseEventListener::GetCurrentMousePosition()
{
	return mouse;
}

glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition()
{
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);
	tempY = engineInstance->GetWindowSize().y - tempY;
	if (firstUpdate) {
		prevMouse.x = mouse.x = tempX;
		prevMouse.y = mouse.y = tempX;
		firstUpdate = false;
	}

	else {
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tempX;
		mouse.y = tempY;
	}
}
