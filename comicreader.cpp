#include "comicreader.h"
#include "ui_comicreader.h"

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    ui->setupUi(this);
    loadAndShowImage(":/test/000.jpg"); // Load and show a test image loaded in the resources
}

ComicReader::~ComicReader()
{
    delete ui;
}

void ComicReader::loadAndShowImage(QString fileName)
{
    currentImage.load(fileName); // Load an image file
    // TODO: Possible image processing goes here...
    currentPixmap.convertFromImage(currentImage);
    ui->label->setPixmap(currentPixmap); // Load image to the label
}

void ComicReader::on_pushButton_left_clicked()
{
    loadAndShowImage(":/test/000.jpg");
}

void ComicReader::on_pushButton_right_clicked()
{
    loadAndShowImage(":/test/001.jpg");
}
