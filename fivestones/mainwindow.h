#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class MainWindow : public QWidget, public Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int blackWinTimes;
    int whiteWinTimes;

protected:

signals:

public slots:

};
#endif // MAINWINDOW_H
