#include "life.hpp"

Game::Game(){}

Game::Game(std::vector<std::pair<int,int>> starting_list)
{
  for (auto item : starting_list)
  {
    board[{item.first,item.second}]=true;
  }
}


int Game::boardSize()
{
    return board.size();
}

void Game::setField(int x, int y, bool state)
{
    board[{x,y}]=state;
}

boardType Game::checkNeighbours(int x, int y)
{
    std::map<std::pair<int,int>,bool> NeighboursMap;
    NeighboursMap[{x-1,y+1}] = board[{x-1,y+1}];
    NeighboursMap[{x,y+1}] =  board[{x,y+1}];
    NeighboursMap[{x+1,y+1}] = board[{x+1,y+1}];
    NeighboursMap[{x-1,y}] = board[{x-1,y}];
    NeighboursMap[{x+1,y}] = board[{x+1,y}];
    NeighboursMap[{x-1,y-1}] = board[{x-1,y-1}];
    NeighboursMap[{x,y-1}] = board[{x,y-1}];
    NeighboursMap[{x+1,y-1}] = board[{x+1,y-1}];

    return NeighboursMap;
}

int Game::liveCells()
{
    int liveCellsNumber{0};
    //int liveCellsNumber = std::count_if(board.begin(), board.end(), [](int i) {if (board.second == true) return ++i;});
    for (auto element : board)
    {
        if (element.second == true)
        liveCellsNumber++;
    }
    return liveCellsNumber;
}

int Game::countLiveNeighbours(int x, int y)
{
    int liveCellsNumber{0};
    for (auto element : this->checkNeighbours(x,y))
    {
        if (element.second == true)
        liveCellsNumber++;
    }
    return liveCellsNumber;
}

int Game::countDeadNeighbours(int x, int y)
{
    return 8 - this->countLiveNeighbours(x, y);
}

boardType Game::preparedBoard()
{
    boardType preparedBoard;
     for (auto element : board)
    {
        if (element.second == true)
        {
            preparedBoard.insert(element);
            boardType map_to_merge= this->checkNeighbours(element.first.first, element.first.second);
            for(auto mtm_element: map_to_merge)
            {
                preparedBoard.insert(mtm_element);

            }
            //preparedBoard.merge(map_to_merge);
            //preparedBoard.insert((this->checkNeighbours(element.first.first, element.first.second));
        }
    }
    return preparedBoard;

}

void Game::clearUp()
{
  for(auto it = board.begin(); it != board.end(); ) {
       if(it->second == false)
           it = board.erase(it);
       else
           ++it;
   }
}

void Game::nextRound()
{
    boardType temp_map = this->preparedBoard();

    for (auto element : temp_map)
    {
       int neighbours = this->countLiveNeighbours(element.first.first, element.first.second);
       if((neighbours<2 || neighbours>3) && element.second==true)
       {
         board[{element.first.first,element.first.second}]=false;
       }
       else if(neighbours==3 && element.second==false)
       {
         board[{element.first.first,element.first.second}]=true;
       }

    }
    this->clearUp();

}

boardType Game::getBoard()
{
  return board;
}
