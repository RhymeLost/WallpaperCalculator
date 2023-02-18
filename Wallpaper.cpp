
                     //ВЫЧИСЛЕНИЕ КОЛИЧЕСТВА ОБОЕВ И СУММЫ ДЛЯ КВАДРАТНЫХ КОМНАТ С ЦЕЛОЧИСЛЕННЫМИ ПАРАМЕТАМИ
#include <windows.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class flat {
	int rooms_c = 0;    //количество комнат
public:
	flat() {
		bool temp = 0;
		while (!temp) {
			cout << "В скольких комнатах в квартире надо поклеить обои? ";
			cin >> rooms_c;
			if (rooms_c < 1) { cout << "\nНеверное значение! "; }
			else { temp = 1; }
		}
		cout << endl;
	};
	int get_room_c()const {  //get для количества комнат
		return rooms_c;
	}
};

class room {
public:
	string room_name="Комната без имени";
	int H = 0,S =0;   //H - высота S - площадь
	bool roof = 0;    //клеить потолок или нет
public:
	room() {};
	string get_room_name()const {  // ниже - get для параметров
		return room_name;
	}
	int get_S()const {
		return S;
	}
	int get_H()const {
		return H;
	}
	bool get_roof()const {
		return roof;
	}
	void check_roof() {           // ниже - set для параметров
		cout << "Надо ли клеить полок комнаты \"" << room_name << "\" ? (1 - да 0 - нет) ";
		cin >> roof;
	}
	void set_param() {
		cout << "Введите площадь комнаты (целое) \"" << room_name << "\": ";
		cin >> S;
		cout << "Введите высоту комнаты (целое) \"" << room_name << "\": ";
		cin >> H;
	}
	void set_room_name(int i) {
		cout << "Введите название комнаты " << i + 1 << ": ";
		cin >> room_name;
	}
	~room() {  //нечего чистить вроде
	}
};

class wallpaper {
	string paper_name ="Обои без имени";
	int LW = 0, WW = 0;    //LW - длина WW - ширина
	int roll_c = 0;   //количество видов
	float price = 0;
public:
	wallpaper() {};
	wallpaper(int room_c) {   //конструктор для вспомогательного экземпляра
		cout << "Сколько видов обоев планируется использовать? (Не больше " << room_c << ") ";
		cin >> roll_c;
		cout << endl;
	};
	string get_paper_name()const {    // ниже - get для параметров
		return paper_name;
	}
	int get_roll_c()const {
		return roll_c;
	}
	int get_LW()const {
		return LW;
	}
	int get_WW()const {
		return WW;
	}
	float get_price()const {
		return price;
	}
	void set_paper_name(int i) {       // ниже - set для параметров
		cout << "Введите название обоев " << i + 1 << ": ";
		cin >> paper_name;
	}
	void set_price() {
		cout << "Введите цену за рулон обоев \"" << paper_name << "\": ";
		cin>>price;
	}
	void set_paper_param() {
		cout << "Введите длину рулона обоев (целое) \"" << paper_name << "\": ";
		cin >> LW;
		cout << "Введите ширину рулона обоев (целое) \"" << paper_name << "\": ";
		cin >> WW;
	}
	~wallpaper() {
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	flat FLAT;

	room* ROOMS = new room[FLAT.get_room_c()];   //массив с команатми
	for (int i = 0; i < FLAT.get_room_c(); i++) { //установка параметров
		ROOMS[i].set_room_name(i);
		ROOMS[i].set_param();
		ROOMS[i].check_roof();
		cout << endl;
	}

	wallpaper EXMPLPAPER(FLAT.get_room_c());   //вспомогательный экземпляр
	wallpaper* PAPERS = new wallpaper[EXMPLPAPER.get_roll_c()];  //установка параметров
	for (int i = 0; i < EXMPLPAPER.get_roll_c(); i++) {
		PAPERS[i].set_paper_name(i);
		PAPERS[i].set_paper_param();
		PAPERS[i].set_price();
		cout << endl;
	}

	float summ = 0;
	int* list = new int[EXMPLPAPER.get_roll_c()];              //список обоев 
	string *list_name = new string [EXMPLPAPER.get_roll_c()];  //и список названий
	for (int i = 0; i < EXMPLPAPER.get_roll_c(); i++) {
		list[i] = 0;
		list_name[i] = PAPERS[i].get_paper_name();           //присваивание имен
	}
	//подсчет по каждой команате
	for (int i = 0, P = 0, S1 = 0, S2 = 0, T = 0; i < FLAT.get_room_c(); i++) {    //S1 - площадь стен  S2 - площадь рулона 
		cout << endl << "Какие обои применить к комнате \"" << ROOMS[i].get_room_name() << "\"?\n";     //Р - периметр
		for (int j = 0; j < EXMPLPAPER.get_roll_c(); j++) {  //список обоев
			cout << j + 1 << ") " << PAPERS[j].get_paper_name() << endl;
		}
		cin >> T;
		P = sqrt(ROOMS[i].get_S()) * 4; //вычисление периметра
		if (ROOMS[i].get_roof()) { //вычисление площади поклейки с проверкой условий потолка 
			S1 = P * ROOMS[i].get_H() + ROOMS[i].get_S(); 
		}
		else { //если не надо
			S1 = P * ROOMS[i].get_H();
		}
		S2 = PAPERS[T-1].get_LW() * PAPERS[T-1].get_WW(); //площадь рулона обоев
		list[T-1] += ceil(S1 / S2);  //вычисление количества обоев с округлением в большую сторону 
		summ += floor(list[i] * PAPERS[i].get_price()); //вычисление стоимости
	}

	cout << "\nВам необходимо: \n";
	for (int i = 0; i < EXMPLPAPER.get_roll_c(); i++) {
		cout << "\"" << list_name[i] << "\": " << list[i] << " рулона(-ов)\n";
	}
	cout << "\n\nСтоимость всех обоев: " << summ;

	delete[]list;
	delete[]list_name;
	delete[]PAPERS;
	delete[]ROOMS;
	cout << endl << endl; return 0;
}