#include "textBox.hpp"
namespace GameEngine{
    TextBox::TextBox(int size,sf::Color color,bool selected){
        this->textBox.setCharacterSize(size);
        this->textBox.setFillColor(color);
        this->isSelected = selected;
        if(selected){
            this->textBox.setString("_");
        }else{
            this->textBox.setString("");
        }
    }
    void TextBox::typedOn(sf::Event input){
        if(this->isSelected){
            int charTyped = input.text.unicode;
            
            if(charTyped>0 && charTyped< 128 ){
                std::cout<<charTyped<<std::endl;
                if(this->hasLimit){
                    if(text.str().length() <= this->limit){
                        this->inputLogic(charTyped);
                    }
                    else if(text.str().length() > limit && charTyped == DELETE_KEY){
                        this->deleteLastChar();
                    }
                }
                else{
                    this->inputLogic(charTyped);
                }
            }
        }
    }
    void TextBox::setFont(sf::Font &font){
        this->textBox.setFont(font);
    }
    void TextBox::setPosition(sf::Vector2f pos){
        this->textBox.setPosition(pos);
    }
    void TextBox::setSelected(bool sel){
        this->isSelected = sel;
        if(!sel){
            std::string t = this->text.str();
            std::string newT = "";
            for(int i=0;i<t.length() - 1; i++){
                newT += t[i];
            }
            this->textBox.setString(newT);
        }
    }
    std::string TextBox::getText(){
        return this->text.str();
    }
    void TextBox::drawTo(sf::RenderWindow &window){
        window.draw(this->textBox);
    }
    void TextBox::setLimit(bool ToF){
        this->hasLimit = ToF;
    }
    void TextBox::setLimit(bool ToF, int limit){
        this->hasLimit = ToF;
        this->limit = limit - 1;
    }
    void TextBox::deleteLastChar(){
        std::string t = this->text.str();
        std::string newT = "";
        for(int i=0;i<t.length(); i++){
            newT += t[i];
        }
        this->text.str("");
        this->text << newT;
        this->textBox.setString(text.str());
    }
    void TextBox::inputLogic(int charTyped){
        if(charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped != DELETE_KEY){
            this->text << static_cast<char>(charTyped);
            this->textBox.setString(this->text.str() + "_");
        }
        else if(charTyped == DELETE_KEY){
            if(text.str().length()>0){
                this->deleteLastChar();
            }
            this->textBox.setString(this->text.str() + "_");
        }
        else if(charTyped == ENTER_KEY){
            this->isSelected = false;
        }
    }
    bool TextBox::getSelected(){
        return this->isSelected;
    }
}