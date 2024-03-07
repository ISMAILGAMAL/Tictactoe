#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

const int square_size = 300;

struct O {
    Vector2f xy;
    CircleShape shape;
    O(Vector2f XY) : xy(XY) {
        shape.setRadius(50);
        shape.setFillColor(Color::Black);
        shape.setOutlineThickness(20);
        shape.setOutlineColor(Color::White);
        shape.setPosition(xy);
        shape.setOrigin(50, 50);
    }
    void update(float x, float y) {
        xy = Vector2f(x, y);
        shape.setPosition(xy);
    }
};
struct X {
    Vector2f xy;
    RectangleShape shape1, shape2;
    X(Vector2f XY) : xy(XY) {
        shape1.setSize(Vector2f(20, 100));
        shape2.setSize(Vector2f(20, 100));
        shape1.setRotation(45);
        shape2.setRotation(-45);
        shape1.setFillColor(Color::White);
        shape2.setFillColor(Color::White);
        shape1.setOrigin(10, 50);
        shape2.setOrigin(10, 50);
        shape1.setPosition(XY);
        shape2.setPosition(XY);
    }
    void update(float x, float y) {
        xy = Vector2f(x, y);
        shape1.setPosition(xy);
        shape2.setPosition(xy);
    }
};
int main() {
    RenderWindow window(VideoMode(900, 900), "XO");
    RectangleShape squares[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            squares[i][j].setSize(Vector2f(295, 295));
            squares[i][j].setPosition(i * 300, j * 300);
            squares[i][j].setFillColor(Color::Black);
        }
    }
    vector<O> v;
    for (int i = 0; i < 9; i++)
        v.push_back(O(Vector2f(-1000, 1000)));
    vector<X> vv;
    for (int i = 0; i < 9; i++)
        vv.push_back(X(Vector2f(-1000, 1000)));
    int round = 1;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (squares[i][j].getGlobalBounds().contains(mousePosFloat)) {
                            if (round % 2 == 0) {
                                for (int k = 0; k < 9; k++) {
                                    if (v[k].xy == Vector2f(-1000, 1000)) {
                                        v[k].update((i * 300) + 150, (j * 300) + 150);
                                        break;
                                    }
                                }
                            }
                            else {
                                for (int k = 0; k < 9; k++) {
                                    if (vv[k].xy == Vector2f(-1000, 1000)) {
                                        vv[k].update((i * 300) + 150, (j * 300) + 150);
                                        break;
                                    }
                                }
                            }                       
                        }
                    }
                }
                round++;
            }
        }
        window.clear(Color::White);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                window.draw(squares[i][j]);
            }
        }
        for (int i = 0; i < 9; i++)
            window.draw(v[i].shape);
        for (int i = 0; i < 9; i++) {
            window.draw(vv[i].shape1);
            window.draw(vv[i].shape2);
        }
        window.display();
    }
    return 0;
}