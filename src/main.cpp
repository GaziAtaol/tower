#include <iostream>
#include <array>
#include <string_view>
#include <limits>

namespace {
void printHeader() {
    std::cout << "============================\n"
              << "    Tower Defense Menu\n"
              << "============================\n";
}

void printMenuOptions() {
    constexpr std::array<std::string_view, 3> options{"Play", "Settings", "Quit"};

    for (std::size_t index = 0; index < options.size(); ++index) {
        std::cout << index + 1 << ") " << options[index] << '\n';
    }
    std::cout << "\nSelect an option: ";
}

bool handleChoice(int choice) {
    switch (choice) {
        case 1:
            std::cout << "Starting the game... (placeholder)\n";
            break;
        case 2:
            std::cout << "Opening settings... (placeholder)\n";
            break;
        case 3:
            std::cout << "Exiting. Goodbye!\n";
            return false;
        default:
            std::cout << "Invalid option. Please choose 1, 2, or 3.\n";
            break;
    }
    return true;
}
}

int main() {
    bool running = true;

    while (running) {
        printHeader();
        printMenuOptions();

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cout << "Input error. Please enter numbers only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        running = handleChoice(choice);

        if (running) {
            std::cout << "\nPress Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
        std::cout << '\n';
    }

    return 0;
}
