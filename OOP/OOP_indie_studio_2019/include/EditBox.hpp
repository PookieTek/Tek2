/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EditBox
*/

#ifndef EDITBOX_HPP_
#define EDITBOX_HPP_

class editBoxPlayer
{
private:
    int     nbEditBoxPlayer;
    int     x;
    int     x2;
    int     y;
    int     y2;
public:
    void    addNbEditBoxPlayer();
    int     getNbEditBoxPlayer();
    void    resetEditBoxPlayer();
    void    setX(int _x);
    void    setX2(int _x2);
    int     getX();
    int     getX2();
    int     getY();
    int     getY2();
    editBoxPlayer();
    ~editBoxPlayer();
};

#endif /* !EDITBOX_HPP_ */
