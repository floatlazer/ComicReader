#include "decompress.h"

void Decompress::DecFiles(const char *Path)
{
    streaming=ar_open_file(Path);
    listing=ar_open_rar_archive(streaming);
    listing=ar_open_tar_archive(streaming);
    listing=ar_open_7z_archive(streaming);
}

Decompress::~Decompress()
{
    ar_close_archive(listing);
    ar_close(streaming);
}

bool Decompress::GetFiles(ar_archive *listing, const char *filename)
{
    filename=ar_entry_get_name(listing);
    return ar_parse_entry(listing);
}

