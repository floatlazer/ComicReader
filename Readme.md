# ComicReader

Developped by **Xuan Zhang** and **Zhufeng Li**

## Overview

A comic book reader written in Qt who can read and navigate .cbr or .cbz files (or any archive of images).

**There are three threads in the application:**

* A GUI thread whos shows images and manages user interactions.
* A page loading thread to read images asychronously with memory control.
* A image processing thread to resize images asynchronously.

We use [unarr](https://github.com/zeniko/unarr) library to uncompress archive because Qt functions for uncompressing are very limited.

**The application supports:**

* Select archive file by using a file browser


* Go to previous page or go to next page


* Skip to a certain page by using a combobox for page selecting
* Zoom in and zoom out
* Fit image to window or show the normal size of image
* Double page mode

***Note:*** Imageprocessing thread is currently not working, we continue to developing it.

## Compilation

### Prerequistes

* Qt 5.10
* Qt creator 4.5.0
* A C compiler (clang, gcc, etc,  to compile *unarr* library )
* GNU Make (To build *unarr* library)

## Build

***Note:*** This application is only tested on mac OSX.

### Build unarr library

We add *unarr* as a submodule of the project, to get the source files, in project folder:

```bash
git submodule init
git submodule update
```

Build the library:

```bash
cd unarr/
make build=release
```

### Build the application

Open the project in Qt creator and build normally. Building as release can improve the performance.

## Architecture description

#### Classes

There are five classes:

* ComicReader: Inherits from QMainWindow, this is the GUI thread.
* Page: A abstraction for one page in a comicbook, including information such as page number, image or scale factor
* PageLoader: Class for loading image, provides worker functions in page loading thread
* ImageProcess: Class for image processing, provides worker functions in resizing thread
* Decompress: C++ wrapper class for *unarr*, provides functions to read images from archive

#### Data storage

We store pages (images) in a [QVector](http://doc.qt.io/qt-5/qvector.html)<Page>, the vector is created in ComicReader class and it is shared with PageLoader class and ImageProcess class.

#### Page loading thread

Every time the user choose a new page, page loading will load current page, 9 pages before current page and 10 pages after current pages to prepare pages before user moves to neighbor pages

#### Communication between threads

Qt use [signals and slots](http://doc.qt.io/archives/qt-4.8/signalsandslots.html) to communicate between threads.

After user choosing a archive via open, ```ComicReader``` will send a *preparePages* signal which contains the path of the archive. This signal is connected to the slot *prepare* in ```PageLoader``` which is a function to initialize page vector. 

```c++
connect(this, &ComicReader::preparePages, &pageLoader, &PageLoader::prepare);
...
emit preparePages(filePath);
```

We don't use a reponse signal to inform GUI thread that pages are ready. Instead, page loading thread will modify a member in ```Page``` and GUI thread will keep checking ths member to know if the work is done.

```c++
while(pageVector.empty()) QThread::msleep(10); // Wait to load the first element
```

The same, when user navigates to a certain page, ```ComicReader``` will send a *loadImages* signal which contains current page number. The signal is connected to the slot *loadImages* in ```PageLoader``` which will load and release images.

#### Memory management

As a comic book may have many pages, we don't want to load them all in memory.

```PageLoader``` class maintains a vector to keep track of for which pages images have been loaded. Every time a new page is requested, page loading thread will first load all images in range [currentPage-9, currentPage+10] and then release all other images. This can considerably constrain the memory using when the archive is of large size.

Image memory releasing is very easy in Qt because images uses [implicit sharing](http://doc.qt.io/qt-5/implicit-sharing.html), so that an image is automatically released when no pointer is pointing at it.

```c++
QImage dockImage;
...
pageVector->operator [](p-1).setImage(dockImage); // Redirect image pointer to release image memory
```
