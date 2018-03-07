#include "pageloader.h"
#include <QDebug>

PageLoader::PageLoader()
{}

void PageLoader::prepare(const QString path)
{
    qDebug()<<"Prepare to load pages"<<path;
    nameList.clear();
    pageLoaded.clear();
    decom.setPath(path);
    decom.decFiles(nameList, totalPages);
    qDebug()<<"number in archive"<<totalPages;
    pageVector->resize(totalPages);
    for(auto i = pageVector->begin(); i < pageVector->end(); i++)
    {
        pageComboBox->addItem(QString("%1 / %2").arg(i-pageVector->begin()+1).arg(totalPages));
    }
}

void PageLoader::loadImages(int pageNumber)
{
    qDebug()<<"loadImages";
    // Load images [pageNumber - 2, pageNumber + 3]
    int loadOrder[6] = {0, 1, -1, 2, -2, 3};
    for(int i = 0; i < 6; i++)
    {
        int p = pageNumber + loadOrder[i]; // page to be loaded
        if(p >=1 && p <= totalPages)
        {
            loadPage(p);
        }
    }

    // Clean images loaded that are not in [pageNumber - 2, pageNumber + 3]
    for(int i = 0; i < pageLoaded.size(); i++)
    {
        int p = pageLoaded[i];
        QImage dockImage;
        if(p < pageNumber-2 || p > pageNumber + 3)
        {
            pageVector->operator [](p-1).setLoaded(false);
            pageVector->operator [](p-1).setImage(dockImage); // Redirect image pointer to release image memory
            pageLoaded.remove(i--);
            qDebug()<<"Release image"<<p<<"pages loaded"<<pageLoaded.size();
        }
    }
}

void PageLoader::loadPage(int pageNumber)
{
    if(!pageVector->operator [](pageNumber - 1).isLoaded())
    {
        decom.getFiles(nameList[pageNumber-1].toStdString().c_str()); //buffer in this
        QImage* img = new QImage();
        img->loadFromData(decom.getBuffer(),decom.getEntrySize());
        pageVector->operator [](pageNumber - 1).setImage(*img);
        delete img; // Delete this pointer to avoid problem of memory release of shared pointer
        pageVector->operator [](pageNumber - 1).setLoaded(true);
        pageLoaded.push_back(pageNumber); // Add the page go pageLoaded vector
        qDebug()<<"Load image"<<pageNumber;
    }
}

void PageLoader::setPageVector(QVector<Page>* _pageVector){pageVector = _pageVector;}

void PageLoader::setPageComboBox(QComboBox* _pageComboBox){pageComboBox = _pageComboBox;}

