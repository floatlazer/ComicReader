#include "comicreader.h"
#include "ui_comicreader.h"

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader),
    centerLabel(new QLabel)
{
    ui->setupUi(this);
    centerScrollArea = ui->centerScrollArea;
    sideLabel = ui->sideLabel;
    scaleFactor = 1.0;
    centerLabel->setScaledContents(true);
    centerScrollArea->setWidget(centerLabel);
    centerLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored); // We can resize the label as we wish

    centerScrollArea->setWidgetResizable(false); // Scroll area will not resize the widget to fill itself
    createActions();
    sideLabel->setVisible(false);
    loadPages();
    setPage();
    //normalSize(); // Adjust label size to the normal size of the image
    fitToWindow();
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

void ComicReader::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void ComicReader::setPage()
{
    // Enable actions
    zoomInAct->setEnabled(true);
    zoomOutAct->setEnabled(true);
    // Convert image
    currentPixmap.convertFromImage(*(pageIterator->getImage()));
    centerLabel->setPixmap(currentPixmap);
    // Scale image
    /*if (normalSizeAct->isChecked())
    {
        scaleImage(1.0); // keep the old scaleFactor
        //centerLabel->adjustSize();
    }*/
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
    //centerLabel->adjustSize();
    scaleFactor = 1.0;
    scaleImage(1.0);
    normalSizeAct->setEnabled(false);
    normalSizeAct->setChecked(true);
    fitToWindowAct->setEnabled(true);
    fitToWindowAct->setChecked(false);
}

void ComicReader::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    double widthFactor = centerScrollArea->contentsRect().width() / centerLabel->pixmap()->width();
    double heightFactor = centerScrollArea->contentsRect().height() / centerLabel->pixmap()->height();
    double factor = widthFactor < heightFactor ? widthFactor : heightFactor; // Take a smaller one
    scaleImage(factor);
    normalSizeAct->setEnabled(true);
    normalSizeAct->setChecked(false);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setChecked(true);
}

void ComicReader::resizeEvent(QResizeEvent *event)
{

}

// Load image and add to pageVector
void ComicReader::loadPages()
{
    pageVector.append(*(new Page(new QImage(":/test/000.jpg"), 1)));
    pageVector.append(*(new Page(new QImage(":/test/001.jpg"), 2)));
    pageVector.append(*(new Page(new QImage(":/test/002.jpg"), 3)));

    pageIterator = pageVector.begin();
}

// Trigger show/hide center label and side label
void ComicReader::triggerSideLabel()
{
    isShowSideLabel = !isShowSideLabel;
    sideLabel->setVisible(isShowSideLabel);
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
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

// Free images in imageVector
void ComicReader::freePageVector()
{
    for(QVector<Page>::Iterator it = pageVector.begin(); it != pageVector.end(); it++)
    {
        it->getImage()->~QImage();
    }
}

