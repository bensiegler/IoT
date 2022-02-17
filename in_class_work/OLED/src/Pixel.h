#pragma once

class Pixel {
    private:
        int x;
        int y;

    public:
        Pixel();

        Pixel(int xCoord, int yCoord) {
            x = xCoord;
            y = yCoord;
        };

        int getX();
        int getY();
};

int Pixel::getX() {
    return x;
}

int Pixel::getY() {
    return y;
}