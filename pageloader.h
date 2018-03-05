#ifndef LOADPAGETHREAD_H
#define LOADPAGETHREAD_H
#include "page.h"
#include <QComboBox>
#include <QVector>

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
};

#endif // LOADPAGETHREAD_H
