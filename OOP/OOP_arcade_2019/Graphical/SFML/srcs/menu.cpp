/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** menu
*/

#include <iostream>
#include "sfml.hpp"
#include <string.h>

sf::Text Sfml::InitText(std::string text, int size, sf::Color color) {
    sf::Text print;

    font.loadFromFile("Graphical/SFML/assets/font/arial.ttf");
    print.setFont(font);
    print.setString(text);
    print.setCharacterSize(size);
    print.setFillColor(color);
    print.setStyle(sf::Text::Bold);
    return print;
}

void Sfml::CreateBox(sf::RectangleShape rect, float posx, float posy, float sizex, float sizey, int thick, sf::Color fg, sf::Color bg) {
    rect.setSize(sf::Vector2f(sizex, sizey));
    rect.setPosition(posx, posy);
    rect.setOutlineThickness(thick);
    rect.setOutlineColor(fg);
    rect.setFillColor(bg);
    window.draw(rect);
}


void Sfml::DisplayBackMenu() {
    sf::Text title;
    sf::RectangleShape line;

    CreateBox(leftMenu, 1, 1, 540, 1070, 2, sf::Color(35, 230, 0), sf::Color::Black);
    CreateBox(rigthMenu, 1378, 1, 540, 1070, 2, sf::Color(35, 230, 0), sf::Color::Black);
    title = InitText("Graphicals", 30, sf::Color::Cyan);
    title.setPosition(180, 2);
    window.draw(title);
    title.setString("Games");
    title.setPosition(1600, 2);
    window.draw(title);
    CreateBox(line, 50, 80, 440, 2, 1, sf::Color::Red, sf::Color::Red);
    CreateBox(line, 1428, 80, 440, 2, 1, sf::Color::Red, sf::Color::Red);
}

bool Sfml::checkWin() {
    int cols = window.getSize().x;
    int lines = window.getSize().y;

    if (cols < 800 || lines < 700)
        return false;
    return true;
}

void Sfml::DisplayList(std::vector<std::string> graph, std::vector<std::string> game) {
    sf::Text graphelem;
    sf::Text gameelem;

    for (int i = 0; i < (int)graph.size(); i++) {
        graphelem = InitText(parseLib(graph.at(i)), 25, sf::Color::Cyan);
        graphelem.setPosition(3, 135 + (40 * i));
        menuX.push_back(10 + strlen(parseLib(graph.at(i)).c_str()) * 15);
        menuY.push_back(135 + (40 * i));
        window.draw(graphelem);
        if (cursGraph.compare(graph.at(i)) == 0) {
            sf::CircleShape sq(10, 4);
            sq.setFillColor(sf::Color::Cyan);
            sq.setPosition(10 + strlen(parseLib(graph.at(i)).c_str()) * 15, 139 + (40 * i));
            window.draw(sq);
        }

    }
    menuX.push_back(0);
    menuX.push_back(0);
    menuY.push_back(0);
    menuY.push_back(0);
    for (int i = 0; i < (int)game.size(); i++) {
        gameelem = InitText(parseLib(game.at(i)), 25, sf::Color::Cyan);
        gameelem.setPosition(1380, 135 + (40 * i));
        menuX.push_back(1390 + strlen(parseLib(game.at(i)).c_str()) * 15);
        menuY.push_back(135 + (40 * i));
        window.draw(gameelem);
        if (cursGame.compare(game.at(i)) == 0) {
            sf::CircleShape sq(10, 4);
            sq.setFillColor(sf::Color::Cyan);
            sq.setPosition(1370 + strlen(parseLib(graph.at(i)).c_str()) * 15, 139 + (40 * i));
            window.draw(sq);
        }
    }
}

void Sfml::PrintError(std::string error) {
    sf::Text err = InitText(error,  30, sf::Color::Red);
    err.setPosition(960 - (15 * strlen(error.c_str()) / 2), 830);
    window.draw(err);
}

void Sfml::ValidSelection(MenuData data, std::vector<std::string> graph, std::vector<std::string> game) {
    if (data.isPseudo) {
        isPseudo = false;
    } else if (data.index < (int)graph.size()) {
       cursGraph = graph.at(data.index);
    } else if (data.index > (int)graph.size() + 1) {
        cursGame = game.at(data.index - 2 - graph.size());
    } else if (data.index == (int)graph.size() + 1) {
        if (data.data["pseudo"].size() == 0) {

            ErrorTxt = "Please, Chose a Pseudonyme.";
            IsError = true;
        } else if (data.data["game"].size() == 0) {
            ErrorTxt = "Please, Choose a game.";
            IsError = true;
        }
        else
            isStart = true;
    } else if (data.index == (int)graph.size()) {
        isPseudo = true;
    }
    isEnter = false;
}

void Sfml::DisplayButton(MenuData data, int graphsize) {
    std::vector<std::string> Scores = ReadScores();
    sf::Text text;
    sf::RectangleShape line;

    CreateBox(scorebox, 640, 216, 640, 540, 2, sf::Color(35, 230, 0), sf::Color::Black);
    CreateBox(startbutton, 890, 900, 100, 50, 2, sf::Color::Cyan, sf::Color::Black);
    text = InitText("Pseudo :", 25, sf::Color::Green);
    text.setPosition(sf::Vector2f(840, 30));
    window.draw(text);
    text = InitText("High Score", 30, sf::Color::Cyan);
    text.setPosition(sf::Vector2f(895, 250));
    window.draw(text);
    CreateBox(line, 690, 320, 540, 2, 1, sf::Color::Red, sf::Color::Red);
    for (int i = 0; i < 10 && i < Scores.size(); i++) {
        text = InitText("- "+ Scores.at(i), 20, sf::Color::Cyan);
        text.setPosition(sf::Vector2f(650, 360 + (40 * i)));
        window.draw(text);
    }
    text = InitText("Start", 35, sf::Color::Green);
    text.setPosition(sf::Vector2f(900, 900));
    window.draw(text);
    menuX.at(graphsize) = 1080 + pseudo.size() * 10;
    menuY.at(graphsize) = 30;
    menuX.at(graphsize + 1) = 1000;
    menuY.at(graphsize + 1) = 910;
}

void Sfml::DisplayCursor(MenuData data) {
    sf::ConvexShape cursor;
    float lines = menuY.at(data.index);
    float cols = menuX.at(data.index);
    lines += 15;
    cols += 35;
    sf::Color curscolor = sf::Color::Cyan;

    if (isPseudo) {
        curscolor = sf::Color::Magenta;
    }
    cursor.setPointCount(4);
    cursor.setPoint(0, sf::Vector2f(cols, lines));
    cursor.setPoint(1, sf::Vector2f(cols + 10, lines + 10));
    cursor.setPoint(2, sf::Vector2f(cols + 5, lines));
    cursor.setPoint(3, sf::Vector2f(cols + 10, lines - 10));
    cursor.setFillColor(curscolor);
    window.draw(cursor);
}

void Sfml::DisplayPseudo() {
    sf::Text text;

    if (pseudo.size() > 0) {
        CreateBox(pseudobox, 980, 30, pseudo.size() * 13 + 20, 30, 2, sf::Color::Cyan, sf::Color::Black);
        text = InitText(pseudo, 20, sf::Color::Cyan);
        text.setPosition(sf::Vector2f(990, 35));
        window.draw(text);
    }
}

int Sfml::DisplayMenu(std::vector<std::string> listGraph,  std::vector<std::string> listGame, MenuData data, bool toClear) {
    sf::Text Error;
    sf::Event eventpseudo;

    cursGraph = data.data["graphical"];
    cursGame = data.data["game"];
    pseudo = data.data["pseudo"];

    menuX.clear();
    menuY.clear();
    window.clear();

    window.pollEvent(event);
    if (event.type == sf::Event::EventType::Closed) {
        window.close();
        return -1;
    }
    if (data.isEnter)
        ValidSelection(data, listGraph, listGame);
    if (!checkWin()) {
        Error = InitText("Please, resize your window.", 40, sf::Color::Red);
        Error.setPosition(0, 0);
        window.draw(Error);
    } else {
        DisplayBackMenu();
        DisplayList(listGraph, listGame);
        DisplayButton(data, listGraph.size());
        DisplayCursor(data);
        DisplayPseudo();

    }
    if (isPseudo) {
        while (window.pollEvent(eventpseudo)) {
            if (eventpseudo.type == sf::Event::TextEntered) {
                if (pseudo.size() < 20 && eventpseudo.text.unicode > 65)
                    pseudo += eventpseudo.text.unicode;
                DisplayPseudo();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && pseudoDelClock.getElapsedTime().asMilliseconds() > 200) {
                if (pseudo.size() > 0)
                    pseudo.resize(pseudo.size() - 1);
                pseudoDelClock.restart();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                isPseudo = false;
            }
        }
    }
    if (errorClock.getElapsedTime().asSeconds() > 5) {
        IsError = false;
        errorClock.restart();
    }
    if (IsError)
        PrintError(ErrorTxt);
    if (isStart)
        return 1;
    window.display();
    return 0;
}
