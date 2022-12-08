#pragma once
#include <Windows.h>
#include <iostream>
#include <malloc.h>
#include <iomanip>
#include <string>

class Reservoir
{
	char* name;
	char* type;
	int width;
	int lenght;
	int depth;
public:
	//Конструктор с двумя параметрами и основной
	Reservoir(char* n, char* t) :
		lenght{ -1 }, width{ -1 }, depth{- 1}, 
		name{ new char[125] }, type{ new char[125] } 
	{
		strcpy_s(name, strlen(n) + 4, n);
		strcpy_s(type, strlen(t) + 4, t);
	};
	//Конструктом со всем набором параметров
	Reservoir(char* n,  char* t, int w, int l, int d) : Reservoir(n, t) {
		lenght = l; width = w; depth = d;
	};
	//Пустой конструктор, или по умолчанию
	Reservoir() : Reservoir((char*)"Nothing",(char*)"Nothing") {};

	//Вывод информациии
	void printData() {
		std::cout << "\n";
		std::cout << "|-Name of reservoir - " << name << std::endl;
		std::cout << "|-Type of reservoir - " << type << std::endl;
		std::cout << "|-Lenght of reservoir - " << lenght << std::endl;
		std::cout << "|-Width of reservoir - " << width << std::endl;
		std::cout << "|-Depth of reservoir - " << depth << std::endl;
		std::cout << "|-Volume of reservoir - " << indetifyVolume() << std::endl;
		std::cout << "\n";
	}
	//Объём
	int indetifyVolume() {
		return lenght * width * depth;
	}
	//Сравнение типов
	bool compareType(char* t) {
		if (strcmp(type, t) == 0)
			return 1;
		return 0;
	}
	//Сравнение площадей поверхностей
	bool compareSurface(int l, int w) {
		if (l * w < lenght * width)
			return 1;
		return 0;
	}
	//Копирование объектов
	void copyReservoir(Reservoir p) {
		delete[]name;
		delete[]type;
		name = new char[strlen(p.name)];
		type = new char[strlen(p.name)];
		strcpy_s(name, strlen(p.name) + 1, p.name);
		strcpy_s(type, strlen(p.type) + 1, p.type);
		width = p.width;
		lenght = p.lenght;
		depth = p.depth;
	}
	//Изменение параметров размера
	void changeSizes() {
		std::cout << "Enter the new lenght:\n";
		std::cin >> lenght;
		std::cout << "Enter the new width:\n";
		std::cin >> width;
		std::cout << "Enter the new depth:\n";
		std::cin >> depth;
	}
	//Изменение имени и типа водоёма
	void changeNameType() {
		delete[]name;
		delete[]type;
		name = new char[125];
		type = new char[125];
		std::cout << "Enter the new name:\n";
		gets_s(name, 126);
		std::cout << "Enter the new type:\n";
		gets_s(type, 126);
	}
	//Функции get
	int getLenght() {
		return lenght;
	}
	int getWidth() {
		return width;
	}
	int getDepth() {
		return depth;
	}
	char* getName() {
		return name;
	}
	char* getType() {
		return type;
	}
	//Функции set
	void setLenght(int l) {
		lenght = l;
	}
	void setWidth(int w) {
		width = w;
	}
	void setDepth(int d) {
		depth = d;
	}
	void setName(char* n) {
		delete[]name;
		name = new char[126];
		strcpy_s(name, 136, n);
	}
	void setType(char* t) {
		delete[]type;
		type = new char[125];
		strcpy_s(type, 126, t);
	}

	~Reservoir() {
		delete[]name;
		delete[]type;
	} 
};

