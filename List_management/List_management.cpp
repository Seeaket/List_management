#include<iostream>
#include"Statement.h"
#include<iomanip>

int main()
{
	int counter = 0;
	List* list = Loadfile(&counter);
	Funcs Function[] = { (Funcs)Exits,(Funcs)Addperson,(Funcs)Deletely,(Funcs)Modify,(Funcs)View,(Funcs)Sort };
	while (1)
	{
		system("cls");
		Menu();
		char num[Max];
		std::cin >> num;
		if ( num[0] >= 48 && num[0] <= 53)
			Function[atoi(num)](list,&counter);
		else
		{
			std::cout << Blank(6) << "ÎÞÐ§ÊäÈë" << std::endl;
		}
		if (counter == 0)
			delete list;
		std::cout << std::endl << Blank(6);
		system("pause");
	}

	return 0;
}