#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->BlackChessIconLabel->setScaledContents(true);
    ui->WhiteChessIconLabel->setScaledContents(true);

    p->setWindowModality(Qt::ApplicationModal);
    connect(p,&StartSettingsWidget::setMode,this,&Widget::changemode);

    connect(ui->SaveButton,&QPushButton::clicked,this,&Widget::save);
    connect(ui->ReadButton,&QPushButton::clicked,this,&Widget::read);

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            btn[i][j] = new QPushButton(ui->ChessBoardWidget);
            btn[i][j]->resize(100,100);
            btn[i][j]->move(i*100,j*100);
            connect(btn[i][j],&QPushButton::clicked,this,[=](){
                if(stop==0 && canput(i,j,color))
                {
                    //qDebug()<<"Yes";
                    putdown(i,j,color);
                }
                //else qDebug()<<"No";
            });
        }

    //Start
    connect(ui->StartButton,&QPushButton::clicked,this,[=](){
        if(stop==0||stop==3)
        {
            p->show();
        }
    });

    //Exit
    connect(ui->ExitButton,&QPushButton::clicked,this,&Widget::close);

    connect(timer,&QTimer::timeout,this,[=](){
        //qDebug()<<(int)stop;
        if(stop==1){
            nextround();
        }
    });

    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::out()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            switch(board[i][j])
            {
            case 0:
            {
                btn[i][j]->setIcon(QIcon(":/image/NoPiece.png"));
                btn[i][j]->setIconSize(QSize(100,100));
                break;
            }
            case 1:
            {
                btn[i][j]->setIcon(QIcon(":/image/BlackPiece.png"));
                btn[i][j]->setIconSize(QSize(100,100));
                break;
            }
            case -1:
            {
                btn[i][j]->setIcon(QIcon(":/image/WhitePiece.png"));
                btn[i][j]->setIconSize(QSize(100,100));
                break;
            }
            }
        }
}

void Widget::init()
{
    blackchessnum=2;
    whitechessnum=2;
    color=-1;
    round=0;
    memset(board,0,sizeof board);
    board[3][3]=-1;
    board[3][4]=1;
    board[4][3]=1;
    board[4][4]=-1;
    out();
    timer->start(100);
    stop=1;
}

bool Widget::inboard(int x,int y)
{
    if(x<0||x>=8||y<0||y>=8) return 0;
    return 1;
}

bool Widget::canput(int x,int y,int color)
{
    if(board[x][y]!=0) return 0;
    bool ans=0;
    for(int dire=0;dire<8;dire++)
    {
        int x1=x+dx[dire],y1=y+dy[dire];
        while(inboard(x1,y1))
        {
            if(board[x1][y1]==0) break;
            if(board[x1][y1]==color)
            {
                if(x1!=x+dx[dire] || y1!=y+dy[dire]) ans=1;
                break;
            }
            x1+=dx[dire];
            y1+=dy[dire];
        }
        if(ans==1) break;
    }
    return ans;
}

void Widget::putdown(int x,int y,int color)
{
    stop=2;
    if(x==-1&&y==-1)
    {
        stop=1;
        return;
    }
    board[x][y]=color;
    for(int dire=0;dire<8;dire++)
    {
        bool flag=0;
        int x1=x+dx[dire],y1=y+dy[dire];
        while(inboard(x1,y1))
        {
            if(board[x1][y1]==0) break;
            if(board[x1][y1]==color)
            {
                flag=1;
                break;
            }
            x1+=dx[dire];
            y1+=dy[dire];
        }
        if(flag==1)
        {
            x1=x+dx[dire],y1=y+dy[dire];
            while(board[x1][y1]!=color)
            {
                board[x1][y1]=color;
                x1+=dx[dire];
                y1+=dy[dire];
            }
        }
    }
    out();
    stop=1;
}

void Widget::nextround()
{
    color*=-1;
    ui->RoundNumLabel->setText(QString::number(round));
    round++;
    int situation=check();
    ui->BlackChessNumLabel->setText(QString::number(blackchessnum));
    ui->WhiteChessNumLabel->setText(QString::number(whitechessnum));
    switch(situation)
    {
    case 1:stop=3;victory(1);break;
    case-1:stop=3;victory(-1);break;
    case 0:break;
    case 3:
    {
        if(round%2!=mode) {stop=0;break;}
        else
        {
            stop=2;
            ai * p = new ai;
            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++)
                {
                    if(board[i][j]>=0) boardai[i][j]=board[i][j];
                    else boardai[i][j]=2;
                }
            if(color==1) colorai=1;
            else colorai=2;
            p->min_max(boardai,x,y,colorai);
            //qDebug()<<x<<y<<colorai;
            putdown(x,y,color);
            break;
        }
    }
    case 2:if(blackchessnum>whitechessnum) {stop=3;victory(1);break;}
        else if(whitechessnum>blackchessnum) {stop=3;victory(-1);break;}
        else {stop=3;victory(0);break;}
    }
}

int Widget::check()//  1:黑赢  -1：白赢   0：不能走   2:结束根据棋子数量计算输赢   3:正常走
{
    int blackcnt=0,whitecnt=0;
    bool cannotmovecolor=1,cannotmoveanticolor=1;

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(board[i][j]==1) blackcnt++;
            else if(board[i][j]==-1) whitecnt++;
            else
            {
                if(cannotmovecolor==1 && canput(i,j,color)) cannotmovecolor=0;
                if(cannotmoveanticolor==1 && canput(i,j,-color)) cannotmoveanticolor=0;
            }
        }
    blackchessnum=blackcnt;
    whitechessnum=whitecnt;
    if(blackcnt==0) return -1;
    if(whitecnt==0) return 1;
    if(blackcnt+whitecnt==64) return 2;
    if(cannotmoveanticolor==1 && cannotmovecolor==1) return 2;
    if(cannotmovecolor==1) return 0;
    return 3;
}

void Widget::victory(int color)
{
    switch(color)
    {
    case 1:
    {
        QMessageBox::information(this,"结束","黑方胜利");
        break;
    }
    case -1:
    {
        QMessageBox::information(this,"结束","白方胜利");
        break;
    }
    case 0:
    {
        QMessageBox::information(this,"结束","平局");
        break;
    }
    }
}
/*
void Widget::ai()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(canput(i,j,color))
            {
                putdown(i,j,color);
                return;
            }
        }
}
*/
void Widget::changemode(int x)
{
    mode=x;
    init();
}

void Widget::save()//  board  round  color  mode
{
    if(stop!=0)
    {
        QMessageBox::critical(this,"错误","存档失败");
        return;
    }
    stop=2;
    std::fstream file("save.txt",std::ios::out);
    if(!file.is_open())
    {
        QMessageBox::critical(this,"错误","打开失败");
        return;
    }
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            file<<board[i][j]<<" ";
        }
    file<<round-1<<" "<<-color<<" "<<mode;
    file.close();
    QMessageBox::information(this,"提示","保存完成");
}

void Widget::read()
{
    stop=2;
    std::fstream file;
    file.open("save.txt",std::ios::in);
    if(!file.is_open())
    {
        QMessageBox::critical(this,"错误","打开失败");
        return;
    }
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            file>>board[i][j];
        }
    file>>round>>color>>mode;
    file.close();
    out();
    stop=1;
}
