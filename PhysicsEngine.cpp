#include "PhysicsEngine.h"

void PhysicsEngine::GenerateForce(const float deltaTime)
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		if (!obj->isUseGravity) continue;

		obj->vel += (C_gravitycoeff * obj->inverseMass) * deltaTime;
		obj->pos += obj->vel * deltaTime;

		obj->angularVel += (C_gravitycoeff * obj->inverseMass) * deltaTime;
		obj->theta += obj->angularVel * deltaTime;

		//std::cout << obj->pos.x << " " << obj->pos.y << std::endl;

		//std::cout << "obj 법선 : " << obj->shape->normVec[0].x << " " << obj->shape->normVec[0].y << std::endl;
		//std::cout << "obj 법선 : " << obj->shape->normVec[1].x << " " << obj->shape->normVec[1].y << std::endl;
		//std::cout << "obj 법선 : " << obj->shape->normVec[2].x << " " << obj->shape->normVec[2].y << std::endl;
	}
}

void PhysicsEngine::RigidbodyUpdate(const float deltaTime)
{
	Matrix4f model;

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		//오브젝트 삭제 후, 다시 삽입하는 과정 구현이 필요함.

		model = Utill::GetModelMatrix(obj->pos, vector3f(0), 0);

		//obj->UpdateVertices();
		obj->UpdateNormVectors();
		//obj->UpdateObjAABB();
	}
}

void PhysicsEngine::DetectCollision()
{
	std::vector<std::unordered_set<IQTData*>> collisionableSetFamily;

	BoardPhase(collisionableSetFamily);
	NarrowPhase(collisionableSetFamily);
}

void PhysicsEngine::BoardPhase(std::vector<std::unordered_set<IQTData*>>& collisionableSetFamily) const
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		std::unordered_set<IQTData*> collisionableSet = objects.Query(obj->objMinAABB, obj->objMaxAABB);

		if (!collisionableSet.empty() && collisionableSet.size() > 1)
		{
			collisionableSetFamily.push_back(collisionableSet);
		}
	}
}

void PhysicsEngine::NarrowPhase(std::vector<std::unordered_set<IQTData*>>& collisionableSetFamily) const
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