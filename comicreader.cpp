#include "comicreader.h"
#include "ui_comicreader.h"
#include <QScreen>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    ui->setupUi(this);
    centerLabel = ui->centerLabel;
    scaleFactor = 1.0;
    zoomCount = 0;
    isFirstPage = true;
    centerScrollArea = ui->centerScrollArea;
    sideLabel = ui->sideLabel;
    centerLabel->setScaledContents(true);
    sideLabel->setVisible(false);
    createActions();
    loadPages();
    fitToWindowAct->setChecked(true);
    normalSizeAct->setEnabled(true);
    setPage();
    isFirstPage = false;
    adjustSize();
}

ComicReader::~ComicReader()
{
    freePageVector();
    delete ui;
}

void ComicReader::createActions()
{
    // Create column "Control" and "View" in the menubar and create a control toolbar
    QMenu * controlMenu = menuBar()->addMenu(tr("&Control"));
    QMenu * viewMenu = menuBar()->addMenu(tr("&View"));
    QToolBar *controlToolBar = addToolBar(tr("Control"));

    // Open action
    openAct = new QAction (tr("&Open"), this);
    openAct->setStatusTip(tr("Open"));
    connect(openAct, &QAction::triggered, this, &ComicReader::open);
    controlMenu->addAction(openAct);

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

    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &ComicReader::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setCheckable(true);
    viewMenu->addSeparator();

    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ComicReader::fitToWindow);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    // Set default status
    normalSizeAct->setEnabled(false);
    normalSizeAct->setChecked(false);
    zoomInAct->setEnabled(false);
    zoomOutAct->setEnabled(false);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setChecked(false);
}

// Note that use check will take effect after actions
void ComicReader::updateActions()
{
    if(normalSizeAct->isEnabled())
    {
        normalSizeAct->setEnabled(false);
        fitToWindowAct->setEnabled(true);
        fitToWindowAct->setChecked(false);
    }
    else
    {
        fitToWindowAct->setEnabled(false);
        normalSizeAct->setEnabled(true);
        normalSizeAct->setChecked(false);
    }
}

void ComicReader::setPage()
{
    qDebug()<<"setPage"<<"FitToWindow"<<fitToWindowAct->isChecked();
    // Enable actions
    zoomInAct->setEnabled(true);
    zoomOutAct->setEnabled(true);
    // Convert image
    currentPixmap.convertFromImage(*(pageIterator->getImage()));
    scaleImage(1.0); // Keep scaleFactor
    if(fitToWindowAct->isChecked() && zoomCount == 0 && ! isFirstPage) // fitToWindow and not zoomed, keep fit to window
    {
        scaleImageToWindow();
    }
}

void ComicReader::zoomIn()
{
    double factor = 1.25;
    scaleImage(factor);
    zoomCount++;
}

void ComicReader::zoomOut()
{
    double factor = 0.8;
    scaleImage(factor);
    zoomCount--;
}

// Scale image, multiply the current scaleFactor by factor. Every image scaling function should use thise method.
void ComicReader::scaleImage(double factor)
{
    scaleFactor *= factor;
    qDebug()<<"scaleImage"<<scaleFactor;
    centerLabel->setPixmap(currentPixmap.scaled(currentPixmap.size()*scaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    centerLabel->adjustSize();
    ui->scrollAreaWidgetContents->adjustSize();
    adjustScrollBar(centerScrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(centerScrollArea->verticalScrollBar(), factor);
    // Disable zooming if too large or too small
    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ComicReader::normalSize()
{
    qDebug()<<"normalSize";
    //centerLabel->adjustSize();
    scaleImage(1/scaleFactor);
    updateActions();
}

void ComicReader::fitToWindow()
{
    qDebug()<<"fitToWindow";
    scaleImageToWindow();
    zoomCount = 0;
    updateActions();
}

void ComicReader::scaleImageToWindow()
{
    centerLabel->setPixmap(currentPixmap.scaled(ui->centralWidget->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    centerLabel->adjustSize();
    ui->scrollAreaWidgetContents->adjustSize();
    // Update scaleFactor
    double factorWidth = double(centerLabel->pixmap()->width())/double(currentPixmap.width());
    double factorHeight = double(centerLabel->pixmap()->height())/double(currentPixmap.height());
    scaleFactor = factorWidth < factorHeight ? factorWidth : factorHeight;
    qDebug()<<"scaleImageToWindow"<<scaleFactor;

}

// Resize image when resize the window
void ComicReader::resizeEvent(QResizeEvent *event)
{
    if(fitToWindowAct->isChecked() && zoomCount == 0)
    {
        qDebug()<<"resizeEvent"<<"mainWindow"<<size();
        scaleImageToWindow();
    }
}

QSize ComicReader::sizeHint() const
{
    return centerLabel->sizeHint()+QSize(0, ui->mainToolBar->height()+ui->statusBar->height()+11); // Dont know why add 11
}


// Load image and add to pageVector
void ComicReader::loadPages()
{
    pageVector.append(*(new Page(new QImage(":/test/000.jpg"), 2)));
    pageVector.append(*(new Page(new QImage(":/test/002.jpg"), 3)));
    pageVector.append(*(new Page(new QImage(":/test/001.jpg"), 1)));

    pageIterator = pageVector.begin();
}


// Trigger show/hide center label and side label
void ComicReader::triggerSideLabel()
{
    isShowSideLabel = !isShowSideLabel;
    sideLabel->setVisible(isShowSideLabel);
}

void ComicReader::open()
{
    // Select a png, jpg, cbr or cbz
    qDebug()<<"open"<<QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
               QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
               tr("Image Files (*.png *.jpg *.cbr *.cbz)"));
    qDebug()<<"Filename"<<fileName;
}

void ComicReader::prevPage()
{
    if(pageIterator != pageVector.begin())
    {
        pageIterator--;
        setPage();
    }
}

void ComicReader::nextPage()
{
    if(pageIterator < pageVector.end()-1)
    {
        pageIterator++;
        setPage();
    }
}

void ComicReader::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

// Free images in imageVector
void ComicReader::freePageVector()
{
    for(QVector<Page>::Iterator it = pageVector.begin(); it != pageVector.end(); it++)
    {
        it->getImage()->~QImage();
    }
}

