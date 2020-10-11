#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class imageCheck
{
public:
    vector<string> fileName;
    imageCheck()
    {
        fileName.push_back(MAIN_MENU_TITLE_FILEPATH);
        fileName.push_back(MAIN_MENU_PLAY_BUTTON);
        fileName.push_back(MAIN_MENU_PLAY_BUTTON_OUTER);
        fileName.push_back(FELT_FRONT);
        fileName.push_back(PLAY_BTN_ALTER);
        fileName.push_back(X_WINNING_PIECE_FILEPATH);
        fileName.push_back(O_WINNING_PIECE_FILEPATH);
        fileName.push_back(PLAY_BUTTON);
        fileName.push_back(PAUSE_BUTTON);
        fileName.push_back(X_PIECE_FILEPATH);
        fileName.push_back(O_PIECE_FILEPATH);
        fileName.push_back(resume_button);
        fileName.push_back(Home_button);
        fileName.push_back(GRID_SPRITE_FILEPATH);
    }

    void check_image_exist()
    {
        for (unsigned int i = 0; i < fileName.size(); i++)
        {
            std::ifstream infile(fileName[i]);
            if (!infile.good())
            {
                cout << "Some image files are missing" << endl << fileName[i] << endl;
                exit(0); // exit
            }
        }
        cout<<"Image files check finished"<<endl;
    }
};
