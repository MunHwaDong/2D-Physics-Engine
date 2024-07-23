#ifndef QUADTNODE_H
#define QUADTNODE_H

#include <vector>
#include "vector3f.h"
#include "IQTData.h"

enum AREA {NW, NE, SW, SE};

class QuadTNode
{
private:
	std::vector<IQTData> datas;
	//NW -> NE -> SW -> SE
	std::vector<QuadTNode*> areaPtrs;

public:
	vector3f minCoordi;
	vector3f maxCoordi;

	QuadTNode() : minCoordi(vector3f(-100, 100, 0)), maxCoordi(vector3f(100, -100, 0)), areaPtrs(4, nullptr)
	{};
	QuadTNode(vector3f minCoordi, vector3f maxCoordi) : minCoordi(minCoordi), maxCoordi(maxCoordi), areaPtrs(4, nullptr)
	{};
	QuadTNode(vector3f minCoordi, vector3f maxCoordi, std::vector<QuadTNode*> areaPtr) : minCoordi(minCoordi), maxCoordi(maxCoordi), areaPtrs(areaPtr)
	{};

	~QuadTNode();

	QuadTNode* GetAreaPtr(AREA area) const;
	void SetAreaPtr();

	std::vector<IQTData> GetData() const;
	int GetDataCount() const;
	void PushData(const IQTData& data) const;

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

std::vector<IQTData> QuadTNode::GetData() const
{
	return std::vector<IQTData>(this->datas);
}

int QuadTNode::GetDataCount() const
{
	return datas.size();
}

void QuadTNode::PushData(const IQTData& data) const
{
	const_cast<QuadTNode*>(this)->PushData(data);
	static_cast<const QuadTNode*>(this);
}

#endif QUADTNODE_H