#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    setupUi(this);

    this->setWindowTitle("枫叶五子棋人机对弈软件，如有疑问请联系QQ404757434");

    blackWinTimes = 0;
    whiteWinTimes = 0;

    Label5->hide();
    Label6->hide();
    PushButton1->setEnabled(true);
    PushButton2->setEnabled(false);
    PushButton3->setEnabled(false);

    connect(ChessBoardWidget, &ChessBoard::SWITCH_PHOTO, this, [&](PLAYER player)
    {
        if (player == BLACK_PLAYER)
        {
            Label5->show();
            Label6->hide();
        }
        else if (player == WHITE_PLAYER)
        {
            Label5->hide();
            Label6->show();
        }
        else
        {
            ;
        }
    });

    connect(ChessBoardWidget, &ChessBoard::IS_WIN, this, [&](PLAYER player)
    {
        if (player == BLACK_PLAYER)
        {
            blackWinTimes++;
        }
        else if (player == WHITE_PLAYER)
        {
            whiteWinTimes++;
        }
        else
        {
            ;
        }
        ScoreLabel->setText(QString("%1 : %2").arg(blackWinTimes).arg(whiteWinTimes));

        PushButton1->setEnabled(true);
        PushButton2->setEnabled(false);
        PushButton3->setEnabled(false);

        ChessBoardWidget->isStart = false;
    });

    connect(ChessBoardWidget, &ChessBoard::CHESS_IS_FULL, this, [&]()
    {
        PushButton1->setEnabled(true);
        PushButton2->setEnabled(false);
        PushButton3->setEnabled(false);
    });

    //开始游戏
    connect(PushButton1, &QPushButton::clicked, this, [&](){
        Label5->show();
        Label6->hide();
        PushButton1->setEnabled(false);
        PushButton2->setEnabled(true);
        PushButton3->setEnabled(true);

        ChessBoardWidget->resetChessBoard();
        ChessBoardWidget->AImodel.resetBoard();

        ChessBoardWidget->isStart = true;
    });
    //求和
    connect(PushButton2, &QPushButton::clicked, this, [&](){
        Label5->hide();
        Label6->hide();
        PushButton1->setEnabled(true);
        PushButton2->setEnabled(false);
        PushButton3->setEnabled(false);

        ChessBoardWidget->resetChessBoard();
    });
    //认输
    connect(PushButton3, &QPushButton::clicked, this, [&](){
        Label5->hide();
        Label6->hide();
        PushButton1->setEnabled(true);
        PushButton2->setEnabled(false);
        PushButton3->setEnabled(false);

        if (ChessBoardWidget->player == BLACK_PLAYER)
        {
            whiteWinTimes++;
        }
        else if (ChessBoardWidget->player == WHITE_PLAYER)
        {
            blackWinTimes++;
        }
        else
        {
            ;
        }
        ScoreLabel->setText(QString("%1 : %2").arg(blackWinTimes).arg(whiteWinTimes));

        ChessBoardWidget->resetChessBoard();
    });
}

MainWindow::~MainWindow()
{
    ;
}
