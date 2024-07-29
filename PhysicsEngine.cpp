#include "include/PhysicsEngine.h"

//��� ������Ʈ�鿡 �߷��� ���Ѵ�.
void PhysicsEngine::GenerateForce(const float deltaTime)
{
	for (auto ele : objects)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(ele);

		obj->vel += (C_gravitycoeff * obj->inverseMass) * deltaTime;
		obj->pos += obj->vel * deltaTime;

		std::cout << "obj 속도 : " << obj->vel.y << std::endl;
		std::cout << obj->pos.x << " " << obj->pos.y << std::endl;
	}
}

void PhysicsEngine::RigidbodyUpdate(const float deltaTime)
{
	for (auto ele : objects)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(ele);

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