#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#define ENTER_KEY 13  //dont change these values
#define ESCAPE_KEY 27 //dont change these values
#define DELETE_KEY 8  //dont change these values
namespace GameEngine{
    class TextBox{
        public:
            TextBox();
            TextBox(int size,sf::Color,bool select);
            void deleteLastChar();
            void setFont(sf::Font &font);
            void setPosition(sf::Vector2f pos);
            void setLimit(bool ToF, int limit);
            void setSelected(bool sel);
            bool getSelected();
            std::string getText();
            void drawTo(sf::RenderWindow &window);
            void setLimit(bool ToF);
            void typedOn(sf::Event input);
            void inputLogic(int charTyped);
        private:
            sf::Text textBox;
            std::ostringstream text;
            bool isSelected = false;
            int limit;
            bool hasLimit = false;
    };
}