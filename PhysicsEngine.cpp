#include "PhysicsEngine.h"

void PhysicsEngine::GenerateForce(const float deltaTime)
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		RenderableObject* obj = dynamic_cast<RenderableObject*>(*iter);

		// std::cout << obj->name << std::endl;
		// for (int i = 0; i < 3; ++i)
		// {
		// 	std::cout << obj->shape->vertices[i].x << ", " << obj->shape->vertices[i].y << std::endl;
		// }
		 
		//std::cout << obj->name << " : " << obj->pos.x << " " << obj->pos.y << std::endl;

		if (!obj->isUseGravity) continue;

		obj->vel += (C_gravitycoeff * obj->inverseMass) * deltaTime;
		obj->pos += obj->vel * deltaTime;

		obj->angularVel += (C_gravitycoeff * obj->inverseMass) * deltaTime;
		obj->theta += obj->angularVel * deltaTime;

		//std::cout << obj->name << " : " << obj->pos.x << " " << obj->pos.y << std::endl;

		//std::cout << beforevel.x - obj->vel.x << " " << beforevel.y - obj->vel.y << std::endl;
		//beforevel = obj->vel;

		//std::cout << obj->name << std::endl;
		//for (int i = 0; i < 3; ++i)
		//{
		//	std::cout << obj->shape->vertices[i].x << ", " << obj->shape->vertices[i].y << std::endl;
		//}

		//std::cout << obj->name << " 법선 : " << obj->shape->normVec[0].x << " " << obj->shape->normVec[0].y << std::endl;
		//std::cout << obj->name << " 법선 : " << obj->shape->normVec[1].x << " " << obj->shape->normVec[1].y << std::endl;
		//std::cout << obj->name << " 법선 : " << obj->shape->normVec[2].x << " " << obj->shape->normVec[2].y << std::endl;
	}
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


		1. 처음 다각형의 법선 정보를 가져온다.
		2. 해당 법선에 두 도형의 모든 면을 투영한다.
		3. 투영 시, 각 도형들의 면들에 대해 최대 값과 최소 값을 저장한다.
		4. 두 도형의 범위가 겹친다면, (1)로 돌아간다.
		5. 두 도형의 범위가 겹치지 않는다면, 두 도형은 충돌하지 않은 것이므로 다음 도형을 검사한다.
	*/
	
	const int collisionableNum = collisionableSet.size();

	for(int objNum = 0; objNum < collisionableNum; ++objNum)
	{
		RenderableObject* obj1 = dynamic_cast<RenderableObject*>(collisionableSet[objNum]);

		for(int targetObj = objNum + 1; targetObj < collisionableNum; ++targetObj)
		{
			RenderableObject* obj2 = dynamic_cast<RenderableObject*>(collisionableSet[targetObj]);
			std::pair<vector3f, vector3f> collisionInfo;

			if(IsOverlap(obj1, obj2, collisionInfo))
			{
				std::cout << obj1->name << " / " << obj2->name << " is Collision!" << std::endl;
				ResolutionCollision(obj1, obj2);
			}
		}
	}

}

bool PhysicsEngine::IsOverlap(const RenderableObject* o1, const RenderableObject* o2, std::pair<vector3f, vector3f>& collisionInfo) const
{
	const auto o1Edges = o1->GetEdge();
	const auto o2Edges = o2->GetEdge();

	double o1Min = Utill::INF;
	double o1Max = (-1) * Utill::INF;
	double o2Min = Utill::INF;
	double o2Max = (-1) * Utill::INF;

	for(int normNum = 0; normNum < o1->shape->numVertices; ++normNum)
	{
		float proj = o1->shape->normVec[normNum].DotProduct(o1Edges[normNum]);

		if(o1Min > proj) o1Min = proj;
		if(o1Max < proj) o1Max = proj;

		proj = o1->shape->normVec[normNum].DotProduct(o2Edges[normNum]);

		if(o2Min > proj) o2Min = proj;
		if(o2Max < proj) o2Max = proj;
	}

	if(o1Min > o2Max || o1Max < o2Min) return false;

	//obj2의 법선 벡터들에도 투영해서 검사해야한다.
	o1Min = Utill::INF;
	o1Max = (-1) * Utill::INF;
	o2Min = Utill::INF;
	o2Max = (-1) * Utill::INF;

	for(int normNum = 0; normNum < o2->shape->numVertices; ++normNum)
	{
		float proj = o2->shape->normVec[normNum].DotProduct(o1Edges[normNum]);

		if(o1Min > proj) o1Min = proj;
		if(o1Max < proj) o1Max = proj;

		proj = o2->shape->normVec[normNum].DotProduct(o2Edges[normNum]);

		if(o2Min > proj) o2Min = proj;
		if(o2Max < proj) o2Max = proj;
	}

	if(o1Min > o2Max || o1Max < o2Min) return false;
	else return true;
}


void PhysicsEngine::ResolutionCollision(RenderableObject* o1,  RenderableObject* o2)
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