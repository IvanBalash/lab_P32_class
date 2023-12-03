#include "MOSFET.h"

MOSFET::MOSFET(){
	this->id = -1;
	this->quantity = -1;
	this->max_Uce = -1;
	this->max_Ube = -1;
	this->max_Ice = -1;
	this->name = "";
	this->type = "";
}

MOSFET::~MOSFET(){

}

MOSFET::MOSFET(int id, int quantity, float max_Uce, float max_Ube, float max_Ice, string name, string type){
	this->id = id;
	this->quantity = quantity;
	this->max_Uce = max_Uce;
	this->max_Ube = max_Ube;
	this->max_Ice = max_Ice;
	this->name = name;
	this->type = type;
}

void MOSFET::edit(int id, int quantity, float max_Uce, float max_Ube, float max_Ice, string name, string type){
	this->id = id;
	this->quantity = quantity;
	this->max_Uce = max_Uce;
	this->max_Ube = max_Ube;
	this->max_Ice = max_Ice;
	this->name = name;
	this->type = type;
}

void MOSFET::edit_console(MOSFET* arr, int length) {
	string edit_cmd;//���������� ������
	bool icmd = 0;//���� �������� �������
	bool aeid = 0;//���� �������������� id
	bool wc = 0;//���� ��������� �������� ���� ������
	bool ival = 0;//���� ������������ ��������
	while (edit_cmd != "EXIT") {//���� ������ � ������ ��������������
		system("cls");
		this->print();
		if (icmd) cout << "incorrect command" << endl;
		if (aeid) cout << "id alredy exist" << endl;
		if (wc) cout << "channle can be only P or N" << endl;
		if (ival) cout << "incorrect value" << endl;//������� ��������� �� �������
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tEXIT - return to main menu" << endl << endl;//������� ������ ������
		cin >> edit_cmd;//����������� ���� �������
		icmd = 0;
		aeid = 0;
		wc = 0;
		ival = 0;//�������� ����� ����� ������� ��������
		if (edit_cmd == "id") {
			int new_id;//���������� ��� ������ ��������
			cin >> new_id;//��������� ����� ��������
			if (new_id < 1) {//���������, ����� id �� ��� < 1
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				for (size_t i = 0; i < length; i++) {//���� �������� ������������ id
					if (arr[i].id == new_id) {
						icmd = 1;
						aeid = 1;//���������� ����� ������
					}
				}
			}
			if (!icmd) {//���� ������ ��� ����������� ����� ��������
				this->id = new_id;
			}
		
		}

		else if (edit_cmd == "name") {
			string new_name;//���������� ��� ������ ��������
			cin >> new_name;//��������� ����� ��������
			this->name = new_name;//����������� ����� ��������
		}

		else if (edit_cmd == "channle") {
			string new_channle;//���������� ��� ������ ��������
			cin >> new_channle;//��������� ����� ��������
			if (new_channle == "N" || new_channle == "P") {//�������� ����������� ���������� ��������
				this->type = new_channle;//����������� ����� ��������
			}
			else {
				icmd = 1;
				wc = 1;//���������� ����� ������
			}

		}

		else if (edit_cmd == "max_Uce") {
			float new_max_Uce;//���������� ��� ������ ��������
			cin >> new_max_Uce;//��������� ����� ��������
			if (new_max_Uce < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				this->max_Uce = new_max_Uce;//����������� ����� ��������
			}

		}

		else if (edit_cmd == "max_Ube") {
			float new_max_Ube;//���������� ��� ������ ��������
			cin >> new_max_Ube;//��������� ����� ��������
			if (new_max_Ube < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				this->max_Ube = new_max_Ube;//����������� ����� ��������
			}
		}

		else if (edit_cmd == "max_Ice") {
			float new_max_Ice;//���������� ��� ������ ��������
			cin >> new_max_Ice;//��������� ����� ��������
			if (new_max_Ice < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				this->max_Ice = new_max_Ice;//����������� ����� ��������
			}
		}

		else if (edit_cmd == "quantity") {
			float new_quantity;//���������� ��� ������ ��������
			cin >> new_quantity;//��������� ����� ��������
			if (new_quantity < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				this->quantity = new_quantity;//����������� ����� ��������
			}
		}

		else {
			icmd = 1;//���������� ���� ������ ��� �������� �������
		}
	}
	system("cls");
}

void MOSFET::edit_console(){
	string edit_cmd;//���������� ������
	bool icmd = 0;//���� �������� �������
	bool wc = 0;//���� ��������� �������� ���� ������
	bool ival = 0;//���� ������������ ��������
	while (edit_cmd != "EXIT") {//���� ������ � ������ ��������������
		system("cls");
		this->print();
		if (icmd) cout << "incorrect command" << endl;
		if (wc) cout << "channle can be only P or N" << endl;
		if (ival) cout << "incorrect value" << endl;//������� ��������� �� �������
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tEXIT - return to main menu" << endl << endl;//������� ������ ������
		cin >> edit_cmd;//����������� ���� �������
		icmd = 0;
		aeid = 0;
		wc = 0;
		ival = 0;//�������� ����� ����� ������� ��������
		if (edit_cmd == "id") {
			int new_id;//���������� ��� ������ ��������
			cin >> new_id;//��������� ����� ��������
			if (new_id < 1) {//���������, ����� id �� ��� < 1
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			if (!icmd) {//���� ������ ��� ����������� ����� ��������
				this->id = new_id;
			}

		}

		else if (edit_cmd == "name") {
			string new_name;//���������� ��� ������ ��������
			cin >> new_name;//��������� ����� ��������
			this->name = new_name;//����������� ����� ��������
		}

		else if (edit_cmd == "channle") {
			string new_channle;//���������� ��� ������ ��������
			cin >> new_channle;//��������� ����� ��������
			if (new_channle == "N" || new_channle == "P") {//�������� ����������� ���������� ��������
				this->type = new_channle;//����������� ����� ��������
			}
			else {
				icmd = 1;
				wc = 1;//���������� ����� ������
			}

		}

		else if (edit_cmd == "max_Uce") {
			float new_max_Uce;//���������� ��� ������ ��������
			cin >> new_max_Uce;//��������� ����� ��������
			if (new_max_Uce < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				this->max_Uce = new_max_Uce;//����������� ����� ��������
			}

		}

		else if (edit_cmd == "max_Ube") {
			float new_max_Ube;//���������� ��� ������ ��������
			cin >> new_max_Ube;//��������� ����� ��������
			if (new_max_Ube < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				this->max_Ube = new_max_Ube;//����������� ����� ��������
			}
		}

		else if (edit_cmd == "max_Ice") {
			float new_max_Ice;//���������� ��� ������ ��������
			cin >> new_max_Ice;//��������� ����� ��������
			if (new_max_Ice < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				this->max_Ice = new_max_Ice;//����������� ����� ��������
			}
		}

		else if (edit_cmd == "quantity") {
			float new_quantity;//���������� ��� ������ ��������
			cin >> new_quantity;//��������� ����� ��������
			if (new_quantity < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				this->quantity = new_quantity;//����������� ����� ��������
			}
		}

		else {
			icmd = 1;//���������� ���� ������ ��� �������� �������
		}
	}
	system("cls");
}

void MOSFET::print(){
	cout << setw(10) << "id:" << "| " << this->id << endl
		<< setw(10) << "name:" << "| " << this->name << endl
		<< setw(10) << "channle:" << "| " << this->type << endl
		<< setw(10) << "max_Uce:" << "| " << this->max_Uce << endl
		<< setw(10) << "max_Ube:" << "| " << this->max_Ube << endl
		<< setw(10) << "max_Ice:" << "| " << this->max_Ice << endl
		<< setw(10) << "quantity:" << "| " << this->quantity << endl
		<< endl;//������� ��� ���������� �� ���������� ��������
}

void MOSFET::print_in_array(int num){
	cout << '|' << setw(8) << num << '|'
		<< setw(5) << this->id << '|'
		<< setw(12)<< this->name << '|'
		<< setw(7) << this->type << '|'
		<< setw(7) << this->max_Uce << '|'
		<< setw(7) << this->max_Ube << '|'
		<< setw(7) << this->max_Ice << '|'
		<< setw(8) << this->quantity << '|'
		<< endl;
	cout << "---------------------------------------------------------------------" << endl;//������� ��� ���������� �� ���������� ��������
}

string MOSFET::save_print(){
	string result = "";
	result += to_string(this->id) + " " + 
			  this->name + " " +
			  this->type + " " +
			  to_string(this->max_Uce) + " " +
			  to_string(this->max_Ube) + " " +
			  to_string(this->max_Ice) + " " +
			  to_string(this->quantity) + "\n";//��������� ������ � ������ �������
	return result;//���������� ������
}

bool MOSFET::put(int quantity){
	if (quantity > 0) {//�������� ����������� quantity
		this->quantity += quantity;//�������� ��������
		return 1;//���������� true ���� ��� ��������
	}
	return 0;//����� ���������� false
}

bool MOSFET::take(int quantity){
	if ((quantity > 0) && (quantity <= this->quantity)) {//�������� ����������� quantity
		this->quantity -= quantity;//�������� ��������
		return 1;//���������� true ���� ��� ��������
	}
	return 0;//����� ���������� false
}

int MOSFET::get_id(){
	return this->id;
}

int MOSFET::get_quantity(){
	return this->quantity;
}

float MOSFET::get_max_Uce(){
	return this->max_Uce;
}

float MOSFET::get_max_Ube(){
	return this->max_Ube;
}

float MOSFET::get_max_Ice(){
	return this->max_Ice;
}

string MOSFET::get_name(){
	return this->name;
}

string MOSFET::get_type(){
	return this->type;
}

bool MOSFET::set_id(int new_id){
	if (new_id < 1) {//�������� ����������� ��������
		return 0;//���������� false ���� �������� �� ��������
	}
	this->id = new_id;//����������� ��������
	return 1;//���������� true ���� ��� ��������
}

bool MOSFET::set_quantity(int new_quantity){
	if (new_quantity < 0) {//�������� ����������� ��������
		return 0;//���������� false ���� �������� �� ��������
	}
	this->quantity = new_quantity;//����������� ��������
	return 1;//���������� true ���� ��� ��������
}

bool MOSFET::set_max_Uce(float new_max_Uce){
	if (new_max_Uce < 0) {//�������� ����������� ��������
		return 0;//���������� false ���� �������� �� ��������
	}
	this->max_Uce = new_max_Uce;//����������� ��������
	return 1;//���������� true ���� ��� ��������
}

bool MOSFET::set_max_Ube(float new_max_Ube){
	if (new_max_Ube < 0) {//�������� ����������� ��������
		return 0;//���������� false ���� �������� �� ��������
	}
	this->max_Ube = new_max_Ube;//����������� ��������
	return 1;//���������� true ���� ��� ��������
}

bool MOSFET::set_max_Ice(float new_max_Ice){
	if (new_max_Ice < 0) {//�������� ����������� ��������
		return 0;//���������� false ���� �������� �� ��������
	}
	this->max_Ice = new_max_Ice;//����������� ��������
	return 1;//���������� true ���� ��� ��������
}

void MOSFET::set_name(string new_name){
	this->name = new_name;//����������� ��������
}

bool MOSFET::set_type(string new_type){
	if ((new_type == "P") || (new_type == "N")) {//�������� ����������� ��������
		this->type = new_type;//����������� ��������
		return 1;//���������� true ���� ��� ��������
	}
	return 0;//���������� false ���� �������� �� ��������
}
