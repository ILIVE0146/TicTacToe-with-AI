#include "options.hpp"
#include "MainMenuState.hpp"

namespace std{
    string getct(){
		string ct;	
		fstream color;
		color.open("colorscheme.txt");	
		getline(color,ct,'\n');
		color.close();
		return ct;
	}
    void changethemevalue(){
        string ct;	
		fstream color;
		color.open("colorscheme.txt");	
		getline(color,ct,'\n');
        if(ct=="true")
            color<<"false";
        else
        {
            color<<"true";
        }
        
		color.close();
    }
}

namespace GameEngine{
    Options::Options(GameDataRef data): _data(data){}
    void Options::Init(){
        this->details.setFont(this->_data->assets.GetFont("Felt"));
        this->details.setCharacterSize(60);
        this->details.setPosition(100,150);
        this->details.setString("CHANGE THEME");
        this->theme.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->theme.setPosition(200,400);
        this->themeText.setFont(this->_data->assets.GetFont("Felt"));
        this->themeText.setPosition(this->theme.getPosition().x + 30,this->theme.getPosition().y + 5);
        this->themeText.setString("CLICK ME");
        this->back.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->back.setPosition(350,825);
        this->backText.setFont(this->_data->assets.GetFont("Felt"));
        this->backText.setPosition(this->back.getPosition().x + 60, this->back.getPosition().y + 5);
        this->backText.setString("BACK");
    }
    void Options::HandleInput(){
        sf::Event event;
        
        while(this->_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                this->_data->window.close();
            }
            else if(this->_data->input.IsSpriteClicked(this->back,sf::Mouse::Left,this->_data->window)){
                this->_data->machine.RemoveState();
            }else if(this->_data->input.IsSpriteClicked(this->theme,sf::Mouse::Left,this->_data->window)){
                // std::ofstream color;
                // color.open("colorscheme.txt");
                // color<<"ASDFADSF";
                // std::string ct = std::getct();
                this->_data->isdefaultTheme = !this->_data->isdefaultTheme;
                std::changethemevalue();
                // if(ct=="true")
                //     color<<"false";
                // else
                //     color<<"true";
                // color.close();
            }
        }
    }
    void Options::Update(float dt){
        if(this->back.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
            this->back.setScale(1.25,1.25);
        }else{
            this->back.setScale(1,1);
        }
        if(this->theme.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
            this->theme.setScale(1.25,1.25);
        }else{
            this->theme.setScale(1,1);
        }
    }
    void Options::Draw(float dt){
        if(this->_data->isdefaultTheme){
			this->_data->window.clear(sf::Color(this->_data->themeDefault->getMainMenuR(),this->_data->themeDefault->getMainMenuG(),this->_data->themeDefault->getMainMenuB()));
		}else{
			this->_data->window.clear(sf::Color(this->_data->themeNew->getMainMenuR(),this->_data->themeNew->getMainMenuG(),this->_data->themeNew->getMainMenuB()));
		}
        this->_data->window.draw(this->details);
        this->_data->window.draw(this->theme);
        this->_data->window.draw(this->themeText);
        this->_data->window.draw(this->back);
        this->_data->window.draw(this->backText);
        this->_data->window.display();
    }
}

// #include"options.hpp"
// #include"MainMenuState.hpp"
// namespace GameEngine{
//     Options::Options(GameDataRef data) : _data(data){ }
//     void Options::Init(){
//         // this->state = "THEME SELECTION MENU";
//         // this->Mainmenu.setTexture(this->_data->assets.GetTexture("Play Button"));
//         // this->playerOne.setTexture(this->_data->assets.GetTexture("Play Button"));
//         // this->PlayerTwo.setTexture(this->_data->assets.GetTexture("Play Button"));
//         // this->backButton.setTexture(this->_data->assets.GetTexture("Play Button"));
//         // this->backText.setFont(this->_data->assets.GetFont("Felt"));
//         // this->details.setFont(this->_data->assets.GetFont("Felt"));
//         // this->mainmenuText.setFont(this->_data->assets.GetFont("Felt"));
//         // this->playerOneText.setFont(this->_data->assets.GetFont("Felt"));
//         // this->playerTwoText.setFont(this->_data->assets.GetFont("Felt"));
//         // this->backText.setString("BACK");
//         // this->details.setString("THEME SELECTION MENU:");
//         // this->mainmenuText.setString("MAIN MENU");
//         // this->playerOneText.setString("PLAYER 1");
//         // this->playerTwoText.setString("PLAYER 2");
//         // this->backButton.setPosition(350,825);
//         // this->details.setPosition(100,150);
//         // this->details.setScale(1.2,1.2);
//         // this->Mainmenu.setPosition((SCREEN_WIDTH / 2) - (this->Mainmenu.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->Mainmenu.getGlobalBounds().height / 2) - 150);
//         // this->playerOne.setPosition(this->Mainmenu.getPosition().x , this->Mainmenu.getPosition().y + 100);
//         // this->PlayerTwo.setPosition(this->Mainmenu.getPosition().x , this->Mainmenu.getPosition().y + 200);
//         // this->backText.setPosition(this->backButton.getPosition().x + 60 , this->backButton.getPosition().y + 5); 
//         // this->mainmenuText.setPosition(this->Mainmenu.getPosition().x + 20 , this->Mainmenu.getPosition().y + 5); 
//         // this->playerOneText.setPosition(this->playerOne.getPosition().x + 45 , this->playerOne.getPosition().y + 5); 
//         // this->playerTwoText.setPosition(this->PlayerTwo.getPosition().x + 45 , this->PlayerTwo.getPosition().y + 5); 
//         // this->A.setFont(this->_data->assets.GetFont("Felt"));
//         // this->R.setFont(this->_data->assets.GetFont("Felt"));
//         // this->G.setFont(this->_data->assets.GetFont("Felt"));
//         // this->B.setFont(this->_data->assets.GetFont("Felt"));
//         // this->R.setString("R");
//         // this->G.setString("G");
//         // this->B.setString("B");
//         // this->A.setString("A");
//         // this->R.setPosition(200,300);
//         // this->G.setPosition(200,340);
//         // this->B.setPosition(200,380);
//         // this->A.setPosition(200,420);
//         // this->rbox.setPosition(this->R.getPosition().x + 40, this->R.getPosition().y + 10);
//         // this->gbox.setPosition(this->G.getPosition().x + 40, this->G.getPosition().y+ 10);
//         // this->bbox.setPosition(this->B.getPosition().x + 40, this->B.getPosition().y+ 10);
//         // this->abox.setPosition(this->A.getPosition().x + 40, this->A.getPosition().y+ 10);
//         // this->rbox.setSize(sf::Vector2f(150,20));
//         // this->gbox.setSize(sf::Vector2f(150,20));
//         // this->bbox.setSize(sf::Vector2f(150,20));
//         // this->abox.setSize(sf::Vector2f(150,20));
//         // this->colorBox.setPosition(100,500);
//         // this->colorBox.setSize(sf::Vector2f(400,300));
//         // this->rtext = new TextBox(15,sf::Color::Black,false);
//         // this->rtext->setLimit(true,3);
//         // this->rtext->setFont(this->_data->assets.GetFont("arial"));
//         // this->rtext->setPosition(this->rbox.getPosition());
//         // this->gtext = new TextBox(15,sf::Color::Black,false);
//         // this->btext = new TextBox(15,sf::Color::Black,false);
//         // this->atext = new TextBox(15,sf::Color::Black,false);
//     }
//     void Options::HandleInput(){
//         sf::Event event;
//         while(this->_data->window.pollEvent(event)){
//             if(sf::Event::Closed == event.type){
//                 this->_data->window.close();
//             }
//             if(this->state == "THEME SELECTION MENU")
//             {
//                 if(this->_data->input.IsSpriteClicked(this->backButton,sf::Mouse::Left,this->_data->window))
//                 {
//                     this->_data->machine.RemoveState();
//                 }
//                 else if(this->_data->input.IsSpriteClicked(this->Mainmenu,sf::Mouse::Left,this->_data->window)){
//                     this->state = "MAINMENU";
//                     this->details.setString("MAIN MENU COLOR SELECTION");
//                 }
//                 else if(this->_data->input.IsSpriteClicked(this->playerOne,sf::Mouse::Left,this->_data->window)){
//                     this->state = "PLAYERONE";
//                     this->details.setString("PLAYER ONE COLOR SELECTION");
//                 }
//                 else if(this->_data->input.IsSpriteClicked(this->PlayerTwo,sf::Mouse::Left,this->_data->window)){
//                     this->state = "PLAYERTWO";
//                     this->details.setString("PLAYER TWO COLOR SELECTION");
//                 }
//             }
//             else{
//                 if(this->_data->input.IsSpriteClicked(this->backButton,sf::Mouse::Left,this->_data->window))
//                 {
//                     this->state = "THEME SELECTION MENU";
//                     this->details.setString("THEME SELECTION MENU");
//                 }
//                 else  if(this->rbox.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition   (this->_data->window)))){
//                     if(this->state != "THEME SELECTION MENU"){
//                         if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//                             this->rtext->setSelected(true);
//                             this->setMouseLock(this->rtext->getSelected());
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     void Options::Update(float dt){
//         sf::Event event;
//         if(this->rtext->getSelected()){
//             if(sf::Event::TextEntered){
//                 this->rtext->typedOn(event);
//             }
//         }else{
//             this->setMouseLock(this->rtext->getSelected());
//         }
//         if(mouseLockStatus){
//             sf::Mouse::setPosition({10,10},this->_data->window);
//         }
//         if(this->backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition (this->_data->window)))){
//                 this->backButton.setScale(1.25,1.25);
//             }else{
//                 this->backButton.setScale(1,1);
//             }
//         if(this->state == "THEME SELECTION MENU"){
//             if(this->Mainmenu.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition   (this->_data->window)))){
//                 this->Mainmenu.setScale(1.25,1.25);
//             }else{
//                 this->Mainmenu.setScale(1,1);
//             }
//             if(this->playerOne.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition  (this->_data->window)))){
//                 this->playerOne.setScale(1.25,1.25);
//             }else{
//                 this->playerOne.setScale(1,1);
//             }
//             if(this->PlayerTwo.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition  (this->_data->window)))){
//                 this->PlayerTwo.setScale(1.25,1.25);
//             }else{
//                 this->PlayerTwo.setScale(1,1);
//             }
//         }
//         else{
                
//         }
//     }
//     void Options::setMouseLock(bool status){
//         this->mouseLockStatus = status;
//         if(status)
//             this->_data->window.setMouseCursorVisible(false);
//     }
//     void Options::Draw(float dt){
//         this->_data->window.clear(sf::Color(245, 144, 66));
//         this->_data->window.draw(this->backButton);
//         this->_data->window.draw(this->backText);
//         this->_data->window.draw(this->details);
//         if(this->state == "THEME SELECTION MENU"){
//             this->_data->window.draw(this->Mainmenu);
//             this->_data->window.draw(this->mainmenuText);
//             this->_data->window.draw(this->playerOne);
//             this->_data->window.draw(this->playerOneText);
//             this->_data->window.draw(this->PlayerTwo);
//             this->_data->window.draw(this->playerTwoText);
//         }
//         else{
//             this->_data->window.draw(this->A);
//             this->_data->window.draw(this->R);
//             this->_data->window.draw(this->G);
//             this->_data->window.draw(this->B);
//             this->_data->window.draw(this->rbox);
//             this->_data->window.draw(this->gbox);
//             this->_data->window.draw(this->bbox);
//             this->_data->window.draw(this->abox);
//             this->_data->window.draw(this->colorBox);
//             this->rtext->drawTo(this->_data->window);
//             this->gtext->drawTo(this->_data->window);
//             this->btext->drawTo(this->_data->window);
//             this->atext->drawTo(this->_data->window);
//         }

//         this->_data->window.display();
//     }
// }