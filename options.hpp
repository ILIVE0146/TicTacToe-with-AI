#pragma once
#include "state.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include <string>
#include <fstream>
#include <sstream>
std::string getct();
namespace GameEngine{
	class Options:public State{
		public:
			Options(GameDataRef data);
			void Init();
			void HandleInput();
			void Update(float dt);
			void Draw(float dt);
		private:
			GameDataRef _data;
			sf::Text details;
			sf::Sprite theme;
			sf::Text themeText;
			sf::Sprite back;
			sf::Text backText;
	};
}

// #pragma once
// #include <SFML/Graphics.hpp>
// #include "State.hpp"
// #include "Game.hpp"
// #include "DEFINITIONS.hpp"
// #include "textBox.hpp"
// namespace GameEngine{
// 	class Options : public State{
// 	public:
// 		Options(GameDataRef data);
// 		void Init();
// 		void HandleInput();
// 		void Update(float dt);
// 		void Draw(float dt);
// 		void setMouseLock(bool status);
// 	private:
// 		GameDataRef _data;
// 		sf::Sprite backButton;
// 		sf::Text backText;
// 		sf::Text details;
// 		sf::Sprite Mainmenu;
// 		sf::Sprite playerOne;
// 		sf::Sprite PlayerTwo;
// 		sf::Text mainmenuText;
// 		sf::Text playerOneText;
// 		sf::Text playerTwoText;
// 		std::string state;
// 		sf::RectangleShape colorBox;
// 		sf::RectangleShape rbox,gbox,bbox,abox;
// 		sf::Text R,G,B,A;
// 		bool mouseLockStatus;
// 		int red,blue,green,alpha;
// 		TextBox *rtext,*btext,*gtext,*atext;
// 	};
// }