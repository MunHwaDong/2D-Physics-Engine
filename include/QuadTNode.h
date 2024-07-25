#ifndef QUADTNODE_H
#define QUADTNODE_H

#include <vector>
#include <functional>
#include "vector3f.h"
#include "IQTData.h"

enum AREA {NW, NE, SW, SE};

class QuadTNode
{
private:
	std::vector<IQTData*> datas;
	//NW -> NE -> SW -> SE
	std::vector<QuadTNode*> areaPtrs;
	int depth;

public:
	vector3f minCoordi;
	vector3f maxCoordi;

	QuadTNode() : datas(),areaPtrs(4, nullptr), depth(0), minCoordi(vector3f(-100, -100, 0)), maxCoordi(vector3f(100, 100, 0))
	{};
	QuadTNode(vector3f minCoordi, vector3f maxCoordi) : datas(), areaPtrs(4, nullptr), depth(0), minCoordi(minCoordi), maxCoordi(maxCoordi)
	{};
	QuadTNode(vector3f minCoordi, vector3f maxCoordi, int depth) : datas(), areaPtrs(), depth(depth), minCoordi(minCoordi), maxCoordi(maxCoordi)
	{};

	~QuadTNode();

	QuadTNode* GetAreaPtr(AREA area) const;
	void SetAreaPtr(AREA area, QuadTNode* node);

	int GetNodeDepth() const;

	std::vector<IQTData*> GetData() const;
	int GetDataCount() const;
	void PushData(IQTData* data) const;

};

QuadTNode::~QuadTNode()
{
	for(const auto& ptr : areaPtrs)
	{
		delete ptr;
	}
}

QuadTNode* QuadTNode::GetAreaPtr(AREA area) const
{
	return areaPtrs.at(area);
}

void QuadTNode::SetAreaPtr(AREA area, QuadTNode* node)
{
	areaPtrs.at(area) = node;
}

int QuadTNode::GetNodeDepth() const
{
	return depth;
}

std::vector<IQTData*> QuadTNode::GetData() const
{
	return std::vector<IQTData*>(this->datas);
}

int QuadTNode::GetDataCount() const
{
	return datas.size();
}

void QuadTNode::PushData(IQTData* data) const
{
	const_cast<QuadTNode*>(this)->datas.push_back(data);
}

#endif