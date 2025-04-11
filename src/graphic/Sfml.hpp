/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Sfml.hpp
*/

#ifndef SFML_H
    #define SFML_H
    #define INTO_PERCENT(x) (x / 100)
    #define FROM_PERCENT(x) (x * 100)

    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window/Event.hpp>
    #include "IGraphic.hpp"

class SFML : public arcade::IGraphic {
    public:
        SFML();
        ~SFML();
        event_t getEvent(void) override;
        void display(data_t data) override;
        void createEntities(std::vector<entity_t> entities);
        void createTexts(std::vector<text_t> texts);
    private:
        sf::RenderWindow window_;
};

const std::map<event_e, sf::Keyboard::Key> KEYBOARD_EVENT_LINK =
{
    {A_KEY_ESC, sf::Keyboard::Escape},
    {A_KEY_SPACE, sf::Keyboard::Space},
    {A_KEY_DEL, sf::Keyboard::Delete},
    {A_KEY_ENTER, sf::Keyboard::Enter},
    {A_KEY_TAB, sf::Keyboard::Tab},
    {A_KEY_CTRL, sf::Keyboard::LControl},
    {A_KEY_CTRL, sf::Keyboard::RControl},
    {A_KEY_SHIFT, sf::Keyboard::LShift},
    {A_KEY_SHIFT, sf::Keyboard::RShift},
    {A_KEY_ALT, sf::Keyboard::LAlt},
    {A_KEY_ALT, sf::Keyboard::RAlt},
    {A_KEY_UP, sf::Keyboard::Up},
    {A_KEY_DOWN, sf::Keyboard::Down},
    {A_KEY_LEFT, sf::Keyboard::Left},
    {A_KEY_RIGHT, sf::Keyboard::Right},
    {A_KEY_ENTER, sf::Keyboard::Enter},
    {A_KEY_A, sf::Keyboard::A},
    {A_KEY_B, sf::Keyboard::B},
    {A_KEY_C, sf::Keyboard::C},
    {A_KEY_D, sf::Keyboard::D},
    {A_KEY_E, sf::Keyboard::E},
    {A_KEY_F, sf::Keyboard::F},
    {A_KEY_G, sf::Keyboard::G},
    {A_KEY_H, sf::Keyboard::H},
    {A_KEY_I, sf::Keyboard::I},
    {A_KEY_J, sf::Keyboard::J},
    {A_KEY_K, sf::Keyboard::K},
    {A_KEY_L, sf::Keyboard::L},
    {A_KEY_M, sf::Keyboard::M},
    {A_KEY_N, sf::Keyboard::N},
    {A_KEY_O, sf::Keyboard::O},
    {A_KEY_P, sf::Keyboard::P},
    {A_KEY_Q, sf::Keyboard::Q},
    {A_KEY_R, sf::Keyboard::R},
    {A_KEY_S, sf::Keyboard::S},
    {A_KEY_T, sf::Keyboard::T},
    {A_KEY_U, sf::Keyboard::U},
    {A_KEY_V, sf::Keyboard::V},
    {A_KEY_W, sf::Keyboard::W},
    {A_KEY_Y, sf::Keyboard::Y},
    {A_KEY_0, sf::Keyboard::Num0},
    {A_KEY_1, sf::Keyboard::Num1},
    {A_KEY_2, sf::Keyboard::Num2},
    {A_KEY_3, sf::Keyboard::Num3},
    {A_KEY_4, sf::Keyboard::Num4},
    {A_KEY_5, sf::Keyboard::Num5},
    {A_KEY_6, sf::Keyboard::Num6},
    {A_KEY_7, sf::Keyboard::Num7},
    {A_KEY_8, sf::Keyboard::Num8},
    {A_KEY_9, sf::Keyboard::Num9},
    {A_KEY_F1, sf::Keyboard::F1},
    {A_KEY_F2, sf::Keyboard::F2},
    {A_KEY_F3, sf::Keyboard::F3},
    {A_KEY_F4, sf::Keyboard::F4},
    {A_KEY_F5, sf::Keyboard::F5},
    {A_KEY_F6, sf::Keyboard::F6},
    {A_KEY_F7, sf::Keyboard::F7},
    {A_KEY_F8, sf::Keyboard::F8},
    {A_KEY_F9, sf::Keyboard::F9},
    {A_KEY_F10, sf::Keyboard::F10},
    {A_KEY_F11, sf::Keyboard::F11},
    {A_KEY_F12, sf::Keyboard::F12}
};

const std::map<event_e, sf::Mouse::Button> MOUSE_EVENT_LINK =
{
    {A_MOUSE_LEFT, sf::Mouse::Left},
    {A_MOUSE_RIGHT, sf::Mouse::Right}
};

const sf::VideoMode RESOLUTION = {1000, 1000};

extern "C" arcade::IGraphic* makeGraphic();

#endif /* SFML_H */