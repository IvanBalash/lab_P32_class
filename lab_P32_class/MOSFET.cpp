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
	string edit_cmd;//переменная команд
	bool icmd = 0;//флаг неверной команды
	bool aeid = 0;//флаг неуникальности id
	bool wc = 0;//флаг неверного значения типа канала
	bool ival = 0;//флаг некоректного значения
	while (edit_cmd != "EXIT") {//цикл работы в режиме редактирования
		system("cls");
		this->print();
		if (icmd) cout << "incorrect command" << endl;
		if (aeid) cout << "id alredy exist" << endl;
		if (wc) cout << "channle can be only P or N" << endl;
		if (ival) cout << "incorrect value" << endl;//выводим сообщения об ошибках
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tEXIT - return to main menu" << endl << endl;//выводим список команд
		cin >> edit_cmd;//запрашиваем ввод команды
		icmd = 0;
		aeid = 0;
		wc = 0;
		ival = 0;//зануляем флаги после прошлой итерации
		if (edit_cmd == "id") {
			int new_id;//переменная для нового значения
			cin >> new_id;//считываем новое значение
			if (new_id < 1) {//проверяем, чтобы id не был < 1
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				for (size_t i = 0; i < length; i++) {//цикл проверки уникальности id
					if (arr[i].id == new_id) {
						icmd = 1;
						aeid = 1;//выставляем флаги ошибок
					}
				}
			}
			if (!icmd) {//если ошибок нет присваеваем новое значение
				this->id = new_id;
			}
		
		}

		else if (edit_cmd == "name") {
			string new_name;//переменная для нового значения
			cin >> new_name;//считываем новое значение
			this->name = new_name;//присваеваем новое значение
		}

		else if (edit_cmd == "channle") {
			string new_channle;//переменная для нового значения
			cin >> new_channle;//считываем новое значение
			if (new_channle == "N" || new_channle == "P") {//проверям коректность введенного значения
				this->type = new_channle;//присваеваем новое значение
			}
			else {
				icmd = 1;
				wc = 1;//выставляем флаги ошибок
			}

		}

		else if (edit_cmd == "max_Uce") {
			float new_max_Uce;//переменная для нового значения
			cin >> new_max_Uce;//считываем новое значение
			if (new_max_Uce < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				this->max_Uce = new_max_Uce;//присваеваем новое значение
			}

		}

		else if (edit_cmd == "max_Ube") {
			float new_max_Ube;//переменная для нового значения
			cin >> new_max_Ube;//считываем новое значение
			if (new_max_Ube < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				this->max_Ube = new_max_Ube;//присваеваем новое значение
			}
		}

		else if (edit_cmd == "max_Ice") {
			float new_max_Ice;//переменная для нового значения
			cin >> new_max_Ice;//считываем новое значение
			if (new_max_Ice < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				this->max_Ice = new_max_Ice;//присваеваем новое значение
			}
		}

		else if (edit_cmd == "quantity") {
			float new_quantity;//переменная для нового значения
			cin >> new_quantity;//считываем новое значение
			if (new_quantity < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				this->quantity = new_quantity;//присваеваем новое значение
			}
		}

		else {
			icmd = 1;//выставляем флаг ошибки при неверной команде
		}
	}
	system("cls");
}

void MOSFET::edit_console(){
	string edit_cmd;//переменная команд
	bool icmd = 0;//флаг неверной команды
	bool wc = 0;//флаг неверного значения типа канала
	bool ival = 0;//флаг некоректного значения
	while (edit_cmd != "EXIT") {//цикл работы в режиме редактирования
		system("cls");
		this->print();
		if (icmd) cout << "incorrect command" << endl;
		if (wc) cout << "channle can be only P or N" << endl;
		if (ival) cout << "incorrect value" << endl;//выводим сообщения об ошибках
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tEXIT - return to main menu" << endl << endl;//выводим список команд
		cin >> edit_cmd;//запрашиваем ввод команды
		icmd = 0;
		aeid = 0;
		wc = 0;
		ival = 0;//зануляем флаги после прошлой итерации
		if (edit_cmd == "id") {
			int new_id;//переменная для нового значения
			cin >> new_id;//считываем новое значение
			if (new_id < 1) {//проверяем, чтобы id не был < 1
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			if (!icmd) {//если ошибок нет присваеваем новое значение
				this->id = new_id;
			}

		}

		else if (edit_cmd == "name") {
			string new_name;//переменная для нового значения
			cin >> new_name;//считываем новое значение
			this->name = new_name;//присваеваем новое значение
		}

		else if (edit_cmd == "channle") {
			string new_channle;//переменная для нового значения
			cin >> new_channle;//считываем новое значение
			if (new_channle == "N" || new_channle == "P") {//проверям коректность введенного значения
				this->type = new_channle;//присваеваем новое значение
			}
			else {
				icmd = 1;
				wc = 1;//выставляем флаги ошибок
			}

		}

		else if (edit_cmd == "max_Uce") {
			float new_max_Uce;//переменная для нового значения
			cin >> new_max_Uce;//считываем новое значение
			if (new_max_Uce < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				this->max_Uce = new_max_Uce;//присваеваем новое значение
			}

		}

		else if (edit_cmd == "max_Ube") {
			float new_max_Ube;//переменная для нового значения
			cin >> new_max_Ube;//считываем новое значение
			if (new_max_Ube < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				this->max_Ube = new_max_Ube;//присваеваем новое значение
			}
		}

		else if (edit_cmd == "max_Ice") {
			float new_max_Ice;//переменная для нового значения
			cin >> new_max_Ice;//считываем новое значение
			if (new_max_Ice < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				this->max_Ice = new_max_Ice;//присваеваем новое значение
			}
		}

		else if (edit_cmd == "quantity") {
			float new_quantity;//переменная для нового значения
			cin >> new_quantity;//считываем новое значение
			if (new_quantity < 0) {//проверям коректность введенного значения
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			else {
				this->quantity = new_quantity;//присваеваем новое значение
			}
		}

		else {
			icmd = 1;//выставляем флаг ошибки при неверной команде
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
		<< endl;//выводим всю информацию по выбранному элементу
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
	cout << "---------------------------------------------------------------------" << endl;//выводим всю информацию по выбранному элементу
}

string MOSFET::save_print(){
	string result = "";
	result += to_string(this->id) + " " + 
			  this->name + " " +
			  this->type + " " +
			  to_string(this->max_Uce) + " " +
			  to_string(this->max_Ube) + " " +
			  to_string(this->max_Ice) + " " +
			  to_string(this->quantity) + "\n";//формируем строку в нужном формате
	return result;//возвращаем строку
}

bool MOSFET::put(int quantity){
	if (quantity > 0) {//проверям коректность quantity
		this->quantity += quantity;//изменяем значение
		return 1;//возвращаем true если все коректно
	}
	return 0;//иначе возвращвем false
}

bool MOSFET::take(int quantity){
	if ((quantity > 0) && (quantity <= this->quantity)) {//проверям коректность quantity
		this->quantity -= quantity;//изменяем значение
		return 1;//возвращаем true если все коректно
	}
	return 0;//иначе возвращвем false
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
	if (new_id < 1) {//проверям коректность значения
		return 0;//возвращвем false если значение не коректно
	}
	this->id = new_id;//присваеваем значение
	return 1;//возвращаем true если все коректно
}

bool MOSFET::set_quantity(int new_quantity){
	if (new_quantity < 0) {//проверям коректность значения
		return 0;//возвращвем false если значение не коректно
	}
	this->quantity = new_quantity;//присваеваем значение
	return 1;//возвращаем true если все коректно
}

bool MOSFET::set_max_Uce(float new_max_Uce){
	if (new_max_Uce < 0) {//проверям коректность значения
		return 0;//возвращвем false если значение не коректно
	}
	this->max_Uce = new_max_Uce;//присваеваем значение
	return 1;//возвращаем true если все коректно
}

bool MOSFET::set_max_Ube(float new_max_Ube){
	if (new_max_Ube < 0) {//проверям коректность значения
		return 0;//возвращвем false если значение не коректно
	}
	this->max_Ube = new_max_Ube;//присваеваем значение
	return 1;//возвращаем true если все коректно
}

bool MOSFET::set_max_Ice(float new_max_Ice){
	if (new_max_Ice < 0) {//проверям коректность значения
		return 0;//возвращвем false если значение не коректно
	}
	this->max_Ice = new_max_Ice;//присваеваем значение
	return 1;//возвращаем true если все коректно
}

void MOSFET::set_name(string new_name){
	this->name = new_name;//присваеваем значение
}

bool MOSFET::set_type(string new_type){
	if ((new_type == "P") || (new_type == "N")) {//проверям коректность значения
		this->type = new_type;//присваеваем значение
		return 1;//возвращаем true если все коректно
	}
	return 0;//возвращвем false если значение не коректно
}
