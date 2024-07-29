#include "QuadTree.h"

Iterator QuadTree::begin() const
{
    return Iterator(headptr);
}

Iterator QuadTree::end() const
{
    return Iterator();
}

void QuadTree::Insert(IQTData* data)
{
    InsertData(*headptr, data);
}

void QuadTree::InsertData(const QuadTNode& node, IQTData* data)
{
    /*
        1. 데이터가 들어온 노드가 최대깊이에 도달했으면 해당 노드에 저장하고 끝낸다.
        2. 최대 깊이가 아니라면 데이터의 좌표값(들)이 NW, ..., SE 영역들 중 한 곳에 완전히 들어가 있는지 확인한다.
        3. 만약, 한 곳이라도 완전하게 들어가 있지 않다면 AABB 체크에서 모두 False가 나올 것이다.
        4. 모두 False가 나왔다면 루트 노드에 삽입한다.
        5. 한 곳에 완전하게 들어가있다면 해당 노드에서 공간을 분할하여 다시 1번으로 돌아간다.
    */

    //최대 깊이에 도달했다면, 더 이상 나누지 않고 해당 노드에 데이터를 저장한다.
    if(node.GetNodeDepth() >= this->maxDepth)
    {
        node.PushData(data);
        return;
    }

    bool flag = false;
    const vector3f* datasPos = data->GetPosition();
    QuadTNode* dataInArea;

    for(int area = 0; area < 4; ++area)
    {
        for(int idx = 0; idx < data->GetDataCount(); ++idx)
        {
            flag = CheckAABB(*node.GetAreaPtr(static_cast<AREA>(area)), datasPos[idx]);

            if(flag)
            {
                dataInArea = node.GetAreaPtr(static_cast<AREA>(area));
                break;
            }
        }

        if(flag) {break;};
    }

    if(!flag)
    {
        node.PushData(data);
    }
    else if(flag)
    {
        DivideSubArea(*dataInArea);
        InsertData(*dataInArea, data);
    }

}

bool QuadTree::CheckAABB(const QuadTNode& node, const vector3f& position)
{
    if(node.minCoordi.x < position.x && node.minCoordi.y < position.y &&
       node.maxCoordi.x > position.x && node.minCoordi.y > position.y)
       {
        return true;
       }
    else
    {
        return false;
    }
}

//나눠져야하는 타겟 노드가 들어옴
void QuadTree::DivideSubArea(QuadTNode& node)
{
    node.SetAreaPtr(NW, new QuadTNode(vector3f(node.minCoordi.x, node.minCoordi.y / 2, 0),
                                        vector3f(node.maxCoordi.x / 2, node.maxCoordi.y, 0)));

    node.SetAreaPtr(NE, new QuadTNode(vector3f(node.maxCoordi.x / 2, node.maxCoordi.y / 2, 0),
                                        vector3f(node.maxCoordi.x, node.maxCoordi.y, 0)));
    
    node.SetAreaPtr(SW, new QuadTNode(vector3f(node.minCoordi.x, node.minCoordi.y, 0),
                                        vector3f(node.maxCoordi.x / 2, node.maxCoordi.y / 2, 0)));

    node.SetAreaPtr(SE, new QuadTNode(vector3f(node.maxCoordi.x / 2, node.minCoordi.y, 0),
                                        vector3f(node.maxCoordi.x, node.maxCoordi.y / 2, 0)));
}

void QuadTree::DeleteData(IQTData* data)
{

}

QuadTree::~QuadTree()
{

}