#include "QuadTNode.h"

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

IQTData* QuadTNode::GetData(const int idx) const
{
	return datas.at(idx);
}

int QuadTNode::GetDataCount() const
{
	return datas.size();
}

void QuadTNode::PushData(IQTData* data) const
{
	const_cast<QuadTNode*>(this)->datas.push_back(data);
}