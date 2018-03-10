#include "comicreader.h"
#include "ui_comicreader.h"
#include <QScreen>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPainter>

ComicReader::ComicReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComicReader)
{
    // Set up ui
    ui->setupUi(this);
    ui->mainToolBar->addWidget(&pageComboBox);    // page combo box
    connect(&pageComboBox, QOverload<int>::of(&QComboBox::activated),[=](int index){qDebug()<<"page index change"; pageIterator = pageVector.begin() + index; setPage(); });
    centerLabel = ui->centerLabel;
    centerScrollArea = ui->centerScrollArea;
    // Init params
    scaleFactor = 1.0;
    isFirstPage = true;
    // Create Actions
    createActions();
    doublePageAct->setEnabled(true);

    // Connect pageLoader thread
    pageLoader.setPageVector(&pageVector);
    pageLoader.setPageComboBox(&pageComboBox);
    pageLoader.moveToThread(&loadPagesThread);
    connect(this, &ComicReader::preparePages, &pageLoader, &PageLoader::prepare);
    connect(this, &ComicReader::loadImages, &pageLoader, &PageLoader::loadImages);
    loadPagesThread.start();
    // Open archive
    open();
}

ComicReader::~ComicReader()
{
    pageVector.clear();
    loadPagesThread.terminate();
    loadPagesThread.wait();
    delete ui;
}

void ComicReader::open()
{
    // Clear old comicbook before open new one
    if(!pageVector.isEmpty())
    {
        qDebug() << "Clear old data";
        pageVector.clear();
    }
    if(pageComboBox.count() > 0)
    {
        qDebug()<<"Clear pageComboBox";
        pageComboBox.clear();
    }
    // Select a png, jpg, cbr or cbz
    qDebug()<<"open"<<QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    filePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
               QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
               tr("Image Files (*.png *.jpg *.cbr *.cbz *.rar *.zip *.tar)"));
    // Quit application if nothing is selected
    if(filePath.isEmpty() || filePath == NULL)
    {
        qDebug()<<"cancel";
        exit(0);
    }
    // Load pages without loading images
    loadPages();
    // Show page
    setPage();
    isFirstPage = false;
    adjustSize(); // Adjust window size to the first image
}

// Load pages without loading images
void ComicReader::loadPages()
{
    qDebug()<<"Load Pages";
    emit preparePages(filePath);
    while(pageVector.empty()) QThread::msleep(10); // Wait to load the first element
    qDebug()<<"ok";
    pageIterator=pageVector.begin();
}

void ComicReader::setPage()
{
    qDebug()<<"setPage"<<"FitToWindow"<<fitToWindowAct->isChecked()<<"DoublePageMode"<<doublePageAct->isChecked();
    // Load images for this page and its neighbour pages
    emit loadImages(pageIterator - pageVector.begin() +1);
    // Enable actions
    zoomInAct->setEnabled(true);
    zoomOutAct->setEnabled(true);
    // Check if page is loaded, wait for page loading if not
    while(!pageIterator->isLoaded());
    if(doublePageAct->isChecked() && pageIterator < pageVector.end()-1)
        while(!(pageIterator+1)->isLoaded()); // Wait second page to be loaded
    // Set pixmap
    if(!doublePageAct->isChecked() || pageIterator == pageVector.end()-1)     // Single page mode
        currentPixmap.convertFromImage(pageIterator->getImage());
    else{                  // Double pages mode
        int pageMargin = 30;
        int HEIGHT = qMax(pageIterator->getImage().height(), (pageIterator + 1)->getImage().height());
        int width1 = HEIGHT / pageIterator->getImage().height() * pageIterator->getImage().width();
        int width2 = HEIGHT / (pageIterator+1)->getImage().height() * (pageIterator+1)->getImage().width();
        QPixmap *pixmap=new QPixmap(width1+width2 + pageMargin, HEIGHT);
        pixmap->fill(Qt::transparent);
        currentPixmap = *pixmap;
        // Paint two pix map on one pixmap
        QPainter *painter=new QPainter(&currentPixmap); // New painter
        painter->drawPixmap(0, 0, width1, HEIGHT, QPixmap::fromImage(pageIterator->getImage()));
        painter->drawPixmap(width1 + pageMargin, 0, width2, HEIGHT, QPixmap::fromImage((pageIterator+1)->getImage()));
        painter->~QPainter(); // destroy painter
        delete pixmap; // destroy local pointer
    }

    if(fitToWindowAct->isChecked() && ! isFirstPage) // fitToWindow and not zoomed, keep fit to window
    {
        scaleImageToWindow();
    }
    else
    {
        scaleImage(1.0); // Keep scaleFactor
    }
    // Set pageComboBox
    pageComboBox.setCurrentIndex(pageIterator - pageVector.begin());
}

void ComicReader::prevPage()
{
    if(!doublePageAct->isChecked() || pageIterator == pageVector.begin()+1)
    {
        if(pageIterator != pageVector.begin())
        {
            pageIterator--;
            setPage();
        }
    }
    else
    {
        if(pageIterator >= pageVector.begin()+2)
        {
            pageIterator-=2;
            setPage();
        }
    }
}

void ComicReader::nextPage()
{
    if(!doublePageAct->isChecked()){
        if(pageIterator < pageVector.end()-1)
        {
            pageIterator++;
            setPage();
        }
    }
    else
    {
        if(pageIterator < pageVector.end()-2)
        {
            pageIterator+=2;
            setPage();
        }
    }
}

void ComicReader::zoomIn()
{
    double factor = 1.25;
    scaleImage(factor);
    updateActions();
}

void ComicReader::zoomOut()
{
    double factor = 0.8;
    scaleImage(factor);
    updateActions();
}

// Scale image, multiply the current scaleFactor by factor. Every image scaling function should use this method.
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

void ComicReader::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
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
    updateActions();
}

void ComicReader::triggerDoublePage()
{
    qDebug()<<"triggerDoublePage";
    setPage();
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
    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

// Resize image when resize the window
void ComicReader::resizeEvent(QResizeEvent *event)
{
    if(fitToWindowAct->isChecked())
    {
        qDebug()<<"resizeEvent"<<"mainWindow"<<size();
        scaleImageToWindow();
    }
    updateActions();
}

QSize ComicReader::sizeHint() const
{
    return centerLabel->sizeHint()+QSize(0, ui->mainToolBar->height()+ui->statusBar->height() + ui->menuBar->height());
}



