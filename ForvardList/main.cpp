#include<iostream>
#include"Windows.h"

class ForwardList;
class Element
{
	int Data;
	Element* pNext;
	static unsigned int count;
public:
	/*int get_Data()const
	{
		return Data;
	}
	void set_Data(int Data)
	{
		this->Data = Data;
	}*/
	
	
	Element(int Data, Element* pNext = nullptr)
		:Data(Data), pNext(pNext)
	{
		count++;
		std::cout << "EConstructor:\t" << this << std::endl;
	}
	~Element()
	{
		count--;
		std::cout << "EDestructor:\t" << this << std::endl;
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& rigth);
};
unsigned int Element::count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Element* getHead()const
	{ return Head; }
	unsigned int size()const
	{ return size; }
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		std::cout << typeid(il.begin()).name() << std::endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		std::cout << " IL_Constructor:\t" << this << std::endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}*/

		*this = other;
		std::cout << "CopyConstructor:\t" << this << std::endl;
	}
	ForwardList(ForwardList& other) :ForwardList()
	{
		*this = std::move(other);
		std::cout << "MoveConstructor:\t" << this << std::endl;
	}

		
	~ForwardList()
	{
		while (Head)pop_front();
		std::cout << "LDestructor:\t" << this << std::endl;
	}
	//               Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		return *this;
	}
	ForwardList& operator=(ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_back();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		std::cout << "CopyAsignment:\t" << this << std::endl;
		return *this;
	}
	//Adding elements
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;*/
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	//Removing elements:

	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int index, int Data)
	{		
		if (index > Head->count)
		{
			std::cout << " Error: Out of the list " << std::endl;
			return;
		}			
			Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int index)
	{
		if (index == 0)return pop_front();
		if (index == Head->count - 1)return pop_back();
		if (index >= Head->count)
		{
			std::cout << "Error: out of rang" << std::endl; return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
	}
	//Methods
	void print()const
	{
		//Element* Temp = Head; //Temp - iterator
		//while (Temp)
		//{			
		//	std::cout << Temp << "\t" << Temp->Data << "\t" <<
		//		Temp->pNext << std::endl;
		//	Temp = Temp->pNext;
		//}
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
		std::cout << "Number of elements list: " << size << std::endl;
		std::cout << "Number of elements general: " << Head->count << std::endl;
	}
	/*ForwardList& copy(const ForwardList& obj)
	{		
		clear(*this);
		Head = nullptr;
		Element* Temp = obj.Head;		
		while(Temp)
		{
			push_back(Temp->Data);			
			 Temp = Temp->pNext;
		}
		return *this;
	}*/
	/*ForwardList& operator=(const ForwardList& obj)
	{
		copy(obj);
		return *this;
	}*/	
	Element* move(int index)
	{		
		if (Head->count > 0 && index <= Head->count)
		{
			Element* Temp = Head;
			for (int i = 0; i < index-1; i++) Temp = Temp->pNext;
			return Temp;		
		}			
		if (index > Head->count && Head->count != 0) { std::cout << "Out of the list "; }
		else if (index != 0 && Head == nullptr) { std::cout << "No elements "; }		
	}
	void clear(ForwardList& obj)
	{
		Element* Temp = obj.Head;
		while (Temp)
		{
			delete Temp->pNext;
		}
	}
};
//std::ostream& operator<<(std::ostream& os, const Element& obj)
//{
//	std::cout << obj.get_Data();
//	return os;
//}

ForwardList operator+(const ForwardList& left, const ForwardList& rigth)
{
	ForwardList cat = left;
	for (Element* Temp = rigth.getHead(); Temp; Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}
//#define BASE_CHECK
#define COPY_METHODS_CHECK
//#define MOVE_METHODS_CHECK 
void main()
{
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD console_rect{ 120, 32 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &console_rect);*/

#ifdef BASE_CHECK
	int index;
	int list_size;

	std::cout << "Enter list_size: "; std::cin >> list_size;
	ForwardList list;

	for (int i = 0; i < list_size; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();

	//std::cout << "Enter index for list\t"; std::cin >> index;
	//std::cout << "Element number: " << index << " = " << *list.move(index) << std::endl;

	//int value;
	//std::cout << "Enter inserted elements index: "; std::cin >> index;
	//std::cout << "Enter number inserted elements: "; std::cin >> value;
	//list.insert(index, value);
	//list.print();

	//std::cout << "Enter erased elements index: "; std::cin >> index;
	//list.erase(index-1);
	////list.push_front(999);
	//list.print();

	
#endif // BASE_CHECK

#ifdef COPY_METHODS_CHECK
	ForwardList list_1 = { 3, 5, 8, 13, 21 };
	list_1 = list_1;
	list_1.print();
	//ForwardList list_2 = list_1;//Copyconstructor
	ForwardList list_2;
	list_2 = list_1;//CopyAssignment
	list_2.print();
#endif // COPY_METHODS_CHECK
	/*ForwardList list1 = { 3, 5, 8, 13, 21 };
	ForwardList list2 = { 34, 55, 89 };
	ForwardList list3 = list1 + list2;
	list3.print();*/

	
}