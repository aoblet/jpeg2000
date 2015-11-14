#include "bitmap.hpp"
#include <fstream>
#include <stdexcept>
#include <boost/algorithm/clamp.hpp>
#include <bitset>

#include <cstring>

namespace jpeg2000{
namespace bmp{
    Signal2D loadBMP_256(const std::string& filePath){
        file::InfoBMP infoBMP;
        Signal2D res;
        std::ifstream bmpFile(filePath, std::ifstream::binary);

        if(!bmpFile.is_open())
            throw std::runtime_error("loadBMP_256: cannot open " + filePath + " file");

        // header reading: sizeof(infoBMP) == 54 bytes
        bmpFile.read((char*) &infoBMP, sizeof(infoBMP));
        if (infoBMP.header.type != 19778)
            throw std::logic_error("loadBMP_256: the file " + filePath + " is not a BMP file");

        // check image mode 256 colors
        if (infoBMP.dataInfo.bits != 8)
            throw std::logic_error("loadBMP_256: the bmp file is not in 256 colors mode " + infoBMP.dataInfo.bits);

        // uncompressed file check
        if (infoBMP.dataInfo.compression != 0)
            throw std::logic_error("loadBMP_256: the bmp file is in compressed mode ");

        // prepare pixels image array storage
        int width = infoBMP.dataInfo.imWidth,
            height = infoBMP.dataInfo.imHeight,
            pixelsSize = width * height;
        unsigned char pixels[pixelsSize];

        // position the cursor at the pixels data and read
        bmpFile.seekg(infoBMP.header.offset, bmpFile.beg);
        bmpFile.read((char*)pixels, pixelsSize);

        // write pixel values inside the signal
        for(int y=0; y<height; ++y) {
            Signal1D tmp;
            for(int x=0; x<width; ++x){
                tmp += (double) pixels[y*width + x];
            }
            res.push_back(std::move(tmp));
        }
        return res;
    }

    void writeBMP_256(const std::string& filePath, const Signal2D& s){
        std::ofstream bmpFile(filePath, std::ofstream::binary);
        file::InfoBMP infoBMP = {};

        if(!bmpFile.is_open())
            throw std::runtime_error("writeBMP_256: cannot open or create file " + filePath);

        // Conversion double => unsigned char
        unsigned int height = (unsigned int) s.size(),
                     width = (unsigned int) s[0].size(),
                     pixelsSize = width * height;
        unsigned char pixels[pixelsSize];

        for (int y=0; y< height; y++) {
            for (int x=0; x< width; x++)
                pixels[x + width*y] = (unsigned char) boost::algorithm::clamp(s[y][x], 0, 255);
        }

        infoBMP.header.type = 19778;
        infoBMP.header.size =  pixelsSize + 14 + 40 + 256*4;
        infoBMP.header.reserved1 = 0;
        infoBMP.header.reserved2 = 0;
        infoBMP.header.offset = 14 + 40 + 256*4;  // BITMAPFILEHEADER size + BITMAPINFOHEADER size + palette size

        infoBMP.dataInfo.headerSize = 40;
        infoBMP.dataInfo.imWidth = width;
        infoBMP.dataInfo.imHeight = height;
        infoBMP.dataInfo.planes = 1;
        infoBMP.dataInfo.bits = 8;
        infoBMP.dataInfo.compression = 0;
        infoBMP.dataInfo.imageSizeBytes = pixelsSize;
        infoBMP.dataInfo.xRes = 0;
        infoBMP.dataInfo.yRes = 0;
        infoBMP.dataInfo.coloursNumber = 0;
        infoBMP.dataInfo.importantColours = 0;

        // writing the palette to gray level
        unsigned char palette[256*4];
        unsigned char intToUChar;
        unsigned int tmpArrayChar = 0;
        int grayOffset = 0;
        for(int grayVal=1; grayVal<255; ++grayVal){
            intToUChar = grayVal;
            palette[grayOffset] = intToUChar;
            palette[grayOffset + 1] = intToUChar;
            palette[grayOffset + 2] = intToUChar;
            palette[grayOffset + 3] = 0;
            grayOffset += 4;
        }

        // image writing
        bmpFile.write((char*) &infoBMP, sizeof(infoBMP));
        bmpFile.write((char*) &palette, sizeof(palette));
        bmpFile.write((char*) &pixels, sizeof(pixels));
    }
}
}
