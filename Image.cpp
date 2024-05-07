#include "./h/Image.h"

#include <iostream>
#include <fstream>

Color::Color() : r(0), g(0), b(0) {

}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {

}

Color::~Color() {

}

Image::Image(int width, int height) : m_width(width), m_height(height), m_colors(std::vector<Color>(width * height)) {

}

Image::~Image() {

}

Color Image::GetColor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void Image::SetColor(const Color& color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void Image::Export(const char* path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if(!f.is_open()) {
        std::cout << "File could not be opened\n";
        return;
    }

    /**
     * Three parts (required):
     * 1) File Header - General information.
     * 2) Information header (DIB header) - Detailed information.
     * 3) Pixel array - Color data for each pixel.
     * 
     * Image (width = 3, height = 4);
     * 
     *          9 bytes
     *  _______________________
     * |                       |
     *  ____________________________
     * |3 bytes |         |         |
     * |--------|---------|---------|
     * |3 bytes | 3 bytes | 3 bytes |
     * |--------|---------|---------|
     * |3 bytes | 3 bytes | 3 bytes |
     * |--------|---------|---------|
     * |3 bytes | 3 bytes | 3 bytes |
     * |--------|---------|---------|
     * (0, 0)
     * 9 % 4 = 1
     * 4 - 1 = 3 bytes of padding
    */

    unsigned char bmpPad[3] = { 0, 0, 0 };
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileHeaderSize        = 14;
    const int informationHeaderSize = 40;
    const int fileSize              = fileHeaderSize + informationHeaderSize * m_width * m_height * 3 + paddingAmount * m_height;
}