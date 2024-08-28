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

		//std::cout << beforevel.x - obj->vel.x << " " << beforevel.y - obj->vel.y << std::endl;
		//beforevel = obj->vel;

		//for (int i = 0; i < 3; ++i)
		//{
		//	std::cout << obj->shape->vertices[i].x << ", " << obj->shape->vertices[i].y << std::endl;
		//}
		//std::cout << obj->name << std::endl;

		//std::cout << "obj 법선 : " << obj->shape->normVec[0].x << " " << obj->shape->normVec[0].y << std::endl;
		//std::cout << "obj 법선 : " << obj->shape->normVec[1].x << " " << obj->shape->normVec[1].y << std::endl;
		//std::cout << "obj 법선 : " << obj->shape->normVec[2].x << " " << obj->shape->normVec[2].y << std::endl;
	}
}

//오브젝트 삭제 후, 다시 삽입하는 과정 구현이 필요함.
void PhysicsEngine::RigidbodyUpdate()
{
	Matrix4f model;

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj(dynamic_cast<RenderableObject*>(*iter));

		model = Utill::GetModelMatrix(obj->pos, vector3f(1, 1, 0), 0.02f);

		std::transform(obj->shape->vertices,
					   obj->shape->vertices + 3,
					   obj->shape->vertices,
					   [&model](vector3f vertex) { return model.Transform(vertex); });

		obj->UpdateNormVectors();

		obj->objMinAABB = model.Transform(obj->objMinAABB);
		obj->objMaxAABB = model.Transform(obj->objMaxAABB);

		if (!objects.CheckAABB(*iter.GetNode(), obj->objMinAABB) &&
			!objects.CheckAABB(*iter.GetNode(), obj->objMaxAABB))
		{
			std::cout << "DDU (" << obj->objMinAABB.x << ", " << obj->objMinAABB.y << ") / (" 
				<< obj->objMaxAABB.x << ", " << obj->objMaxAABB.y << ") " << std::endl;
			//objects.Delete(*iter);
			//objects.Insert(obj);
		}
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
			std::cout << "Collision Doubt" << std::endl;
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
	RigidbodyUpdate();
	DetectCollision();
}

void PhysicsEngine::AddObject(RenderableObject* object)
{
	objects.Insert(dynamic_cast<IQTData*>(object));
}