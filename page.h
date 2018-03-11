#ifndef PAGE_H
#define PAGE_H
#include <QImage>
#include <QPixmap>
// Class contains image and information of a page in a comic book
// Note: QImage is implicitly shared so we may call by value instead of its address
class Page
{
public:
    Page();
    //Page(Page& _page);
    Page(QImage _image, unsigned int number);
    Page(unsigned int number);
    ~Page();
    // Getter
    QPixmap getPixmap();
    QImage getImage();
    unsigned int getPageNumber();
    bool isLoaded();
    double getScaled();
    // Setter
    void setPixmap(QPixmap _Pixmap);
    void setImage(QImage _image);
    void setPageNumber(unsigned int number);
    void setLoaded(bool _loaded);
    void setScaled(double factor);
private:
    QImage image;
    QPixmap pixmap;
    double scalefactor;
    unsigned int pageNumber;
    void initParams();
    bool loaded; // Whether the page has been loaded
};

#endif // PAGE_H
