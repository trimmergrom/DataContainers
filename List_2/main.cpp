#include<iostream>


class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr,
			Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			std::cout << " EConstrucyor:\t" << this << std::endl;
		}

		~Element()
		{
			std::cout << "EDestructor:\t" << this << std::endl;
		}
		friend class List;
	}*Head, *Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	~List()
	{
		std::cout << "LDestructor:\t" << this << std::endl;
	}

	//Adding elements:

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext;

	}
};
int main()
{


}