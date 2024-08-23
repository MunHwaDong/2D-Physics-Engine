#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "QuadTNode.h"
#include "Iterator.h"
#include "Utill.h"
#include <unordered_set>

class QuadTree
{
private:
	QuadTNode* headptr;
	int maxDepth;

	//Public Insert 도우미 함수들
	void InsertRecursive(QuadTNode& node, IQTData* data);
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
	std::unordered_set<IQTData*> Query(vector3f& min, vector3f& max);
	void QueryRecusive(QuadTNode* node, vector3f& min, vector3f& max, std::unordered_set<IQTData*>& foundObj) const;

	void DeleteData(IQTData* data);

	~QuadTree();
};

#endif