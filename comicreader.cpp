#include "comicreader.h"
#include "ui_comicreader.h"

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    ui->setupUi(this);
    loadImages();
    createActions();    
}

ComicReader::~ComicReader()
{
    freeImageVector();
    delete ui;
}

void ComicReader::createActions()
{
    // Create column "Control" in the menubar and create a control toolbar
    QMenu * controlMenu = menuBar()->addMenu(tr("&Control"));
    QToolBar *controlToolBar = addToolBar(tr("Control"));

    // Previous page action
    const QIcon prevIcon = QIcon::fromTheme("document-new", QIcon(":/icon/leftArrow.png"));
    QAction *prevAct = new QAction(prevIcon, tr("&Previous page"), this);
    prevAct->setShortcuts(QKeySequence::MoveToPreviousChar);
    prevAct->setStatusTip(tr("Previous page"));
    connect(prevAct, &QAction::triggered, this, &ComicReader::prevPage);
    controlMenu->addAction(prevAct);
    controlToolBar->addAction(prevAct);

    // Next page action
    const QIcon nextIcon = QIcon::fromTheme("document-new", QIcon(":/icon/rightArrow.png"));
    QAction *nextAct = new QAction(nextIcon, tr("&Next page"), this);
    nextAct->setShortcuts(QKeySequence::MoveToNextChar);
    nextAct->setStatusTip(tr("Next page"));
    connect(nextAct, &QAction::triggered, this, &ComicReader::nextPage);
    controlMenu->addAction(nextAct);
    controlToolBar->addAction(nextAct);
}


void ComicReader::showImage()
{
    currentPixmap.convertFromImage(*imageIterator);
    ui->label->setPixmap(currentPixmap); // Load image to the label
}

// Load image to imageVector
void ComicReader::loadImages()
{
    imageVector.push_back(new QImage(":/test/000.jpg"));
    imageVector.push_back(new QImage(":/test/001.jpg"));
    imageIterator = imageVector.begin();
}

void ComicReader::prevPage()
{
    if(imageIterator != imageVector.begin())
    {
        imageIterator--;
        showImage();}
    }

void ComicReader::nextPage()
{
    if(imageIterator != imageVector.end())
    {
        imageIterator++;
        showImage();
    }
}

// Free image vector and its images
void ComicReader::freeImageVector()
{
    for(QVector::Iterator it = imageVector.begin(); it != imageVector.end(); it++)
    {
        delete it;
    }
}
