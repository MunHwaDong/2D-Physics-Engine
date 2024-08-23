#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <iostream>
#include <vector>
#include "RenderableObject.h"
#include "QuadTree.h"

/*

물리 파이프라인의 각 단계들을 제어하는 책임을 가진다.

    GenerateForce : 엔진에 등록된 물체들한테 deltaTime 간격으로 힘을 적용한다. (물체에 대한 알짜힘을 구한다.)
    RigidbodyUpdate : 힘을 적용한 후, Update된 물체의 중심점으로부터 다시 Rigidbody를 Update한다.
    DetectedCollision : 물체들의 충돌이 일어났는지 검출한다.
    ResolutionCollision : 충돌이 감지된 "물체 쌍(Pair)"의 역학적인 처리를 해준다.
*/

class PhysicsEngine
{
private:
    const vector3f C_gravitycoeff;
    //std::vector<RenderableObject*> objects;
    QuadTree objects;

    void GenerateForce(const float deltaTime);
    void RigidbodyUpdate(const float deltaTime);
    void DetectCollision();
    void ResolutionCollision();

public:
    //Constructor
    PhysicsEngine() : C_gravitycoeff(0.0f, -9.8f, 0.0f), objects()
    {};

    //Deconstructor
    ~PhysicsEngine()
    {};

    void Update(const float deltaTime);
    void AddObject(RenderableObject* object);
};
#endif