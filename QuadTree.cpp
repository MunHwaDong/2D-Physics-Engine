#include "QuadTree.h"

Iterator QuadTree::begin() const
{
    return Iterator(headptr);
}

Iterator QuadTree::end() const
{
    return Iterator();
}

std::unordered_set<IQTData*> QuadTree::Query(vector3f& min, vector3f& max) const
{
    std::unordered_set<IQTData*> foundObj;

    if (headptr)
    {
        QueryRecusive(*headptr, min, max, foundObj);
    }

    return foundObj;
}

void QuadTree::QueryRecusive(const QuadTNode& node, const vector3f& minCoordi, const vector3f& maxCoordi, std::unordered_set<IQTData*>& foundObjects) const
{
    if (node.GetNodeDepth() >= maxDepth || node.GetDataCount() <= 0) return;

    // 노드의 영역이 검색 영역과 교차하지 않으면 종료
    if (node.maxCoordi.x < minCoordi.x || node.minCoordi.x > maxCoordi.x || node.maxCoordi.y < minCoordi.y || node.minCoordi.y > maxCoordi.y)
    {
        return;
    }

    // 노드의 객체들을 결과에 추가
    for (int i = 0; i < node.GetDataCount(); ++i)
    {
        IQTData* data = node.GetData(i);

        const vector3f* dataPos = data->GetPosition();

        for (int j = 0; j < data->GetDataCount(); ++j)
        {
            if (dataPos[j].x >= minCoordi.x && dataPos[j].x <= maxCoordi.x && dataPos[j].y >= minCoordi.y && dataPos[j].y <= maxCoordi.y)
            {
                foundObjects.insert(data);
                break;
            }
        }
    }

    // 하위 노드를 재귀적으로 검색
    if (node.GetAreaPtr(NW)) QueryRecusive(*node.GetAreaPtr(NW), minCoordi, maxCoordi, foundObjects);
    if (node.GetAreaPtr(NE)) QueryRecusive(*node.GetAreaPtr(NE), minCoordi, maxCoordi, foundObjects);
    if (node.GetAreaPtr(SW)) QueryRecusive(*node.GetAreaPtr(SW), minCoordi, maxCoordi, foundObjects);
    if (node.GetAreaPtr(SE)) QueryRecusive(*node.GetAreaPtr(SE), minCoordi, maxCoordi, foundObjects);
}

void QuadTree::Insert(IQTData* data)
{
    InsertRecursive(*headptr, data);
}

void QuadTree::InsertRecursive(QuadTNode& node, IQTData* data)
{
    /*
        1. 데이터가 들어온 노드가 최대깊이에 도달했으면 해당 노드에 저장하고 끝낸다.
        2. 최대 깊이가 아니라면 데이터의 좌표값(들)이 NW, ..., SE 영역들 중 한 곳에 완전히 들어가 있는지 확인한다.
        3. 데이터 좌표가 해당 AABB 영역에 완전히 포함되어 있으면 카운터 값을 증가시킨다.
        4. 카운터 값과 데이터 개수와 같다면, 해당 Area로 다시 재귀적으로 InsertRecursive한다.
        5. 모든 Area를 돌아봤는데도 데이터 좌표들이 Area들에 완전히 포함되지 않는다면, 루트에 삽입한다.
    */

    if (node.GetNodeDepth() < this->maxDepth)
    {
        const vector3f* datasPos = data->GetPosition();
        int counter = 0;

        for (int area = 0; area < 4; ++area)
        {
            for (int idx = 0; idx < data->GetDataCount(); ++idx)
            {
                if (CheckAABB(*node.GetAreaPtr(static_cast<AREA>(area)), datasPos[idx]))
                {
                    ++counter;
                }
            }
            if (counter == data->GetDataCount())
            {
                DivideSubArea(*node.GetAreaPtr(static_cast<AREA>(area)));
                InsertRecursive(*node.GetAreaPtr(static_cast<AREA>(area)), data);
                break;
            }
            else
            {
                counter = 0;
            }
        }
    }

    //모든 Area들에 완전히 포함되지 않는다면, 루트에 삽입한다.
    node.PushData(data);
    return;
}

bool QuadTree::CheckAABB(const QuadTNode& node, const vector3f& position) const
{
    if (node.minCoordi.x < position.x && node.minCoordi.y < position.y &&
        node.maxCoordi.x > position.x && node.maxCoordi.y > position.y)
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
    node.SetAreaPtr(NW, new QuadTNode(vector3f(node.minCoordi.x, (node.maxCoordi.y + node.minCoordi.y) / 2, 0),
        vector3f((node.maxCoordi.x + node.minCoordi.x) / 2, node.maxCoordi.y, 0),
        node.GetNodeDepth() + 1));

    node.SetAreaPtr(NE, new QuadTNode(vector3f((node.maxCoordi.x + node.minCoordi.x) / 2, (node.maxCoordi.y + node.minCoordi.y) / 2, 0),
        vector3f(node.maxCoordi.x, node.maxCoordi.y, 0),
        node.GetNodeDepth() + 1));

    node.SetAreaPtr(SW, new QuadTNode(vector3f(node.minCoordi.x, node.minCoordi.y, 0),
        vector3f((node.maxCoordi.x + node.minCoordi.x) / 2, (node.maxCoordi.y + node.minCoordi.y) / 2, 0),
        node.GetNodeDepth() + 1));

    node.SetAreaPtr(SE, new QuadTNode(vector3f((node.maxCoordi.x + node.minCoordi.x) / 2, node.minCoordi.y, 0),
        vector3f(node.maxCoordi.x, (node.maxCoordi.y + node.minCoordi.y) / 2, 0),
        node.GetNodeDepth() + 1));
}

void QuadTree::Delete(IQTData* data)
{
    DeleteRecursive(*headptr, data);
}

void QuadTree::DeleteRecursive(QuadTNode& node, IQTData* data)
{
    if (node.GetNodeDepth() < this->maxDepth)
    {
        const vector3f* datasPos = data->GetPosition();
        int counter = 0;

        for (int area = 0; area < 4; ++area)
        {
            for (int idx = 0; idx < data->GetDataCount(); ++idx)
            {
                if (CheckAABB(*node.GetAreaPtr(static_cast<AREA>(area)), datasPos[idx]))
                {
                    ++counter;
                }
            }
            if (counter == data->GetDataCount())
            {
                DeleteRecursive(*node.GetAreaPtr(static_cast<AREA>(area)), data);
                break;
            }
            else
            {
                counter = 0;
            }
        }
    }

    //Root에 존재한다 판단
    node.DeleteData(data);
    return;
}

QuadTree::~QuadTree()
{

}