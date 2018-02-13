#include "filebrowser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileBrowser w;
    w.show();

    return a.exec();
}
