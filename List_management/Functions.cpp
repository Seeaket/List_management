#define	_CRTDBG_MAP_ALLOC
#include"Statement.h"
#include<iomanip>//std::setw()函数可用于输出型变量的对齐，括号内就是可以设置的字段宽度
#include<string>
#include<fstream>
#include<stdlib.h>
#include<crtdbg.h>

#define EPS 1e-6

List* Loadfile(List* list,int* counter)
{
	std::ifstream openfile("链表名单.txt");
	List* temp = list;
	List* temps = temp;
	if (openfile.is_open())
	{
		while(openfile >> temp->Data.Name >> temp->Data.Id >> temp->Data.Wages)
		{
			temp->next = new List;
			(*counter)++;
			temps = temp;
			temp = temp->next;
		}
		if(*counter == 0)
			return list = nullptr;
		temps->next = nullptr;
		delete temp;
	}
	openfile.close();
	return list;
}

void Savefile(List* list)
{
	std::ofstream openfile("链表名单.txt");
	if (openfile.is_open())
	{
		List* temp = list;
		while (temp != nullptr)
		{
			openfile << temp->Data.Name << std::endl << temp->Data.Id << std::endl << temp->Data.Wages << std::endl;
			temp = temp->next;
		}
	}
	openfile.close();
}

void Menu()
{
	std::cout << Blank(5) << "   ---------------------------" << std::endl;
	std::cout << Blank(6) << "List模式-管理系统" << std::endl;
	std::cout << Blank(6) << "1、添加人物信息" << std::endl << Blank(6) << "2、删除人物信息" << std::endl;
	std::cout << Blank(6) << "3、修改人物信息" << std::endl << Blank(6) << "4、浏览人物信息" << std::endl;
	std::cout << Blank(6) << "5、排序人物信息" << std::endl << Blank(6) << "0、退出系统" << std::endl;
	std::cout << Blank(5) << "   ---------------------------" << std::endl;
	std::cout << Blank(5) << "   请选择功能:";
}

void Exits(List* list,int* counter)
{
	std::cout << Blank(5) << "是否确认退出\t\ty[Y]/n[N]" << std::endl << Blank(6) << "     请选择:";
	int c = Judge();
	if (c == 1)
	{
		if(*counter == 0)
		{
			delete list;
			_CrtDumpMemoryLeaks();//内存泄漏报告函数
			exit(0);
		}
		List* temp = list->next;
		while (c == 1)
		{
			delete list;
			if(temp == nullptr)
			{
				_CrtDumpMemoryLeaks();//内存泄漏报告函数
				exit(0);
			}
			list = temp;
			temp = temp->next;
			//内存泄漏可能存在于temp==nullptr没有进行判断，系统进行了判别，提前进行判断即可
		}		
	}
	std::cout << (c == 0 ? "\t\t\t\t\t\t     取消退出！" : "\t\t\t\t\t\t无效操作取消退出！") << std::endl;
}

void Addperson(List* list,int* counter)
{
	std::cout << Blank(4) << "    ---------------------------------------" << std::endl;
	std::cout << Blank(4) << "    1、信息头部添加\t\t2、信息尾部添加" << std::endl << Blank(6) << "    请选择:";
	char num[Max];
	std::cin >> num;
	if (num[0] != 49 && num[0] != 50)
	{
		std::cout << Blank(6) << "错误输入！" << std::endl;
		return;
	}
	List* temp = Add_list();
	Add_just(list,temp,counter);
	if (*counter == 0)
	{
		list->Data = temp->Data;
		Savefile(list);
		delete temp;
		(*counter)++;
		std::cout << Blank(7) << "添加成功！" << std::endl;
		return;
	}
	if (num[0] == 49)
	{
		/*此处添加需要注意,在函数内不能更改指针参数的指向或者说地址，但是你可以在后面添加就是不能改变首地址位置
		否则返回函数后，链表还是原来的地址,地址实参的问题*/
		List* temps = new List;
		temps->Data = list->Data;
		temp->next = list->next;
		list->Data = temp->Data;
		temp->Data = temps->Data;
		list->next = temp;
		Savefile(list);
		(*counter)++;
		delete temps;
		std::cout << Blank(7) << "添加成功！" << std::endl;
	}
	else if (num[0] == 50)
	{
		List* temps = list;
		while (temps->next != nullptr)
			temps = temps->next;
		temps->next = temp;
		Savefile(list);
		(*counter)++;
		std::cout << Blank(7) << "添加成功！" << std::endl;
	}
}

void Deletely(List* list, int* counter)
{
	std::cout << Blank(5) << "请输入删除编号:";
	int id;
	std::cin >> id;
	List* temp = list;
	List* temps = list;
	std::cout << Blank(4) << "      ---------------------------------------" << std::endl;
	std::cout << Blank(5) << "姓名\t\t编号\t\t工资" << std::endl;
	if (*counter == 0)
	{
		std::cout << std::endl << Blank(6) << "未找到匹配编号！" << std::endl;
		return;
	}
	while (temp->Data.Id != id)
	{
		temps = temp;
		temp = temp->next;
		if (temp == nullptr)
		{
			std::cout << std::endl << Blank(6) <<"未找到匹配编号！" << std::endl;
			return;
		}
	}
	std::cout << Blank(5) << std::left << std::setw(16) << temp->Data.Name << std::left << std::setw(16) << temp->Data.Id
		<< temp->Data.Wages << std::endl;
	std::cout << Blank(4) << "是否删除该条匹配数据？\t\t\ty[Y]/n[N]" << std::endl << Blank(6) << "     请选择:";
	int c = Judge();
	if (c == 1)
	{
		temps->next = temp->next;
		(*counter)--;
		if (*counter == 0)
			list = nullptr;
		else
		{
			delete temp;
		}
		Savefile(list);
		std::cout << Blank(6) << "删除成功！" << std::endl;
		return;
	}
	std::cout << Blank(5) << (c == 0 ?  "已取消删除！" : "无效操作已取消删除！") << std::endl;
}

void Modify(List* list, int* counter)
{
	std::cout << Blank(5) << "请输入修改编号:";
	int id;
	std::cin >> id;
	List* temp = list;
	List* temps = temp;
	std::cout << Blank(4) << "      ---------------------------------------" << std::endl;
	std::cout << Blank(5) << "姓名\t\t编号\t\t工资" << std::endl;
	if(*counter == 0)
	{
		std::cout << std::endl << Blank(6) << "未找到匹配编号！" << std::endl;
		return;
	}
	while (temp->Data.Id != id)
	{
		temps = temp;
		temp = temp->next;
		if (temp == nullptr)
		{
			std::cout  << std::endl << Blank(6)<< "未找到匹配编号！" << std::endl;
			return;
		}
	}
	std::cout << Blank(5) << std::left << std::setw(16) << temp->Data.Name << std::left << std::setw(16) << temp->Data.Id
		<< temp->Data.Wages << std::endl;
	std::cout << Blank(4) << "是否修改匹配数据？\t\t\ty[Y]/n[N]" << std::endl << Blank(6) << "     请选择:";
	int c = Judge();
	if (c == 1)
	{
		List* node = Add_list();
		Add_just(list, node, counter);
		temp->Data = node->Data;
		Savefile(list);
		delete node;
		std::cout << Blank(5) << "修改成功！" << std::endl;
		return;
	}
	std::cout << Blank(5) << (c == 0 ? "已取消修改！" : "无效操作已取消修改！") << std::endl;
}

void View(List* list,int* counter)
{
	List* temp = list;
	std::cout << Blank(4) << "      ---------------------------------------" << std::endl;
	std::cout << Blank(5) << "姓名\t\t编号\t\t工资" << std::endl;
	if (*counter == 0)
	{
		std::cout << std::endl << Blank(6) << "    暂无数据" << std::endl;
		return;
	}
	while (temp != nullptr)
	{
		std::cout << Blank(5) << std::left << std:: setw(16) << temp->Data.Name << std::left << std::setw(16) << temp->Data.Id 
			<< temp->Data.Wages << std::endl;
		temp = temp->next;
	}
}

void Sort(List* list, int* counter)
{
	std::cout << Blank(4) << "--------------------------------------------------" << std::endl;
	std::cout << Blank(4) << "1、姓名排序\t    2、编号排序\t      3、工资排序" << std::endl 
		<< std::endl << Blank(6) << "    请选择:";
	char num[Max];
	std::cin >> num;
	if (num[0] != 49 && num[0] != 50 && num[0] != 51)
	{
		std::cout << Blank(6) << "错误输入！" << std::endl;
		return;
	}
	if (*counter == 0)
	{
		std::cout << Blank(6) << "暂无数据！" << std::endl;
		return;
	}
	Sortfunc func[] = { (Sortfunc)namesearch,(Sortfunc)idsearch,(Sortfunc)wagesearch };
	List* temp = list;
	List* sist = temp;
	List* tr = sist;
	List* ar = sist;
	List* cc = new List;
	int nn = *counter, tt = *counter - 1;
	while (nn--)
	{
		tr = temp;
		sist = temp->next;
		ar = sist;
		while (tt)
		{
			if (func[atoi(num)-1](tr, ar) == 1)
			{
				cc->Data = ar->Data;
				ar->Data = tr->Data;
				tr->Data = cc->Data;
			}
			tr = tr->next;
			ar = ar->next;
			tt--;
		}
		tt = *counter - (*counter - nn) - 1;
	}
	delete cc;
	std::cout << std::endl;
	View(list, counter);
}

int namesearch(List* list,List* temp)
{
	return temp->Data.Name < list->Data.Name;
}

int idsearch(List* list, List* temp)
{
	return  temp->Data.Id < list->Data.Id;
}

int wagesearch(List* list, List* temp)
{
	return (temp->Data.Wages + EPS) < list->Data.Wages;
}



int Determine(List* list, int id)
{
	List* tt = list;
	while (tt != nullptr && tt->Data.Id != id)
	{
		tt = tt->next;
		if (tt == nullptr)
			return 0;
	}
	return 1;
}

int Judge()
{
	char c;
	std::cin >> c;
	if (c == 'y' || c == 'Y')
		return 1;
	else if (c == 'n' || c == 'N')
	{
		return 0;
	}
	return -1;
}

std::string Blank(int num)
{
	std::string tabs(num, '\t');
	return tabs;
}

List* Add_list()
{
	List* sist = new List;
	sist->next = nullptr;
	return sist;
}

void Add_just(List* list,List* temp,int* counter)
{
	std::cout << Blank(5) << "姓名:";
	std::cin >> temp->Data.Name;
	while(1)
	{
		std::cout << Blank(5) << "编号:";
		std::cin >> temp->Data.Id;
		if (*counter == 0 || Determine(list, temp->Data.Id) == 0)
			break;
		else
		{
			std::cout << Blank(5) << "编号重复!" << std::endl;
		}
	}
	std::cout << Blank(5) << "工资:";
	std::cin >> temp->Data.Wages;
}
