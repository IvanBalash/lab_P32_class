#include <iostream>
#include <string>
#include <iomanip>
#include <regex>
#include <fstream>
#include "MOSFET.h"

using namespace std;

void data_write(MOSFET* data, int length) { // фунция вывода данных на экран

	cout << '|' << setw(7) << "number" << setw(2) << '|'
		<< setw(4) << "id" << setw(2) << '|'
		<< setw(8) << "name" << setw(5) << '|'
		<< setw(7) << "channle" << setw(1) << '|'
		<< setw(7) << "max Uce" << setw(1) << '|'
		<< setw(7) << "max Ube" << setw(1) << '|'
		<< setw(7) << "max Ice" << setw(1) << '|'
		<< setw(8) << "quantity" << setw(1) << '|'
		<< endl;
	cout << "=====================================================================" << endl;// делаем заголовок
	for (int i = 0; i < length; i++){ // цикл в котором выписываем все структуры по очереди
		data[i].print_in_array(i+1);
	}
	cout << endl;
}

bool read_file(string file_name, MOSFET** data, int* length) {
	ifstream fin; // содаем поток ввода
	fin.open(file_name); // отурывем файл
	if (!fin.is_open()) { // проверям получилось ли открыть файл
		return 0; // возвращаем 0 если открыть не получилось
	}
	delete[](*data);//отчищаем память 
	fin >> *length; // считываем длину масива с
	MOSFET* local_data = new MOSFET[*length]; // создаем масив структур нужного размера
	int new_id, new_quantity;
	float new_max_Uce, new_max_Ube, new_max_Ice;
	string new_name, new_type;
	for (size_t i = 0; i < *length; i++) { //присваеваем новому масиву значения из фаила
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
	fin.close();// закрываем файл
	*data = local_data;//присваеваем новое значения исходному масиву
	return 1;
}

void save_file(MOSFET* data, int length) {
	string file_name;//переменная имени файла
	ofstream fout;//создае поток вывода
	bool iname = 0;//флаг неверного имени
	bool is_saved = 0;//флаг успешного сохранения
	while (!is_saved) {
		system("cls");
		if (iname) {
			cout << "incorrect name, it should look like name.txt" << endl;//сообщение о неверном имени
		}
		cout << "input name of the file you want to save to: ";
		cin >> file_name;//просим ввести имя файла
		if (regex_match(file_name, regex("[a-zA-Z_][a-zA-Z0-9_]*\\.txt"))) {//проверяем коректность введеного имени
			fout.open(file_name);//открываем файл на вывод
			fout << length << endl;//записываем в файл длину масива
			for (size_t i = 0; i < length; i++) {//записываем все элементы в цикле
				fout << data[i].save_print();
			}
			fout.close();//закрываем файл вывода
			is_saved = 1;//ставим флаг успешного сохранения
			system("cls");//чистим экран
		}
		else {
			iname = 1;//ставим флаг неверного имени
		}
	}
}

void ADD(MOSFET** data, int length) {
	string add_cmd;
	bool icmd = 0;//флаг неверной команды
	bool aeid = 0;//флаг неуникальности id
	bool wc = 0;//флаг неверного значения типа канала
	bool ival = 0;//флаг некоректного значения
	bool id_added = 0;
	bool name_added = 0;
	bool type_added = 0;
	bool Uce_added = 0;
	bool Ube_added = 0;
	bool Ice_added = 0;
	bool quantity_added = 0;
	bool all_added = 0;//флаги введенных значений
	bool exit = 0; //флаг выхода
	MOSFET* old_data = *data;
	MOSFET* new_data = new MOSFET[length + 1];
	for (size_t i = 0; i < length; i++) {
		new_data[i] = old_data[i];
	}

	while (!exit) {//цикл работы в режиме редактирования
		system("cls");
		new_data[length].print();
		if (icmd) cout << "incorrect command" << endl;
		if (aeid) cout << "id alredy exist" << endl;
		if (wc) cout << "channle can be only P or N" << endl;
		if (ival) cout << "incorrect value" << endl;
		if (!all_added) {//выводим сообщения об ошибках
			cout << "input all parametrs" << endl;
		}
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tEXIT - return to main menu" << endl << endl;//выводим список команд
		cin >> add_cmd;//запрашиваем ввод команды
		icmd = 0;
		aeid = 0;
		wc = 0;
		ival = 0;//зануляем флаги после прошлой итерации
		if (add_cmd == "id") {
			int new_id;//переменная для нового значения
			cin >> new_id;//считываем новое значение
			if (new_id < 1) {//проверяем, чтобы id не был < 1
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				for (size_t i = 0; i < length; i++) {//цикл проверки уникальности id
					if (new_data[i].get_id() == new_id) {
						icmd = 1;
						aeid = 1;//выставляем флаги ошибок
					}
				}
				if (!icmd) {//если ошибок нет присваеваем новое значение
					new_data[length].set_id(new_id);
					id_added = 1;
				}
			}

		}

		else if (add_cmd == "name") {
			string new_name;//переменная для нового значения
			cin >> new_name;//считываем новое значение
			new_data[length].set_name(new_name);//присваеваем новое значение
			name_added = 1;
		}

		else if (add_cmd == "channle") {
			string new_channle;//переменная для нового значения
			cin >> new_channle;//считываем новое значение
			if (new_channle == "N" || new_channle == "P") {//проверям коректность введенного значения
				new_data[length].set_type(new_channle);//присваеваем новое значение
				type_added = 1;
			}
			else {
				icmd = 1;
				wc = 1;//выставляем флаги ошибок
			}

		}

		else if (add_cmd == "max_Uce") {
			float new_max_Uce;//переменная для нового значения
			cin >> new_max_Uce;//считываем новое значение
			if (new_max_Uce < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				new_data[length].set_max_Uce(new_max_Uce);//присваеваем новое значение
				Uce_added = 1;
			}

		}

		else if (add_cmd == "max_Ube") {
			float new_max_Ube;//переменная для нового значения
			cin >> new_max_Ube;//считываем новое значение
			if (new_max_Ube < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				new_data[length].set_max_Ube(new_max_Ube);//присваеваем новое значение
				Ube_added = 1;
			}
		}

		else if (add_cmd == "max_Ice") {
			float new_max_Ice;//переменная для нового значения
			cin >> new_max_Ice;//считываем новое значение
			if (new_max_Ice < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				new_data[length].set_max_Ice(new_max_Ice);//присваеваем новое значение
				Ice_added = 1;
			}
		}

		else if (add_cmd == "quantity") {
			float new_quantity;//переменная для нового значения
			cin >> new_quantity;//считываем новое значение
			if (new_quantity < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				new_data[length].set_quantity(new_quantity);//присваеваем новое значение
				quantity_added = 1;
			}
		}

		else if (add_cmd == "EXIT") {
			if (all_added) {//проверяем все ли значения введены
				exit = 1;
			}
			else {
				icmd = 1;
			}
		}

		else {

			icmd = 1;//выставляем флаг ошибки при неверной команде
		}

		if ((id_added && name_added && type_added && quantity_added
			&& Uce_added && Ube_added && Ice_added)) {//проверяем, что все элементы добавлены
			all_added = 1;//ставим флаг
		}
	}
	*data = new_data;
	delete[](old_data);
	system("cls");
}

void EDIT(MOSFET** data, int line, int length) {
	MOSFET* new_data = *data;//переменная для работы с масивом
	new_data[line].edit_console(new_data, length);
}

void DEL(MOSFET** data, int length, int line) {
	MOSFET* new_data = new MOSFET[length - 1];//создаем новый масив маеньшего размера
	MOSFET* old_data = *data;//копируем исхлдный масив в новую переменную
	int j = 0;//счетчик нового масива
	for (size_t i = 0; i < length; i++) {//проходим по старому масиву
		if (i != line) {//игнорируем удаленный элемент
			new_data[j] = old_data[i];//копируем остальные в новый масив
			j++;
		}
	}
	*data = new_data;//присваеваем новый масив исходному
	delete[](old_data);//удаляем старый масив
}
int main() {
	string in_file_name;//переменная для имени входного файла
	string out_file_name;//переменная для имени выходного файла
	string cmd = "READ";// создаем переменную для команд со значение по умолчанию READ
	int length = 0;//создаем переменную с длиной масива
	int line = 0; // переменная номера лини для взаимодействия
	bool icmd = 0;
	bool nl = 0;
	bool nq = 0;
	bool bq = 0;// флаг неверной команды
	bool is_saved = 0;//флаг успешного сохранения
	bool is_added = 0;//флаг успешного добавления
	MOSFET* data = new MOSFET[1];// создаем масив данных
	while (cmd != "STOP") {//основной цикл программы, который будет работать пока мы не введем команду STOP
		if (cmd == "READ") {// если введина команда READ четем файл
			cout << "input the file name: ";
			cin >> in_file_name;// просим ввести имя файла для чтения
			if (read_file(in_file_name, &data, &length)) {// читаем файл и проверям получилось ли его открыть
				cmd = "";//отчищаем переменную команд
				system("cls");//отчищаем экран
			}
			else {//если файл не получилось открыть выводим меню ошибки
				cout << "Could not open " << in_file_name << " :(" << endl;
				cout << "READ - try again" << endl;
				cout << "STOP - exit the console app" << endl;
				cin >> cmd;//просим ввести команду
				system("cls");//отчищаем экран
			}
		}
		else {
			data_write(data, length);// выводим данные масива
			cout << "commands:" << endl;
			cout << "\tREAD - read a new file" << endl;
			cout << "\tSAVE - save data to file" << endl;
			cout << "\tADD - add new record" << endl;
			cout << "\tPUT x y - put y number to x transistors" << endl;
			cout << "\tTAKE x y - take y number of x transistors" << endl;
			cout << "\tEDIT x - edit record number x" << endl;
			cout << "\tDEL x - delete record number x" << endl;
			cout << "\tSTOP - exit the console app" << endl << endl;// выводим список команд

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
			}//выводим сообщения об ошибках
			if (is_saved) {
				cout << "successfuly saved" << endl;//сообщение об успешном сохранении
			}
			if (is_added) {
				cout << "successfuly added" << endl;//сообщение об успешном сохранении
			}
			cout << "command: ";
			cin >> cmd;//просим ввести команду
			system("cls");//отчищаем экран
			icmd = 0;
			nl = 0;
			nq = 0;
			is_saved = 0;
			is_added = 0;
			bq = 0;//зануляем флаги после прошлой итерации

			if (cmd == "SAVE") {
				save_file(data, length);//вызываем функцию обработчик задачи
				is_saved = 1;//выставляем флаг успешного сохранения
			}

			else if (cmd == "ADD") {
				ADD(&data, length);
				length++;
				is_added = 1;
			}

			else if (cmd == "PUT") {
				int quantity;//переменная для значения y
				cin >> line;//считываем значение x
				if (line > length || line < 1) {//проверям коректность x
					icmd = 1;
					nl = 1;//выставляем флаги ошибок
				}
				else {
					line--;//дикриментируем line, чтобы проще работать с масивом
					cin >> quantity;//считываем значение y
					if (!data[line].put(quantity)) {//проверям коректность y и вызываем нужный метод
						icmd = 1;
						nq = 1;//выставляем флаги ошибок
					}
				}
			}

			else if (cmd == "TAKE") {
				int quantity;//переменная для значения y
				cin >> line;//считываем значение x
				if (line > length || line < 1) {//проверям коректность x
					icmd = 1;
					nl = 1;//выставляем флаги ошибок
				}
				else {
					line--;//дикриментируем line, чтобы проще работать с масивом
					cin >> quantity;//считываем значение y
					if (!data[line].take(quantity)) {//вызываем метод обработчик задачи, проверяя возвращаемое значение
						icmd = 1;
						nq = 1;
						bq = 1;//выставляем флаги ошибок, если функция вернула false
						
					}
				}
			}

			else if (cmd == "EDIT") {
				cin >> line;//считываем значение x
				if (line > length || line < 1) {//проверям коректность x
					icmd = 1;
					nl = 1;//выставляем флаги ошибок
				}
				else {
					line--;//дикриментируем line, чтобы проще работать с масивом
					EDIT(&data, line, length);//вызываем функцию обработчик задачи
				}
			}

			else if (cmd == "DEL") {
				cin >> line;//считываем значение x
				if (line > length || line < 1) {//проверям коректность x
					icmd = 1;
					nl = 1;//выставляем флаги ошибок
				}
				else {
					line--;//дикриментируем line, чтобы проще работать с масивом
					DEL(&data, length, line);//вызываем функцию обработчик задачи
					length--;//дикриментируем переменную длины масива
				}
			}

			else {
				icmd = 1;//выставляем флаг ошибки при неверной команде
			}
		}
	}
	delete[](data);//освобождаем память
	cout << "goodbay :)" << endl;//прощаемся с пользователем
	return 0;
}