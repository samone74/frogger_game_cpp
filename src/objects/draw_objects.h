#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

struct Color
{
  int red;
  int green;
  int blue;
  int transparency;
};

struct Rectangle {
  int x;
  int y;
  int width;
  int height;
};

struct DrawObject{
  Color color{0,0,0,255};
  Rectangle rectangle{0,0,0,0};
  int layer=0;
  bool fill = true;
};

#endif //DRAWOBJECT_H
