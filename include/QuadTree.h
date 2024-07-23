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
	{};

	~QuadTree();

	void InsertData(const QuadTNode& node, const IQTData& data);
	bool CheckAABB(const QuadTNode& node, const vector3f& position);
	void DivideSubArea(const QuadTNode& node);

	void DeleteData();

	void TraversalTree() const;
	void DivideArea();
};

#endif QUAD_TREE_H