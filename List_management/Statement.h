#pragma once
#include<iostream>
//#include<string>

#define Max 100

struct Message
{
	std::string Name;
	int Id;
	float Wages;
};

struct List
{
	Message Data;
	struct List* next;
};



typedef int (*Funcs)(List* list,int* counter);
typedef int (*Sortfunc)(List* list,List* temp);

List* Loadfile(int* counter);
void Savefile(List* list);


void Menu();
void Exits();
void Addperson(List* list,int* counter);
void Deletely(List* list, int* counter);
void Modify(List* list, int* counter);
void View(List* list, int* counter);
void Sort(List* list, int* counter);

int namesearch(List* list, List* temp);
int idsearch(List* list, List* temp);
int wagesearch(List* list, List* temp);


int Determine(List* list,int id);
int Judge();
std::string Blank(int num);
List* Add_list();
void Add_just(List* list,List* temp,int* counter);

