#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
#include "QuadTNode.h"

class Iterator
{
private:
    std::stack<QuadTNode*> nodePtrs;
    QuadTNode* currentNode;
    int dataIdx;

    void Traversal(QuadTNode* node)
    {
        if (!node) return;

        if (node->GetAreaPtr(AREA::SE)->GetDataCount() != 0)
        {
            Traversal(node->GetAreaPtr(AREA::SE));
        }
        if (node->GetAreaPtr(AREA::SW)->GetDataCount() != 0)
        {
            Traversal(node->GetAreaPtr(AREA::SW));
        }
        if (node->GetAreaPtr(AREA::NE)->GetDataCount() != 0)
        {
            Traversal(node->GetAreaPtr(AREA::NE));
        }
        if (node->GetAreaPtr(AREA::NW)->GetDataCount() != 0)
        {
            Traversal(node->GetAreaPtr(AREA::NW));
        }

        if(node->GetDataCount() != 0)
            nodePtrs.push(node);
    }

public:
    Iterator() : nodePtrs(), currentNode(nullptr), dataIdx(0)
    {};

    Iterator(QuadTNode* headPtr) : nodePtrs(), currentNode(nullptr), dataIdx(0)
    {
        if(headPtr)
        {
            Traversal(headPtr);
            if(!nodePtrs.empty())
            {
                currentNode = nodePtrs.top();
                nodePtrs.pop();
            }
        }
    }

    ~Iterator()
    {};

    Iterator& operator++()
    {
        //currentNode is nullptr
        if(!currentNode) return *this;

        ++dataIdx;

        if(currentNode->GetDataCount() <= dataIdx)
        {
            //모든 노드 순회 완료
            if(nodePtrs.empty())
            {
                currentNode = nullptr;
            }
            else
            {
                currentNode = nodePtrs.top();
                nodePtrs.pop();
                dataIdx = 0;
            }
        }

        return *this;
    }

    IQTData* operator*() const
    {
        return currentNode->GetData(dataIdx);
    }

    bool operator==(const Iterator& operand) const
    {
        return currentNode == operand.currentNode;
    }

    bool operator!=(const Iterator& operand) const
    {
        return currentNode != operand.currentNode;
    }

    //QT의 삭제 연산을 구현하기 위한, 임시 연산자
    QuadTNode* GetNode()
    {
        return currentNode;
    }
};

#endif