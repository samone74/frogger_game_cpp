#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H
#include <string>

struct Color {
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

struct DrawObject {
  Color color{0, 0, 0, 255};
  Rectangle rectangle{0, 0, 0, 0};
  int layer = 0;
  bool fill = true;
};

enum class TextID : uint32_t { Score, Lives, Level, Debug };

struct TextDrawObject {
  TextID id; // unique key for caching
  std::string text; // the actual text
  int x;
  int y;
  SDL_Color color;
  int layer = 0;
};


#endif //DRAWOBJECT_H
