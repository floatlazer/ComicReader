#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <QString>
#include <QImage>
#include <iostream>

extern "C"
{
    #include "unarr.h"
    //#include "7z.h"
}


//class decompress the archieve file
class Decompress
{
public:
    Decompress();
    ~Decompress();

    //Open archive file and decompress
    void DecFiles(const char *Path);
    //get file from decompress archive
    void GetFiles();
    unsigned char buffer[102400];
    const char *filename;
    size_t taille;

private:
    ar_archive *listing;
    ar_stream *streaming;
};

#endif // DECOMPRESS_H
