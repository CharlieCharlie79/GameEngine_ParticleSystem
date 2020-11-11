#include "CollisionDetection.h"

#include "Ray.h"
#include "../Core/CoreEngine.h"

CollisionDetection::~CollisionDetection()
{
}

Ray CollisionDetection::ScreenPosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_)
{
	glm::vec4 rayStart_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, -1.0f, 1.0f);
	glm::vec4 rayEnd_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, 0.0f, 1.0f);
	
	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	glm::vec4 rayStart_World = inverse * rayStart_NDC;
	rayStart_World /= rayStart_World.w;

	glm::vec4 rayEnd_World = inverse * rayEnd_NDC;
	rayEnd_World /= rayEnd_World.w;

	glm::vec3 rayDir_World(rayEnd_World - rayStart_World);
	rayDir_World = glm::normalize(rayDir_World);

	return Ray(glm::vec3(rayStart_World), rayDir_World);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_)
{
	float tMin = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().x;
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().y;

	glm::vec3 obbPosition_World(box_->transform[3].x, box_->transform[3].y, box_->transform[3].z);
	glm::vec3 delta = obbPosition_World - ray_->origin;

	glm::vec3 e;
	glm::vec3 f;

	//X axis
	glm::vec3 xAxis(box_->transform[0].x, box_->transform[0].y, box_->transform[0].z);
	e.x = glm::dot(xAxis, delta);
	f.x = glm::dot(ray_->direction, xAxis);
	if (fabs(f.x) > 0.001f) {
		float t1 = (e.x + box_->minVert.x) / f.x;
		float t2 = (e.x + box_->maxVert.x) / f.x;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t1 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-e.x + box_->minVert.x > 0.0f || -e.x + box_->maxVert.x < 0.0f) {
			return false;
		}
	}

	//Y axis
	glm::vec3 yAxis(box_->transform[1].x, box_->transform[1].y, box_->transform[1].z);
	e.y = glm::dot(yAxis, delta);
	f.y = glm::dot(ray_->direction, yAxis);
	if (fabs(f.y) > 0.001f) {
		float t1 = (e.y + box_->minVert.y) / f.y;
		float t2 = (e.y + box_->maxVert.y) / f.y;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t1 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-e.y + box_->minVert.y > 0.0f || -e.y + box_->maxVert.y < 0.0f) {
			return false;
		}
	}

	//Z axis
	glm::vec3 zAxis(box_->transform[2].x, box_->transform[2].y, box_->transform[2].z);
	e.z = glm::dot(zAxis, delta);
	f.z = glm::dot(ray_->direction, zAxis);
	if (fabs(f.z) > 0.001f) {
		float t1 = (e.z + box_->minVert.z) / f.z;
		float t2 = (e.z + box_->maxVert.z) / f.z;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t1 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-e.z + box_->minVert.z > 0.0f || -e.z + box_->maxVert.z < 0.0f) {
			return false;
		}
	}

	ray_->intersectionDist = tMin;
	return true;
}
