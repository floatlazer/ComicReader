#ifndef PAGE_H
#define PAGE_H
#include<QImage>
// Class contains image and information of a page in a comic book
class Page
{
public:
    Page();
    Page(QImage* _image, unsigned int number);
    // Getter
    QImage* getImage();
    int getHorizontalScrollBarValue();
    int getVerticalScrollBarValue();
    int isZoomed();
    unsigned int getPageNumber();
    double getZoomFactor();
    // Setter
    void setImage(QImage* _image);
    void setZoomOut();
    void setZoomIn();
    void setZoomFactor(double factor);
    void setPageNumber(unsigned int number);
private:
    QImage* image;
    unsigned int pageNumber;
    double zoomFactor;
    int zoomCount; // Zoom in +1, zoom out -1
    int horizontalScrollBarValue;
    int verticalScrollBarValue;
    void initParams();
};

#endif // PAGE_H
