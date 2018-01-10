#ifndef COMICREADER_H
#define COMICREADER_H

#include <QMainWindow>

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
    void loadAndShowImage(QString fileName);
    void createActions();
    QImage currentImage;
    QPixmap currentPixmap;
    void prevPage();
    void nextPage();
};

#endif // COMICREADER_H
