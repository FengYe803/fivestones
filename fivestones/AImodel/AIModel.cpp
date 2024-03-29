#include "AIModel.h"

AIModel::AIModel()
{
    resetBoard();
}

void AIModel::actionByHuman(int humanPosRow, int humanPosColumn)
{
    //减1是因为UI是从1-15，而算法里面的board是从0-14
    board[humanPosRow - 1][humanPosColumn - 1] = 'B';

    return ;
}

void AIModel::actionByAI(int &machinePosRow, int &machinePosColumn)
{
    auto pos = gt.get_next_pos();
    if (pos.first != 255 && pos.second != 255) board[pos.first][pos.second] = 'W';
    //加1是因为UI是从1-15，而算法里面的board是从0-14
    machinePosRow = pos.first + 1;
    machinePosColumn = pos.second + 1;

    return ;
}

bool AIModel::isWin(int &firstPointRow, int &firstPointColumn, uint8_t &result, WinType &winType)
{
    gt = GameTree(8, 2, board);
    result = gt.game(firstPointRow, firstPointColumn, winType);
    //加1是因为UI是从1-15，而算法里面的board是从0-14
    firstPointRow += 1;
    firstPointColumn += 1;
    if (result == 'B')
    {
        qDebug() << "Black Win !";

        return true;
    }
    else if (result == 'W')
    {
        qDebug() << "White Win !";

        return true;
    }
    else
    {
        return false;
    }
}

bool AIModel::chessIsFull()
{
    for (int i = 0; i < BOARD_GRAD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_GRAD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
            else
            {
                continue;
            }
        }
    }

    return true;
}

void AIModel::resetBoard()
{
    memset(board, 0, sizeof(board));

    return ;
}

void AIModel::AIPlay()
{
    /*cout << endl;
    uint8_t turn = 'B', board[15][15]{}, inputBoard[15][15]{};
    for (uint8_t k = 0; k < 225; k++)
    {
        cout << "[" << k + 1 << "] ";
        memcpy(inputBoard, board, sizeof(board));
        if (turn == 'W')
            for (uint8_t i = 0; i < 15; i++)
                for (uint8_t j = 0; j < 15; j++)
                {
                    if (board[i][j] == 'W') inputBoard[i][j] = 'B';
                    if (board[i][j] == 'B') inputBoard[i][j] = 'W';
                }
        GameTree gt = GameTree(8, 2, inputBoard);
        uint8_t result = gt.game();
        if (turn == 'W' && result != 0)
        {
            if (result == 'B') cout << "White Win !";
            if (result == 'W') cout << "Black Win !";
            gt.show_board(true);
            return;
        }
        if (turn == 'B' && result != 0)
        {
            if (result == 'B') cout << "Black Win !";
            if (result == 'W') cout << "White Win !";
            gt.show_board(false);
            return;
        }
        auto pos = gt.get_next_pos();
        if (turn == 'B')
        {
            turn = 'W';
            board[pos.first][pos.second] = 'B';
            cout << "Black ";
            gt.show_next_pos();
            gt.show_board(false);
        } else
        {
            turn = 'B';
            board[pos.first][pos.second] = 'W';
            cout << "White ";
            gt.show_next_pos();
            gt.show_board(true);
        }
    }*/

    return ;
}

AIModel::~AIModel()
{
    ;
}
