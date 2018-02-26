#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QDialog>
#include <QFileSystemModel>
#include <QtCore>
#include <QtGui>
#include <QTextBrowser>

namespace Ui {
class FileBrowser;
}

class FileBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit FileBrowser(QWidget *parent = 0);
    ~FileBrowser();

private slots:
    void on_pushButton_2_clicked();
    void on_treeView_clicked(QModelIndex index);
    void on_listView_clicked(QModelIndex index);
    void on_pushButton_clicked();

private:
    Ui::FileBrowser *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
};

#endif // FILEBROWSER_H
