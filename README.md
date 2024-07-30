# 2D-Physics-Engine

1. 중력 구현
2. Quad Tree 구현 및 충돌 검출
3. 충돌에 대한 역학적 처리
4. vector3f를 구조체에서, Class로 분리함에 따라 Client.cpp에서 OpenGL VAO인자를 수정하였음
5. Quadtree Insert 구현 완료 및 Iterator Pattern을 적용하여 for loop순회를 가능하게 구현하였음

**#Todo-list**
1. InputManager Class를 구현해서 펙토리 패턴을 적용해 RenderableObject Class의 객체 생성 책임을 부여하기
2. 충돌 검출 구현
   2-1. QuadTree를 이용해 먼저 광역 탐지 수행 로직 구현
   2-2. 광역 탐지에 걸린 객체들만 지역 탐지를 수행하는 로직 구현
3. 충돌에 대한 역학적 처리에 대한 로직 구현.
   3-1. 충돌에 대한 벡터 방정식 공부 및 Shape객체에 Normal 벡터를 어떻게 정의해서 저장할 것 인지 고민
   3-2. 구현
