#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    private:
        int width;
        int height;
    public:
        Rectangle(int w = 0, int h = 0);
        int area();
};

#endif
