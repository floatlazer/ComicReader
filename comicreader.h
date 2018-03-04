#ifndef COMICREADER_H
#define COMICREADER_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include <QMouseEvent>
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
    void open();
    void prevPage();
    void nextPage();
    void triggerSideLabel();
    void normalSize();
    void fitToWindow();
    void triggerDoublePage();
    void scaleImageToWindow();
    bool isFirstPage;

    QVector<Page> pageVector; // The vector of loaded pages
    QVector<Page>::Iterator pageIterator;
    QPixmap currentPixmap;
    QLabel* centerLabel;
    QScrollArea* centerScrollArea;
    QLabel* sideLabel;
    bool isShowSideLabel;
    double scaleFactor;
    int zoomCount; // 0 if not zoomed
    // QAction
    QAction* openAct;
    QAction* prevAct;
    QAction* nextAct;
    QAction* zoomInAct;
    QAction* zoomOutAct;
    QAction* triggerAct;
    QAction* normalSizeAct;
    QAction* fitToWindowAct;
    QAction* doublePageAct;
    QString fileName;

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual QSize sizeHint() const;
    virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // COMICREADER_H
