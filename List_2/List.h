#pragma once
#include<iostream>
#include<string>

#define tab "\t"
//#define DEBUG

template <typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
		//public:
		Element(T Data, Element* pNext = nullptr,
			Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			std::cout << " EConstructor:\t" << this << std::endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			std::cout << "EDestructor:\t" << this << std::endl;
#endif // DEBUG

		}
		friend class List<T>;
	}*Head, * Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{

	public:
		ConstIterator(Element* Temp);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator& operator--();
		ConstIterator& operator++(int);
		ConstIterator& operator--(int);
	};
	class ConstReversIterator :public ConstBaseIterator
	{

	public:
		ConstReversIterator(Element* Temp);
		~ConstReversIterator();
		ConstReversIterator& operator++();
		ConstReversIterator operator++(int);
		ConstReversIterator& operator--();
		ConstReversIterator operator--(int);
	};
	class Iterator : public ConstIterator
	{

	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReversIterator : public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) :ConstReversIterator(Temp) {}
		~ReversIterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReversIterator crbegin()const;
	ConstReversIterator crend()const;
	Iterator begin();
	Iterator end();
	ReversIterator rbegin();
	ReversIterator rend();
	List();
	List(const std::initializer_list<T>& il);
	List(const List& other);
	~List();
	//Opeators
	List& operator=(const List& other);
	//Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	//Methods
	//Adding elements
	void print()const;
	void revers_print()const;
	//Removing elements
	void pop_front();
	void pop_back();
	//Removing elements
	void insert(int index, T Data);
	void erase(int index);
};
template<typename T> void print(const List<T>& list);