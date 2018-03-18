#ifndef PAGE_H
#define PAGE_H
#include <QImage>
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
    QImage getImage();
    unsigned int getPageNumber();
    int isLoaded();
    // Setter
    void setImage(QImage _image);
    void setPageNumber(unsigned int number);
    void setLoaded(int _loaded);
private:
    QImage image;
    unsigned int pageNumber;
    void initParams();
    QAtomicInt loaded; // Whether the page has been loaded
};

#endif // PAGE_H
