#include "filebrowser.h"
#include "ui_filebrowser.h"


FileBrowser::FileBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileBrowser)
{
    ui->setupUi(this);
    QString myPath;
    dirmodel=new QFileSystemModel(this);
    dirmodel->setRootPath(QDir::currentPath());
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setModel(dirmodel);
    for(int i=1;i<dirmodel->columnCount();i++)
    {
        ui->treeView->hideColumn(i);
    }

    filemodel=new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setRootPath(myPath);
    ui->listView->setModel(filemodel);

    this->setFixedWidth(598);
    this->setFixedHeight(477);
}

FileBrowser::~FileBrowser()
{
    delete ui;
}

void FileBrowser::on_pushButton_2_clicked()
{
    this->close();
}

void FileBrowser::on_treeView_clicked(QModelIndex index)
{
    QString myPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filemodel->setRootPath(myPath));
}


void FileBrowser::on_listView_clicked(QModelIndex index)
{
    const QString Path = filemodel->fileInfo(index).fileName();
    ui->textBrowser->setText(Path);
    const QString Type = filemodel->fileInfo(index).suffix();
    ui->textBrowser_2->setText(Type);
}


void FileBrowser::on_pushButton_clicked()
{
     //probleme ici
    this->close();
}
