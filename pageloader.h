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
    void doLoadPages(const QString &path);
private:
    QVector<Page>* pageVector;
    QComboBox* pageComboBox;
    Decompress decom;
};

#endif // LOADPAGETHREAD_H
