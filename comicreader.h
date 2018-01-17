#ifndef COMICREADER_H
#define COMICREADER_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
namespace Ui {
class ComicReader;
}

class ComicReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComicReader(QWidget *parent = 0);
    ~ComicReader();

public slots:
    void prevPage();
    void nextPage();

private:
    Ui::ComicReader *ui;
    void createActions();
    void loadImages();
    void showImage();
    void freeImageVector();
    QVector<QImage> imageVector; // The vector of loaded images
    QVector<QImage>::Iterator imageIterator;
    QPixmap currentPixmap;
    QLabel* centerLabel;

protected:
    virtual void resizeEvent(QResizeEvent *event); // Functiion called when we resize the mainWindow
};

#endif // COMICREADER_H
