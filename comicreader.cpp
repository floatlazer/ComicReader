#include "comicreader.h"
#include "ui_comicreader.h"

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    ui->setupUi(this);
    centerLabel = ui->label;
    createActions();
    loadImages();
    showImage();
}

ComicReader::~ComicReader()
{
    freeImageVector();
    delete ui;
}

void ComicReader::resizeEvent(QResizeEvent *event)
{
    int w = ui->centralWidget->size().width();
    int h = ui->centralWidget->size().height();
    centerLabel->resize(w,h); // resize center label
    showImage();
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
    int w = centerLabel->size().width();
    int h = centerLabel->size().height();
    centerLabel->setPixmap(currentPixmap.scaled(w, h, Qt::KeepAspectRatio)); // Load image to the label and resize it to the size of label
}

// Load image to imageVector
void ComicReader::loadImages()
{
    imageVector.append(*(new QImage(":/test/000.jpg")));
    imageVector.append(*(new QImage(":/test/001.jpg")));
    imageVector.append(*(new QImage(":/test/002.jpg")));

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
    if(imageIterator < imageVector.end()-1)
    {
        imageIterator++;
        showImage();
    }
}

// Free images in imageVector
void ComicReader::freeImageVector()
{
    for(QVector<QImage>::Iterator it = imageVector.begin(); it != imageVector.end(); it++)
    {
        it->~QImage();
    }
}
