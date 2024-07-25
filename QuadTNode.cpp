#include "QuadTNode.h"

QuadTNode::~QuadTNode()
{
	for (const auto& ptr : areaPtrs)
	{
		delete ptr;
	}
}

QuadTNode* QuadTNode::GetAreaPtr(AREA area) const
{
	return areaPtrs.at(static_cast<int>(area));
}

void QuadTNode::SetAreaPtr(AREA area, QuadTNode* node)
{
	areaPtrs.at(static_cast<int>(area)) = node;
}

int QuadTNode::GetNodeDepth() const
{
	return depth;
}

std::vector<IQTData*> QuadTNode::GetData() const
{
	return std::vector<IQTData*>(this->datas);
}

int QuadTNode::GetNodeDataCount() const
{
	return datas.size();
}

void QuadTNode::PushData(IQTData* data) const
{
	const_cast<QuadTNode*>(this)->datas.push_back(data);
}