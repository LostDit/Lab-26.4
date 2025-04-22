#include <iostream>
#include <string>
#include <algorithm>

class Window {
    int x, y, width, height;

    void adjust() {
        // Вариант 1: с использованием std::min и std::max
        x = std::max(0, std::min(x, 80 - width));
        y = std::max(0, std::min(y, 50 - height));
    }
public:
    Window(int x, int y, int w, int h)
        : x(x), y(y), width(std::max(0, w)), height(std::max(0, h)) {
        adjust();
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
        adjust();
        std::cout << "Moved to (" << x << "," << y << ")\n";
    }

    void resize(int w, int h) {
        width = std::max(0, w);
        height = std::max(0, h);
        adjust();
        std::cout << "Resized to " << width << "x" << height << "\n";
    }

    void display() const {
        for (int y_ = 0; y_ < 50; ++y_) {
            for (int x_ = 0; x_ < 80; ++x_) {
                bool inX = x_ >= x && x_ < x + width;
                bool inY = y_ >= y && y_ < y + height;
                std::cout << (inX && inY ? '1' : '0');
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Window window(0, 0, 10, 10);
    std::string command;
    while (true) {
        std::cout << "Enter command move/resize/display/close: ";
        std::getline(std::cin, command);
        if (command == "move") {
            int dx, dy;
            std::cin >> dx >> dy;
            std::cin.ignore();
            window.move(dx, dy);
        } else if (command == "resize") {
            int w, h;
            std::cin >> w >> h;
            std::cin.ignore();
            window.resize(w, h);
        } else if (command == "display") {
            window.display();
        } else if (command == "close") {
            break;
        }
    }
}