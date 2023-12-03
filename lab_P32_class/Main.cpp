#include <iostream>
#include <string>
#include <iomanip>
#include <regex>
#include <fstream>
#include "MOSFET.h"

using namespace std;

void data_write(MOSFET* data, int length) { // ������ ������ ������ �� �����

	cout << '|' << setw(7) << "number" << setw(2) << '|'
		<< setw(4) << "id" << setw(2) << '|'
		<< setw(8) << "name" << setw(5) << '|'
		<< setw(7) << "channle" << setw(1) << '|'
		<< setw(7) << "max Uce" << setw(1) << '|'
		<< setw(7) << "max Ube" << setw(1) << '|'
		<< setw(7) << "max Ice" << setw(1) << '|'
		<< setw(8) << "quantity" << setw(1) << '|'
		<< endl;
	cout << "=====================================================================" << endl;// ������ ���������
	for (int i = 0; i < length; i++){ // ���� � ������� ���������� ��� ��������� �� �������
		data[i].print_in_array(i+1);
	}
	cout << endl;
}

bool read_file(string file_name, MOSFET** data, int* length) {
	ifstream fin; // ������ ����� �����
	fin.open(file_name); // �������� ����
	if (!fin.is_open()) { // �������� ���������� �� ������� ����
		return 0; // ���������� 0 ���� ������� �� ����������
	}
	delete[](*data);//�������� ������ 
	fin >> *length; // ��������� ����� ������ �
	MOSFET* local_data = new MOSFET[*length]; // ������� ����� �������� ������� �������
	int new_id, new_quantity;
	float new_max_Uce, new_max_Ube, new_max_Ice;
	string new_name, new_type;
	for (size_t i = 0; i < *length; i++) { //����������� ������ ������ �������� �� �����
		fin >> new_id;
		fin >> new_name;
		fin >> new_type;
		fin >> new_max_Uce;
		fin >> new_max_Ube;
		fin >> new_max_Ice;
		fin >> new_quantity;
		local_data[i].set_id(new_id);
		local_data[i].set_name(new_name);
		local_data[i].set_type(new_type);
		local_data[i].set_max_Uce(new_max_Uce);
		local_data[i].set_max_Ube(new_max_Ube);
		local_data[i].set_max_Ice(new_max_Ice);
		local_data[i].set_quantity(new_quantity);
	}
	fin.close();// ��������� ����
	*data = local_data;//����������� ����� �������� ��������� ������
	return 1;
}

void save_file(MOSFET* data, int length) {
	string file_name;//���������� ����� �����
	ofstream fout;//������ ����� ������
	bool iname = 0;//���� ��������� �����
	bool is_saved = 0;//���� ��������� ����������
	while (!is_saved) {
		system("cls");
		if (iname) {
			cout << "incorrect name, it should look like name.txt" << endl;//��������� � �������� �����
		}
		cout << "input name of the file you want to save to: ";
		cin >> file_name;//������ ������ ��� �����
		if (regex_match(file_name, regex("[a-zA-Z_][a-zA-Z0-9_]*\\.txt"))) {//��������� ����������� ��������� �����
			fout.open(file_name);//��������� ���� �� �����
			fout << length << endl;//���������� � ���� ����� ������
			for (size_t i = 0; i < length; i++) {//���������� ��� �������� � �����
				fout << data[i].save_print();
			}
			fout.close();//��������� ���� ������
			is_saved = 1;//������ ���� ��������� ����������
			system("cls");//������ �����
		}
		else {
			iname = 1;//������ ���� ��������� �����
		}
	}
}

void ADD(MOSFET** data, int length) {
	string add_cmd;
	bool icmd = 0;//���� �������� �������
	bool aeid = 0;//���� �������������� id
	bool wc = 0;//���� ��������� �������� ���� ������
	bool ival = 0;//���� ������������ ��������
	bool id_added = 0;
	bool name_added = 0;
	bool type_added = 0;
	bool Uce_added = 0;
	bool Ube_added = 0;
	bool Ice_added = 0;
	bool quantity_added = 0;
	bool all_added = 0;//����� ��������� ��������
	bool exit = 0; //���� ������
	MOSFET* old_data = *data;
	MOSFET* new_data = new MOSFET[length + 1];
	for (size_t i = 0; i < length; i++) {
		new_data[i] = old_data[i];
	}

	while (!exit) {//���� ������ � ������ ��������������
		system("cls");
		new_data[length].print();
		if (icmd) cout << "incorrect command" << endl;
		if (aeid) cout << "id alredy exist" << endl;
		if (wc) cout << "channle can be only P or N" << endl;
		if (ival) cout << "incorrect value" << endl;
		if (!all_added) {//������� ��������� �� �������
			cout << "input all parametrs" << endl;
		}
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tEXIT - return to main menu" << endl << endl;//������� ������ ������
		cin >> add_cmd;//����������� ���� �������
		icmd = 0;
		aeid = 0;
		wc = 0;
		ival = 0;//�������� ����� ����� ������� ��������
		if (add_cmd == "id") {
			int new_id;//���������� ��� ������ ��������
			cin >> new_id;//��������� ����� ��������
			if (new_id < 1) {//���������, ����� id �� ��� < 1
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				for (size_t i = 0; i < length; i++) {//���� �������� ������������ id
					if (new_data[i].get_id() == new_id) {
						icmd = 1;
						aeid = 1;//���������� ����� ������
					}
				}
				if (!icmd) {//���� ������ ��� ����������� ����� ��������
					new_data[length].set_id(new_id);
					id_added = 1;
				}
			}

		}

		else if (add_cmd == "name") {
			string new_name;//���������� ��� ������ ��������
			cin >> new_name;//��������� ����� ��������
			new_data[length].set_name(new_name);//����������� ����� ��������
			name_added = 1;
		}

		else if (add_cmd == "channle") {
			string new_channle;//���������� ��� ������ ��������
			cin >> new_channle;//��������� ����� ��������
			if (new_channle == "N" || new_channle == "P") {//�������� ����������� ���������� ��������
				new_data[length].set_type(new_channle);//����������� ����� ��������
				type_added = 1;
			}
			else {
				icmd = 1;
				wc = 1;//���������� ����� ������
			}

		}

		else if (add_cmd == "max_Uce") {
			float new_max_Uce;//���������� ��� ������ ��������
			cin >> new_max_Uce;//��������� ����� ��������
			if (new_max_Uce < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				new_data[length].set_max_Uce(new_max_Uce);//����������� ����� ��������
				Uce_added = 1;
			}

		}

		else if (add_cmd == "max_Ube") {
			float new_max_Ube;//���������� ��� ������ ��������
			cin >> new_max_Ube;//��������� ����� ��������
			if (new_max_Ube < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				new_data[length].set_max_Ube(new_max_Ube);//����������� ����� ��������
				Ube_added = 1;
			}
		}

		else if (add_cmd == "max_Ice") {
			float new_max_Ice;//���������� ��� ������ ��������
			cin >> new_max_Ice;//��������� ����� ��������
			if (new_max_Ice < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				new_data[length].set_max_Ice(new_max_Ice);//����������� ����� ��������
				Ice_added = 1;
			}
		}

		else if (add_cmd == "quantity") {
			float new_quantity;//���������� ��� ������ ��������
			cin >> new_quantity;//��������� ����� ��������
			if (new_quantity < 0) {//�������� ����������� ���������� ��������
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			else {
				new_data[length].set_quantity(new_quantity);//����������� ����� ��������
				quantity_added = 1;
			}
		}

		else if (add_cmd == "EXIT") {
			if (all_added) {//��������� ��� �� �������� �������
				exit = 1;
			}
			else {
				icmd = 1;
			}
		}

		else {

			icmd = 1;//���������� ���� ������ ��� �������� �������
		}

		if ((id_added && name_added && type_added && quantity_added
			&& Uce_added && Ube_added && Ice_added)) {//���������, ��� ��� �������� ���������
			all_added = 1;//������ ����
		}
	}
	*data = new_data;
	delete[](old_data);
	system("cls");
}

void EDIT(MOSFET** data, int line, int length) {
	MOSFET* new_data = *data;//���������� ��� ������ � �������
	new_data[line].edit_console(new_data, length);
}

void DEL(MOSFET** data, int length, int line) {
	MOSFET* new_data = new MOSFET[length - 1];//������� ����� ����� ��������� �������
	MOSFET* old_data = *data;//�������� �������� ����� � ����� ����������
	int j = 0;//������� ������ ������
	for (size_t i = 0; i < length; i++) {//�������� �� ������� ������
		if (i != line) {//���������� ��������� �������
			new_data[j] = old_data[i];//�������� ��������� � ����� �����
			j++;
		}
	}
	*data = new_data;//����������� ����� ����� ���������
	delete[](old_data);//������� ������ �����
}
int main() {
	string in_file_name;//���������� ��� ����� �������� �����
	string out_file_name;//���������� ��� ����� ��������� �����
	string cmd = "READ";// ������� ���������� ��� ������ �� �������� �� ��������� READ
	int length = 0;//������� ���������� � ������ ������
	int line = 0; // ���������� ������ ���� ��� ��������������
	bool icmd = 0;
	bool nl = 0;
	bool nq = 0;
	bool bq = 0;// ���� �������� �������
	bool is_saved = 0;//���� ��������� ����������
	bool is_added = 0;//���� ��������� ����������
	MOSFET* data = new MOSFET[1];// ������� ����� ������
	while (cmd != "STOP") {//�������� ���� ���������, ������� ����� �������� ���� �� �� ������ ������� STOP
		if (cmd == "READ") {// ���� ������� ������� READ ����� ����
			cout << "input the file name: ";
			cin >> in_file_name;// ������ ������ ��� ����� ��� ������
			if (read_file(in_file_name, &data, &length)) {// ������ ���� � �������� ���������� �� ��� �������
				cmd = "";//�������� ���������� ������
				system("cls");//�������� �����
			}
			else {//���� ���� �� ���������� ������� ������� ���� ������
				cout << "Could not open " << in_file_name << " :(" << endl;
				cout << "READ - try again" << endl;
				cout << "STOP - exit the console app" << endl;
				cin >> cmd;//������ ������ �������
				system("cls");//�������� �����
			}
		}
		else {
			data_write(data, length);// ������� ������ ������
			cout << "commands:" << endl;
			cout << "\tREAD - read a new file" << endl;
			cout << "\tSAVE - save data to file" << endl;
			cout << "\tADD - add new record" << endl;
			cout << "\tPUT x y - put y number to x transistors" << endl;
			cout << "\tTAKE x y - take y number of x transistors" << endl;
			cout << "\tEDIT x - edit record number x" << endl;
			cout << "\tDEL x - delete record number x" << endl;
			cout << "\tSTOP - exit the console app" << endl << endl;// ������� ������ ������

			if (icmd) {
				cout << "incorrect command" << endl;
			}
			if (nl) {
				cout << "there is no such number of record" << endl;
			}
			if (nq) {
				cout << "number of transistors can not be 0 or less" << endl;
			}
			if (bq) {
				cout << "there is not enough transistors" << endl;
			}//������� ��������� �� �������
			if (is_saved) {
				cout << "successfuly saved" << endl;//��������� �� �������� ����������
			}
			if (is_added) {
				cout << "successfuly added" << endl;//��������� �� �������� ����������
			}
			cout << "command: ";
			cin >> cmd;//������ ������ �������
			system("cls");//�������� �����
			icmd = 0;
			nl = 0;
			nq = 0;
			is_saved = 0;
			is_added = 0;
			bq = 0;//�������� ����� ����� ������� ��������

			if (cmd == "SAVE") {
				save_file(data, length);//�������� ������� ���������� ������
				is_saved = 1;//���������� ���� ��������� ����������
			}

			else if (cmd == "ADD") {
				ADD(&data, length);
				length++;
				is_added = 1;
			}

			else if (cmd == "PUT") {
				int quantity;//���������� ��� �������� y
				cin >> line;//��������� �������� x
				if (line > length || line < 1) {//�������� ����������� x
					icmd = 1;
					nl = 1;//���������� ����� ������
				}
				else {
					line--;//�������������� line, ����� ����� �������� � �������
					cin >> quantity;//��������� �������� y
					if (!data[line].put(quantity)) {//�������� ����������� y � �������� ������ �����
						icmd = 1;
						nq = 1;//���������� ����� ������
					}
				}
			}

			else if (cmd == "TAKE") {
				int quantity;//���������� ��� �������� y
				cin >> line;//��������� �������� x
				if (line > length || line < 1) {//�������� ����������� x
					icmd = 1;
					nl = 1;//���������� ����� ������
				}
				else {
					line--;//�������������� line, ����� ����� �������� � �������
					cin >> quantity;//��������� �������� y
					if (!data[line].take(quantity)) {//�������� ����� ���������� ������, �������� ������������ ��������
						icmd = 1;
						nq = 1;
						bq = 1;//���������� ����� ������, ���� ������� ������� false
						
					}
				}
			}

			else if (cmd == "EDIT") {
				cin >> line;//��������� �������� x
				if (line > length || line < 1) {//�������� ����������� x
					icmd = 1;
					nl = 1;//���������� ����� ������
				}
				else {
					line--;//�������������� line, ����� ����� �������� � �������
					EDIT(&data, line, length);//�������� ������� ���������� ������
				}
			}

			else if (cmd == "DEL") {
				cin >> line;//��������� �������� x
				if (line > length || line < 1) {//�������� ����������� x
					icmd = 1;
					nl = 1;//���������� ����� ������
				}
				else {
					line--;//�������������� line, ����� ����� �������� � �������
					DEL(&data, length, line);//�������� ������� ���������� ������
					length--;//�������������� ���������� ����� ������
				}
			}

			else {
				icmd = 1;//���������� ���� ������ ��� �������� �������
			}
		}
	}
	delete[](data);//����������� ������
	cout << "goodbay :)" << endl;//��������� � �������������
	return 0;
}