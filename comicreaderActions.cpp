#include "comicreader.h"
#include "ui_comicreader.h"

void ComicReader::createActions()
{
    // Create column "Control" and "View" in the menubar and create a control toolbar
    QMenu * controlMenu = menuBar()->addMenu(tr("&Control"));
    QMenu * viewMenu = menuBar()->addMenu(tr("&View"));

    // Open action
    openAct = new QAction (tr("&Open"), this);
    openAct->setStatusTip(tr("Open"));
    connect(openAct, &QAction::triggered, this, &ComicReader::open);
    controlMenu->addAction(openAct);

    // Previous page action
    const QIcon prevIcon = QIcon::fromTheme("document-new", QIcon(":/icon/left-arrow.png"));
    prevAct = new QAction(prevIcon, tr("&Previous page"), this);
    prevAct->setShortcuts(QKeySequence::MoveToPreviousChar);
    prevAct->setStatusTip(tr("Previous page"));
    connect(prevAct, &QAction::triggered, this, &ComicReader::prevPage);
    controlMenu->addAction(prevAct);
    ui->mainToolBar->addAction(prevAct);

    // Next page action
    const QIcon nextIcon = QIcon::fromTheme("document-new", QIcon(":/icon/right-arrow.png"));
    nextAct = new QAction(nextIcon, tr("&Next page"), this);
    nextAct->setShortcuts(QKeySequence::MoveToNextChar);
    nextAct->setStatusTip(tr("Next page"));
    connect(nextAct, &QAction::triggered, this, &ComicReader::nextPage);
    controlMenu->addAction(nextAct);
    ui->mainToolBar->addAction(nextAct);

    // ZoomIn action
    const QIcon zoomInIcon = QIcon::fromTheme("document-new", QIcon(":/icon/ZoomIn.png"));
    zoomInAct = new QAction(zoomInIcon, tr("&Zoom in"), this);
    zoomInAct->setShortcuts(QKeySequence::ZoomIn);
    zoomInAct->setStatusTip(tr("Zoom In"));
    connect(zoomInAct, &QAction::triggered, this, &ComicReader::zoomIn);
    viewMenu->addAction(zoomInAct);
    ui->mainToolBar->addAction(zoomInAct);

    // ZoomOut action
    const QIcon zoomOutIcon = QIcon::fromTheme("document-new", QIcon(":/icon/ZoomOut.png"));
    zoomOutAct = new QAction(zoomOutIcon, tr("&Zoom out"), this);
    zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
    zoomOutAct->setStatusTip(tr("Zoom Out"));
    connect(zoomOutAct, &QAction::triggered, this, &ComicReader::zoomOut);
    viewMenu->addAction(zoomOutAct);
    ui->mainToolBar->addAction(zoomOutAct);

    // NormalSize action
    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &ComicReader::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setCheckable(true);
    viewMenu->addSeparator();

    // FitToWindow action
    const QIcon fitToWindowIcon = QIcon::fromTheme("Document-new",QIcon(":/icon/Expand.png"));
    fitToWindowAct = new QAction(fitToWindowIcon, tr("&Fit to Window"), this);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    fitToWindowAct->setStatusTip(tr("Fit to Window"));
    connect(fitToWindowAct,&QAction::triggered,this,&ComicReader::fitToWindow);
    viewMenu->addAction(fitToWindowAct);
    ui->mainToolBar->addAction(fitToWindowAct);
    fitToWindowAct->setCheckable(true);

    // DoublePageMode action
    doublePageAct = viewMenu->addAction(tr("&Double page mode"), this, &ComicReader::triggerDoublePage);
    doublePageAct->setCheckable(true);
    doublePageAct->setShortcut(tr("Ctrl+D"));

    // About
    QMenu * about = menuBar()->addMenu(tr("&About"));
    about->addAction(tr("&Comic book reader developped by Xuan Zhang and Zhufeng Li"));

    // Set default status
    normalSizeAct->setEnabled(false);
    normalSizeAct->setChecked(true);
    zoomInAct->setEnabled(false);
    zoomOutAct->setEnabled(false);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setChecked(true);
    doublePageAct->setEnabled(false);
    doublePageAct->setChecked(false);
}

// Note that use check will take effect after actions
void ComicReader::updateActions()
{
    if(currentPixmap.size() == centerLabel->pixmap()->size())
    {
        normalSizeAct->setEnabled(false);
        normalSizeAct->setChecked(true);
    }
    else
    {
        normalSizeAct->setEnabled(true);
        normalSizeAct->setChecked(false);
    }
    if(size().width()==sizeHint().width() || size().height() == sizeHint().height())
    {
        fitToWindowAct->setEnabled(false);
        fitToWindowAct->setChecked(true);
    }
    else
    {
        fitToWindowAct->setEnabled(true);
        fitToWindowAct->setChecked(false);
    }
}
