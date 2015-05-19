#ifndef MAPPING_H
#define MAPPING_H

#include <core/rect.h>

class Bitmap;

class Mapping
{
public:
    Mapping(double ratio = 0.6);

    void draw(Bitmap *screen, Bitmap *bitmap, const Rect clip);
    void draw(Bitmap *screen, Bitmap *bitmap, const Rect front, const Rect back);

private:
    double m_ratio;
};

#endif