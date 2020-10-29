#include "rgba.hpp"
namespace GameEngine{
    rgba::rgba(){
        this->MainMenuRed = 142;
        this->MainMenuGreen = 237;
        this->MainMenuBlue = 210;
        this->Xred = 250;
        this->Xgreen = 181;
        this->Xblue = 127;
        this->Ored = 127;
        this->Ogreen = 197;
        this->Oblue = 250;
    }
    rgba::rgba(bool hello){
        this->MainMenuRed = 89;
        this->MainMenuGreen = 151;
        this->MainMenuBlue = 255;
        this->Xred = 252;
        this->Xgreen = 78;
        this->Xblue = 170;
        this->Ored = 117;
        this->Ogreen = 78;
        this->Oblue = 170;
    }
    int rgba::getMainMenuR(){
        return this->MainMenuRed;
    }
    int rgba::getMainMenuG(){
        return this->MainMenuGreen;
    }
    int rgba::getMainMenuB(){
        return this->MainMenuBlue;
    }
    int rgba::getXR(){
        return this->Xred;
    }
    int rgba::getXG(){
        return this->Xgreen;
    }
    int rgba::getXB(){
        return this->Xblue;
    }
    int rgba::getOR(){
        return this->Ored;
    }
    int rgba::getOB(){
        return this->Oblue;
    }
    int rgba::getOG(){
        return this->Ogreen;
    }
}