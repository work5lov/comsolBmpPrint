#ifndef BMPREADER_H
#define BMPREADER_H

#include <string>
#include <fstream>
#include <windows.h>

class BMPReader {
public:
    BMPReader();
    ~BMPReader();

    bool openBMP(const std::string &fileName);
    void displayBMP();
    void closeBMP();

private:
    std::ifstream bmpFile;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    unsigned char* pixelData;

    void clearData();
};

#endif // BMPREADER_H
