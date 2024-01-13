#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QDebug>
#include<QPushButton>
#include<QTimer>
#include<QMessageBox>
#include<startsettingswidget.h>
#include<fstream>
#include<ai.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QPushButton * btn[8][8];
    QTimer * timer = new QTimer;
    StartSettingsWidget * p = new StartSettingsWidget;

    int dx[8]{-1,-1,0,1,1,1,0,-1},dy[8]{0,-1,-1,-1,0,1,1,1};
    int board[8][8],boardai[8][8];//   1:blace  -1:white   0:empty
    int color=-1,colorai,x,y,blackchessnum,whitechessnum;
    int mode=2; //  2:人人对战  0:后手ai  1:先手ai
    int stop=1;   // 1:待输入  0：可以输入  2:不准输入
    int round;
    void out();//显示
    void init();//初始化
    bool inboard(int x,int y);
    bool canput(int x,int y,int color);
    void putdown(int x,int y,int color);
    int check();
    void changemode(int x);
    void nextround();
    void victory(int color);
    void save();
    void read();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
