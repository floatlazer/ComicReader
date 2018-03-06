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
    const QIcon prevIcon = QIcon::fromTheme("document-new", QIcon(":/icon/leftArrow.png"));
    prevAct = new QAction(prevIcon, tr("&Previous page"), this);
    prevAct->setShortcuts(QKeySequence::MoveToPreviousChar);
    prevAct->setStatusTip(tr("Previous page"));
    connect(prevAct, &QAction::triggered, this, &ComicReader::prevPage);
    controlMenu->addAction(prevAct);
    ui->mainToolBar->addAction(prevAct);

    // Next page action
    const QIcon nextIcon = QIcon::fromTheme("document-new", QIcon(":/icon/rightArrow.png"));
    nextAct = new QAction(nextIcon, tr("&Next page"), this);
    nextAct->setShortcuts(QKeySequence::MoveToNextChar);
    nextAct->setStatusTip(tr("Next page"));
    connect(nextAct, &QAction::triggered, this, &ComicReader::nextPage);
    controlMenu->addAction(nextAct);
    ui->mainToolBar->addAction(nextAct);

    // ZoomIn action
    const QIcon zoomInIcon = QIcon::fromTheme("document-new", QIcon(":/icon/zoomIn.png"));
    zoomInAct = new QAction(zoomInIcon, tr("&Zoom in"), this);
    zoomInAct->setShortcuts(QKeySequence::ZoomIn);
    zoomInAct->setStatusTip(tr("Zoom In"));
    connect(zoomInAct, &QAction::triggered, this, &ComicReader::zoomIn);
    viewMenu->addAction(zoomInAct);
    ui->mainToolBar->addAction(zoomInAct);

    // ZoomOut action
    const QIcon zoomOutIcon = QIcon::fromTheme("document-new", QIcon(":/icon/zoomOut.png"));
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
    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ComicReader::fitToWindow);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    // DoublePageMode action
    doublePageAct = viewMenu->addAction(tr("&Double page mode"), this, &ComicReader::triggerDoublePage);
    doublePageAct->setCheckable(true);
    doublePageAct->setShortcut(tr("Ctrl+D"));

    // Set default status
    normalSizeAct->setEnabled(false);
    normalSizeAct->setChecked(false);
    zoomInAct->setEnabled(false);
    zoomOutAct->setEnabled(false);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setChecked(false);
    doublePageAct->setEnabled(false);
    doublePageAct->setChecked(false);
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