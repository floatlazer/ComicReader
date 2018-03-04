#include "decompress.h"

//open a file and open archive
void Decompress::DecFiles(const char *Path)
{
    streaming=ar_open_file(Path);
    listing = ar_open_rar_archive(streaming);
    //if (!listing)
   //   listing = ar_open_7z_archive(streaming);
    if (!listing)
        listing = ar_open_tar_archive(streaming);
}

Decompress::~Decompress()
{
    ar_close_archive(listing);
    ar_close(streaming);
}

void Decompress::GetFiles()
{
    //ar_parse_entry(listing);
    //ar_parse_entry(listing);
    ar_parse_entry(listing);
    ar_parse_entry(listing);
    filename=ar_entry_get_name(listing);
    std::cout<<filename<<std::endl;
    taille = ar_entry_get_size(listing);
    ar_entry_uncompress(listing, buffer, taille);
}

Decompress::Decompress()
{
    streaming=NULL;
    listing=NULL;
}

