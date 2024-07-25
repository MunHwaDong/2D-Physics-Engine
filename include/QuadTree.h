#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "QuadTNode.h"

class QuadTree
{
private:
	QuadTNode* headptr;
	int maxDepth;

public:
	QuadTree() : headptr(new QuadTNode), maxDepth(3)
	{
		DivideSubArea(*headptr);
	};

	~QuadTree();

	void InsertData(const QuadTNode& node, IQTData* data);
	bool CheckAABB(const QuadTNode& node, const vector3f& position);

	//초기화에도 사용함으로 static 선언함
	static void DivideSubArea(QuadTNode& node);

	void DeleteData(IQTData* data);

	void TraversalTree(QuadTNode* node) const;
};

#endif