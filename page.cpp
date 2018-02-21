#include "page.h"

Page::Page()
{
    initParams();
}

Page::Page(QImage* _image, unsigned int number)
{
    initParams();
    image = _image;
    pageNumber = number;
}

void Page::initParams()
{
    pageNumber = 0;
}

// Getter

QImage* Page::getImage(){ return image;}

unsigned int Page::getPageNumber(){return pageNumber;}

// Setter

void Page::setImage(QImage* _image){image = _image;}

void Page::setPageNumber(unsigned int number){pageNumber = number;}
