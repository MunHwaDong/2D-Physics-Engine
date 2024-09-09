#include "PhysicsEngine.h"

void PhysicsEngine::GenerateForce(vector3f Force, const float deltaTime)
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		if (!obj->isUseGravity && Force == C_gravitycoeff) continue;

		Integrator(obj, C_gravitycoeff, deltaTime);
	}
}

void PhysicsEngine::Integrator(RenderableObject* obj, vector3f Force, const float deltaTime)
{
	obj->vel += (Force * obj->inverseMass) * deltaTime;
	obj->pos += obj->vel * deltaTime;

	obj->angularVel += (Force * obj->inverseMass) * deltaTime;
	obj->theta += obj->angularVel * deltaTime;
}

void PhysicsEngine::RigidbodyUpdate()
{
	Matrix4f model;
	std::vector<std::pair<IQTData*, RenderableObject*>> events;

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj(dynamic_cast<RenderableObject*>(*iter));

		model = Utill::GetModelMatrix(vector3f(0), vector3f(Utill::WORLD_MAX, Utill::WORLD_MAX, 0), 0);

		vector3f t = model.Transform(obj->pos);

		model = Utill::GetModelMatrix(t, vector3f(1), 0.02f);

		std::transform(obj->shape->vertices,
					   obj->shape->vertices + 3,
					   obj->shape->vertices,
					   [model](vector3f vertex) -> vector3f { return model.Transform(vertex); });

		obj->UpdateNormVectors();
		model = Utill::GetModelMatrix(t, vector3f(1), 0);

		obj->objMinAABB = model.Transform(obj->objMinAABB);
		obj->objMaxAABB = model.Transform(obj->objMaxAABB);

		if (objects.CheckAABB(*iter.GetNode(), obj->objMinAABB) &&
			objects.CheckAABB(*iter.GetNode(), obj->objMaxAABB))
		{
			//obj = new RenderableObject(obj);
			//events.push_back({ *iter, obj });
		}
	}

	for (const auto& ele : events)
	{
		objects.Delete(ele.first);
		objects.Insert(ele.second);
	}
}

void PhysicsEngine::DetectCollision()
{
	BoardPhase();
}

void PhysicsEngine::BoardPhase()
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		std::vector<IQTData*> collisionableSet = objects.Query(obj->objMinAABB, obj->objMaxAABB);

		if (!collisionableSet.empty() && collisionableSet.size() > 1)
		{
			std::cout << "Collision Doubt" << std::endl;
			NarrowPhase(collisionableSet);
		}
	}
}



void PhysicsEngine::NarrowPhase(std::vector<IQTData*>& collisionableSet)
{
	//Using SAT(Seperating Axis Theorem)
	/*
		!. 각 면의 Normal Vector는 RenderableObject->shape에 저장되어 있다.
		!!. Utill::Nomalize를 통해 Normalization을 진행할 수 있다.
		!!!. RenderableObject->shape에 월드 좌표로 변환되어 있는 정점 위치들이 존재함.
		!!!!. 도형의 각 Normal Vector들에 대해서, 도형의 모든 정점들을 투영해서 검사해봐야함.
				(A 도형의 Normal들과 B 도형의 Normal 모두에 대해서 검사해야한다.)
	*/
	
	const int collisionableNum = collisionableSet.size();

	for(int objNum = 0; objNum < collisionableNum; ++objNum)
	{
		RenderableObject* obj1 = dynamic_cast<RenderableObject*>(collisionableSet[objNum]);

		for(int targetObj = objNum + 1; targetObj < collisionableNum; ++targetObj)
		{
			RenderableObject* obj2 = dynamic_cast<RenderableObject*>(collisionableSet[targetObj]);
			CollisionInfo collisionInfo;

			if(IsOverlap(obj1, obj2, collisionInfo))
			{
				std::cout << obj1->name << " / " << obj2->name << " is Collision!" << std::endl;
				ResolutionCollision(obj1, obj2, collisionInfo);
			}
		}
	}

}

bool PhysicsEngine::IsOverlap(const RenderableObject* o1, const RenderableObject* o2, CollisionInfo& collisionInfo) const
{
	/*
		1. o2의 한 정점을 선택한다.
		2. o1의 한 법선을 선택한다.
		3. o1의 한 정점들에 대해 (1)에서 선택한 o2의 한 정점과 뺄셈을 진행하여 나온 각 벡터들을 (2)에서 선택한 법선과 내적한다.
		4. 이 때 SAT에 의해, 하나라도 내적 결과가 양수라면 해당 방향에서 충돌하지 않은 것이니 break하여 다음 법선을 검사한다.
		5. 양수가 아니라면, 최소값과 비교하여 최소값을 업데이트하고, 어떤 정점에서 최솟값이였는지 저장한다.

		(1) ~ (5)를 o2에도 적용하여, 두 최솟값이 모두 무한이 아니면 충돌이 발생한 것.
	*/
	double o1Min = Utill::INF;
	double o2Min = Utill::INF;

	vector3f o1MinVer;
	vector3f o2MinVer;

	for(int o2VertexNum = 0, normNum = 0; o2VertexNum < o2->shape->numVertices; ++o2VertexNum)
	{
		double proj = 0.0;

		for(int o1VertexNum = 0; o1VertexNum < o1->shape->numVertices; ++o1VertexNum)
		{
			proj = o1->shape->normVec[normNum].DotProduct(
				(o1->shape->vertices[o1VertexNum] - o2->shape->vertices[o2VertexNum]));

			if(proj > 0) break;
			if(o1Min > proj)
			{
				o1Min = proj;
				o1MinVer = o1->shape->normVec[normNum];
			}
		}

		++normNum;
	}

	for(int o1VertexNum = 0, normNum = 0; o1VertexNum < o1->shape->numVertices; ++o1VertexNum)
	{
		double proj = 0.0;

		for(int o2VertexNum = 0; o2VertexNum < o2->shape->numVertices; ++o2VertexNum)
		{
			proj = o2->shape->normVec[normNum].DotProduct(
				(o2->shape->vertices[o1VertexNum] - o1->shape->vertices[o2VertexNum]));

			if(proj > 0) break;
			if(o2Min > proj)
			{
				o2Min = proj;
				o2MinVer = o2->shape->normVec[normNum];
			}
		}

		++normNum;
	}

	if(o1Min == Utill::INF && o2Min == Utill::INF) return false;
	else
	{
		collisionInfo.SetCollisionInfo(o1Min, o2Min, o1MinVer, o2MinVer);
		return true;
	}
}

void PhysicsEngine::ResolutionCollision(RenderableObject* o1,  RenderableObject* o2, CollisionInfo& collisionInfo)
{
	const float restitution = 1.0f;

	const vector3f relativeVelocity = o1->vel - o2->vel;

	const float o1NormDirScalar = relativeVelocity.DotProduct(collisionInfo.o2Norm);
	const float o2NormDirScalar = relativeVelocity.DotProduct(collisionInfo.o1Norm);

	const float o1ImpulseScalar = (-(1 + restitution) * o1NormDirScalar / o1->inverseMass + o2->inverseMass);
	const float o2ImpulseScalar = (-(1 + restitution) * o2NormDirScalar / o1->inverseMass + o2->inverseMass);

	//vector3f o1Impulse = collisionInfo.o2Norm * (o1ImpulseScalar * o1->inverseMass);
	//vector3f o2Impulse = collisionInfo.o1Norm * (o2ImpulseScalar * o2->inverseMass);

	vector3f o1Impulse = collisionInfo.o2Norm * (o1ImpulseScalar * o1->inverseMass);
	vector3f o2Impulse = collisionInfo.o1Norm * (o2ImpulseScalar * o2->inverseMass);

	//o1->vel = o1->vel + o1Impulse;
	//o2->vel = o2->vel - o2Impulse;

	Integrator(o1, o1Impulse, 0.02f);
	Integrator(o2, o2Impulse, 0.02f);

	//RigidbodyUpdate();
}

void PhysicsEngine::Update(const float deltaTime)
{
	GenerateForce(C_gravitycoeff, deltaTime);
	RigidbodyUpdate();
	DetectCollision();
}

void PhysicsEngine::AddObject(RenderableObject* object)
{
	objects.Insert(dynamic_cast<IQTData*>(object));
}