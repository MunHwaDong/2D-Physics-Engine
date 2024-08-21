#include "include/PhysicsEngine.h"

void PhysicsEngine::GenerateForce(const float deltaTime)
{
	for(auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		if(!obj->isUseGravity) continue;

		obj->vel += (C_gravitycoeff * obj->inverseMass) * deltaTime;
		obj->pos += obj->vel * deltaTime;

		obj->angularVel += (C_gravitycoeff * obj->inverseMass) * deltaTime;
		obj->theta += obj->angularVel * deltaTime;

		std::cout << obj->pos.x << " " << obj->pos.y << std::endl;

		//std::cout << "obj 법선 : " << obj->shape->normVec[0].x << " " << obj->shape->normVec[0].y << std::endl;
		//std::cout << "obj 법선 : " << obj->shape->normVec[1].x << " " << obj->shape->normVec[1].y << std::endl;
		//std::cout << "obj 법선 : " << obj->shape->normVec[2].x << " " << obj->shape->normVec[2].y << std::endl;
	}
}

void PhysicsEngine::RigidbodyUpdate(const float deltaTime)
{
	for(auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		obj->UpdateVertices();
	}
}

void PhysicsEngine::DetectCollision()
{
}

void PhysicsEngine::ResolutionCollision()
{

}

void PhysicsEngine::Update(const float deltaTime)
{
	GenerateForce(deltaTime);
	RigidbodyUpdate(deltaTime);
	DetectCollision();
}

void PhysicsEngine::AddObject(RenderableObject* object)
{
	objects.Insert(dynamic_cast<IQTData*>(object));
}