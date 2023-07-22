#define	_CRTDBG_MAP_ALLOC
#include"Statement.h"
#include<iomanip>//std::setw()��������������ͱ����Ķ��룬�����ھ��ǿ������õ��ֶο��
#include<string>
#include<fstream>
#include<stdlib.h>
#include<crtdbg.h>

#define EPS 1e-6

List* Loadfile(List* list,int* counter)
{
	std::ifstream openfile("��������.txt");
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
	std::ofstream openfile("��������.txt");
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
	std::cout << Blank(6) << "Listģʽ-����ϵͳ" << std::endl;
	std::cout << Blank(6) << "1�����������Ϣ" << std::endl << Blank(6) << "2��ɾ��������Ϣ" << std::endl;
	std::cout << Blank(6) << "3���޸�������Ϣ" << std::endl << Blank(6) << "4�����������Ϣ" << std::endl;
	std::cout << Blank(6) << "5������������Ϣ" << std::endl << Blank(6) << "0���˳�ϵͳ" << std::endl;
	std::cout << Blank(5) << "   ---------------------------" << std::endl;
	std::cout << Blank(5) << "   ��ѡ����:";
}

void Exits(List* list,int* counter)
{
	std::cout << Blank(5) << "�Ƿ�ȷ���˳�\t\ty[Y]/n[N]" << std::endl << Blank(6) << "     ��ѡ��:";
	int c = Judge();
	if (c == 1)
	{
		if(*counter == 0)
		{
			delete list;
			_CrtDumpMemoryLeaks();//�ڴ�й©���溯��
			exit(0);
		}
		List* temp = list->next;
		while (c == 1)
		{
			delete list;
			if(temp == nullptr)
			{
				_CrtDumpMemoryLeaks();//�ڴ�й©���溯��
				exit(0);
			}
			list = temp;
			temp = temp->next;
			//�ڴ�й©���ܴ�����temp==nullptrû�н����жϣ�ϵͳ�������б���ǰ�����жϼ���
		}		
	}
	std::cout << (c == 0 ? "\t\t\t\t\t\t     ȡ���˳���" : "\t\t\t\t\t\t��Ч����ȡ���˳���") << std::endl;
}

void Addperson(List* list,int* counter)
{
	std::cout << Blank(4) << "    ---------------------------------------" << std::endl;
	std::cout << Blank(4) << "    1����Ϣͷ�����\t\t2����Ϣβ�����" << std::endl << Blank(6) << "    ��ѡ��:";
	char num[Max];
	std::cin >> num;
	if (num[0] != 49 && num[0] != 50)
	{
		std::cout << Blank(6) << "�������룡" << std::endl;
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
		std::cout << Blank(7) << "��ӳɹ���" << std::endl;
		return;
	}
	if (num[0] == 49)
	{
		/*�˴������Ҫע��,�ں����ڲ��ܸ���ָ�������ָ�����˵��ַ������������ں�����Ӿ��ǲ��ܸı��׵�ַλ��
		���򷵻غ�����������ԭ���ĵ�ַ,��ַʵ�ε�����*/
		List* temps = new List;
		temps->Data = list->Data;
		temp->next = list->next;
		list->Data = temp->Data;
		temp->Data = temps->Data;
		list->next = temp;
		Savefile(list);
		(*counter)++;
		delete temps;
		std::cout << Blank(7) << "��ӳɹ���" << std::endl;
	}
	else if (num[0] == 50)
	{
		List* temps = list;
		while (temps->next != nullptr)
			temps = temps->next;
		temps->next = temp;
		Savefile(list);
		(*counter)++;
		std::cout << Blank(7) << "��ӳɹ���" << std::endl;
	}
}

void Deletely(List* list, int* counter)
{
	std::cout << Blank(5) << "������ɾ�����:";
	int id;
	std::cin >> id;
	List* temp = list;
	List* temps = list;
	std::cout << Blank(4) << "      ---------------------------------------" << std::endl;
	std::cout << Blank(5) << "����\t\t���\t\t����" << std::endl;
	if (*counter == 0)
	{
		std::cout << std::endl << Blank(6) << "δ�ҵ�ƥ���ţ�" << std::endl;
		return;
	}
	while (temp->Data.Id != id)
	{
		temps = temp;
		temp = temp->next;
		if (temp == nullptr)
		{
			std::cout << std::endl << Blank(6) <<"δ�ҵ�ƥ���ţ�" << std::endl;
			return;
		}
	}
	std::cout << Blank(5) << std::left << std::setw(16) << temp->Data.Name << std::left << std::setw(16) << temp->Data.Id
		<< temp->Data.Wages << std::endl;
	std::cout << Blank(4) << "�Ƿ�ɾ������ƥ�����ݣ�\t\t\ty[Y]/n[N]" << std::endl << Blank(6) << "     ��ѡ��:";
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
		std::cout << Blank(6) << "ɾ���ɹ���" << std::endl;
		return;
	}
	std::cout << Blank(5) << (c == 0 ?  "��ȡ��ɾ����" : "��Ч������ȡ��ɾ����") << std::endl;
}

void Modify(List* list, int* counter)
{
	std::cout << Blank(5) << "�������޸ı��:";
	int id;
	std::cin >> id;
	List* temp = list;
	List* temps = temp;
	std::cout << Blank(4) << "      ---------------------------------------" << std::endl;
	std::cout << Blank(5) << "����\t\t���\t\t����" << std::endl;
	if(*counter == 0)
	{
		std::cout << std::endl << Blank(6) << "δ�ҵ�ƥ���ţ�" << std::endl;
		return;
	}
	while (temp->Data.Id != id)
	{
		temps = temp;
		temp = temp->next;
		if (temp == nullptr)
		{
			std::cout  << std::endl << Blank(6)<< "δ�ҵ�ƥ���ţ�" << std::endl;
			return;
		}
	}
	std::cout << Blank(5) << std::left << std::setw(16) << temp->Data.Name << std::left << std::setw(16) << temp->Data.Id
		<< temp->Data.Wages << std::endl;
	std::cout << Blank(4) << "�Ƿ��޸�ƥ�����ݣ�\t\t\ty[Y]/n[N]" << std::endl << Blank(6) << "     ��ѡ��:";
	int c = Judge();
	if (c == 1)
	{
		List* node = Add_list();
		Add_just(list, node, counter);
		temp->Data = node->Data;
		Savefile(list);
		delete node;
		std::cout << Blank(5) << "�޸ĳɹ���" << std::endl;
		return;
	}
	std::cout << Blank(5) << (c == 0 ? "��ȡ���޸ģ�" : "��Ч������ȡ���޸ģ�") << std::endl;
}

void View(List* list,int* counter)
{
	List* temp = list;
	std::cout << Blank(4) << "      ---------------------------------------" << std::endl;
	std::cout << Blank(5) << "����\t\t���\t\t����" << std::endl;
	if (*counter == 0)
	{
		std::cout << std::endl << Blank(6) << "    ��������" << std::endl;
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
	std::cout << Blank(4) << "1����������\t    2���������\t      3����������" << std::endl 
		<< std::endl << Blank(6) << "    ��ѡ��:";
	char num[Max];
	std::cin >> num;
	if (num[0] != 49 && num[0] != 50 && num[0] != 51)
	{
		std::cout << Blank(6) << "�������룡" << std::endl;
		return;
	}
	if (*counter == 0)
	{
		std::cout << Blank(6) << "�������ݣ�" << std::endl;
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
	std::cout << Blank(5) << "����:";
	std::cin >> temp->Data.Name;
	while(1)
	{
		std::cout << Blank(5) << "���:";
		std::cin >> temp->Data.Id;
		if (*counter == 0 || Determine(list, temp->Data.Id) == 0)
			break;
		else
		{
			std::cout << Blank(5) << "����ظ�!" << std::endl;
		}
	}
	std::cout << Blank(5) << "����:";
	std::cin >> temp->Data.Wages;
}
