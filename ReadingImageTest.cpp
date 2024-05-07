#include "./h/Image.h"

int main() {

    Image copy(0, 0);
    copy.Read("image.bmp");
    copy.Export("copy.bmp");
    
}