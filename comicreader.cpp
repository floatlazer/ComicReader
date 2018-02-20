#include "comicreader.h"
#include "ui_comicreader.h"

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    ui->setupUi(this);
    centerLabel = ui->centerLabel;
    centerScrollArea = ui->centerScrollArea;
    sideLabel = ui->sideLabel;
    scaleFactor = 1.0;
    centerLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    centerLabel->setScaledContents(true);
    createActions();
    sideLabel->setVisible(false);
    loadImages();
    setImage();
    normalSize();
}

ComicReader::~ComicReader()
{
    freeImageVector();
    delete ui;
}

void ComicReader::createActions()
{
    // Create column "Control" and "View" in the menubar and create a control toolbar
    QMenu * controlMenu = menuBar()->addMenu(tr("&Control"));
    QMenu * viewMenu = menuBar()->addMenu(tr("&View"));
    QToolBar *controlToolBar = addToolBar(tr("Control"));

    // Trigger hide/show sideLabel action
    const QIcon triggerIcon = QIcon::fromTheme("document-new", QIcon(":/icon/doubleArrow.png"));
    triggerAct = new QAction(triggerIcon, tr("&Show/hide side label"), this);
    triggerAct->setStatusTip(tr("Show/hide side label"));
    connect(triggerAct, &QAction::triggered, this, &ComicReader::triggerSideLabel);
    viewMenu->addAction(triggerAct);
    controlToolBar->addAction(triggerAct);

    // Previous page action
    const QIcon prevIcon = QIcon::fromTheme("document-new", QIcon(":/icon/leftArrow.png"));
    prevAct = new QAction(prevIcon, tr("&Previous page"), this);
    prevAct->setShortcuts(QKeySequence::MoveToPreviousChar);
    prevAct->setStatusTip(tr("Previous page"));
    connect(prevAct, &QAction::triggered, this, &ComicReader::prevPage);
    controlMenu->addAction(prevAct);
    controlToolBar->addAction(prevAct);

    // Next page action
    const QIcon nextIcon = QIcon::fromTheme("document-new", QIcon(":/icon/rightArrow.png"));
    nextAct = new QAction(nextIcon, tr("&Next page"), this);
    nextAct->setShortcuts(QKeySequence::MoveToNextChar);
    nextAct->setStatusTip(tr("Next page"));
    connect(nextAct, &QAction::triggered, this, &ComicReader::nextPage);
    controlMenu->addAction(nextAct);
    controlToolBar->addAction(nextAct);

    // ZoomIn action
    const QIcon zoomInIcon = QIcon::fromTheme("document-new", QIcon(":/icon/zoomIn.png"));
    zoomInAct = new QAction(zoomInIcon, tr("&Zoom in"), this);
    zoomInAct->setShortcuts(QKeySequence::ZoomIn);
    zoomInAct->setStatusTip(tr("Zoom In"));
    connect(zoomInAct, &QAction::triggered, this, &ComicReader::zoomIn);
    viewMenu->addAction(zoomInAct);
    controlToolBar->addAction(zoomInAct);

    // ZoomOut action
    const QIcon zoomOutIcon = QIcon::fromTheme("document-new", QIcon(":/icon/zoomOut.png"));
    zoomOutAct = new QAction(zoomOutIcon, tr("&Zoom out"), this);
    zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
    zoomOutAct->setStatusTip(tr("Zoom Out"));
    connect(zoomOutAct, &QAction::triggered, this, &ComicReader::zoomOut);
    viewMenu->addAction(zoomOutAct);
    controlToolBar->addAction(zoomOutAct);

}

void ComicReader::updateActions()
{

}

void ComicReader::setImage()
{
    currentPixmap.convertFromImage(*imageIterator);
    centerLabel->setPixmap(currentPixmap);
}

void ComicReader::zoomIn()
{
    scaleImage(1.25);
}

void ComicReader::zoomOut()
{
    scaleImage(0.8);
}


void ComicReader::scaleImage(double factor)
{
    Q_ASSERT(centerLabel->pixmap());

    scaleFactor *= factor;
    centerLabel->resize(scaleFactor * centerLabel->pixmap()->size());

    adjustScrollBar(centerScrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(centerScrollArea->verticalScrollBar(), factor);
    // Disable zooming if too large or too small
    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ComicReader::normalSize()
{
    centerLabel->adjustSize();
    scaleFactor = 1.0;
}

void ComicReader::fitToWindow()
{
    //bool fitToWindow = fitToWindowAct->isChecked();
    bool fitToWindow = true;
    centerScrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSize();
    updateActions();
}

// Load image to imageVector
void ComicReader::loadImages()
{
    imageVector.append(*(new QImage(":/test/000.jpg")));
    imageVector.append(*(new QImage(":/test/001.jpg")));
    imageVector.append(*(new QImage(":/test/002.jpg")));

    imageIterator = imageVector.begin();
}

// Trigger show/hide center label and side label
void ComicReader::triggerSideLabel()
{
    isShowSideLabel = !isShowSideLabel;
    sideLabel->setVisible(isShowSideLabel);
}

void ComicReader::prevPage()
{
    if(imageIterator != imageVector.begin())
    {
        imageIterator--;
        setImage();
    }
}

void ComicReader::nextPage()
{
    if(imageIterator < imageVector.end()-1)
    {
        imageIterator++;
        setImage();
    }
}

void ComicReader::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

// Free images in imageVector
void ComicReader::freeImageVector()
{
    for(QVector<QImage>::Iterator it = imageVector.begin(); it != imageVector.end(); it++)
    {
        it->~QImage();
    }
}

