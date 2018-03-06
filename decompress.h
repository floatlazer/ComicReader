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
    Decompress();
    ~Decompress();
    // Open archive file and decompress
    void decFiles(QVector<QString>& nameList, int& totalPages);
    // Get file from decompress archive
    void getFiles(const char* filename);
    // Get file number in the archive
    int getEntryNumber();
    size_t getEntrySize();
    QString getEntryName();
    void setPath(QString _path);
    unsigned char* getBuffer();

private:
    ar_archive *listing;
    ar_stream *streaming;
    int indicator; //zip indicator
    unsigned char buffer[1024*1024*2];
    const char *path;
    const char *entryName;
    size_t entrySize;
};

#endif // DECOMPRESS_H
