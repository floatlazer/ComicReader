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

/*Page::Page(Page& _page)
{
    pageNumber = _page.pageNumber;
    loaded = _page.isLoaded();
    image = _page.getImage();
}*/

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

QImage Page::getImage(){ return image;}

unsigned int Page::getPageNumber(){return pageNumber;}

bool Page::isLoaded(){return loaded;}


// Setter

void Page::setImage(QImage _image){image = _image;}

void Page::setPageNumber(unsigned int number){pageNumber = number;}

void Page::setLoaded(bool _loaded){loaded = _loaded;}
