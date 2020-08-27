/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sfml
*/

#include "sfml.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

Sfml::Sfml() : IGraphicalLib(), window(sf::VideoMode(1920, 1080), "Menu", sf::Style::Default, sf::ContextSettings{0, 0, 8})
{
    isStart = false;
    pseudo = "";
    cursGraph = "";
    cursGame = "";
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false); 	
    window.setFramerateLimit(60);
    RetKey = false;
    IsError = false;
    initGame = false;
}

std::map<Interaction::Bind, int> Sfml::GetMapping() {
    std::map<Interaction::Bind, int> mapping;

    mapping[Interaction::Bind::RIGHT] = sf::Keyboard::Right;
    mapping[Interaction::Bind::LEFT] = sf::Keyboard::Left;
    mapping[Interaction::Bind::UP] = sf::Keyboard::Up;
    mapping[Interaction::Bind::DOWN] = sf::Keyboard::Down;
    mapping[Interaction::Bind::GR_PREVIOUS] = sf::Keyboard::PageDown;
    mapping[Interaction::Bind::GR_NEXT] = sf::Keyboard::PageUp;
    mapping[Interaction::Bind::GA_PREVIOUS] = sf::Keyboard::Home;
    mapping[Interaction::Bind::GA_NEXT] = sf::Keyboard::End;
    mapping[Interaction::Bind::RESTART] = sf::Keyboard::R;
    mapping[Interaction::Bind::BREAK] = sf::Keyboard::P;
    mapping[Interaction::Bind::MENU] = sf::Keyboard::Backspace;
    mapping[Interaction::Bind::EXIT] = sf::Keyboard::Escape;
    mapping[Interaction::Bind::ENTER] = sf::Keyboard::Enter;
    mapping[Interaction::Bind::SPEED] = sf::Keyboard::Space;
    return mapping;
}


void Sfml::DisplayContent(std::vector<std::vector<AssetInfo>> board) {
    sf::Sprite tmpSprite;
    std::string tmp;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.at(i).size(); j++) {
            tmp = board.at(i).at(j).path;
            tmp.erase(tmp.size() - 1);
            tmpSprite = assets[tmp].sprite;
            switch (board.at(i).at(j).orientation) {
                case 0:
                    tmpSprite.setRotation(180);
                    break;
                case 1:
                    tmpSprite.setRotation(270);
                    break;
                case 2:
                    tmpSprite.setRotation(0);
                    break;
                case 3:
                    tmpSprite.setRotation(90);
                    break;
                default:
                    break;
            }
            tmpSprite.setPosition(sf::Vector2f(96 + j * 23, 59 + i * 27));
            tmpSprite.scale(sf::Vector2f(0.1, 0.1));
            window.draw(tmpSprite);
        }
    }
}

void Sfml::InitGame(std::string nick, int score) {
    std::string tmppseudo = "PLAYER: " + nick;
    std::string gamename = parseLib(cursGame.c_str());


    pseudotxt = InitText(tmppseudo, 20, sf::Color::Cyan);
    scoretxt = InitText("", 20, sf::Color::Cyan);
    pseudotxt.setPosition(sf::Vector2f(200, 20));
    scoretxt.setPosition(sf::Vector2f(1700, 20));
    initGame = true;
    window.setFramerateLimit(8);
    window.setTitle(gamename + " -");
}

int Sfml::DisplayBoard(std::vector<std::vector<AssetInfo>> board, std::map<std::string, std::string> data, int score) {
    std::string tmpscore = "SCORE: " + std::to_string(score);

    cursGame = data["game"];    
    if (!initGame)
        InitGame(data["pseudo"], score);
    scoretxt.setString(tmpscore);
    window.clear();
    window.pollEvent(event);
    if (event.type == sf::Event::EventType::Closed) {
        window.close();
        return -1;
    }
    window.draw(pseudotxt);
    window.draw(scoretxt);
    CreateBox(gamebox, 96, 59, 1728, 960, 2, sf::Color::Green, sf::Color::Transparent); 
    DisplayContent(board);

    window.display();
    return 1;
}

void Sfml::Quit() {
    this->~Sfml();
}

int Sfml::GetKey() {
    window.pollEvent(event);
    if (clock.getElapsedTime().asMilliseconds() > 100)
        RetKey = true;
    if (!RetKey)
        return -1;
    if (event.type != sf::Event::KeyPressed)
        return -1;
    RetKey = false;
    clock.restart();
    lastKey = event.key.code;
    return event.key.code;
}

void Sfml::SfmlAsset(std::string filename, std::string path) {
    assets[path].texture.loadFromFile(filename);
    assets[path].sprite.setTexture(assets[path].texture);
}

void Sfml::InitAsset(std::string path) {
    std::string totalpath = "./Game";
    totalpath.append(path);

    DIR *dir = opendir(totalpath.c_str());
    struct dirent *dirdata;
    std::string tmp = totalpath;

    while ((dirdata = readdir(dir)) != NULL) {
        if (strcmp(dirdata->d_name, ".") != 0 && strcmp(dirdata->d_name, "..") != 0) {
            tmp.append(dirdata->d_name);
            tmp.append("/sprite.png");
            SfmlAsset(tmp, dirdata->d_name);
            tmp = totalpath;
        }
    }
    return;
}

MenuData Sfml::GetData(MenuData data) {
    data.data["game"] = cursGame;
    data.data["graphical"] = cursGraph;
    data.data["pseudo"] = pseudo;
    data.menuX = menuX;
    data.menuY = menuY;
    data.isStart = isStart;
    data.isPseudo = isPseudo;
    data.isEnter = isEnter;
    return data;
}

void Sfml::displayPauseScreen(void) {
    CreateBox(blur, 0, 0, 1920, 1080, 0, sf::Color::Transparent, sf::Color(255, 255, 255, 50));
    textbreak = InitText("Pause", 35, sf::Color::Cyan);
    textbreak.setPosition(sf::Vector2f(920, 300));
    window.draw(textbreak);
    
    textbreak = InitText("CONTINUE (ENTER)", 20, sf::Color::Red);
    textbreak.setPosition(sf::Vector2f(850, 400));
    window.draw(textbreak);
    textbreak.setString("RESTART GAME (R)");
    textbreak.setPosition(sf::Vector2f(850, 450));
    window.draw(textbreak);
    textbreak.setString("RETURN TO MENU (DEL)");
    textbreak.setPosition(sf::Vector2f(850, 500));
    window.draw(textbreak);
    textbreak.setString("QUIT (ESC)");
    textbreak.setPosition(sf::Vector2f(850, 550));
    window.draw(textbreak);
    window.display();
    return;
}

int Sfml::DisplayGameOver(std::string player, int score) {
    sf::RectangleShape gameOverBox;
    sf::Text title;

    window.clear();
    if (event.type == sf::Event::EventType::Closed) {
        window.close();
        return -1;
    }
    CreateBox(gameOverBox, 640, 240, 640, 600, 2, sf::Color(35, 230, 0), sf::Color::Black);
    title = InitText("Player: " + player, 20, sf::Color::Cyan);
    title.setPosition(sf::Vector2f(860 - 15 * (4 + strlen(player.c_str()) / 2), 250));
    window.draw(title);
    title.setString("Score: " + std::to_string(score));
    title.setPosition(sf::Vector2f(860 - 15 * (4 + strlen(player.c_str()) / 2), 300));
    window.draw(title);
    title.setString("PRESS (ENTER) TO RESTART GAME");
    title.setPosition(sf::Vector2f(680, 450));
    window.draw(title);
    title.setString("PRESS (DEL) TO RETURN TO MENU");
    title.setPosition(sf::Vector2f(680, 500));
    window.draw(title);
    title.setString("PRESS (ESC) TO QUIT");
    title.setPosition(sf::Vector2f(680, 550));
    window.draw(title);
    title.setPosition(sf::Vector2f(680, 200));
    title.setString("Game Over");
    window.draw(title);
    window.display();
    return (1);
}

int Sfml::DisplayGameWin(std::string player, int score) {
    sf::RectangleShape gameOverBox;
    sf::Text title;

    window.clear();
    if (event.type == sf::Event::EventType::Closed) {
        window.close();
        return -1;
    }
    CreateBox(gameOverBox, 640, 240, 640, 600, 2, sf::Color(35, 230, 0), sf::Color::Black);
    title = InitText("Player: " + player, 20, sf::Color::Cyan);
    title.setPosition(sf::Vector2f(860 - 15 * (4 + strlen(player.c_str()) / 2), 250));
    window.draw(title);
    title.setString("Score: " + std::to_string(score));
    title.setPosition(sf::Vector2f(860 - 15 * (4 + strlen(player.c_str()) / 2), 300));
    window.draw(title);
    title.setString("PRESS (ENTER) TO RESTART GAME");
    title.setPosition(sf::Vector2f(680, 450));
    window.draw(title);
    title.setString("PRESS (DEL) TO RETURN TO MENU");
    title.setPosition(sf::Vector2f(680, 500));
    window.draw(title);
    title.setString("PRESS (ESC) TO QUIT");
    title.setPosition(sf::Vector2f(680, 550));
    window.draw(title);
    title.setPosition(sf::Vector2f(680, 200));
    title.setString("Success");
    window.draw(title);
    window.display();
    return (1);
}


void Sfml::setStart(bool start) { isStart = start; }

extern "C" IGraphicalLib *creatorGraph() {
    return (new Sfml);
}