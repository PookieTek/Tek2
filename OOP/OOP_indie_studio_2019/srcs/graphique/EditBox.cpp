/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EditBox
*/

#include "EditBox.hpp"

editBoxPlayer::editBoxPlayer() { nbEditBoxPlayer = 0; x = 200; y = 300; x2 = 350; y2 = 330; }
editBoxPlayer::~editBoxPlayer() {}
void editBoxPlayer::addNbEditBoxPlayer() { nbEditBoxPlayer += 1; }
int editBoxPlayer::getNbEditBoxPlayer() { return nbEditBoxPlayer; }
void editBoxPlayer::resetEditBoxPlayer() { nbEditBoxPlayer = 0; x = 200; x2 = 350; }
void editBoxPlayer::setX(int _x) { x += _x; }
void editBoxPlayer::setX2(int _x2) { x2 += _x2; }
int editBoxPlayer::getX() { return x; }
int editBoxPlayer::getX2() { return x2; }
int editBoxPlayer::getY() { return y; }
int editBoxPlayer::getY2() { return y2; }