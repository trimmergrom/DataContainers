#include<iostream>
#include"Windows.h"
#define tab "\t" 

class ForwardList;
class Element
{
	int Data;
	Element* pNext;
	static unsigned int count;
public:
	int get_Data()const
	{
		return Data;
	}
	void set_Data(int Data)
	{
		this->Data = Data;
	}


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
	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& rigth);

};
unsigned int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		std::cout << "ItConstructor:\t" << this << std::endl;
	}
	~Iterator()
	{
		std::cout << "ItDestructor:\t" << this << std::endl;
	}
	Iterator& operator++()//prefix
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator& operator++(int)//postfix
	{
		Iterator old = *this;
		Temp = Temp->pNext;
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

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	Element* getHead()const { return Head; }
	unsigned int get_size()const { return size; }
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
		/*int* pa;
		const int* cpa;
		int const* pca;
		const int const* cpca;*/
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}*/
		*this = other;
		std::cout << "Copy_LConstructor:\t" << this << std::endl;
	}
	ForwardList(ForwardList&& other)
	{
		*this = std::move(other);
		std::cout << "Move_LConstructor:\t" << this << std::endl;
	}

	~ForwardList()
	{
		while (Head)pop_front();
		std::cout << "LDestructor:\t" << this << std::endl;
	}

	//					Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		std::cout << "CopyAssignment:\t" << this << std::endl;
		return *this;
	}
	//			Move Methods
	
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		std::cout << "MoveAssignment:\t" << this << std::endl;
		return *this;
	}
	int& operator[](unsigned int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	const int& operator[](unsigned int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
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
		//for (Element* Temp = Head; Temp; Temp = Temp++)
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
		std::cout << "Number of elements list: " << size << std::endl;
		std::cout << "Number of elements general: " << Head->count << std::endl;
	}
	ForwardList& copy(const ForwardList& obj)
	{
		clear(*this);
		Head = nullptr;
		Element* Temp = obj.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		return *this;
	}
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
			for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
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
	
	/*ForwardList& revers(const ForwardList& other)
	{
		Element* Temp = Head;
		
		while (Temp)
		{
		push_front(Temp->Data);
		Temp = Temp->pNext;
		}
		
		return *this;
	}*/
	void revers()
	{
		ForwardList reverse_list;
		while (Head)
		{
			reverse_list.push_front(Head->Data);
			pop_front();
		}
		Head = reverse_list.Head;
		reverse_list.Head = nullptr;
	}
	/*void unique()
	{
		for (Element* Temp = Head; Temp->pNext; Temp = Temp->pNext)
		{
			for (Element* Temp2 = Temp; Temp2->pNext; Temp2 = Temp2->pNext)
			{
				if (Temp->Data == Temp2->pNext->Data)
				{
					Element* Erased = Temp2->pNext;
					Temp2->pNext = Temp2->pNext->pNext;
					delete Erased;
					size--;
					Temp2 = Temp;
				}
			}
		}
		
	}*/
	//void unique()
	//{
	//	for (Element* Temp = Head; Temp->pNext; Temp = Temp->pNext)
	//	{
	//		for (Element* Temp2 = Head; Temp2->pNext; Temp2 = Temp2->pNext)
	//		{
	//			if (Temp == Temp2)continue;
	//			if (Temp->Data == Temp2->pNext->Data)
	//			{
	//				Element* Erased = Temp2->pNext;
	//				Temp2->pNext = Temp2->pNext->pNext;
	//				delete Erased;
	//				//Temp2 = Temp;
	//				size--;
	//			}
	//		}
	//	}
	//	
	//}
};
ForwardList operator+(const ForwardList& left, const ForwardList& rigth)
{
	ForwardList cat = left;
	for (Element* Temp = rigth.getHead(); Temp; Temp = Temp->pNext)
	{
		cat.push_back(Temp->Data);
	}
	return cat;
}
std::ostream& operator<<(std::ostream& os, const Element& obj)
{
	std::cout << obj.get_Data();
	return os;
}
//#define BASE_CHECK
//#define COPY_METHODS_CHECK
//#define MOVE_METHODS_CHECK
//#define UNIGUE_METHODS_CHECK
#define REVERS_METHODS_CHECK
//#define RANG_BASE_FOR_ARRAY
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

	std::cout << "Enter index for list\t"; std::cin >> index;
	std::cout << "Element number: " << index << " = " << *list.move(index) << std::endl;

	int value;
	std::cout << "Enter inserted elements index: "; std::cin >> index;
	std::cout << "Enter number inserted elements: "; std::cin >> value;
	list.insert(index, value);
	list.print();

	std::cout << "Enter erased elements index: "; std::cin >> index;
	list.erase(index);
	list.push_front(999);
	list.print();

	ForwardList list_1;
	/*list_1 = list;
	list_1.print();*/
#endif // BASE_CHECK

#ifdef COPY_METHODS_CHECK
	ForwardList list = { 3, 5, 8, 13, 21 };
	list = list;
	list.print();
	//ForwardList list2 = list; //CopyConstructor
	ForwardList list2;
	list2 = list;//CopyAssignment
	list2.print();
#endif // COPY_METHODS_CHECK

#ifdef MOVE_METHODS_CHECK
	ForwardList list1 = { 3, 5, 8, 13, 21 };
	ForwardList list2 = { 34, 55, 89 };
	ForwardList list3 = list1 + list2;
	list3.print();

	for (int i = 0; i < list3.get_size(); i++)
	{
		list3[i] = rand() % 100;
	}

	for (int i = 0; i < list3.get_size(); i++)
	{
		std::cout << list3[i] << "\t";
	}
	std::cout << std::endl;
#endif // MOVE_METHODS_CHECK


#ifdef UNIGUE_METHODS_CHECK
	int n;
	std::cout << "Enter size: "; std::cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 10);
	}
	list.print();
	list.unique();
	list.print();
#endif // UNIGUE_METHODS_CHECK

#ifdef REVERS_METHODS_CHECK
	ForwardList list = { 3, 5, 8, 13, 21 };

	list.print();
	std::cout << "\n---------------------------------\n" << std::endl;;
	list.revers();
	list.print();
#endif // REVERS_METHODS_CHECK

	/*for (Iterator it = list.getHead(); it != nullptr; it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;*/
#ifdef RANG_BASE_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		std::cout << arr[i] << tab;
	}
	std::cout << std::endl;

	for (int i : arr)
	{
		std::cout << i << tab;
	}
	std::wcout << std::endl;
#endif // RANG_BASE_FOR_ARRAY

	/*ForwardList list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;*/


}