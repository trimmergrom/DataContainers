#include"List_2.h"

template<typename T> List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	std::cout << "CBItConstructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstBaseIterator::~ConstBaseIterator()
{
#ifdef DEBUG
	std::cout << "CBItDestructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

template<typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	std::cout << "CItConstructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	std::cout << "CItDestructor:\t" << this << std::endl;
#endif // DEBUG
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()//prefix
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()//prefix
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++(int)//postfix
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--(int)//postfix
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

template<typename T> List<T>::ConstReversIterator::ConstReversIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	std::cout << "CRev_It_Constr" << this << std::endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstReversIterator::~ConstReversIterator()
{
#ifdef DEBUG
	std::cout << "CRev_It_Destr" << this << std::endl;
#endif // DEBUG
}
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::ConstReversIterator::operator++(int)
{
	ConstReversIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::ConstReversIterator::operator--(int)
{
	ConstReversIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

template<typename T>typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::crbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::crend()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReversIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReversIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	std::cout << "LConstructor:\t" << this << std::endl;
#endif // DEBUG

}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
		push_back(*it);
#ifdef DEBUG
	std::cout << "IL_Constructor:\t" << this << std::endl;
#endif // DEBUG

}
template<typename T>List<T>::List(const List& other) :List()
{
	*this = other;
	std::cout << "Copy_LConstructor:\t" << this << std::endl;
}
template<typename T>List<T>::~List()
{
	while (Head)pop_front();
	//while (Tail)pop_back();
#ifdef DEBUG
	std::cout << "LDestructor:\t" << this << std::endl;
#endif // DEBUG

}

//Opeators

template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
#ifdef DEBUG
	std::cout << "CopyAssignment:\t" << this << std::endl;
#endif // DEBUG

	return *this;
}

//Adding elements:
template<typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Element* New = new Element(Data);	
	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)return push_front(Data);
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
//Methods
//						Adding elements
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		std::cout << Temp->pPrev << tab << Temp << tab
		<< Temp->Data << tab << Temp->pNext << std::endl;
	std::cout << "Namber elements at list: " << size << std::endl;
}
template<typename T>void List<T>::revers_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		std::cout << Temp->pPrev << tab << Temp << tab
		<< Temp->Data << tab << Temp->pNext << std::endl;
	std::cout << "Namber elements at list: " << size << std::endl;
}
//						Removing elements
template<typename T>void  List<T>::pop_front()
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
template<typename T>void  List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
//							Removing elements
template<typename T>void List<T>::insert(int index, T Data)
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
template<typename T>void List<T>::erase(int index)
{
	if (index == 0)return pop_front();
	if (index == size - 1)return pop_back();
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

template<typename T> void print(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;

}