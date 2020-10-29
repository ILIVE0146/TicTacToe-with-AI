#pragma once
namespace GameEngine{
    class rgba
    {
    private:
        int MainMenuRed;
        int MainMenuGreen;
        int MainMenuBlue;
        int Xred,Xblue,Xgreen;
        int Ored,Oblue,Ogreen;
    public:
        int getMainMenuR();
        int getMainMenuG();
        int getMainMenuB();
        int getXR();
        int getXG();
        int getXB();
        int getOR();
        int getOG();
        int getOB();
        rgba();
        rgba(bool hello);
    };
}