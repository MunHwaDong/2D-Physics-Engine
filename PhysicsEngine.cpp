#include "PhysicsEngine.h"

void PhysicsEngine::GenerateForce(const float deltaTime)
{
	for (auto& obj : objects)
	{
		//test
		if (obj.shape.vertices[1].y <= -1 && obj.shape.vertices[2].y <= 1)
		{
			break;
		}

		obj.vel += (C_gravitycoeff * obj.mass) * deltaTime;

		obj.pos += obj.vel * deltaTime;

		std::cout << obj.pos.x << " " << obj.pos.y << std::endl;
	}
}

void PhysicsEngine::RigidbodyUpdate(const float deltaTime)
{
	for (auto& obj : objects)
	{
		obj.UpdateVertices();
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
}

void PhysicsEngine::AddObject(const RenderableObject& object)
{
	objects.push_back(object);
}
