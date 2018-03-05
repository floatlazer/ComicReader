#include "pageloader.h"
#include <QDebug>

PageLoader::PageLoader()
{}

void PageLoader::doLoadPages(const QString &path)
{
    qDebug()<<"doLoadPages";
    int totalPages = 52;
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
    }
}

void PageLoader::setPageVector(QVector<Page>* _pageVector){pageVector = _pageVector;}

void PageLoader::setPageComboBox(QComboBox* _pageComboBox){pageComboBox = _pageComboBox;}

