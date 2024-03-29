#include "chessboard.h"

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);

    isStart = false;
    player = BLACK_PLAYER;

    humanPosRow = 0;
    humanPosColumn = 0;
    aiPosRow = 0;
    aiPosColumn = 0;
    firstPointRowTemp = -1;
    firstPointColumnTemp = -1;
    firstPointRow = -1;
    firstPointColumn = -1;
    result = 0;
    winType = NONE;

    mousePressed = false;
    mouseMoving = false;
    chessIsFull = false;

    memset(&chessInfo, 0, sizeof(ChessInfo));
    rowColumnVector.clear();
    chessInfoVector.clear();

    this->setFixedSize(480, 480);

    QPainter painter;
    drawChessBoard(painter);
}

void ChessBoard::drawChessBoard(QPainter &painter)
{
    pen.setColor(QColor(100, 100, 100));
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    brush.setColor(QColor(228, 190, 130));
    painter.setBrush(brush);

    painter.drawRect(0, 0, this->width(), this->height());

    for (int index = 0; index < ROW; index++)
    {
        painter.drawLine(QPoint(LEFTPOINT, LEFTPOINT + STEP * index), QPoint(RIGHTPOINT, LEFTPOINT + STEP * index));
    }

    for (int index = 0; index < COLUMN; index++)
    {
        painter.drawLine(QPoint(LEFTPOINT + STEP * index, LEFTPOINT), QPoint(LEFTPOINT + STEP * index, RIGHTPOINT));
    }

    brush.setColor(QColor(80, 80, 80));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawEllipse(QPoint(LEFTPOINT + 3 * STEP, LEFTPOINT + 3 * STEP), 4, 4);
    painter.drawEllipse(QPoint(RIGHTPOINT - 3 * STEP, LEFTPOINT + 3 * STEP), 4, 4);
    painter.drawEllipse(QPoint(LEFTPOINT + 3 * STEP, RIGHTPOINT - 3 * STEP), 4, 4);
    painter.drawEllipse(QPoint(RIGHTPOINT - 3 * STEP, RIGHTPOINT - 3 * STEP), 4, 4);
    painter.drawEllipse(QPoint(LEFTPOINT + 7 * STEP, LEFTPOINT + 7 * STEP), 4, 4);

    font.setFamily("Microsoft YaHei");
    font.setPointSize(9);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(25, 21, "A");
    painter.drawText(55, 21, "B");
    painter.drawText(85, 21, "C");
    painter.drawText(115, 21, "D");
    painter.drawText(145, 21, "E");
    painter.drawText(175, 21, "F");
    painter.drawText(205, 21, "G");
    painter.drawText(235, 21, "H");
    painter.drawText(265, 21, "I");
    painter.drawText(295, 21, "J");
    painter.drawText(325, 21, "K");
    painter.drawText(355, 21, "L");
    painter.drawText(385, 21, "M");
    painter.drawText(415, 21, "N");
    painter.drawText(445, 21, "O");
    painter.drawText(13, 35, "1");
    painter.drawText(13, 65, "2");
    painter.drawText(13, 95, "3");
    painter.drawText(13, 125, "4");
    painter.drawText(13, 155, "5");
    painter.drawText(13, 185, "6");
    painter.drawText(13, 215, "7");
    painter.drawText(13, 245, "8");
    painter.drawText(13, 275, "9");
    painter.drawText(10, 305, "10");
    painter.drawText(10, 335, "11");
    painter.drawText(10, 365, "12");
    painter.drawText(10, 395, "13");
    painter.drawText(10, 425, "14");
    painter.drawText(10, 455, "15");

    return ;
}

void ChessBoard::resetChessBoard()
{
    isStart = false;
    player = BLACK_PLAYER;

    humanPosRow = 0;
    humanPosColumn = 0;
    aiPosRow = 0;
    aiPosColumn = 0;
    firstPointRowTemp = -1;
    firstPointColumnTemp = -1;
    firstPointRow = -1;
    firstPointColumn = -1;
    result = 0;
    winType = NONE;

    mousePressed = false;
    mouseMoving = false;
    chessIsFull = false;

    memset(&chessInfo, 0, sizeof(ChessInfo));
    rowColumnVector.clear();
    chessInfoVector.clear();

    update();

    return ;
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    mouseMoving = false;
    if (!isStart)
    {
        return ;
    }
    else
    {
        ;
    }
    if (event->button() == Qt::LeftButton)
    {
        int xPos = event->x();
        int yPos = event->y();
        humanPosRow = yPos / STEP + yPos % STEP / (STEP / 2);
        humanPosColumn = xPos / STEP + xPos % STEP / (STEP / 2);
        if ((humanPosRow < 1) || (humanPosRow > 15))
        {
            return ;
        }
        else
        {
            ;
        }
        if ((humanPosColumn < 1) || (humanPosColumn > 15))
        {
            return ;
        }
        else
        {
            ;
        }
        if (!rowColumnVector.contains({humanPosRow, humanPosColumn}))
        {
            mousePressed = true;

            AImodel.actionByHuman(humanPosRow, humanPosColumn);

            rowColumnVector.push_back({humanPosRow, humanPosColumn});
            chessInfo.posRow = humanPosRow;
            chessInfo.posColumn = humanPosColumn;
            chessInfo.color = player;
            chessInfoVector.push_back(chessInfo);

            update();
            player = WHITE_PLAYER;
            emit SWITCH_PHOTO(player);

            QEventLoop loop;
            QTimer::singleShot(100, &loop, SLOT(quit()));
            loop.exec();

            if (AImodel.isWin(firstPointRowTemp, firstPointColumnTemp, result, winType))
            {
                firstPointRow = firstPointRowTemp;
                firstPointColumn = firstPointColumnTemp;
                update();
                if (result == 'B')
                {
                    player = BLACK_PLAYER;
                }
                else if (result == 'W')
                {
                    player = WHITE_PLAYER;
                }
                else
                {
                    ;
                }
                emit IS_WIN(player);

                return ;
            }
            else
            {
                ;
            }

            chessIsFull = AImodel.chessIsFull();
            if (chessIsFull)
            {
                update();
                emit CHESS_IS_FULL();
                return ;
            }
            else
            {
                ;
            }

            AImodel.actionByAI(aiPosRow, aiPosColumn);

            rowColumnVector.push_back({aiPosRow, aiPosColumn});
            chessInfo.posRow = aiPosRow;
            chessInfo.posColumn = aiPosColumn;
            chessInfo.color = player;
            chessInfoVector.push_back(chessInfo);

            update();
            player = BLACK_PLAYER;
            emit SWITCH_PHOTO(player);

            QTimer::singleShot(100, &loop, SLOT(quit()));
            loop.exec();

            if (AImodel.isWin(firstPointRowTemp, firstPointColumnTemp, result, winType))
            {
                firstPointRow = firstPointRowTemp;
                firstPointColumn = firstPointColumnTemp;
                update();
                if (result == 'B')
                {
                    player = BLACK_PLAYER;
                }
                else if (result == 'W')
                {
                    player = WHITE_PLAYER;
                }
                else
                {
                    ;
                }
                emit IS_WIN(player);

                return ;
            }
            else
            {
                ;
            }
        }
        else
        {
            qDebug() << "重复位置";
        }
    }
    else
    {
        ;
    }

    return QWidget::mousePressEvent(event);
}

void ChessBoard::mouseMoveEvent(QMouseEvent *event)
{
    int xPos = event->x();
    int yPos = event->y();
    humanPosRow = yPos / STEP + yPos % STEP / (STEP / 2);
    humanPosColumn = xPos / STEP + xPos % STEP / (STEP / 2);
    if ((humanPosRow < 1) || (humanPosRow > 15))
    {
        mouseMoving = false;
        update();
        return ;
    }
    else
    {
        ;
    }
    if ((humanPosColumn < 1) || (humanPosColumn > 15))
    {
        mouseMoving = false;
        update();
        return ;
    }
    else
    {
        ;
    }
    mouseMoving = true;
    update();

    return QWidget::mouseMoveEvent(event);
}

void ChessBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing); //设置抗锯齿
	
    drawChessBoard(painter);

    if (isStart && mouseMoving)
    {
        painter.drawPixmap(LEFTPOINT * humanPosColumn - 17, LEFTPOINT * humanPosRow - 17, 34, 34, QPixmap(":/images/mark.png"));
    }
    else
    {
        ;
    }
    if (mousePressed)
    {
        for (int index = 0; index < chessInfoVector.size(); index++)
        {
            if (chessInfoVector[index].color == BLACK_PLAYER)
            {
                //painter.drawPixmap(LEFTPOINT * chessInfoVector[index].humanPosColumn - 16, LEFTPOINT * chessInfoVector[index].humanPosRow - 16, 32, 32, QPixmap(":/images/black.png"));
                brush.setColor(QColor(0, 0, 0));
                brush.setStyle(Qt::SolidPattern);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(LEFTPOINT * chessInfoVector[index].posColumn, LEFTPOINT * chessInfoVector[index].posRow), STEP / 2 - 4, STEP / 2 - 4);

                if (index == (chessInfoVector.size() - 1))
                {
                    pen.setColor(QColor(53, 125, 210));
                    pen.setWidth(3);
                    pen.setStyle(Qt::SolidLine);
                    painter.setPen(pen);
                    QRect rect(LEFTPOINT * chessInfoVector[index].posColumn - 12, LEFTPOINT * chessInfoVector[index].posRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                    painter.drawArc(rect, 0 * 16, 360 * 16);

                    if (chessIsFull)
                    {
                        pen.setColor(QColor(255, 0, 0));
                        pen.setWidth(3);
                        pen.setStyle(Qt::SolidLine);
                        painter.setPen(pen);
                        font.setFamily("Microsoft YaHei");
                        font.setPointSize(28);
                        font.setBold(false);
                        painter.setFont(font);
                        painter.drawText(LEFTPOINT + 5 * STEP, LEFTPOINT + 7 * STEP, "和棋！");
                        return QWidget::paintEvent(event);
                    }
                    else
                    {
                        ;
                    }

                    if ((firstPointRow != -1) && (firstPointColumn != -1))
                    {
                        switch (winType)
                        {
                            case NONE:
                            {
                                break;
                            }
                            case HORIZONTAL:
                            {
                                pen.setColor(QColor(53, 125, 210));
                                pen.setWidth(3);
                                pen.setStyle(Qt::SolidLine);
                                painter.setPen(pen);
                                QRect rect1(LEFTPOINT * (firstPointColumn + 0) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect2(LEFTPOINT * (firstPointColumn + 1) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect3(LEFTPOINT * (firstPointColumn + 2) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect4(LEFTPOINT * (firstPointColumn + 3) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect5(LEFTPOINT * (firstPointColumn + 4) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                painter.drawArc(rect1, 0 * 16, 360 * 16);
                                painter.drawArc(rect2, 0 * 16, 360 * 16);
                                painter.drawArc(rect3, 0 * 16, 360 * 16);
                                painter.drawArc(rect4, 0 * 16, 360 * 16);
                                painter.drawArc(rect5, 0 * 16, 360 * 16);
                                break;
                            }
                            case VERTICAL:
                            {
                                pen.setColor(QColor(53, 125, 210));
                                pen.setWidth(3);
                                pen.setStyle(Qt::SolidLine);
                                painter.setPen(pen);
                                QRect rect1(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow  + 0) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect2(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow + 1) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect3(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow + 2) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect4(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow+ 3) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect5(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow  + 4) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                painter.drawArc(rect1, 0 * 16, 360 * 16);
                                painter.drawArc(rect2, 0 * 16, 360 * 16);
                                painter.drawArc(rect3, 0 * 16, 360 * 16);
                                painter.drawArc(rect4, 0 * 16, 360 * 16);
                                painter.drawArc(rect5, 0 * 16, 360 * 16);
                                break;
                            }
                            case SOUTHWEST:
                            {
                                pen.setColor(QColor(53, 125, 210));
                                pen.setWidth(3);
                                pen.setStyle(Qt::SolidLine);
                                painter.setPen(pen);
                                QRect rect1(LEFTPOINT * (firstPointColumn - 0) - 12, LEFTPOINT * (firstPointRow + 0) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect2(LEFTPOINT * (firstPointColumn - 1) - 12, LEFTPOINT * (firstPointRow + 1) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect3(LEFTPOINT * (firstPointColumn - 2) - 12, LEFTPOINT * (firstPointRow + 2) -12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect4(LEFTPOINT * (firstPointColumn - 3) - 12, LEFTPOINT * (firstPointRow + 3) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect5(LEFTPOINT * (firstPointColumn - 4) - 12, LEFTPOINT * (firstPointRow + 4) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                painter.drawArc(rect1, 0 * 16, 360 * 16);
                                painter.drawArc(rect2, 0 * 16, 360 * 16);
                                painter.drawArc(rect3, 0 * 16, 360 * 16);
                                painter.drawArc(rect4, 0 * 16, 360 * 16);
                                painter.drawArc(rect5, 0 * 16, 360 * 16);
                                break;
                            }
                            case SOUTHEAST:
                            {
                                pen.setColor(QColor(53, 125, 210));
                                pen.setWidth(3);
                                pen.setStyle(Qt::SolidLine);
                                painter.setPen(pen);
                                QRect rect1(LEFTPOINT * (firstPointColumn + 0) - 12, LEFTPOINT * (firstPointRow + 0 ) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect2(LEFTPOINT * (firstPointColumn + 1) - 12, LEFTPOINT * (firstPointRow + 1) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect3(LEFTPOINT * (firstPointColumn + 2) - 12, LEFTPOINT * (firstPointRow + 2) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect4(LEFTPOINT * (firstPointColumn + 3) - 12, LEFTPOINT * (firstPointRow + 3) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect5(LEFTPOINT * (firstPointColumn + 4) - 12, LEFTPOINT * (firstPointRow + 4) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                painter.drawArc(rect1, 0 * 16, 360 * 16);
                                painter.drawArc(rect2, 0 * 16, 360 * 16);
                                painter.drawArc(rect3, 0 * 16, 360 * 16);
                                painter.drawArc(rect4, 0 * 16, 360 * 16);
                                painter.drawArc(rect5, 0 * 16, 360 * 16);
                                break;
                            }
                            default:
                            {
                                ;
                            }
                        }
                        pen.setColor(QColor(255, 0, 0));
                        pen.setWidth(3);
                        pen.setStyle(Qt::SolidLine);
                        painter.setPen(pen);
                        font.setFamily("Microsoft YaHei");
                        font.setPointSize(28);
                        font.setBold(false);
                        painter.setFont(font);
                        painter.drawText(LEFTPOINT + 3 * STEP, LEFTPOINT + 7 * STEP, "恭喜，黑棋获胜！");
                    }
                    else
                    {
                        ;
                    }
                }
                else
                {
                    ;
                }
            }
            else if (chessInfoVector[index].color == WHITE_PLAYER)
            {
                //painter.drawPixmap(LEFTPOINT * chessInfoVector[index].humanPosColumn - 25, LEFTPOINT * chessInfoVector[index].humanPosRow - 25, 50, 50, QPixmap(":/images/white.png"));
                brush.setColor(QColor(255, 255, 255));
                brush.setStyle(Qt::SolidPattern);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(LEFTPOINT * chessInfoVector[index].posColumn, LEFTPOINT * chessInfoVector[index].posRow), STEP / 2 - 4, STEP / 2 - 4);

                if (index == (chessInfoVector.size() - 1))
                {
                    pen.setColor(QColor(53, 125, 210));
                    pen.setWidth(3);
                    pen.setStyle(Qt::SolidLine);
                    painter.setPen(pen);
                    QRect rect(LEFTPOINT * chessInfoVector[index].posColumn - 12, LEFTPOINT * chessInfoVector[index].posRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                    painter.drawArc(rect, 0 * 16, 360 * 16);

                    if (chessIsFull)
                    {
                        pen.setColor(QColor(255, 0, 0));
                        pen.setWidth(3);
                        pen.setStyle(Qt::SolidLine);
                        painter.setPen(pen);
                        font.setFamily("Microsoft YaHei");
                        font.setPointSize(28);
                        font.setBold(false);
                        painter.setFont(font);
                        painter.drawText(LEFTPOINT + 5 * STEP, LEFTPOINT + 7 * STEP, "和棋！");
                        return QWidget::paintEvent(event);
                    }
                    else
                    {
                        ;
                    }

                    if ((firstPointRow != -1) && (firstPointColumn != -1))
                    {
                        switch (winType)
                        {
                            case NONE:
                            {
                                break;
                            }
                            case HORIZONTAL:
                            {
                                pen.setColor(QColor(53, 125, 210));
                                pen.setWidth(3);
                                pen.setStyle(Qt::SolidLine);
                                painter.setPen(pen);
                                QRect rect1(LEFTPOINT * (firstPointColumn + 0) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect2(LEFTPOINT * (firstPointColumn + 1) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect3(LEFTPOINT * (firstPointColumn + 2) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect4(LEFTPOINT * (firstPointColumn + 3) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect5(LEFTPOINT * (firstPointColumn + 4) - 12, LEFTPOINT * firstPointRow - 12, CHESS_RADIUS, CHESS_RADIUS);
                                painter.drawArc(rect1, 0 * 16, 360 * 16);
                                painter.drawArc(rect2, 0 * 16, 360 * 16);
                                painter.drawArc(rect3, 0 * 16, 360 * 16);
                                painter.drawArc(rect4, 0 * 16, 360 * 16);
                                painter.drawArc(rect5, 0 * 16, 360 * 16);
                                break;
                            }
                            case VERTICAL:
                            {
                                pen.setColor(QColor(53, 125, 210));
                                pen.setWidth(3);
                                pen.setStyle(Qt::SolidLine);
                                painter.setPen(pen);
                                QRect rect1(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow  + 0) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect2(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow + 1) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect3(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow + 2) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect4(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow+ 3) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect5(LEFTPOINT * firstPointColumn - 12, LEFTPOINT * (firstPointRow  + 4) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                painter.drawArc(rect1, 0 * 16, 360 * 16);
                                painter.drawArc(rect2, 0 * 16, 360 * 16);
                                painter.drawArc(rect3, 0 * 16, 360 * 16);
                                painter.drawArc(rect4, 0 * 16, 360 * 16);
                                painter.drawArc(rect5, 0 * 16, 360 * 16);
                                break;
                            }
                            case SOUTHWEST:
                            {
                                pen.setColor(QColor(53, 125, 210));
                                pen.setWidth(3);
                                pen.setStyle(Qt::SolidLine);
                                painter.setPen(pen);
//                                QRect rect1(LEFTPOINT * (firstPointColumn + 0) - 12, LEFTPOINT * (firstPointRow - 0) - 12, CHESS_RADIUS, CHESS_RADIUS);
//                                QRect rect2(LEFTPOINT * (firstPointColumn + 1) - 12, LEFTPOINT * (firstPointRow - 1) - 12, CHESS_RADIUS, CHESS_RADIUS);
//                                QRect rect3(LEFTPOINT * (firstPointColumn + 2) - 12, LEFTPOINT * (firstPointRow - 2) - 12, CHESS_RADIUS, CHESS_RADIUS);
//                                QRect rect4(LEFTPOINT * (firstPointColumn + 3) - 12, LEFTPOINT * (firstPointRow - 3) - 12, CHESS_RADIUS, CHESS_RADIUS);
//                                QRect rect5(LEFTPOINT * (firstPointColumn + 4) - 12, LEFTPOINT * (firstPointRow - 4) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect1(LEFTPOINT * (firstPointColumn - 0) - 12, LEFTPOINT * (firstPointRow + 0) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect2(LEFTPOINT * (firstPointColumn - 1) - 12, LEFTPOINT * (firstPointRow + 1) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect3(LEFTPOINT * (firstPointColumn - 2) - 12, LEFTPOINT * (firstPointRow + 2) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect4(LEFTPOINT * (firstPointColumn - 3) - 12, LEFTPOINT * (firstPointRow + 3) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect5(LEFTPOINT * (firstPointColumn - 4) - 12, LEFTPOINT * (firstPointRow + 4) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                painter.drawArc(rect1, 0 * 16, 360 * 16);
                                painter.drawArc(rect2, 0 * 16, 360 * 16);
                                painter.drawArc(rect3, 0 * 16, 360 * 16);
                                painter.drawArc(rect4, 0 * 16, 360 * 16);
                                painter.drawArc(rect5, 0 * 16, 360 * 16);
                                break;
                            }
                            case SOUTHEAST:
                            {
                                pen.setColor(QColor(53, 125, 210));
                                pen.setWidth(3);
                                pen.setStyle(Qt::SolidLine);
                                painter.setPen(pen);
                                QRect rect1(LEFTPOINT * (firstPointColumn + 0) - 12, LEFTPOINT * (firstPointRow + 0) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect2(LEFTPOINT * (firstPointColumn + 1) - 12, LEFTPOINT * (firstPointRow + 1) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect3(LEFTPOINT * (firstPointColumn + 2) - 12, LEFTPOINT * (firstPointRow + 2) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect4(LEFTPOINT * (firstPointColumn + 3) - 12, LEFTPOINT * (firstPointRow + 3) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                QRect rect5(LEFTPOINT * (firstPointColumn + 4) - 12, LEFTPOINT * (firstPointRow + 4) - 12, CHESS_RADIUS, CHESS_RADIUS);
                                painter.drawArc(rect1, 0 * 16, 360 * 16);
                                painter.drawArc(rect2, 0 * 16, 360 * 16);
                                painter.drawArc(rect3, 0 * 16, 360 * 16);
                                painter.drawArc(rect4, 0 * 16, 360 * 16);
                                painter.drawArc(rect5, 0 * 16, 360 * 16);
                                break;
                            }
                            default:
                            {
                                ;
                            }
                        }
                        pen.setColor(QColor(255, 0, 0));
                        pen.setWidth(3);
                        pen.setStyle(Qt::SolidLine);
                        painter.setPen(pen);
                        font.setFamily("Microsoft YaHei");
                        font.setPointSize(28);
                        font.setBold(false);
                        painter.setFont(font);
                        painter.drawText(LEFTPOINT + 3 * STEP, LEFTPOINT + 7 * STEP, "恭喜，白棋获胜！");
                    }
                    else
                    {
                        ;
                    }
                }
                else
                {
                    ;
                }
            }
        }
    }
    else
    {
        ;
    }

    return QWidget::paintEvent(event);
}

ChessBoard::~ChessBoard()
{
    ;
}
