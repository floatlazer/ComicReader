#include "page.h"
#include <QDebug>
Page::Page()
{
    initParams();
}

Page::Page(QImage _image, unsigned int number)
{
    initParams();
    image = _image; // QImage is implicite shared
    pageNumber = number;
}

Page::Page(unsigned int number)
{
    initParams();
    pageNumber = number;
}

Page::~Page()
{
    qDebug()<<"Destroy page"<<pageNumber;
    //image.~QImage(); QImage is implicitly shared
}

void Page::initParams()
{
    pageNumber = 0;
    loaded = false;
}

// Getter

QPixmap Page::getPixmap(){return pixmap;}

QImage Page::getImage(){ return image;}

unsigned int Page::getPageNumber(){return pageNumber;}

bool Page::isLoaded(){return loaded;}

double Page::getScaled(){return scalefactor;}


// Setter

void Page::setPixmap(QPixmap _pixmap){pixmap=_pixmap;}

void Page::setImage(QImage _image){image = _image;}

void Page::setPageNumber(unsigned int number){pageNumber = number;}

void Page::setLoaded(bool _loaded){loaded = _loaded;}

void Page::setScaled(double factor){scalefactor=factor;}

