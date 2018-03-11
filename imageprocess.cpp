#include "imageprocess.h"
#include <QDebug>
ImageProcess::ImageProcess()
{

}

void ImageProcess::setPageVector(QVector<Page>* _pageVector)
{
    pageVector = _pageVector;
}

void ImageProcess::scaleImageToFactor(double scaleFactor, int pageNumber)
{
    qDebug()<<"scaleImageToFactor"<<scaleFactor<<pageNumber;
    QPixmap pixmapBuffer=pageVector->operator [](pageNumber-1).getPixmap();
    pageVector->operator [](pageNumber - 1).setPixmap(pixmapBuffer.scaled(pixmapBuffer.size()*scaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    pageVector->operator [](pageNumber - 1).setScaled(scaleFactor);
    pixmapBuffer = dockPixmap;
}

void ImageProcess::scaleImageToWindow(QSize size, int pageNumber)
{
    QPixmap pixmapBuffer=pageVector->operator [](pageNumber).getPixmap();
    pixmapBuffer.scaled(size,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pageVector->operator [](pageNumber).setPixmap(pixmapBuffer);
    pageVector->operator [](pageNumber).setScaled(1);
}
