#ifndef COMICREADER_H
#define COMICREADER_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>

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
    void loadImages();
    void setImage();
    void zoomIn();
    void zoomOut();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void freeImageVector();
    // Control
    void prevPage();
    void nextPage();
    void triggerSideLabel();
    void normalSize();
    void fitToWindow();

    QVector<QImage> imageVector; // The vector of loaded images
    QVector<QImage>::Iterator imageIterator;
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
};

#endif // COMICREADER_H
