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

	void DeleteRecursive(QuadTNode& node, IQTData* data);

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

	//Insert 도우미 함수들
	void InsertRecursive(QuadTNode& node, IQTData* data);
	bool CheckAABB(const QuadTNode& node, const vector3f& position) const;

	//Query 관련 함수들
	std::vector<IQTData*> Query(vector3f& min, vector3f& max) const;
	void QueryRecusive(const QuadTNode& node, const vector3f& min, const vector3f& max, std::vector<IQTData*>& foundObj) const;

	void Delete(IQTData* data);

	~QuadTree();
};

#endif