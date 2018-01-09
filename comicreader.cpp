#include "comicreader.h"
#include "ui_comicreader.h"

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    ui->setupUi(this);
}

ComicReader::~ComicReader()
{
    delete ui;
}
