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

		//std::cout << obj->name << " : " << obj->pos.x << " " << obj->pos.y << std::endl;

		//std::cout << beforevel.x - obj->vel.x << " " << beforevel.y - obj->vel.y << std::endl;
		//beforevel = obj->vel;

		std::cout << obj->name << std::endl;
		for (int i = 0; i < 3; ++i)
		{
			std::cout << obj->shape->vertices[i].x << ", " << obj->shape->vertices[i].y << std::endl;
		}

		//std::cout << "obj 법선 : " << obj->shape->normVec[0].x << " " << obj->shape->normVec[0].y << std::endl;
		//std::cout << "obj 법선 : " << obj->shape->normVec[1].x << " " << obj->shape->normVec[1].y << std::endl;
		//std::cout << "obj 법선 : " << obj->shape->normVec[2].x << " " << obj->shape->normVec[2].y << std::endl;
	}
}

void PhysicsEngine::RigidbodyUpdate()
{
	Matrix4f model;
	std::vector<std::pair<IQTData*, RenderableObject*>> events;

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj(dynamic_cast<RenderableObject*>(*iter));

		//model = Utill::GetScaleMatrix4f(vector3f(0.0001f, 0.0001f, 0)) * Utill::GetRotateMatrix4f(0.02f, vector3f(0, 0, 1.0f)) * Utill::GetTranslateMatrix4f(vector3f(0));
		model = Utill::GetModelMatrix(vector3f(0), vector3f(0.0001f, 0.0001f, 0), 0.02f);

		std::transform(obj->shape->vertices,
					   obj->shape->vertices + 3,
					   obj->shape->vertices,
					   [model](vector3f vertex) -> vector3f { return model.Transform(vertex); });

		model = Utill::GetModelMatrix(obj->pos, vector3f(Utill::WORLD_MAX, Utill::WORLD_MAX, 0), 0);
		//model = Utill::GetScaleMatrix4f(vector3f(Utill::WORLD_MAX, Utill::WORLD_MAX, 0)) * Utill::GetRotateMatrix4f(0, vector3f(0, 0, 1.0f)) * Utill::GetTranslateMatrix4f(vector3f(0));

		std::transform(obj->shape->vertices,
					obj->shape->vertices + 3,
					obj->shape->vertices,
					[model](vector3f vertex) -> vector3f { return model.Transform(vertex); });

		if (objects.CheckAABB(*iter.GetNode(), obj->objMinAABB) &&
			objects.CheckAABB(*iter.GetNode(), obj->objMaxAABB))
		{
			events.push_back({ *iter, obj });
		}
	}

	for (const auto& ele : events)
	{
		objects.Delete(ele.first);
		objects.Insert(ele.second);
	}
}

void PhysicsEngine::DetectCollision() const
{
	BoardPhase();
}

void PhysicsEngine::BoardPhase() const
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		std::unordered_set<IQTData*> collisionableSet = objects.Query(obj->objMinAABB, obj->objMaxAABB);

		if (!collisionableSet.empty() && collisionableSet.size() > 1)
		{
			std::cout << "Collision Doubt" << std::endl;
			NarrowPhase(collisionableSet);
		}
	}
}

void PhysicsEngine::NarrowPhase(std::unordered_set<IQTData*> collisionableSet) const
{
	//Using SAT(Seperating Axis Theorem)
	/*
		!. 각 면의 Normal Vector는 RenderableObject->shape에 저장되어 있다.
		!!. Utill::Nomalize를 통해 Normalization을 진행할 수 있다.
		!!!. RenderableObject->shape에 월드 좌표로 변환되어 있는 정점 위치들이 존재함.
		!!!!. 도형의 각 Normal Vector들에 대해서, 도형의 모든 정점들을 투영해서 검사해봐야함.
				(A 도형의 Normal들과 B 도형의 Normal 모두에 대해서 검사해야한다.)


		1. 두 두형의 처음 정점을 선택한다.
		2. 두 정점을 빼서, 두 정점 사이를 표현하는(거리, 방향) 벡터를 구한다.
			(선택한 Normal을 가진 도형 - 비교하려는 도형)
		3. (2)에서 구한 벡터를, 선택한 Normal에 내적한다.
		4. (3)에서 구한 값이, 최소값이면 저장한다.
	*/

	//해당 지역에서 충돌 가능성이 있는 모든 도형들에 대해 검사를 실시해야함
	//for (auto iter = collisionableSet.begin(); iter != collisionableSet.end(); ++iter)
	//{
	//	auto obj1 = *iter;

	//	const vector3f* o1V = obj1->GetPosition();
	//	const vector3f* o1N = dynamic_cast<RenderableObject*>(obj1)->shape->normVec;

	//	auto next = std::next(iter);
	//	while (next != collisionableSet.end())
	//	{
	//		auto obj2 = *next;

	//		const vector3f* o2V = obj2->GetPosition();

	//		for()


	//		++next;
	//	}
	//}

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