#ifndef COMICREADER_H
#define COMICREADER_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include <QComboBox>
#include <QThread>
#include "page.h"
#include "pageloader.h"
#include "imageprocess.h"

namespace Ui {
class ComicReader;
}

class ComicReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComicReader(QWidget *parent = 0);
    ~ComicReader();
    QVector<Page> pageVector; // The vector of loaded pages

signals:
    void preparePages(const QString& path); // signal to start loading pages without images
    void loadImages(int pageNumber); // signal to load images for this page and its neighbour pages
    void imageToFactor(double scaleFactor, int pageNumber);
    void imageToWindow(QSize size, int pageNumber);

public slots:
    void loadPages();

private:
    Ui::ComicReader *ui;
    // Actions
    void createActions();
    void updateActions();
    // Images
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
    void normalSize();
    void fitToWindow();
    void triggerDoublePage();
    void scaleImageToWindow();
    bool isFirstPage;

    QVector<Page>::Iterator pageIterator;
    QPixmap currentPixmap;
    QLabel* centerLabel;
    QScrollArea* centerScrollArea;
    QComboBox pageComboBox; // comboBox to show page number
    double scaleFactor;
    int pageNumber;

    // QAction
    QAction* openAct;
    QAction* prevAct;
    QAction* nextAct;
    QAction* zoomInAct;
    QAction* zoomOutAct;
    QAction* normalSizeAct;
    QAction* fitToWindowAct;
    QAction* doublePageAct;

    QString filePath;

    QThread loadPagesThread;
    PageLoader pageLoader;
    QThread imageProcessThread;
    ImageProcess imageProcess;
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual QSize sizeHint() const;
};

#endif // COMICREADER_H
