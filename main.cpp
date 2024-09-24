#include "bmpreader.h"
#include <iostream>
#include <windows.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }

    BMPReader reader;
    BMPReader bmpReader;

    if (!bmpReader.openBMP(argv[1])) {
        return 1;
    }

    bmpReader.displayBMP();
    bmpReader.closeBMP();

    return 0;
}
