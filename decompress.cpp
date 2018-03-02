#include "decompress.h"

void Decompress::DecFiles(QString Path)
{
    streaming=ar_open_file(&Path);
    listing=ar_open_rar_archive(streaming);
    listing=ar_open_tar_archive(streaming);
    listing=ar_open_zip_archive(streaming);
    listing=ar_open_7z_archive(streaming);
}

void Decompress::~Decompress()
{
    ar_close_archive(listing);
    ar_close(streaming);
}

bool Decompress::GetFiles(ar_archive *listing, char *filename)
{
    filename=ar_entry_get_name(listing);
    return ar_parse_entry(listing);
}

