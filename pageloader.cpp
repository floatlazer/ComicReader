#include "pageloader.h"
#include <QDebug>

PageLoader::PageLoader()
{}

void PageLoader::doLoadPages(const QString &path)
{
    qDebug()<<"doLoadPages";
    nameList.clear(); // Clear for now
    decom.setPath(path);
    decom.decFiles(nameList, totalPages);
    qDebug()<<"number in archive"<<totalPages;
    pageVector->resize(totalPages);
    for(auto i = pageVector->begin(); i < pageVector->end(); i++)
    {
        decom.getFiles(nameList[i-pageVector->begin()].toStdString().c_str()); //buffer in this
        QImage* img = new QImage();
        img->loadFromData(decom.getBuffer(),decom.getEntrySize());
        i->setImage(*img);
        i->setPageNumber(i-pageVector->begin()+1);
        pageComboBox->addItem(QString("%1 / %2").arg(i-pageVector->begin()+1).arg(totalPages));
        i->setLoaded(true);
        qDebug()<<"Load image"<<i->getPageNumber();
    }
}

void PageLoader::setPageVector(QVector<Page>* _pageVector){pageVector = _pageVector;}

void PageLoader::setPageComboBox(QComboBox* _pageComboBox){pageComboBox = _pageComboBox;}

