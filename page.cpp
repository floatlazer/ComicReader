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
    zoomFactor = 1.0;
    zoomCount = 0;
    horizontalScrollBarValue = 0;
    verticalScrollBarValue = 0;
    pageNumber = 0;
}

// Getter

QImage* Page::getImage(){ return image;}

int Page::getHorizontalScrollBarValue(){return horizontalScrollBarValue;}

int Page::getVerticalScrollBarValue(){return verticalScrollBarValue;}

int Page::isZoomed(){return zoomCount == 0;}

unsigned int Page::getPageNumber(){return pageNumber;}

double Page::getZoomFactor(){return zoomFactor;}

// Setter

void Page::setImage(QImage* _image){image = _image;}

void Page::setZoomOut(){zoomCount--;}

void Page::setZoomIn(){zoomCount++;}

void Page::setZoomFactor(double factor){zoomFactor = factor;}

void Page::setPageNumber(unsigned int number){pageNumber = number;}
