#include "decompress.h"

Decompress::Decompress()
{
    streaming=NULL;
    listing=NULL;
}

//open a file and open archive
void Decompress::decFiles(QVector<QString>& nameList, int& entryCount)
{
    indicator=0;
    streaming=ar_open_file(path);
    listing = ar_open_zip_archive(streaming, true); //set second parameter false for extracting file non-deflate
    if (listing==NULL)
        indicator=1;
    if (!listing)
        listing = ar_open_rar_archive(streaming);
    if (!listing)
        listing = ar_open_tar_archive(streaming);
    // Compute entry number
    int count=0;
    bool next=true;
    while(next)
    {
        if (indicator==1)
            next=ar_parse_entry(listing);
        next=ar_parse_entry(listing);
        nameList.push_back(QString(ar_entry_get_name(listing)));
        count+=1;
    }
    count-=1;
    entryCount = count;
    // Return to first entry
    ar_parse_entry_at(listing, 0);
}

Decompress::~Decompress()
{
    ar_close_archive(listing);
    ar_close(streaming);
}

void Decompress::getFiles(const char* filename)
{
    ar_parse_entry_for(listing, filename);
    entryName=ar_entry_get_name(listing);
    entrySize = ar_entry_get_size(listing);
    ar_entry_uncompress(listing, buffer, entrySize);
}

size_t Decompress::getEntrySize(){return entrySize;}

QString Decompress::getEntryName(){return entryName;}

void Decompress::setPath(QString _path){path = _path.toStdString().c_str();}

unsigned char* Decompress::getBuffer(){return buffer;}


