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
    void startLoadPages(const QString& path); // signal to start loading pages

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
    int zoomCount; // 0 if not zoomed
    int normalIndicator; // 0 if fit to window

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
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual QSize sizeHint() const;
};

#endif // COMICREADER_H
