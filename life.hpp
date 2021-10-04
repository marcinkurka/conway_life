#include <map>
#include <utility>
#include <algorithm>
#include <vector>

using boardType = std::map<std::pair<int, int>,bool>;

class Game
{
public:

    Game();
    Game(std::vector<std::pair<int,int>> starting_list);

    int boardSize();
    void setField(int x, int y, bool state);
    boardType checkNeighbours(int x, int y);
    int liveCells();
    int countLiveNeighbours(int x, int y);
    int countDeadNeighbours(int x, int y);
    boardType preparedBoard();
    void clearUp();
    void nextRound();
    boardType getBoard();

private:

    boardType board;

};
