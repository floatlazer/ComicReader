#include "pageloader.h"
#include <QDebug>

PageLoader::PageLoader()
{}

void PageLoader::doLoadPages(const QString &path)
{
    qDebug()<<"doLoadPages";
   /* int totalPages = 52;
    pageVector->resize(totalPages);
    int n = 1;
    for(auto i = pageVector->begin(); i < pageVector->end(); i++)
    {
        QString number = QString("%1").arg(n, 3, 10, QChar('0'));
        QString p = path + "/"+ number+".png";
        i->setImage(*(new QImage(p)));
        i->setPageNumber(i-pageVector->begin()+1);
        pageComboBox->addItem(QString("%1 / %2").arg(i-pageVector->begin()+1).arg(totalPages));
        qDebug()<<p;
        n++;
        i->setLoaded(true);
    }*/
    decom.setPath(path);
    decom.decFiles();
    qDebug()<<"number in archive"<<decom.getEntryNumber();
    pageVector->resize(decom.getEntryNumber());
    for(auto i = pageVector->begin(); i < pageVector->end(); i++)
    {
        if(i == pageVector->begin())
            decom.getFiles(false); //buffer in this
        else
            decom.getFiles(true); //buffer in this

        QImage* img = new QImage();
        img->loadFromData(decom.getBuffer(),decom.getEntrySize());
        i->setImage(*img);
        i->setPageNumber(i-pageVector->begin()+1);
        pageComboBox->addItem(QString("%1 / %2").arg(i-pageVector->begin()+1).arg(decom.getEntryNumber()));
        i->setLoaded(true);
        qDebug()<<"Load image"<<i->getPageNumber();
    }
}

void PageLoader::setPageVector(QVector<Page>* _pageVector){pageVector = _pageVector;}

void PageLoader::setPageComboBox(QComboBox* _pageComboBox){pageComboBox = _pageComboBox;}

