#include"List.h"	
#include"List.cpp"
	
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
	List<int> list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;
	for (List<int>::ConstReversIterator it = list.crbegin(); it != list.crend(); it++)
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;
	print(list);

	List <double> d_list = { 2.3, 1.3, 3.14, 5.45, 7.62 };
	for (double i : d_list)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;
	for (List<double>::ReversIterator rit = d_list.rbegin(); rit != d_list.rend(); ++rit)
	{
		std::cout << *rit << tab;
	}
	std::cout << std::endl;
	List<std::string> s_list = { "test", "string", "type" };
	print(s_list);
	for (std::string i : s_list)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;
	for (List<std::string>::ReversIterator rit = s_list.rbegin(); rit != s_list.rend(); ++rit)
	{
		std::cout << *rit << tab;
	}
	std::cout << std::endl;
#endif // HOME_WORK
}