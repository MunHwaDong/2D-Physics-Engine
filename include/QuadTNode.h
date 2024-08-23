#ifndef QUADTNODE_H
#define QUADTNODE_H

#include <vector>
#include <unordered_set>

#include "vector3f.h"
#include "IQTData.h"

enum AREA { NW, NE, SW, SE };

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
	QuadTNode(vector3f minCoordi, vector3f maxCoordi, int depth) : datas(), areaPtrs(4, nullptr), depth(depth), minCoordi(minCoordi), maxCoordi(maxCoordi)
	{};

	~QuadTNode();

	QuadTNode* GetAreaPtr(AREA area) const;
	void SetAreaPtr(AREA area, QuadTNode* node);

	int GetNodeDepth() const;

	IQTData* GetData(const int idx) const;
	int GetDataCount() const;
	void PushData(IQTData* data) const;

};
#endif