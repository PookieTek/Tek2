/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Board
*/

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "Interface/IBoard.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Bonus.hpp"
#include "Block.hpp"
#include "SoundTest.hpp"

class Board : public IBoard {
    public:
        Board(std::vector<std::shared_ptr<Player>>);
        ~Board();

        std::pair<float, float> GetSize();
        std::vector<std::vector<std::shared_ptr<IBlock>>> GetBoard();
        std::shared_ptr<IBlock> GetBlock(std::pair<float, float>);
        std::pair<int, int> GetRelativeSize();
        bool SetBomb(std::string);
        bool Move(std::string name, std::pair<float, float>);
        int SetFire(std::shared_ptr<Bomb>);
        void AddBonus(std::shared_ptr<Bonus>);
        std::vector<std::shared_ptr<Bonus>> GetBonus();
        bool IsPlayer(std::pair<float, float>);
        void IABot(std::shared_ptr<Player>);
        int CheckPlayerPresence(std::pair<int, int>, std::string);
        void AStar(std::pair<int, int>, std::pair<int, int>, std::vector<std::vector<int>> *, int);
        std::pair<int, int> FindPath(std::pair<int, int>, std::pair<int, int>, std::shared_ptr<Player>);
        void BotAsset(std::shared_ptr<Player>, std::pair<int, int>);
        std::shared_ptr<Player> GetPlayerByName(std::string);
        std::vector<std::shared_ptr<Bomb>> GetBombs();
        bool IsBombInZone(std::pair<int, int>);

        SoundTest                       soundTest;

    protected:
    private:
        std::pair<int, int> size;
        std::vector<std::vector<std::shared_ptr<Block>>> board;
        std::vector<std::shared_ptr<Bonus>> bonus;
        std::vector<std::shared_ptr<Player>> players;
        std::vector<std::shared_ptr<Bomb>> bombs;
        
};

#endif /* !BOARD_HPP_ */
