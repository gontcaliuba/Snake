#ifndef SIZE_H
#define SIZE_H


class Size
{
    int width, height;

public:
    Size();
    Size(int w, int h);
    Size(const Size &s);

    void setWH(int W, int H);
    void setWH(const Size &s);
    void setW(int W);
    void setH(int H);

    int getW() const;
    int getH() const;

};

#endif // SIZE_H
