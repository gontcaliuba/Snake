#ifndef FIELDIMAGES_H
#define FIELDIMAGES_H

#include <QImage>

enum ImageType
{
    image_field = 0,
    image_port = 1,
    image_wall = 2,
    image_beetle = 3,
    image_snake_bottom_left = 4,
    image_snake_bottom_right = 5,
    image_snake_top_left = 6,
    image_snake_top_right = 7,
    image_snake_hor = 8,
    image_snake_ver = 9,
    image_snake_head_bottom = 10,
    image_snake_head_left = 11,
    image_snake_head_right = 12,
    image_snake_head_top = 13,
    image_snake_tail_bottom = 14,
    image_snake_tail_left = 15,
    image_snake_tail_right = 16,
    image_snake_tail_top = 17,
    image_null = 18

};

class FieldImages
{
public:
    static FieldImages &getInstance()
    {

        static FieldImages field_images;
        return field_images;
    }
    const QImage &getImage(const ImageType &imType)
    {
        return image[imType];
    }

    static int getImageSize()
    {
        return 25;
    }

protected:
    FieldImages()
    {
        image[0].load(":images/images/field.png");
        image[1].load(":images/images/port.png");
        image[2].load(":images/images/wall.png");
        image[3].load(":images/images/beetle.png");
        image[4].load(":snake/images/snake/body/snake_bottom_left.png");
        image[5].load(":snake/images/snake/body/snake_bottom_right.png");
        image[6].load(":snake/images/snake/body/snake_top_left.png");
        image[7].load(":snake/images/snake/body/snake_top_right.png");
        image[8].load(":snake/images/snake/body/snake_hor.png");
        image[9].load(":snake/images/snake/body/snake_ver.png");
        image[10].load(":snake/images/snake/head/snake_head_bottom.png");
        image[11].load(":snake/images/snake/head/snake_head_left.png");
        image[12].load(":snake/images/snake/head/snake_head_right.png");
        image[13].load(":snake/images/snake/head/snake_head_top.png");
        image[14].load(":snake/images/snake/tail/snake_tail_bottom.png");
        image[15].load(":snake/images/snake/tail/snake_tail_left.png");
        image[16].load(":snake/images/snake/tail/snake_tail_right.png");
        image[17].load(":snake/images/snake/tail/snake_tail_top.png");

    }
    FieldImages(const FieldImages &);
    FieldImages & operator = (const FieldImages &);

private:
    QImage image[18];
};

#endif // FIELDIMAGES_H
