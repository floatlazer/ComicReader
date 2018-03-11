#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QObject>
#include <QPixmap>
#include "page.h"

//Object in a new thread to scale Image asynchronously
class ImageProcess : public QObject
{
    Q_OBJECT
public slots:
    void scaleImageToFactor(double scaleFactor, int pageNumber);
    void scaleImageToWindow(QSize size, int pageNumber);

public:
    ImageProcess();
    void setPageVector(QVector<Page>* _pageVector);

private:
    QVector<Page>* pageVector;
    QPixmap dockPixmap;
};

#endif // IMAGEPROCESS_H
