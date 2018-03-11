#include "imageprocess.h"

ImageProcess::ImageProcess()
{

}

void ImageProcess::setPageVector(QVector<Page>* _pageVector)
{
    pageVector = _pageVector;
}

void ImageProcess::scaleImageToFactor(double scaleFactor, int pageNumber)
{
    QPixmap pixmapBuffer=pageVector->operator [](pageNumber).getPixmap();
    pixmapBuffer.scaled(pixmapBuffer.size()*scaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pageVector->operator [](pageNumber).setPixmap(pixmapBuffer);
    pageVector->operator [](pageNumber).setScaled(scaleFactor);
}

void ImageProcess::scaleImageToWindow(QSize size, int pageNumber)
{
    QPixmap pixmapBuffer=pageVector->operator [](pageNumber).getPixmap();
    pixmapBuffer.scaled(size,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pageVector->operator [](pageNumber).setPixmap(pixmapBuffer);
    pageVector->operator [](pageNumber).setScaled(1);
}
