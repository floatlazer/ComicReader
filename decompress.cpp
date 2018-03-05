#include "decompress.h"

//open a file and open archive
void Decompress::DecFiles()
{
    indicator=0;
    streaming=ar_open_file(pathName);
    listing = ar_open_zip_archive(streaming,true); //set second parameter false for extracting file non-deflate
    if (listing==NULL)
        indicator=1;
    if (!listing)
        listing = ar_open_rar_archive(streaming);
    if (!listing)
        listing = ar_open_tar_archive(streaming);
}

Decompress::~Decompress()
{
    ar_close_archive(listing);
    ar_close(streaming);
}

int Decompress::GetNumber()
{
    int count=0;
    bool next=true;
    while(next)
    {
        if (indicator==1)
            next=ar_parse_entry(listing);
        next=ar_parse_entry(listing);
        count+=1;
    }
    count-=1;
    return count;
}

void Decompress::GetFiles()
{
    if (indicator==1)
    {
        ar_parse_entry(listing);
    }
    ar_parse_entry(listing);
    filename=ar_entry_get_name(listing);
    std::cout<<filename<<std::endl;
    taille = ar_entry_get_size(listing);
    std::cout<<taille<<std::endl;
    ar_entry_uncompress(listing, buffer, taille);
}

Decompress::Decompress()
{
    streaming=NULL;
    listing=NULL;
}

