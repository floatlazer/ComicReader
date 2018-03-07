#ifndef LOADPAGETHREAD_H
#define LOADPAGETHREAD_H
#include <QComboBox>
#include <QVector>
#include "page.h"
#include "decompress.h"

// Object run in another thread to load images asynchronously
class PageLoader : public QObject
{
    Q_OBJECT
public:
    PageLoader();
    void setPageVector(QVector<Page>* _pageVector);
    void setPageComboBox(QComboBox* _pageComboBox);
public slots:
    void prepare(const QString path); // Load pages without read images
    void loadImages(int pageNumber); // Load images for this page and its neighbour pages
private:
    void loadPage(int pageNumber); // Load one page
    QVector<Page>* pageVector;
    QComboBox* pageComboBox;
    Decompress decom;
    QVector<QString> nameList;
    QVector<int> pageLoaded; // Pages whose image is loaded
    int totalPages;
};

#endif // LOADPAGETHREAD_H
