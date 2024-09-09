# 2D-Physics-Engine

#구현
1. Semi-implicit Euler method로 Integator를 구현하여 물체에 중력을 적용함
2. QuadTree의 Insert를 구현하고, 기존 PhysicsEngine 클래스의 RenderableObject의 자료구조를 std::vector<RenderableObject*> 에서 QuadTree로 바꿈.
3. QuadTree의 Iterator를 구현하여 for-loop으로 순회할 수 있게 하였음
4. Client에서 Shader 코드를 분리하고 Render-loop에서 PhysicsEngine::Update()를 std::chrono를 이용해 0.02초마다 호출하게 만들었음
5. Normal Vector를 구하는 기능을 Utill 클래스에 Static으로 구현함
6. Matrix3f/Matrix4f 클래스를 구현
7. Matrix4f를 이용해, Model Matrix를 구현하여 Client에서 입력되는 vertex 좌표값들을 world 좌표계로 변환하여 QuadTree에 삽입하는 기능
8. World 좌표 공간의 QuadTree를 이용하여 물체 충돌의 광역 검사를 수행하는 기능

#구현해야할 것
1. 광역 검사에서 검출된 객체들의 실제 충돌이 일어났는지 지역 검사를 하는 기능 (point-point, point-edge...등등 상황에 따라 다른 알고리즘을 사용해야 하니 Strategy Pattern을 적용할 수 있는지 고려해본다.)
2. 실제 충돌이 일어났을시 충돌에 대한 벡터 방정식의 공부와 이를 실제 코드로 구현.
3. Client에서 객체 생성에 대한 기능을, Factory Pattern을 적용하여 분리할 수 있는지 고려한다. (구현중)
