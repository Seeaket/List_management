#ifdef _DEBUG

#ifndef DBG_NEW

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#define new DBG_NEW

#endif

#endif // _DEBUG
//
#include<iostream>
#include"Statement.h"
#include<iomanip>
#include<stdlib.h>
#include<stdlib.h>
#include<crtdbg.h>

int main()
{
	//_CrtSetBreakAlloc(164);
	int counter = 0;
	List* list = new List;
	list = Loadfile(list,&counter);
	if (list == nullptr)
	{
		list = new List;
		list->next = nullptr;
	}
	Funcs Function[] = { (Funcs)Exits,(Funcs)Addperson,(Funcs)Deletely,(Funcs)Modify,(Funcs)View,(Funcs)Sort };
	while (1)
	{
		system("cls");
		Menu();
		char num[Max];
		std::cin >> num;
		int num1 = atoi(num);
		if (num1 >= 0 && num1 <= 5)
			Function[num1](list, &counter);
		else
		{
			std::cout << Blank(6) << "    ÎÞÐ§ÊäÈë" << std::endl;
		}
		std::cout << std::endl << Blank(6);
		system("pause");
	}
	return 0;
}