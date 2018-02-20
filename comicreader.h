#ifndef COMICREADER_H
#define COMICREADER_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include "page.h"

namespace Ui {
class ComicReader;
}

class ComicReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComicReader(QWidget *parent = 0);
    ~ComicReader();

private:
    Ui::ComicReader *ui;
    // Actions
    void createActions();
    void updateActions();
    // Images
    void loadPages();
    void setPage();
    void zoomIn();
    void zoomOut();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void freePageVector();
    // Control
    void prevPage();
    void nextPage();
    void triggerSideLabel();
    void normalSize();
    void fitToWindow();

    QVector<Page> pageVector; // The vector of loaded pages
    QVector<Page>::Iterator pageIterator;
    QPixmap currentPixmap;
    QLabel* centerLabel;
    double scaleFactor;
    QScrollArea* centerScrollArea;
    QLabel* sideLabel;
    bool isShowSideLabel;
    // QAction
    QAction* prevAct;
    QAction* nextAct;
    QAction* zoomInAct;
    QAction* zoomOutAct;
    QAction* triggerAct;
    QAction* normalSizeAct;
    QAction* fitToWindowAct;
protected:
    virtual void resizeEvent(QResizeEvent *event);
};

#endif // COMICREADER_H
