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
    QVector<Page> pageVector;
    QComboBox pageComboBox;
public slots:
    void doLoadPages(const QString &path);
//private:

};

#endif // LOADPAGETHREAD_H
