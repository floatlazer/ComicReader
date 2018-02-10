#include "comicreader.h"
#include "ui_comicreader.h"

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    ui->setupUi(this);
    centerLabel = ui->centerLabel;
    sideLabel = ui->sideLabel;
    setUpCenterWidget();
}

ComicReader::~ComicReader()
{
    freeImageVector();
    delete ui;
}

void ComicReader::resizeEvent(QResizeEvent *event)
{
    resizeLabels();
    showImage();
}

void ComicReader::createActions()
{
    // Create column "Control" in the menubar and create a control toolbar
    QMenu * controlMenu = menuBar()->addMenu(tr("&Control"));
    QToolBar *controlToolBar = addToolBar(tr("Control"));

    // Trigger hide/show sideLabel action
    const QIcon triggerIcon = QIcon::fromTheme("document-new", QIcon(":/icon/doubleArrow.png"));
    QAction *triggerAct = new QAction(triggerIcon, tr("&Show/hide side label"), this);
    triggerAct->setStatusTip(tr("Show/hide side label"));
    connect(triggerAct, &QAction::triggered, this, &ComicReader::triggerSideLabel);
    controlMenu->addAction(triggerAct);
    controlToolBar->addAction(triggerAct);

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

// Set up the center widget layout. Default: show only center label, hide side label.
void ComicReader::setUpCenterWidget()
{
    sideLabel->setGeometry(0, 0, 150, ui->centralWidget->height());
    centerLabel->setGeometry(150, 0, ui->centralWidget->width() - 150, ui->centralWidget->height());
    hideSideLabel();
    isShowSideLabel = false;
    createActions();
    loadImages();
    showImage();
}

// Resize side label and center label according to the situation.
void ComicReader::resizeLabels()
{
    int w = ui->centralWidget->size().width();
    int h = ui->centralWidget->size().height();
    sideLabel->resize(150, h); // Alignment is wierd if we dont do this when hiding, dont know why.
    if(isShowSideLabel)
    {
        centerLabel->resize(w - 150, h); // resize central label
    }
    else
    {
        centerLabel->resize(w, h); // resize central label
    }
}

// Trigger show/hide center label and side label
void ComicReader::triggerSideLabel()
{
    if(isShowSideLabel)
    {
        isShowSideLabel = false;
        hideSideLabel();
    }
    else
    {
        isShowSideLabel = true;
        showSideLabel();
    }
    resizeLabels();
    showImage();
}

void ComicReader::showSideLabel()
{
    sideLabel->show();
    centerLabel->move(sideLabel->geometry().topRight()); // Move left top coner of center label to right top conor of sidelabel
}

void ComicReader::hideSideLabel()
{
    sideLabel->hide();
    centerLabel->move(0, 0); // Move left top coner of center label to left top coner of center widget
}

void ComicReader::prevPage()
{
    if(imageIterator != imageVector.begin())
    {
        imageIterator--;
        showImage();
    }
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

