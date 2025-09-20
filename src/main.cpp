#include "raylib.h"

#include <array>
#include <string>

namespace {

constexpr int kScreenWidth = 960;
constexpr int kScreenHeight = 540;

enum class ScreenState {
    Menu,
    Gameplay,
    Settings,
    Exit
};

struct Button {
    Rectangle rect{};
    const char* label = "";
};

Color BackgroundColorForScreen(ScreenState state) {
    switch (state) {
        case ScreenState::Menu:
            return {20, 26, 66, 255};
        case ScreenState::Gameplay:
            return {24, 80, 24, 255};
        case ScreenState::Settings:
            return {52, 31, 79, 255};
        case ScreenState::Exit:
        default:
            return BLACK;
    }
}

bool IsHovered(const Button& button, const Vector2& mousePosition) {
    return CheckCollisionPointRec(mousePosition, button.rect);
}

void DrawButton(const Button& button, const Vector2& mousePosition) {
    const bool hovered = IsHovered(button, mousePosition);
    const Color baseColor = hovered ? Color{248, 196, 113, 255} : Color{244, 208, 63, 255};
    const Color borderColor = hovered ? Color{235, 152, 78, 255} : Color{212, 172, 13, 255};

    DrawRectangleRounded(button.rect, 0.25f, 8, baseColor);
    DrawRectangleRoundedLines(button.rect, 0.25f, 8, 4.0f, borderColor);

    const int fontSize = 24;
    const Vector2 textSize = MeasureTextEx(GetFontDefault(), button.label, static_cast<float>(fontSize), 1.0f);
    const Vector2 textPosition{
        button.rect.x + (button.rect.width - textSize.x) / 2.0f,
        button.rect.y + (button.rect.height - textSize.y) / 2.0f
    };

    DrawTextEx(GetFontDefault(), button.label, textPosition, static_cast<float>(fontSize), 1.0f, DARKGRAY);
}

void DrawTitle() {
    const char* title = "Tower Defense";
    const int fontSize = 48;
    const Vector2 textSize = MeasureTextEx(GetFontDefault(), title, static_cast<float>(fontSize), 2.0f);
    const Vector2 textPosition{
        (kScreenWidth - textSize.x) / 2.0f,
        80.0f
    };

    DrawTextEx(GetFontDefault(), title, textPosition, static_cast<float>(fontSize), 2.0f, RAYWHITE);
}

void DrawSubTitle(const std::string& text) {
    const int fontSize = 24;
    const Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), static_cast<float>(fontSize), 1.0f);
    const Vector2 textPosition{
        (kScreenWidth - textSize.x) / 2.0f,
        150.0f
    };

    DrawTextEx(GetFontDefault(), text.c_str(), textPosition, static_cast<float>(fontSize), 1.0f, RAYWHITE);
}

void DrawBackButton(const Button& button, const Vector2& mousePosition, ScreenState& state) {
    DrawButton(button, mousePosition);
    if (IsHovered(button, mousePosition) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        state = ScreenState::Menu;
    }
}

void DrawGameplayPlaceholder(const Button& backButton, const Vector2& mousePosition, ScreenState& state) {
    DrawSubTitle("Gameplay prototype coming soon");
    DrawBackButton(backButton, mousePosition, state);
}

void DrawSettingsPlaceholder(const Button& backButton, const Vector2& mousePosition, ScreenState& state) {
    DrawSubTitle("Settings panel under construction");
    DrawBackButton(backButton, mousePosition, state);
}

void DrawMenu(std::array<Button, 3>& buttons, ScreenState& state, const Vector2& mousePosition) {
    DrawSubTitle("Build your defenses and hold the line!");

    for (size_t i = 0; i < buttons.size(); ++i) {
        DrawButton(buttons[i], mousePosition);

        if (IsHovered(buttons[i], mousePosition) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            switch (i) {
                case 0:
                    state = ScreenState::Gameplay;
                    return;
                case 1:
                    state = ScreenState::Settings;
                    return;
                case 2:
                    state = ScreenState::Exit;
                    return;
                default:
                    break;
            }
        }
    }
}

}  // namespace

int main() {
    InitWindow(kScreenWidth, kScreenHeight, "Tower Defense");
    SetTargetFPS(60);

    ScreenState state = ScreenState::Menu;
    std::array<Button, 3> menuButtons{
        Button{Rectangle{kScreenWidth / 2.0f - 120.0f, 220.0f, 240.0f, 60.0f}, "Play"},
        Button{Rectangle{kScreenWidth / 2.0f - 120.0f, 300.0f, 240.0f, 60.0f}, "Settings"},
        Button{Rectangle{kScreenWidth / 2.0f - 120.0f, 380.0f, 240.0f, 60.0f}, "Quit"}
    };

    const Button backButton{Rectangle{30.0f, static_cast<float>(kScreenHeight) - 90.0f, 150.0f, 50.0f}, "Back"};

    while (!WindowShouldClose() && state != ScreenState::Exit) {
        const Vector2 mousePosition = GetMousePosition();

        BeginDrawing();
        ClearBackground(BackgroundColorForScreen(state));

        DrawTitle();

        switch (state) {
            case ScreenState::Menu:
                DrawMenu(menuButtons, state, mousePosition);
                break;
            case ScreenState::Gameplay:
                DrawGameplayPlaceholder(backButton, mousePosition, state);
                break;
            case ScreenState::Settings:
                DrawSettingsPlaceholder(backButton, mousePosition, state);
                break;
            case ScreenState::Exit:
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
