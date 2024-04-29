#include <iostream>
#include <fstream>
#include <cstdint>

template<class T> class Obraz {
	T** pole;
	int width, length;

public:
	//// Inicializaèní konstruktor
	//Obraz() {

	//}

	//// Kopírovací konstruktor
	//Obraz() {

	//}

	//// Konverzní konstruktor
	//Obraz() {

	//}

	//// Destruktor
	//~Obraz() {

	//}

	// Binární operátory +, -, * (konvoluce), +=, -=
	friend Obraz operator+(const Obraz& operand1, const Obraz& operand2);
	friend Obraz operator-(const Obraz& operand1, const Obraz& operand2);
	friend Obraz operator*(const Obraz& operand1, const Obraz& operand2);
	friend Obraz operator+=(const Obraz& operand1, const Obraz& operand2);
	friend Obraz operator-=(const Obraz& operand1, const Obraz& operand2);

	// Unární operátor ~ pro výpoèet negativu
	Obraz operator~() {
		Obraz result();

		return result;
	}

	// Operátory pro rovnost, nerovnost, pøiøazení
	Obraz& operator==(const Obraz& operand) {

	}
	Obraz& operator!=(const Obraz& operand) {

	}
	Obraz& operator=(const Obraz& operand) {

	}

	// Operátor [] pro vracení/pøiøazení intenzity pixelu
	T* operator[](int i) const {
		return pole[i];
	}

	// Operátor << pro uložení do souboru
	friend std::ostream& operator<<(std::ostream& out, Obraz& x);

	// Funkce pro filtraci obrazu, prahování, detekci objektu
	Obraz filter() {
		Obraz result();

		return result;
	}
	Obraz prahovani() {
		Obraz result();

		return result;
	}
	Obraz object_detection() {
		Obraz result();

		return result;
	}
};

//// Binární operátor +
//Obraz operator+(const Obraz& operand1, const Obraz& operand2) {
//	Obraz result();
//
//	return result;
//}
//// Binární operátor -
//Obraz operator-(const Obraz& operand1, const Obraz& operand2) {
//	Obraz result();
//
//	return result;
//}
//// Binární operátor * (konvoluce)
//Obraz operator*(const Obraz& operand1, const Obraz& operand2) {
//	Obraz result();
//
//	return result;
//}
//// Binární operátor +=
//Obraz operator+=(const Obraz& operand1, const Obraz& operand2) {
//	Obraz result();
//
//	return result;
//}
//// Binární operátor -=
//Obraz operator-=(const Obraz& operand1, const Obraz& operand2) {
//	Obraz result();
//
//	return result;
//}
//
//// Operátor << pro uložení do souboru
//std::ostream& operator<<(std::ostream& out, Obraz& x) {
//
//	return out;
//}

class Pixel {

};

int main() {
	std::cout << "Hello World" << std::endl;

	std::ifstream file;
	char test[14];

	file.open("bmp_test_input_bw.bmp", std::ios::binary | std::ios::in);
	file.read((char*)&test, sizeof(test));

	for (int i = 0; i < 14; i++) {
		std::cout << std::hex << (unsigned int)test[i] << " ";
	}

	return 0;
}