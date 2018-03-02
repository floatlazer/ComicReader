#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <QString>
#include "unarr.h"

//class decompress the archieve file


class Decompress
{
public:
    Decompress();
    ~Decompress();

    //Open archive file and decompress
    void DecFiles(const char *Path);

    //get file from decompress archive
    bool GetFiles(ar_archive *listing, const char *filename);
    const char *filename;

private:
    ar_archive *listing;
    ar_stream *streaming;
};

#endif // DECOMPRESS_H
