#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QEventLoop>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <AIModel.h>

#define	ROW             15
#define COLUMN          15
#define LEFTPOINT       30
#define RIGHTPOINT      450
#define STEP            30
#define CHESS_RADIUS    24

typedef enum
{
    BLACK_PLAYER = 1,
    WHITE_PLAYER
}PLAYER;

typedef struct
{
    int posRow;
    int posColumn;
    int color;
}ChessInfo;

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();

public:
    AIModel AImodel;

public:
    void resetChessBoard();

public:
    bool isStart;
    PLAYER player;

private:
    void drawChessBoard(QPainter &painter);

private:
    int humanPosRow;
    int humanPosColumn;
    int aiPosRow;
    int aiPosColumn;
    int firstPointRowTemp;
    int firstPointColumnTemp;
    int firstPointRow;
    int firstPointColumn;
    uint8_t result;
    WinType winType;

    bool mousePressed;
    bool mouseMoving;
    bool chessIsFull;

    ChessInfo chessInfo;
    QVector<QPair<int, int>> rowColumnVector;
    QVector<ChessInfo> chessInfoVector;

private:
    QPen pen;
    QBrush brush;
    QFont font;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void SWITCH_PHOTO(PLAYER);
    void IS_WIN(PLAYER);
    void CHESS_IS_FULL();

public slots:

};

#endif // CHESSBOARD_H
