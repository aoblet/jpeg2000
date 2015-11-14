#pragma once

#include "Signal2D.hpp"

namespace jpeg2000{
namespace bmp{
/**
 * We assume, long <=> 8 bytes, int <=> 4 bytes
 */
namespace file{
    typedef struct{
        unsigned short type;                    ///< Magic identifier
        unsigned int size;                      ///< Bytes file size
        unsigned short reserved1, reserved2;    ///< Unused - must be zero
        unsigned int offset;                    /// Image data offset in bytes
    } __attribute__((packed)) Header;

    typedef struct{
        unsigned int headerSize;        ///< Header size in bytes
        unsigned int imWidth, imHeight; ///< Image dimension
        unsigned short planes;          ///< Number of color planes
        unsigned short bits;            ///< Bits per pixel
        unsigned int compression;       ///< Compression type
        unsigned int imageSizeBytes;    ///< The image size in bytes
        unsigned int xRes, yRes;        ///< Pixels per meter i.e the resolution
        unsigned int coloursNumber;     ///< Number of colours
        unsigned int importantColours;  ///< Important colours
    } __attribute__((packed)) DataInfo;

    typedef struct{
        Header header;
        DataInfo dataInfo;
    } __attribute__((packed)) InfoBMP;

}
    Signal2D loadBMP_256(const std::string& filePath);
    void writeBMP_256(const std::string& filePath, const Signal2D& s);
}
}

