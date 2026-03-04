#ifndef COLOR_H
#define COLOR_H
struct Color {
    int red;
    int green;
    int blue;
    int transparency;
};

constexpr Color RED{255,0,0,255};
constexpr Color GREEN{0,124,0,255};
constexpr Color BLUE{0,0,255,255};
constexpr Color WHITE{255,255,255,255};
constexpr Color BLACK{0,0,0,0};
constexpr Color GRAY{124,124,124,255};
constexpr Color FROGGREEN(0,224,0,255);

#endif //COLOR_H
