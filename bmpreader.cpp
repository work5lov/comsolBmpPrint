#include "BMPReader.h"
#include <iostream>

BMPReader::BMPReader() : pixelData(nullptr) {}

BMPReader::~BMPReader() {
    clearData();
}

bool BMPReader::openBMP(const std::string &fileName) {
    bmpFile.open(fileName, std::ios::binary);
    if (!bmpFile) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return false;
    }

    // Чтение заголовка файла
    bmpFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.bfType != 0x4D42) { // Проверка сигнатуры BMP "BM"
        std::cerr << "Файл не является BMP!" << std::endl;
        return false;
    }

    // Чтение заголовка изображения
    bmpFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) {
        std::cerr << "Поддерживаются только 24-битные и 32-битные BMP!" << std::endl;
        return false;
    }

    // Выделение памяти под пиксельные данные
    int pixelDataSize = fileHeader.bfSize - fileHeader.bfOffBits;
    pixelData = new unsigned char[pixelDataSize];

    // Переход к началу данных изображения
    bmpFile.seekg(fileHeader.bfOffBits, std::ios::beg);
    bmpFile.read(reinterpret_cast<char*>(pixelData), pixelDataSize);

    return true;
}

void BMPReader::displayBMP() {
    if (!pixelData) {
        std::cerr << "Ошибка: файл не открыт или не содержит данных!" << std::endl;
        return;
    }

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int padding = (4 - (width * (infoHeader.biBitCount / 8)) % 4) % 4;

    // Набор символов для отображения разных уровней серого
    const std::string shades = " .:-*#@";

    for (int y = height - 1; y >= 0; --y) { // BMP хранит строки в обратном порядке
        for (int x = 0; x < width; ++x) {
            int pixelOffset = (y * (width * (infoHeader.biBitCount / 8) + padding)) + (x * (infoHeader.biBitCount / 8));

            unsigned char blue = pixelData[pixelOffset];
            unsigned char green = pixelData[pixelOffset + 1];
            unsigned char red = pixelData[pixelOffset + 2];

            // Рассчитываем среднее значение серого
            int grayValue = (red + green + blue) / 3;

            // Определяем индекс символа на основе значения серого
            int shadeIndex = grayValue * (shades.size() - 1) / 255;

            // Выводим соответствующий символ
            std::cout << shades[shadeIndex];
        }
        std::cout << std::endl;
    }
}

void BMPReader::closeBMP() {
    if (bmpFile.is_open()) {
        bmpFile.close();
    }
    clearData();
}

void BMPReader::clearData() {
    if (pixelData) {
        delete[] pixelData;
        pixelData = nullptr;
    }
}
