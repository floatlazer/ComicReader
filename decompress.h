#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <QString>

//class decompress the archieve file


class Decompress
{
public:
    Decompress();
    ~Decompress();

    //decompress the archive file
    void DecFiles(QString Path);

    //get file
    void GetFiles(ar_archive *listing,char *filename);
    char *filename;

private:
    ar_archive *listing;
    ar_stream *streaming;
};

#endif // DECOMPRESS_H
