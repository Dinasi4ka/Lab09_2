// Lab09_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Specialnist { KN, IT, MATH, PHYSIC, WORK };
enum Curs { FIRST, SECOND, THIRD, FOUR };
string cursStr[] = { "I", "II", "III", "IV" };
string specialnistStr[] = { "���� �����", "�����������", "��� �� ��", "Գ� �� ������", "���� ����" };

struct Student
{
	string prizv;
	Curs curs;
	Specialnist specialnist;
	struct
	{
		int physic;
		int math;
		int inform;
	};

};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const Curs curs, const int specialnist, const string prizv);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "������ ������� �������� N: "; cin >> N;

	Student* p = new Student[N];
	int ispecurs;
	Specialnist specialnist1{};
	Curs curs;
	string prizv;
	int specialnist;
	int found;
	char filename[100]{};
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl;
		cout << " [4] - ������� ����� �������� �� ��������, ������ �� ������� �������" << endl;
		cout << " [5] - �������� ������������� �� ���� �����" << endl;

		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:

			cout << "������ ����� ������:" << endl;
			cout << " �������: "; getline(cin, prizv);
			cout << endl;
			cout << "  ���� (0 - I, 1 - II, 2 - III, 3 - IV):";
			cin >> ispecurs;
			curs = (Curs)ispecurs;
			cin.get();
			cin.sync();
			cout<< " ������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
			cin >> specialnist;
			if ((found = BinSearch(p, N, curs, specialnist1, prizv)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int specialnist;
	int curs;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get(); 
		cin.sync(); 

		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ���� (0 - I, 1 - II, 2 - III, 3 - IV): ";
		cin >> curs;
		cout << " ������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
		cin >> specialnist;
		cout << " ������ � ������ : "; cin >> p[i].physic;
		cout << " ������ � ���������� : "; cin >> p[i].math;
		cout << " ������ � ����������� : "; cin >> p[i].inform;
		p[i].specialnist = (Specialnist)specialnist;
		p[i].curs = (Curs)curs;
	}
}
void Print(Student* p, const int N)
{
	cout << "==========================================================================================================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | ������ � ������ | ������ � ���������� | ������ � ������������� | ������ � ��������� ������ | ������ � ��������� |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << i + 1;
		cout << "| " << setw(9) << p[i].prizv;
		cout << "| " << setw(5) << cursStr[p[i].curs];
		cout << "| " << setw(14) << specialnistStr[p[i].specialnist];
		cout << "| " << setw(16) << p[i].physic;
		cout << "| " << setw(20) << p[i].math;
		cout << "| " << setw(21) << p[i].inform << "|";
		cout << endl;
	}
	cout << "==========================================================================================================================================================="
		<< endl;
	cout << endl;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) 
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].curs < p[i1 + 1].curs)
				||
				(p[i1].curs == p[i1 + 1].curs &&
					p[i1].specialnist < p[i1 + 1].specialnist)
				|| (p[i1].curs == p[i1 + 1].curs &&
					p[i1].specialnist == p[i1 + 1].specialnist
					&& p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const Curs curs, const int specialnist, const string prizv)
{ 
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].curs == curs && 
			p[m].specialnist == specialnist)
			return m;
		if ((p[m].curs < curs)
			||
			(p[m].curs == curs &&
				p[m].specialnist < specialnist)
			||
			(p[m].curs == curs &&
				p[m].specialnist == specialnist) &&
			p[m].prizv < prizv)
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; 
	for (int i = 0; i < N; i++)
		I[i] = i; 
	int i, j, value; 
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 &&
			((p[I[j]].curs < p[value].curs)
				||
				(p[I[j]].curs == p[value].curs &&
					p[I[j]].specialnist < p[value].specialnist)
				|| (p[I[j]].curs == p[value].curs &&
					p[I[j]].specialnist == p[value].specialnist &&
					p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	
	cout << "==========================================================================================================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | ������ � ������ | ������ � ���������� | ������ � ������������� | ������ � ��������� ������ | ������ � ��������� |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << i + 1;
		cout << "| " << setw(9) << p[I[i]].prizv;
		cout << "| " << setw(5) << cursStr[p[I[i]].curs];
		cout << "| " << setw(14) << specialnistStr[p[I[i]].specialnist];
		cout << "| " << setw(16) << p[I[i]].physic;
		cout << "| " << setw(20) << p[I[i]].math;
		cout << "| " << setw(21) << p[I[i]].inform << "|";
		cout << endl;
	}
	cout << "===========================================================================================================================================================";

	cout << endl;
}





