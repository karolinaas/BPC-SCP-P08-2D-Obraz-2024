#include <iostream>
#include <fstream>
#include <cstdint>
#include <bitset>

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

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
	uint8_t file_header[FILE_HEADER_SIZE]; // Buffer pro BMP hlavièku (prvních 14 bytù souboru)
	uint8_t info_header[INFO_HEADER_SIZE];

	file.open("bmp_test_input_bw.bmp", std::ios::binary | std::ios::in);
	file.read((char*)&file_header, sizeof(file_header));
	file.read((char*)&info_header, sizeof(info_header));

	// Promìnné pro konkrétní data pøeètená z hlavièky souboru
	uint8_t signature[2];
	uint32_t file_size; // Velková velikost souboru v bytech
	uint32_t data_offset; // Offset, neboli adresa v bajtech, kde se nachází pixelové data

	uint32_t info_header_size;
	uint32_t bm_width;
	uint32_t bm_height;
	uint16_t plane_count;
	uint16_t bit_depth;
	uint32_t compression;
	uint32_t image_size;
	uint32_t h_res;
	uint32_t v_res;
	uint32_t num_colors;
	uint32_t num_important_colors;
	
	memcpy(&signature, &file_header[0], 2);
	memcpy(&file_size, &file_header[2], 4);
	memcpy(&data_offset, &file_header[10], 4);

	memcpy(&info_header_size, &info_header[0], 4);
	memcpy(&bm_width, &info_header[4], 4);
	memcpy(&bm_height, &info_header[8], 4);
	memcpy(&plane_count, &info_header[12], 2);
	memcpy(&bit_depth, &info_header[14], 2);
	memcpy(&compression, &info_header[16], 4);
	memcpy(&image_size, &info_header[20], 4);
	memcpy(&h_res, &info_header[24], 4);
	memcpy(&v_res, &info_header[28], 4);
	memcpy(&num_colors, &info_header[32], 4);
	memcpy(&num_important_colors, &info_header[36], 4);

	std::cout << std::endl << "FILE HEADER:" << std::endl;

	std::cout << "File signature: " << signature[0] << signature[1] << std::endl;
	std::cout << "File size (bytes): " << file_size << std::endl;
	std::cout << "Data offset (bytes): " << data_offset << std::endl;

	std::cout << std::endl << "INFO HEADER:" << std::endl;

	std::cout << "Info header size (bytes): " << info_header_size << std::endl;
	std::cout << "Bitmap width (pixels): " << bm_width << std::endl;
	std::cout << "Bitmap height (pixels): " << bm_height << std::endl;
	std::cout << "Number of planes: " << plane_count << std::endl;
	std::cout << "Bit depth (bits): " << bit_depth << std::endl;
	std::cout << "Compression type (0 = no compression): " << compression << std::endl;
	std::cout << "(Compressed) image size (bytes): " << image_size << std::endl;
	std::cout << "Horizontal resolution (pixels/meter): " << h_res << std::endl;
	std::cout << "Vertical resolution (pixels/meter): " << v_res << std::endl;
	std::cout << "Number of colors: " << num_colors << std::endl;
	std::cout << "Number of important colors: " << num_important_colors << std::endl;

	return 0;
}