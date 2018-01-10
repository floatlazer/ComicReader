#include "comicreader.h"
#include "ui_comicreader.h"

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    ui->setupUi(this);

    loadAndShowImage(":/test/000.jpg"); // Load and show a test image loaded in the resources
    createActions();
}

ComicReader::~ComicReader()
{
    delete ui;
}

void ComicReader::createActions()
{
    QMenu * mainMenu = menuBar()->addMenu(tr("&Control"));
    QToolBar *mainToolBar = addToolBar(tr("Control"));

    const QIcon prevIcon = QIcon::fromTheme("document-new", QIcon(":/icon/leftArrow.png"));
    QAction *prevAct = new QAction(prevIcon, tr("&Previous page"), this);
    prevAct->setShortcuts(QKeySequence::MoveToPreviousChar);
    prevAct->setStatusTip(tr("Previous page"));
    connect(prevAct, &QAction::triggered, this, &ComicReader::prevPage);
    mainMenu->addAction(prevAct);
    mainToolBar->addAction(prevAct);

    const QIcon nextIcon = QIcon::fromTheme("document-new", QIcon(":/icon/rightArrow.png"));
    QAction *nextAct = new QAction(nextIcon, tr("&Next page"), this);
    nextAct->setShortcuts(QKeySequence::MoveToNextChar);
    nextAct->setStatusTip(tr("Next page"));
    connect(nextAct, &QAction::triggered, this, &ComicReader::nextPage);
    mainMenu->addAction(nextAct);
    mainToolBar->addAction(nextAct);
}


void ComicReader::loadAndShowImage(QString fileName)
{
    currentImage.load(fileName); // Load an image file
    // TODO: Possible image processing goes here...
    currentPixmap.convertFromImage(currentImage);
    ui->label->setPixmap(currentPixmap); // Load image to the label
}

void ComicReader::prevPage()
{
    loadAndShowImage(":/test/000.jpg");
}

void ComicReader::nextPage()
{
    loadAndShowImage(":/test/001.jpg");
}
