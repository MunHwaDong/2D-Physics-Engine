#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "QuadTNode.h"

/*

	1. 충돌 되는 도형들은, 다들 Shape가 다를 수 있다.
	2. 도형들의 크기는 각각 다를 수 있다
	3. RenderableObject는 도형의 중심점의 위치를 저장하고 있다. 도형의 크기와 관련된 정보는 Shape 멤버 변수에 들어있다.
	4. 중심점을 기준으로 트리에 삽입하면, 사실 엄청 가까이 존재하는데 멀다고 판단할 수 있지 않을까??
	
	5. 코딩하기 전에 "Quad Tree"의 정의부터 잘 공부하고 설계한 후 코딩하자!

*/

template<typename T>
class QuadTree
{
private:
	QuadTNode& headptr;

public:
	QuadTree();
	~QuadTree();

	//QuadTree는 영역을 4분할한다. D&C Algorithm의 전략을 사용해보자.
	void InsertData(const T& data);
	void DeleteData();

	void TraversalTree() const;
	void DivideArea();

};

#endif QUAD_TREE_H