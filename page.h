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
    unsigned int getPageNumber();
    int getMode();
    // Setter
    void setImage(QImage* _image);
    void setPageNumber(unsigned int number);
private:
    QImage* image;
    unsigned int pageNumber;
    void initParams();
};

#endif // PAGE_H
