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

public:
    Iterator() : currentNode(nullptr), dataIdx(0)
    {};

    Iterator(QuadTNode* headPtr) : currentNode(nullptr), dataIdx(0)
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

    void Traversal(QuadTNode* node)
    {
        if(!node) return;

        if(node->GetAreaPtr(AREA::SE))
        {
            Traversal(node->GetAreaPtr(AREA::SE));
        }
        if(node->GetAreaPtr(AREA::SW))
        {
            Traversal(node->GetAreaPtr(AREA::SW));
        }
        if(node->GetAreaPtr(AREA::NE))
        {
            Traversal(node->GetAreaPtr(AREA::NE));
        }
        if(node->GetAreaPtr(AREA::NW))
        {
            Traversal(node->GetAreaPtr(AREA::NW));
        }

        nodePtrs.push(node);
    }

    Iterator& operator++()
    {
        if(!currentNode) return *this;

        if(currentNode->GetDataCount() == dataIdx + 1)
        {
            if(!nodePtrs.empty())
            {
                currentNode = nodePtrs.top();
                nodePtrs.pop();
                dataIdx = 0;
            }
        }
        else
        {
            ++dataIdx;
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
};

#endif