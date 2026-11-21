#ifndef GAME_MODE_H
#define GAME_MODE_H

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include "player.h"
#include "player1.h"
#include "enemy.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QWidget>
#include<Qstring>
#include<vector>
#include<QPainter>
#include<ctime>
#include<QRectF>
#include<QLabel>
#include<QMovie>
#include <QGraphicsTextItem>
#include <QFont>
#include <QGraphicsProxyWidget>
#include<cmath>
#include <QGuiApplication>
#include <QScreen>
#include <QStyle>
#include <QVBoxLayout>
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>
#include<QParallelAnimationGroup>
#include<QPushButton>
#include<QIcon>
#include <QMediaPlayer>
#include <QAudioOutput>


class Game_mode : public QWidget
{
    Q_OBJECT
public:
    explicit Game_mode(QWidget *parent = nullptr);
    ~Game_mode();
    virtual void start()=0;//启动并初始化游戏
    virtual void end()=0;//退出
    bool isActive()const{return active;}
    

protected:
    //按键控制
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    virtual void keyReleaseEvent(QKeyEvent* event) = 0;
    //位置更新
    virtual void updatePlayerPosition()=0;
    virtual void updateEnemyPosition() = 0;
    bool keyW = false;
    bool keyA = false;
    bool keyS = false;
    bool keyD = false;
    //鼠标控制
    bool MousePressed = false;
    QPointF mousePos; // 存储鼠标位置
    virtual void mousePressEvent(QMouseEvent* event)=0 ;
    virtual void mouseReleaseEvent(QMouseEvent* event)=0;
    virtual void mouseMoveEvent(QMouseEvent* event)=0;
    void setplayer(int code);
    player1* player;//玩家
    bool active;//模式是否激活
    QTimer* moveTimer = nullptr;//角色移动计时器
    QTimer* EnemymoveTimer = nullptr;//敌人移动计时器
    QTimer* modeTimer = nullptr;//游戏计时器
    QTimer* checkTimer = nullptr;//检查计时器
    QGraphicsScene* myscene = nullptr;//游戏场景
    QGraphicsPixmapItem* background=nullptr;//背景
    QGraphicsView* view = nullptr;
    Game_mode* currentMode = nullptr;//模式指针
    int difficulty=1;//难度
    QMovie* playerMovie=nullptr;//玩家动画
    QGraphicsProxyWidget* playerProxyWidget = nullptr;
    virtual void checkpertime() = 0;
signals:
};


#endif // GAME_MODE_H
