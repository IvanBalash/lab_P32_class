#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class MOSFET{
private:
	int id;//id
	int quantity;//����������
	float max_Uce;//max ���������� ����-�����
	float max_Ube;//max ���������� ������-�����
	float max_Ice;//max ��� ����-�����
	string name;//��������
	string type;//��� ������ P ��� N
public:
	MOSFET();//����������� �� ���������
	~MOSFET();//����������
	MOSFET(int id, int quantity, float max_Uce, float max_Ube, float max_Ice, string name, string type);//�����������
	//������
	void edit(int id, int quantity, float max_Uce, float max_Ube, float max_Ice, string name, string type);
	void edit_console(MOSFET* arr, int length);
	void edit_console();
	void print();
	void print_in_array(int num);
	string save_print();
	bool put(int quantity);
	bool take(int quantity);
	//������
	int get_id();
	int get_quantity();
	float get_max_Uce();
	float get_max_Ube();
	float get_max_Ice();
	string get_name();
	string get_type();
	//������
	bool set_id(int new_id);
	bool set_quantity(int new_quantity);
	bool set_max_Uce(float new_max_Uce);
	bool set_max_Ube(float new_max_Ube);
	bool set_max_Ice(float new_max_Ice);
	void set_name(string new_name);
	bool set_type(string new_type);
};																			
