#include <iostream>
#include <string>
#include <regex>

void renderBoard();
bool checkWinner();
bool boardFull();

bool player = false;
int8_t states[9];

int main() {
    // -1 means empty, 0 means 'O', 1 means 'X'
    for (int8_t& state : states)
        state = -1;

    while (true) {
        std::cout << "Player: " << (player ? "X" : "O") << '\n';
        renderBoard();

        std::string input;
        uint8_t x, y;
        while (true) {
            std::cout << "Please enter the coords you want your move to go like this \"x;y\":";
            std::cin >> input;

            std::regex pat { "[1-3];[1-3]" };
            if (!std::regex_search(input, pat)) {
                std::cout << "Please enter valid coordinates between 1 and 3 like \"x;y\"";
                continue;
            }

            x = std::stoi(input.substr(0, input.find(';'))) - 1;
            y = std::stoi(input.substr(input.find(';') + 1, input.length() - 1)) - 1;

            if (states[x + y * 3] == -1)
                break;

            std::cout << "Tis filed has already been selected\n";
        }

        states[x + y * 3] = player;
        player = !player;

        if (checkWinner()) {
            renderBoard();
            std::cout << "Player " << (player ? "O" : "X") << " won the game!";
            return 0;
        }

        if (boardFull()) {
            renderBoard();
            std::cout << "The board is full. Nobody won.";
            return 0;
        }
    }

}

void renderBoard() {
    for (int i = 0; i < 9; ++i) {
        if (i != 0 && i % 3 == 0)
            std::cout << "\n-----------\n";

        char sign = ' ';
        if (states[i] == 0)
            sign = 'O';
        if (states[i] == 1)
            sign = 'X';

        std::cout << " " << sign << " ";

        if (i != 2 && i != 5 && i != 8)
            std::cout << '|';
    }
    std::cout << '\n';
}

bool checkWinner() {
    return (
            ((states[0] == 0 && states[1] == 0 && states[2] == 0) || (states[0] == 1 && states[1] == 1 && states[2] == 1)) ||
            ((states[3] == 0 && states[4] == 0 && states[5] == 0) || (states[3] == 1 && states[4] == 1 && states[5] == 1)) ||
            ((states[6] == 0 && states[7] == 0 && states[8] == 0) || (states[6] == 1 && states[7] == 1 && states[8] == 1)) ||

            ((states[0] == 0 && states[3] == 0 && states[6] == 0) || (states[0] == 1 && states[3] == 1 && states[6] == 1)) ||
            ((states[1] == 0 && states[4] == 0 && states[7] == 0) || (states[1] == 1 && states[4] == 1 && states[7] == 1)) ||
            ((states[2] == 0 && states[5] == 0 && states[8] == 0) || (states[2] == 1 && states[5] == 1 && states[8] == 1)) ||

            ((states[0] == 0 && states[4] == 0 && states[8] == 0) || (states[0] == 1 && states[4] == 1 && states[8] == 1)) ||
            ((states[2] == 0 && states[4] == 0 && states[6] == 0) || (states[2] == 1 && states[4] == 1 && states[6] == 1))
    );
}

bool boardFull() {
    bool full = true;
    for (int8_t& state : states) {
        if (state == -1) {
            full = false;
            break;
        }
    }
    return full;
}