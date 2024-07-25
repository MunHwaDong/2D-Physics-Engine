#ifndef QUADTNODE_H
#define QUADTNODE_H

#include <vector>
#include <functional>
#include "vector3f.h"
#include "IQTData.h"

enum class AREA { NW, NE, SW, SE };

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

	QuadTNode() : datas(), areaPtrs(4, nullptr), depth(0), minCoordi(vector3f(-100, -100, 0)), maxCoordi(vector3f(100, 100, 0))
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
	int GetNodeDataCount() const;
	void PushData(IQTData* data) const;

};
#endif