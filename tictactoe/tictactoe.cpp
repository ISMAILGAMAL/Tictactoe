#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Ai.cpp"

using namespace std;

const int WIDTH = 2000, HEIGHT = 2000;
const int VERTICAL_LINE_WIDTH = WIDTH / 60, VERTICAL_LINE_HEIGHT = HEIGHT / 1.1;
const int HORIZONTAL_LINE_WIDTH = WIDTH / 1.1, HORIZONTAL_LINE_HEIGHT = HEIGHT / 60;
const int CHARACTER_SIZE = WIDTH / 3;
const bool ai_first = true;

struct Board {
    vector<int> board;
    int player = 1;
    int turn = 0;

    // board constructor that initializes the board to a 9 sized vector fiiled with "empty" strings.
    Board() : board(9, 0) {}

    // Update the board with the move
    void play_move(int move) {
        if (board[move] == 0) {
            board[move] = player;
            if (player == 1) player = -1;
            else player = 1;
            turn++;
        }
    }

    // Draw the board
    void render_board(sf::RenderWindow& window, sf::Font font) {
        // Draw vertical lines
        for (int i = 1; i <= 2; i++) {
            sf::RectangleShape line(sf::Vector2f(VERTICAL_LINE_WIDTH, VERTICAL_LINE_HEIGHT));
            line.setPosition(i * (WIDTH / 3), HEIGHT / 22);
            line.setFillColor(sf::Color::Black);
            window.draw(line);
        }
        // draw horizontal line
        for (int i = 1; i <= 2; i++) {
            sf::RectangleShape line(sf::Vector2f(HORIZONTAL_LINE_WIDTH, HORIZONTAL_LINE_HEIGHT));
            line.setPosition(WIDTH / 22, i * (HEIGHT / 3));
            line.setFillColor(sf::Color::Black);
            window.draw(line);
        }
        // Draw the characters (X and O) on the board
        for (int i = 0; i < 9; i++) {
            sf::Text text;
            text.setCharacterSize(CHARACTER_SIZE);
            text.setFont(font);
            text.setFillColor(sf::Color::Black);

            if (board[i] == 1 || board[i] == -1) {
                if (board[i] == 1)
                    text.setString("X");
                else
                    text.setString("O");
                text.setPosition((i % 3) * (WIDTH / 3) + WIDTH / 18, (i / 3) * (HEIGHT / 3) - HEIGHT / 22);
                window.draw(text);
            }
        }
    }

    /* Convert mouse position to board coordinates.
        Input: sf::vector2i mousePos -> the position of the mouse
        Output: int -> the index of the cell in the board */
    int GetCellIndex(sf::Vector2i mousePos) {
        int row = mousePos.y / (HEIGHT / 3);
        int col = mousePos.x / (WIDTH / 3);
        return col + row * 3;
    }

    // Restarts the game by resetting all of the board's member variables.
    void restart() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            for (int i = 0; i < 9; i++) {
                board[i] = 0;
            }
            turn = 0;
            player = 1;
        }
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ew3a el X O");

    window.setFramerateLimit(30);

    sf::Font font;
    // Loading the font that we will use for the text (X and O)
    if (!font.loadFromFile("D:\\CourseStuff\\SP project\\tictactoe\\Arial.ttf")) {
        cerr << "Error loading default font!" << endl;
        return 0;
    }

    Board board;
    Ai ai;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // check if mouse pressed
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Get the mouse position
                    if (board.turn % 2 == ai_first) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        int index = board.GetCellIndex(mousePos);
                        board.play_move(index);
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        if (board.turn % 2 == !ai_first) {
            int move = ai.minimax(board.board, board.turn, board.player);         
            board.play_move(move);
        }

        string winner = CheckWinner(board.board, board.turn);
        if (winner != "Not Finished") {
            if (winner == "Tie") cout << "Tie" << endl;
            else cout << winner << " WINS!!!" << endl;
        }

        board.render_board(window, font);
        board.restart();

        window.display();
    }
    return 0;
}