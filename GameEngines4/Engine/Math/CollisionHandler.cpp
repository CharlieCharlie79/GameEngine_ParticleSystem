#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollision = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;
CollisionHandler::CollisionHandler()
{
	prevCollision.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}

	return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_)
{
	prevCollision.clear();
	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* gameObject_)
{
	scenePartition->AddObject(gameObject_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDetection::ScreenPosToWorldRay(mousePosition_, CoreEngine::GetInstance()->GetWindowSize(), CoreEngine::GetInstance()->GetCamera());

	if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}

		for (auto c : prevCollision) {
			if (c != hitResult && c != nullptr) {
				c->SetHit(false, buttonType_);
			}
			c = nullptr;
		}
		prevCollision.clear();

		if (hitResult) {
			prevCollision.push_back(hitResult);
		}
	}


}

void CollisionHandler::OnDestroy()
{
	delete scenePartition;
	scenePartition = nullptr;

	for (auto entry : prevCollision) {
		entry = nullptr;
	}
	prevCollision.clear();
}


