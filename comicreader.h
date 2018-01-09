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

private slots:
    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

private:
    Ui::ComicReader *ui;
    void loadAndShowImage(QString fileName);
    QImage currentImage;
    QPixmap currentPixmap;
};

#endif // COMICREADER_H
