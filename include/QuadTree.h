#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "QuadTNode.h"
#include "Iterator.h"

using CollisionablePair = std::pair<IQTData*, IQTData*>;

class QuadTree
{
private:
	QuadTNode* headptr;
	int maxDepth;

	//Public Insert 도우미 함수들
	void InsertData(const QuadTNode& node, IQTData* data);
	bool CheckAABB(const QuadTNode& node, const vector3f& position);

	//초기화에도 사용함으로 static 선언함
	static void DivideSubArea(QuadTNode& node);

public:
	QuadTree() : headptr(new QuadTNode), maxDepth(3)
	{
		DivideSubArea(*headptr);
	};

	//Iterators
	Iterator begin() const;
	Iterator end() const;

	void Insert(IQTData* data);

	//Query 관련 함수들

	void DeleteData(IQTData* data);

	~QuadTree();
};

#endif