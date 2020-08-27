/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "../../include/IGraphicalLib.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"

struct AssetSprite {
    sf::Texture texture;
    sf::Sprite sprite;
};

class Sfml : public IGraphicalLib
{
    public:
        Sfml();
        ~Sfml() {
            window.close();
        };

        int DisplayMenu(std::vector<std::string>,  std::vector<std::string>, MenuData, bool);
        int DisplayBoard(std::vector<std::vector<AssetInfo>>, std::map<std::string, std::string>, int);
        int DisplayGameOver(std::string, int);
        int DisplayGameWin(std::string, int);
        void Quit();
        MenuData GetData(MenuData);
        int GetKey();
        void InitAsset(std::string);
        void displayPauseScreen(void);
        std::map<Interaction::Bind, int> GetMapping();
        void setStart(bool);
        void DisplayBackMenu();
        void DisplayList(std::vector<std::string> graph, std::vector<std::string> game);
        bool checkWin();
        void CreateBox(sf::RectangleShape, float, float, float, float, int, sf::Color, sf::Color);
        sf::Text InitText(std::string, int, sf::Color);
        void ValidSelection(MenuData, std::vector<std::string>, std::vector<std::string>);
        void PrintError(std::string);
        void DisplayButton(MenuData, int);
        void DisplayCursor(MenuData);
        void DisplayPseudo();
        void DisplayContent(std::vector<std::vector<AssetInfo>>);
        void InitGame(std::string, int);
        void SfmlAsset(std::string, std::string);


        std::string pseudo;
        std::string cursGraph;
        std::string cursGame;

        sf::RenderWindow window;
        sf::Event event;
        sf::RectangleShape leftMenu;
        sf::RectangleShape rigthMenu;
        sf::RectangleShape pseudobox;
        sf::RectangleShape pausebox;
        sf::RectangleShape scorebox;
        sf::RectangleShape startbutton;
        sf::RectangleShape blur;
        sf::Font font;
        sf::Clock clock;
        sf::Clock errorClock;
        sf::Clock pseudoDelClock;
        sf::Clock refreshClock;
        bool RetKey;
        bool IsError;
        std::string ErrorTxt;
        bool initGame;
        sf::Text pseudotxt;
        sf::Text scoretxt;
        sf::RectangleShape gamebox;
        sf::Text textbreak;
        std::vector<int> menuX;
        std::vector<int> menuY;
        int lastKey;

        bool isStart, isPseudo, isEnter;
        std::map<std::string, AssetSprite> assets;

};

std::vector<std::string> ReadScores();
std::string parseLib(std::string);

#endif /* !SFML_HPP_ */
