#include<iostream>


class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRigth;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRigth = nullptr)
			:Data(Data), pLeft(pLeft), pRigth(pRigth)
		{
			std::cout << "EConstructor:\t" << this << std::endl;
		}
		~Element()
		{
			std::cout << "EDestructor:\t" << this << std::endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* get_Root()const
	{
		return this->Root;
	}
	Tree() :Root(nullptr)
	{		
		std::cout << "TConstructor:\t" << this << std::endl;
	}
	Tree(const std::initializer_list<int>& il) :Root(NULL)
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			insert(*it);
		std::cout << "IT_Constructor:\t" << this << std::endl;
	}	
	~Tree()
	{
		if (Root != nullptr)
		{
			freemem(Root->pLeft);
			freemem(Root->pRigth);
			delete Root;
		}
		std::cout << "TDestructor:\t" << this << std::endl;
	}
	void insert(int Data)
	{
		insert(Data, this->Root);
	}

	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int summ()const
	{
		return summ(Root);
	}
	double avg()const
	{
		return (double)summ(Root) / count(Root);
	}
	void freemem()
	{
		return freemem(Root);
	}
	void print()const
	{
		print(Root);
		std::cout << std::endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else 
		//else if (Data > Root->Data)
		{
			if (Root->pRigth == nullptr)Root->pRigth = new Element(Data);
			else insert(Data, Root->pRigth);
		}
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return int();
		if (Root->pRigth == nullptr)return Root->Data;
		else return maxValue(Root->pRigth);
		//return !Root->pRigth ? Root->Data : maxValue(Root->pRigth);
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return int();
		if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);
		//return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		//return Root->pLeft? minValue(Root->pLeft) : Root->Data;
	}
	int count(Element* Root)const
	{		
		
		if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRigth) + 1;		
		//return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRigth) + 1;
	}
	int summ(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return summ(Root->pLeft) + summ(Root->pRigth) + Root->Data;
	}
	void freemem(Element* Root)
	{
		if (Root != nullptr)
		{
			freemem(Root->pLeft);
			freemem(Root->pRigth);
			delete Root;
		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		std::cout << Root->Data << "\t";
		print(Root->pRigth);
	}
};
class UniqueTree:public Tree
{

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
			//else if (Data > Root->Data)
		{
			if (Root->pRigth == nullptr)Root->pRigth = new Element(Data);
			else insert(Data, Root->pRigth);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};


//#define TREE_CHECK
void main()
{

#ifdef TREE_CHECK
	int n;
	int value;
	srand(10);
	std::cout << "Enter number Tree: "; std::cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	std::cout << std::endl;
	std::cout << "Enter adding value: "; std::cin >> value;
	tree.insert(value);
	tree.print();
	std::cout << "min number in to tree: " << tree.minValue() << std::endl;
	std::cout << "max number in to tree: " << tree.maxValue() << std::endl;
	std::cout << "Number elements in to tree:" << tree.count() << std::endl;
	std::cout << "Summa elements in to tree:" << tree.summ() << std::endl;
	std::cout << "AVG elements in to tree:" << tree.avg() << std::endl;
	UniqueTree unique_tree;
	for (int i = 0; i < n; i++)
	{
		unique_tree.insert(rand() % 100);
	}
	unique_tree.print();
	std::cout << std::endl;

	std::cout << "Enter adding value: "; std::cin >> value;
	tree.insert(value);
	tree.print();
	std::cout << "min number in to Utree: " << unique_tree.minValue() << std::endl;
	std::cout << "max number in to Utree: " << unique_tree.maxValue() << std::endl;
	std::cout << "Number elements in to Utree:" << unique_tree.count() << std::endl;
#endif // TREE_CHECK
	
	Tree iltree = { 50, 25, 75, 16, 32, 64, 80 };
	iltree.print();




}