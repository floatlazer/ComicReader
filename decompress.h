#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <QString>
#include <QImage>
#include <iostream>
#include <QDebug>

extern "C"
{
    #include "unarr.h"
    //#include "7z.h"
}


//class decompress the archieve file
class Decompress
{
public:
    unsigned char buffer[1024000];
    const char *pathName;
    const char *filename;
    size_t taille;

    Decompress();
    ~Decompress();
    //Open archive file and decompress
    void DecFiles();
    //get file from decompress archive
    void GetFiles();
    //get file number in the archive
    int GetNumber();


private:
    ar_archive *listing;
    ar_stream *streaming;
    int indicator; //zip indicator
};

#endif // DECOMPRESS_H
