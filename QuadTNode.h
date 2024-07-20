#ifndef QUADTNODE_H
#define QUADTNODE_H

#include <vector>
#include "vector3f.h"

template <typename T>
class QuadTNode
{
private:
	std::vector<T> datas;
	vector3f minCoordi;
	vector3f maxCoordi;

	QuadTNode* NWptr;
	QuadTNode* NEptr;
	QuadTNode* SWptr;
	QuadTNode* SEptr;

public:
	QuadTNode() : minCoordi(vector3f(-100, 100, 0)), maxCoordi(vector3f(100, -100, 0)), NWptr(nullptr), NEptr(nullptr), SWPtr(nullptr), SEptr(nullptr)
	{};
	QuadTNode(vector3f minCoordi, vector3f maxCoordi) : minCoordi(minCoordi), maxCoordi(maxCoordi), NWptr(nullptr), NEptr(nullptr), SWPtr(nullptr), SEptr(nullptr)
	{};

	~QuadTNode();

	//data 관련 메소드들
	std::vector<T> GetData() const;
	int GetDataCount() const;
	void PushData(const T& data);

};

template <typename T>
QuadTNode<T>::~QuadTNode()
{
	delete NWptr;
	delete NEptr;
	delete SWptr;
	delete SEptr;
}

//현재 영역의 데이터들의 "사본"을 넘겨줌
template <typename T>
std::vector<T> QuadTNode<T>::GetData() const
{
	return std::vector<T>(this->datas);
}

template <typename T>
int QuadTNode<T>::GetDataCount() const
{
	return datas.size();
}

template <typename T>
void QuadTNode<T>::PushData(const T& data)
{
	datas.push_back(data);
}

#endif QUADTNODE_H