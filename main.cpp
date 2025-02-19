#include <iostream>
#include <fstream>
#include <cstdint> // integery
#include <cstddef> //std::byte
#include <cmath>

#define FILE_HEADER_SIZE_BYTES 14
#define INFO_HEADER_SIZE_BYTES 40
#define DEBUG

class Pixel_24bit {
	uint8_t red;
	uint8_t green;
	uint8_t blue;

public:
	void set_color_rgb(uint8_t red, uint8_t green, uint8_t blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	uint8_t get_red() {
		return red;
	}
	uint8_t get_green() {
		return green;
	}
	uint8_t get_blue() {
		return blue;
	}
};

// Prim�rn� obrazov� �ablona
template<class T> class Obraz {
	T** bitmap;
	int32_t width, height;

public:
	// inicializa�n� konstruktor
	Obraz() {

	}

	Obraz(int32_t width, int32_t height) {
		bitmap = new T * [this->height = height];
		for (int32_t i = 0; i < height; i++) {
			bitmap[i] = new T[this->width = width];
		}

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++)
				bitmap[i][j] = NULL;
		}
	}

	// Kop�rovac� konstruktor
	Obraz(const Obraz& x) {
		// Alokace pam�ti
		bitmap = new T * [height = x.height];
		for (int32_t i = 0; i < height; i++) {
			bitmap[i] = new T[width = x.width];
		}

		// Kop�rov�n� dat
		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				bitmap[i][j] = x.bitmap[i][j];
			}
		}
	}

	// Destruktor dealokuj�c� pole bitov� mapy
	~Obraz() {
		for (int32_t i = 0; i < this->height; i++) {
			delete[] bitmap[i];
		}
		delete[] bitmap;
	}

	Obraz color_to_grayscale() {

	}
	Obraz prahovani() {
		Obraz result();

		return result;
	}

	// Bin�rn� oper�tory +, -
	template<class P> friend Obraz<P> operator+(const Obraz<P>& operand1, const Obraz<P>& operand2);
	template<class P> friend Obraz<P> operator-(const Obraz<P>& operand1, const Obraz<P>& operand2);

	// Un�rn� oper�tor ~ pro v�po�et negativu
	Obraz operator~() {
		Obraz result;

		return result;
	}

	// Oper�tory pro rovnost, nerovnost, p�i�azen�
	Obraz& operator==(const Obraz& operand) {
		if (width != operand.width) return false;
		if (height != operand.height) return false;

		for (int32_t i = 0; i < height; i++) {
			for (uint32_t j = 0; j < width; j++) {
				if (bitmap[i][j] != operand.bitmap[i][j]) return false;
			}
		}

		return true;
	}
	Obraz& operator!=(const Obraz& operand) {
		return !(*this == operand);
	}
	Obraz& operator=(const Obraz& operand) {
		if (bitmap != NULL) {
			for (int32_t i = 0; i < height; i++) {
				delete[] bitmap[i];
			}
			delete[] bitmap;
		}

		bitmap = new T * [height = operand.height];
		for (int32_t i = 0; i < height; i++) {
			bitmap[i] = new T[width = operand.width];
		}

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				bitmap[i][j] = operand.bitmap[i][j];
			}
		}

		return *this;
	}
	Obraz operator+=(const Obraz& operand) {
		*this = *this + operand;
		return *this;
	}
	Obraz operator-=(const Obraz& operand) {
		*this = *this - operand;
		return *this;
	}

	// Oper�tor [] pro vracen�/p�i�azen� intenzity pixelu
	T* operator[](int32_t i) const {
		return bitmap[i];
	}

	// Oper�tor << pro ulo�en� do souboru
	template<class P> friend std::ofstream& operator<<(std::ofstream& out, Obraz<P>& x);

	// Oper�tor >> pro na�ten� obrazu ze souboru BMP
	template<class P> friend std::ifstream& operator>>(std::ifstream& in, Obraz<P>& x);
};

// Specializace na 24 bitov� pixely
template<> class Obraz<Pixel_24bit> {
	Pixel_24bit** bitmap;
	int32_t width, height;

public:
	// inicializa�n� konstruktor
	Obraz() {
		width = 0;
		height = 0;

		bitmap = new Pixel_24bit * [height];
		for (int32_t i = 0; i < height; i++) {
			bitmap[i] = new Pixel_24bit[width];
		}

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++)
				bitmap[i][j].set_color_rgb(0, 0, 0);
		}
	}

	Obraz(int32_t width, int32_t height) {
		bitmap = new Pixel_24bit * [this->height = height];
		for (int32_t i = 0; i < height; i++) {
			bitmap[i] = new Pixel_24bit[this->width = width];
		}

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++)
				bitmap[i][j].set_color_rgb(0, 0, 0);
		}
	}

	// Kop�rovac� konstruktor
	Obraz(const Obraz& x) {
		// Alokace pam�ti
		bitmap = new Pixel_24bit * [height = x.height];
		for (int32_t i = 0; i < height; i++) {
			bitmap[i] = new Pixel_24bit[width = x.width];
		}

		// Kop�rov�n� dat
		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				bitmap[i][j] = x.bitmap[i][j];
			}
		}
	}

	// Destruktor dealokuj�c� pole bitov� mapy
	~Obraz() {
		for (int32_t i = 0; i < this->height; i++) {
			delete[] bitmap[i];
		}
		delete[] bitmap;
	}

	// https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale
	Obraz<Pixel_24bit> color_to_grayscale() {
		Obraz<Pixel_24bit> result(width, height);

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				float red = (float)bitmap[i][j].get_red() / 255.0f;
				float green = (float)bitmap[i][j].get_green() / 255.0f;
				float blue = (float)bitmap[i][j].get_blue() / 255.0f;

				float red_linear;
				if (red <= 0.04045) red_linear = red / 12.92;
				else red_linear = pow((red + 0.055) / 1.055, 2.4);
				float green_linear;
				if (green <= 0.04045) green_linear = green / 12.92;
				else green_linear = pow((green + 0.055) / 1.055, 2.4);
				float blue_linear;
				if (blue <= 0.04045) blue_linear = blue / 12.92;
				else blue_linear = pow((blue + 0.055) / 1.055, 2.4);

				float Y_linear = 0.2126 * red_linear + 0.7152 * green_linear + 0.0722 * blue_linear;

				float Y_rgb;
				if (Y_linear <= 0.0031308) Y_rgb = 12.92 * Y_linear;
				else Y_rgb = 1.055 * pow(Y_linear, 1 / 2.4);

				uint8_t Y_rgb_int = Y_rgb * 255;

				result.bitmap[i][j].set_color_rgb(Y_rgb_int, Y_rgb_int, Y_rgb_int);
			}
		}

		return result;
	}
	// https://cs.wikipedia.org/wiki/Prahov%C3%A1n%C3%AD
	Obraz<Pixel_24bit> prahovani(uint8_t threshhold_value, uint8_t low, uint8_t high) {
		Obraz<Pixel_24bit> result(width, height);

		result = color_to_grayscale();

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				if (result.bitmap[i][j].get_red() < threshhold_value) {
					result.bitmap[i][j].set_color_rgb(low, low, low);
				}
				else if (result.bitmap[i][j].get_red() >= threshhold_value) {
					result.bitmap[i][j].set_color_rgb(high, high, high);
				}
			}
		}

		return result;
	}

	// Bin�rn� oper�tory +, -
	friend Obraz<Pixel_24bit> operator+(const Obraz<Pixel_24bit>& operand1, const Obraz<Pixel_24bit>& operand2);
	friend Obraz<Pixel_24bit> operator-(const Obraz<Pixel_24bit>& operand1, const Obraz<Pixel_24bit>& operand2);


	// Un�rn� oper�tor ~ pro v�po�et negativu
	Obraz<Pixel_24bit> operator~() {
		Obraz<Pixel_24bit> result(width, height);

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				uint8_t inv_red = 255 - bitmap[i][j].get_red();
				uint8_t inv_green = 255 - bitmap[i][j].get_green();
				uint8_t inv_blue = 255 - bitmap[i][j].get_blue();

				bitmap[i][j].set_color_rgb(inv_red, inv_green, inv_blue);
			}
		}

		return result;
	}

	// Oper�tory pro rovnost, nerovnost, p�i�azen�
	bool operator==(const Obraz& operand) {
		if (width != operand.width) return false;
		if (height != operand.height) return false;

		for (int32_t i = 0; i < height; i++) {
			for (uint32_t j = 0; j < width; j++) {
				if (bitmap[i][j].get_red() != operand.bitmap[i][j].get_red()) return false;
				if (bitmap[i][j].get_green() != operand.bitmap[i][j].get_green()) return false;
				if (bitmap[i][j].get_blue() != operand.bitmap[i][j].get_blue()) return false;
			}
		}

		return true;
	}
	bool operator!=(const Obraz& operand) {
		return !(*this == operand); // YEP
	}
	Obraz& operator=(const Obraz& operand) {
		if (bitmap != NULL) {
			for (int32_t i = 0; i < height; i++) {
				delete[] bitmap[i];
			}
			delete[] bitmap;
		}

		bitmap = new Pixel_24bit * [height = operand.height];
		for (int32_t i = 0; i < height; i++) {
			bitmap[i] = new Pixel_24bit[width = operand.width];
		}

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				bitmap[i][j] = operand.bitmap[i][j];
			}
		}

		return *this;
	}
	Obraz operator+=(const Obraz& operand) {
		*this = *this + operand;
		return *this;
	}
	Obraz operator-=(const Obraz& operand) {
		*this = *this - operand;
		return *this;
	}

	// Oper�tor [] pro vracen�/p�i�azen� intenzity pixelu
	Pixel_24bit* operator[](int32_t i) const {
		return bitmap[i];
	}

	// Oper�tor << pro ulo�en� do souboru
	friend std::ofstream& operator<<(std::ofstream& out, Obraz<Pixel_24bit>& x);

	// Oper�tor >> pro na�ten� obrazu ze souboru BMP
	friend std::ifstream& operator>>(std::ifstream& in, Obraz<Pixel_24bit>& x);
};

// Bin�rn� oper�tor +
Obraz<Pixel_24bit> operator+(const Obraz<Pixel_24bit>& operand1, const Obraz<Pixel_24bit>& operand2) {
	// Mus�me ov��it zda jsou obr�zky stejn� velk�
	if (operand1.width != operand2.width || operand1.height != operand2.height) {
		throw((std::string)"Both images must have the same dimesions!");
	}

	Obraz<Pixel_24bit> result(operand1.width, operand1.height);

	for (int32_t i = 0; i < operand1.height; i++) {
		for (int32_t j = 0; j < operand1.width; j++) {
			int red = operand1.bitmap[i][j].get_red() + operand2.bitmap[i][j].get_red();
			int green = operand1.bitmap[i][j].get_green() + operand2.bitmap[i][j].get_green();
			int blue = operand1.bitmap[i][j].get_blue() + operand2.bitmap[i][j].get_blue();

			if (red > 255) red = 255;
			if (green > 255) green = 255;
			if (blue > 255) blue = 255;

			result.bitmap[i][j].set_color_rgb(red, green, blue);
		}
	}

	return result;
}
// Bin�rn� oper�tor -
Obraz<Pixel_24bit> operator-(const Obraz<Pixel_24bit>& operand1, const Obraz<Pixel_24bit>& operand2) {
	// Mus�me ov��it zda jsou obr�zky stejn� velk�
	if (operand1.width != operand2.width || operand1.height != operand2.height) {
		throw((std::string)"Both images must have the same dimesions!");
	}

	Obraz<Pixel_24bit> result(operand1.width, operand1.height);

	for (int32_t i = 0; i < operand1.height; i++) {
		for (int32_t j = 0; j < operand1.width; j++) {
			int red = operand1.bitmap[i][j].get_red() - operand2.bitmap[i][j].get_red();
			int green = operand1.bitmap[i][j].get_green() - operand2.bitmap[i][j].get_green();
			int blue = operand1.bitmap[i][j].get_blue() - operand2.bitmap[i][j].get_blue();

			if (red < 0) red = 0;
			if (green < 0) green = 0;
			if (blue < 0) blue = 0;

			result.bitmap[i][j].set_color_rgb(red, green, blue);
		}
	}

	return result;
}

// Oper�tor >> pro na�ten� obrazu z 24 bitov�ho BMP souboru
std::ifstream& operator>>(std::ifstream& in, Obraz<Pixel_24bit>& x) {
	std::byte file_header_read_buff[FILE_HEADER_SIZE_BYTES]; // Buffer pro BMP hlavi�ku (prvn�ch 14 byt� souboru)
	std::byte info_header_read_buff[INFO_HEADER_SIZE_BYTES]; // Buffer pro informa�n� hlavi�ku souboru BMP (n�sleduj�c�ch 4O byt�)

	in.read((char*)&file_header_read_buff, sizeof(file_header_read_buff));
	in.read((char*)&info_header_read_buff, sizeof(info_header_read_buff));

	/* Prom�nn� pro konkr�tn� data p�e�ten� ze souborov� hlavi�ky */
	unsigned char signature[2]; // Slou�� pro identifikaci souboru jako BMP
	uint32_t file_size; // Celkov� velikost souboru v bytech
	uint32_t data_offset; // Offset, neboli adresa bytu, kde se nach�z� obrazov� data

	/* Prom�nn� pro konkr�tn� data p�e�ten� z informa�n� hlavi�ky */
	uint32_t info_header_size; // Velikost informa�n� hlavi�ky (m��e b�t r�zn� v z�vislosti na form�tu, standardn� 40 byt�, potenci�ln� v�t��)
	int32_t bm_width; // ���ka bitov� mapy v pixelech (signed int)
	int32_t bm_height; // V��ka bitov� mapy v pixelech (signed int)
	uint16_t plane_count; // Po�et vrstev (mus� b�t 1)
	uint16_t bit_depth; // Bitov� hloubka
	uint32_t compression; // Typ komprese, 0 znamen� bez komprese
	uint32_t image_size; // Velikost obr�zku (po kompresi)
	int32_t h_res; // Horizont�ln� rozli�en� v pixelech na metr (signed int)
	int32_t v_res; // Vertik�ln� rozli�en� v pixelech na metr (signed int)
	uint32_t num_colors; // Celkov� po�et barev v palet�
	uint32_t num_important_colors; // Po�et d�le�it�ch barev, 0 pokud v�echny

	/* Prom�nn� jsou napln�ny p��m�m kop�rov�n�m pam�ti */
	memcpy(&signature, &file_header_read_buff[0], 2);
	memcpy(&file_size, &file_header_read_buff[2], 4);
	memcpy(&data_offset, &file_header_read_buff[10], 4);

	memcpy(&info_header_size, &info_header_read_buff[0], 4);
	memcpy(&bm_width, &info_header_read_buff[4], 4);
	memcpy(&bm_height, &info_header_read_buff[8], 4);
	memcpy(&plane_count, &info_header_read_buff[12], 2);
	memcpy(&bit_depth, &info_header_read_buff[14], 2);
	memcpy(&compression, &info_header_read_buff[16], 4);
	memcpy(&image_size, &info_header_read_buff[20], 4);
	memcpy(&h_res, &info_header_read_buff[24], 4);
	memcpy(&v_res, &info_header_read_buff[28], 4);
	memcpy(&num_colors, &info_header_read_buff[32], 4);
	memcpy(&num_important_colors, &info_header_read_buff[36], 4);

#ifdef DEBUG
	std::cout << std::endl << "===FILE HEADER===" << std::endl;

	std::cout << "File signature: " << signature[0] << signature[1] << std::endl;
	std::cout << "File size (bytes): " << file_size << std::endl;
	std::cout << "Data offset (bytes): " << data_offset << std::endl;

	std::cout << std::endl << "===INFO HEADER===" << std::endl;

	std::cout << "Info header size (bytes): " << info_header_size << std::endl;
	std::cout << "Bitmap width (pixels): " << bm_width << std::endl;
	std::cout << "Bitmap height (pixels): " << bm_height << std::endl;
	std::cout << "Number of color planes: " << plane_count << std::endl;
	std::cout << "Bit depth (bits): " << bit_depth << std::endl;
	std::cout << "Compression type (0 = no compression): " << compression << std::endl;
	std::cout << "(Compressed) image size (bytes): " << image_size << std::endl;
	std::cout << "Horizontal resolution (pixels/meter): " << h_res << std::endl;
	std::cout << "Vertical resolution (pixels/meter): " << v_res << std::endl;
	std::cout << "Number of colors: " << num_colors << std::endl;
	std::cout << "Number of important colors: " << num_important_colors << std::endl;
#endif // DEBUG

	// Read buff pro samotn� obrazov� data je dynamicky alokovan� podle velikosti p�e�ten� z hlavi�ky
	std::byte* bitmap_read_buff;
	bitmap_read_buff = new std::byte[image_size];

	in.read((char*)bitmap_read_buff, image_size);

	// BMP soubory zaokrouhluij� rozm�ry obr�zku na n�sobky 4, proto je nutn� zjistit kolik byt� bylo pou�ito na padding
	int32_t pad_bytes_count = ((bm_width * 3) % 4); // N�soben� t�emi proto�e ka�d� pixel m� t�i byty (24 bit)

	// Pokud m� objekt alkovanou pam� pro bitovou mapu, je pot�eba ji dealokovat
	if (x.bitmap != NULL) {
		for (int32_t i = 0; i < x.height; i++) {
			delete[] x.bitmap[i];
		}
		delete[] x.bitmap;
	}

	// N�sledn� alokujeme pam� podle rozm�r� p�e�ten�ch z hlavi�ky souboru
	x.bitmap = new Pixel_24bit * [bm_height];
	for (int32_t i = 0; i < bm_height; i++) {
		x.bitmap[i] = new Pixel_24bit[bm_width];
	}

	// A p�e�teme bitovou mapu ze souboru do objektu
	for (int32_t i = 0; i < bm_height; i++) {
		for (int32_t j = 0; j < bm_width; j++) {
			uint8_t red, green, blue;

			int32_t padding = i * pad_bytes_count;
			int32_t pixel_pos = (i * bm_width + j) * 3; // N�soben� t�emi proto�e ka�d� pixel m� t�i byty (24 bit)

			memcpy(&blue, &bitmap_read_buff[padding + pixel_pos], 1);
			memcpy(&green, &bitmap_read_buff[padding + pixel_pos + 1], 1);
			memcpy(&red, &bitmap_read_buff[padding + pixel_pos + 2], 1);

			x.bitmap[i][j].set_color_rgb(red, green, blue); // BMP pou��v� po�ad� barev BGR m�sto RGB
		}
	}

	x.height = bm_height;
	x.width = bm_width;

	delete[] bitmap_read_buff;

	return in;
}

// Oper�tor << pro ulo�en� do 24 bitov�ho BMP souboru
std::ofstream& operator<<(std::ofstream& out, Obraz<Pixel_24bit>& x) {
	unsigned char file_header_write_buff[FILE_HEADER_SIZE_BYTES]; // Buffer pro BMP hlavi�ku (prvn�ch 14 byt� souboru)
	unsigned char info_header_write_buff[INFO_HEADER_SIZE_BYTES]; // Buffer pro informa�n� hlavi�ku souboru BMP (n�sleduj�c�ch 4O byt�)

	int32_t pad_bytes_count = ((x.width * 3) % 4); // N�soben� t�emi proto�e ka�d� pixel m� t�i byty (24 bit)

	/* Prom�nn� pro konkr�tn� data souborov� hlavi�ky */
	unsigned char signature[2] = {'B', 'M'}; // Slou�� pro identifikaci souboru jako BMP
	uint32_t file_size = FILE_HEADER_SIZE_BYTES + INFO_HEADER_SIZE_BYTES + (x.width * 3 + pad_bytes_count) * x.height; // Celkov� velikost souboru v bytech
	uint32_t data_offset = FILE_HEADER_SIZE_BYTES + INFO_HEADER_SIZE_BYTES; // Offset, neboli adresa bytu, kde se nach�z� obrazov� data

	/* Prom�nn� pro konkr�tn� data informa�n� hlavi�ky */
	uint32_t info_header_size = INFO_HEADER_SIZE_BYTES; // Velikost informa�n� hlavi�ky (m��e b�t r�zn� v z�vislosti na form�tu, standardn� 40 byt�, potenci�ln� v�t��)
	int32_t bm_width = x.width; // ���ka bitov� mapy v pixelech (signed int)
	int32_t bm_height = x.height; // V��ka bitov� mapy v pixelech (signed int)
	uint16_t plane_count = 1; // Po�et vrstev (mus� b�t 1)
	uint16_t bit_depth = 24; // Bitov� hloubka
	uint32_t compression = 0; // Typ komprese, 0 znamen� bez komprese
	uint32_t image_size = (x.width * 3 + pad_bytes_count) * x.height; // Velikost obr�zku (po kompresi)
	int32_t h_res = 0; // Horizont�ln� rozli�en� v pixelech na metr (signed int)
	int32_t v_res = 0; // Vertik�ln� rozli�en� v pixelech na metr (signed int)
	uint32_t num_colors = 0; // Celkov� po�et barev v palet�
	uint32_t num_important_colors = 0; // Po�et d�le�it�ch barev, 0 pokud v�echny

	memcpy(&file_header_write_buff[0], &signature, 2);
	memcpy(&file_header_write_buff[2], &file_size, 4);
	memcpy(&file_header_write_buff[10], &data_offset, 4);

	memcpy(&info_header_write_buff[0], &info_header_size, 4);
	memcpy(&info_header_write_buff[4], &bm_width, 4);
	memcpy(&info_header_write_buff[8], &bm_height, 4);
	memcpy(&info_header_write_buff[12], &plane_count, 2);
	memcpy(&info_header_write_buff[14], &bit_depth, 2);
	memcpy(&info_header_write_buff[16], &compression, 4);
	memcpy(&info_header_write_buff[20], &image_size, 4);
	memcpy(&info_header_write_buff[24], &h_res, 4);
	memcpy(&info_header_write_buff[28], &v_res, 4);
	memcpy(&info_header_write_buff[32], &num_colors, 4);
	memcpy(&info_header_write_buff[36], &num_important_colors, 4);
	
	for (int i = 0; i < FILE_HEADER_SIZE_BYTES; i++) {
		out << file_header_write_buff[i];
	}
	for (int i = 0; i < INFO_HEADER_SIZE_BYTES; i++) {
		out << info_header_write_buff[i];
	}

	for (int i = 0; i < bm_height; i++) {
		for (int j = 0; j < bm_width; j++) {
			out << (unsigned char)x.bitmap[i][j].get_blue() << (unsigned char)x.bitmap[i][j].get_green() << (unsigned char)x.bitmap[i][j].get_red();
		}

		for (int j = 0; j < pad_bytes_count; j++) {
			unsigned char pad_byte = 0;
			out << pad_byte;
		}
	}

	return out;
}

int main(int argc, char* argv[]) {
	std::string input1_path = argv[1];
	std::string input2_path = argv[2];

	std::ifstream input1_file, input2_file;
	std::ofstream output_file;

	input1_file.open(input1_path, std::ios::binary | std::ios::in);
	input2_file.open(input2_path, std::ios::binary | std::ios::in);

	Obraz<Pixel_24bit> input1_obraz, input2_obraz, output_obraz;
	
	input1_file >> input1_obraz;
	input2_file >> input2_obraz;

	// 01 Sou�et +
	output_obraz = input1_obraz + input2_obraz;
	output_file.open("01_soucet.bmp", std::ios::binary | std::ios::out);
	output_file << output_obraz;
	output_file.close();

	// 02 Rozdil -
	output_obraz = input1_obraz - input2_obraz;
	output_file.open("02_rozdil.bmp", std::ios::binary | std::ios::out);
	output_file << output_obraz;
	output_file.close();

	// 03 Sou�et +=
	output_obraz = input1_obraz;
	output_obraz += input2_obraz;
	output_file.open("03_soucet.bmp", std::ios::binary | std::ios::out);
	output_file << output_obraz;
	output_file.close();

	// 04 Rozdil -=
	output_obraz = input1_obraz;
	output_obraz -= input2_obraz;
	output_file.open("04_rozdil.bmp", std::ios::binary | std::ios::out);
	output_file << output_obraz;
	output_file.close();

	// 05 Negativ ~
	output_obraz = input1_obraz;
	~output_obraz;
	output_file.open("05_negativ.bmp", std::ios::binary | std::ios::out);
	output_file << output_obraz;
	output_file.close();

	// 06 Grayscale funkce
	output_obraz = input1_obraz;
	output_obraz = input1_obraz.color_to_grayscale();
	output_file.open("06_grayscale.bmp", std::ios::binary | std::ios::out);
	output_file << output_obraz;
	output_file.close();

	// 07 Prahovani funkce
	output_obraz = input1_obraz;
	output_obraz = input1_obraz.prahovani(127, 0, 255);
	output_file.open("07_prahovani.bmp", std::ios::binary | std::ios::out);
	output_file << output_obraz;
	output_file.close();

	if (input1_obraz == input2_obraz) {
		std::cout << "Rovna se!" << std::endl;
	}
	if (input1_obraz != input2_obraz) {
		std::cout << "Nerovna se!" << std::endl;
	}

	return 0;
}