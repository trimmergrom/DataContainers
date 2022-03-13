#include<iostream>

#define tab "\t"
//#define DEBUG


class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	//public:
		Element(int Data, Element* pNext = nullptr,
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

		friend class List;
		//friend class Iterator;
	}*Head, *Tail;
	size_t size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			std::cout << "ItConstructor:\t" << this << std::endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			std::cout << "ItDestructor:\t" << this << std::endl;
#endif // DEBUG

		}

		Iterator& operator++()//prefix
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator& operator--()//prefix
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator& operator++(int)//postfix
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--(int)//postfix
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReversIterator
	{
		Element* Temp;
	public:
		ReversIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			std::cout << "Rev_It_Constr" << this << std::endl;
#endif // DEBUG
		}
		~ReversIterator()
		{
#ifdef DEBUG
			std::cout << "Rev_It_Destr" << this << std::endl;
#endif // DEBUG
		}
		ReversIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReversIterator operator++(int)
		{
			ReversIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReversIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReversIterator operator--(int)
		{
			ReversIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const ReversIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReversIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}

	};

public:
	const Iterator begin()const
	{
		return Head;
	}
	const Iterator end()const
	{
		return nullptr;
	}
	const ReversIterator rbegin()const
	{
		return Tail;
	}
	const ReversIterator rend()const
	{
		return nullptr;
	}

	/*Element* getHead()const { return Head; }
	unsigned int get_size()const { return size; }*/
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
		std::cout << "IL_Constructor:\t" << this << std::endl;
	}
	List(const List& other) :List()
	{
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		*this = other;
		std::cout << "Copy_LConstructor:\t" << this << std::endl;
	}
	~List()
	{
		while (Head)pop_front();
		//while (Tail)pop_back();
		std::cout << "LDestructor:\t" << this << std::endl;
	}

							//Opeators

	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		std::cout << "CopyAssignment:\t" << this << std::endl;
		return *this;
	}

							//Adding elements:

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		/*New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
							//Methods
	//						Adding elements
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp->pPrev << tab << Temp << tab
			<< Temp->Data << tab << Temp->pNext << std::endl;
		std::cout << "Namber elements at list: " << size << std::endl;
	}
	void revers_print()const
	{
		for(Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			std::cout << Temp->pPrev << tab << Temp << tab
			<< Temp->Data << tab << Temp->pNext << std::endl;
		std::cout << "Namber elements at list: " << size << std::endl;
	}
	//						Removing elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	//							Removing elements
	void insert(int index, int Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - 1 - index; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}
	void erase(int index)
	{
		if (index == 0)return pop_front();
		if (index == size-1)return pop_back();
		if (index >= size)return;
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	};
	void print(const List& list)
	{
		for (List::Iterator it = list.begin(); it != list.end(); it++)
		{
			*it *= 10;
			std::cout << *it << tab;
		}
		std::cout << std::endl;

	}
	
//#define BASE_CHECK
//#define COPY_METHODS_CHECK
#define HOME_WORK
int main()
{
#ifdef BASE_CHECK
	int n;
	List list;
	std::cout << "Enter size of list: "; std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.revers_print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

	std::cout << "\n----------------------------------------------\n";
	int index;
	int value;
	std::cout << "Enter index inserted elements: "; std::cin >> index;
	std::cout << "Enter value inserted elements: "; std::cin >> value;
	list.insert(index, value);
	list.print();
	list.revers_print();

	std::cout << "Enter index erased elements: "; std::cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef COPY_METHODS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	list.revers_print();

	List list2 = list;//Copyconstructor
	/*List list2;
	list2 = list;*/	//CopyAssignment
	list2.print();
	list2.revers_print();
#endif // COPY_METHODS_CHECK
#ifdef HOME_WORK
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;
	for (List::ReversIterator it = list.rbegin(); it != list.rend(); it++)
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;
	print(list);
#endif // HOME_WORK


}