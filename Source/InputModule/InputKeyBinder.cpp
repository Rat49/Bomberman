#include "InputKeyBinder.hpp"
#include "Common/Logs.hpp"

InputKeyBinder::InputKeyBinder()
{
    keyMap["A"]         = sf::Keyboard::A;
    keyMap["B"]         = sf::Keyboard::B;
    keyMap["C"]         = sf::Keyboard::C;
    keyMap["D"]         = sf::Keyboard::D;
    keyMap["E"]         = sf::Keyboard::E;
    keyMap["F"]         = sf::Keyboard::F;
    keyMap["G"]         = sf::Keyboard::G;
    keyMap["H"]         = sf::Keyboard::H;
    keyMap["I"]         = sf::Keyboard::I;
    keyMap["J"]         = sf::Keyboard::J;
    keyMap["K"]         = sf::Keyboard::K;
    keyMap["L"]         = sf::Keyboard::L;
    keyMap["M"]         = sf::Keyboard::M;
    keyMap["N"]         = sf::Keyboard::N;
    keyMap["O"]         = sf::Keyboard::O;
    keyMap["P"]         = sf::Keyboard::P;
    keyMap["Q"]         = sf::Keyboard::Q;
    keyMap["R"]         = sf::Keyboard::R;
    keyMap["S"]         = sf::Keyboard::S;
    keyMap["T"]         = sf::Keyboard::T;
    keyMap["U"]         = sf::Keyboard::U;
    keyMap["V"]         = sf::Keyboard::V;
    keyMap["W"]         = sf::Keyboard::W;
    keyMap["X"]         = sf::Keyboard::X;
    keyMap["Y"]         = sf::Keyboard::Y;
    keyMap["Z"]         = sf::Keyboard::Z;
    keyMap["Num0"]      = sf::Keyboard::Num0;
    keyMap["Num1"]      = sf::Keyboard::Num1;
    keyMap["Num2"]      = sf::Keyboard::Num2;
    keyMap["Num3"]      = sf::Keyboard::Num3;
    keyMap["Num4"]      = sf::Keyboard::Num4;
    keyMap["Num5"]      = sf::Keyboard::Num5;
    keyMap["Num6"]      = sf::Keyboard::Num6;
    keyMap["Num7"]      = sf::Keyboard::Num7;
    keyMap["Num8"]      = sf::Keyboard::Num8;
    keyMap["Num9"]      = sf::Keyboard::Num9;
    keyMap["Escape"]    = sf::Keyboard::Escape;
    keyMap["Space"]     = sf::Keyboard::Space;
    keyMap["Enter"]     = sf::Keyboard::Enter;
    keyMap["Tab"]       = sf::Keyboard::Tab;
    keyMap["Backspace"] = sf::Keyboard::Backspace;
    keyMap["Up"]        = sf::Keyboard::Up;
    keyMap["Down"]      = sf::Keyboard::Down;
    keyMap["Left"]      = sf::Keyboard::Left;
    keyMap["Right"]     = sf::Keyboard::Right;
    keyMap["LShift"]    = sf::Keyboard::LShift;
    keyMap["RShift"]    = sf::Keyboard::RShift;
    keyMap["LControl"]  = sf::Keyboard::LControl;
    keyMap["RControl"]  = sf::Keyboard::RControl;
    keyMap["LAlt"]      = sf::Keyboard::LAlt;
    keyMap["RAlt"]      = sf::Keyboard::RAlt;
    keyMap["F1"]        = sf::Keyboard::F1;
    keyMap["F2"]        = sf::Keyboard::F2;
    keyMap["F3"]        = sf::Keyboard::F3;
    keyMap["F4"]        = sf::Keyboard::F4;
    keyMap["F5"]        = sf::Keyboard::F5;
    keyMap["F6"]        = sf::Keyboard::F6;
    keyMap["F7"]        = sf::Keyboard::F7;
    keyMap["F8"]        = sf::Keyboard::F8;
    keyMap["F9"]        = sf::Keyboard::F9;
    keyMap["F10"]       = sf::Keyboard::F10;
    keyMap["F11"]       = sf::Keyboard::F11;
    keyMap["F12"]       = sf::Keyboard::F12;
    keyMap["PageUp"]    = sf::Keyboard::PageUp;
    keyMap["PageDown"]  = sf::Keyboard::PageDown;
    keyMap["Home"]      = sf::Keyboard::Home;
    keyMap["End"]       = sf::Keyboard::End;
    keyMap["Insert"]    = sf::Keyboard::Insert;
    keyMap["Delete"]    = sf::Keyboard::Delete;
}

sf::Keyboard::Key InputKeyBinder::GetButton(const std::string& buttonString) const
{
    auto it = keyMap.find(buttonString);
    if (it != keyMap.end())
    {
        return it->second;
    }
    LOG("Invalid key: $", buttonString);
    return sf::Keyboard::Unknown;
}