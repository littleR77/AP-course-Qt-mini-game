#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include<QGraphicsView>
#include<QWidget>
#include "Game_mode.h"
#include<QPixmap>

class Normal_mode : public Game_mode
{
    Q_OBJECT

private:
    int initHp;
    size_t score=0;
    int mygrenade = 5;
    int mysmokegrenade = 5;
    qreal initaspeed;
    qreal initmaxv;
    qreal xfa;//空气阻力加速度（与速度正比）
    qreal yfa;
    qreal rax= 0;
    qreal ray = 0;//敌人随机移动方向
    qreal bombspeed = 250;
    qreal bgSize;

    const qreal bulletSpeed = 10;
    const QString enemypic = ":/resources/113201048_p3.png";
    const QString grasspic = ":/resources/cao.png";
    const QString scenepos = ":/resources/DesertTileset16x16/DesertTileset16x16/Tileset16x16/Mockup2.png";
    const QString toolpos = ":/Sprout Lands - Sprites - Basic pack/Africa heart.png";
    const QString firepos = ":/resources/113201048_p3.gif";
    const QString heart = ":/resources/heart.png";
    const QString speedy = ":/resources/speedy.png";
    const QString heal = ":/resources/heal.png";
    const QString addweapon = ":/resources/addweapon.png";
    const QString myblood = ":/resources/myblood.png";
    const QString blood = ":/resources/blood.png";
    const QString round = ":/resources/round.png";
    const QString enemyr = ":/resources/enemyR.gif";
    const QString enemyl = ":/resources/enemy.gif";
    const QString headpic = ":/resources/headphoto.png";
    const QString grenadepic = ":/resources/grenade.png";
    const QString smokegrenadepic = ":/resources/smoke.png";
    const QString explode = ":/resources/explode.gif";
    const QString smokegif = ":/resources/smokerelease.gif";
    const QString cursor = "";
    const QString lizi = ":/resources/lizi.gif";
    const QString mydying = ":/resources/dying.gif";
    const QString enemydying = ":/resources/enemydying.gif";
public slots:
    void checkpertime()override;
    void spawnenemy();//敌人生成
public:

    
    void start()override;
    void end()override;
    explicit Normal_mode(QWidget *parent = nullptr);
protected:
    Enemy* target = nullptr;//索敌目标
    QGraphicsProxyWidget* targetEnemywidget = nullptr;
    bool isTargeting = false;
    QTimer* orbitTimer = nullptr;
    QTimer* bulletTimer = nullptr;
    QTimer* enemyTimer = nullptr;
    QTimer* enemyattackTimer = nullptr;
    QTimer* toolTimer = nullptr;
    QTimer* stateTimer = nullptr;
    QTimer* spawnbuTimer = nullptr;
    QTimer* dodgeTimer = nullptr;
    QTimer* mybloodTimer = nullptr;
    QTimer* faTimer = nullptr;
    QTimer* circleTimer = nullptr;
    QTimer* defenseTimer = nullptr;
    QTimer* rspeedTimer = nullptr;
    QTimer* bombTimer = nullptr;
    QTimer* cursorTimer = nullptr;
    QTimer* liziTimer = nullptr;
    QTimer* sizeTimer = nullptr;
    std::vector<int> rx;
    std::vector<int> ry;
    std::vector<QGraphicsProxyWidget*>fireWidgets;//周围的武器
    std::vector<QGraphicsProxyWidget*>firebullets;//射出去的攻击
    std::vector<QGraphicsPixmapItem*>bullets;//子弹容器
    std::vector<Enemy*>enemies;//敌人容器
    std::vector<QGraphicsProxyWidget*> enemywidgets;//敌人图像
    std::vector<QGraphicsPixmapItem*>enemybloods;//敌人血条
    std::vector<QGraphicsPixmapItem*> grassItems;//草丛容器
    std::vector<QGraphicsProxyWidget*> enemybullets;//敌人射出去的子弹
    std::vector<Weapon*>weaponbullets;//敌人射出去的子弹
    std::vector<QGraphicsPixmapItem*>tools;//道具容器
    std::vector<QString>speedybuffs;//加速buff容器
    std::vector<QGraphicsPixmapItem*>bombs;//炸弹容器
    std::vector<QGraphicsProxyWidget*>smokes;//烟雾
    bool keyX = false;
    bool keyV = false;
    qreal dodgeCD = 0;

    void keyPressEvent(QKeyEvent* event)override;
    void keyReleaseEvent(QKeyEvent* event)override;
    void updatePlayerPosition()override;//玩家位置

    void spawngrass();//草丛生成
    void checkplayeringrass();//检查角色处于草丛内(包括烟雾)
    void spawntool();//道具生成
    void spawnfire();//生成武器
 
    bool checkcollideswithme(QGraphicsProxyWidget* enemywidget);
    Enemy* checkcollides();
    Enemy* checkenemycollides(QGraphicsProxyWidget* enemywidget);
    void updateEnemyPosition()override;//更新敌人位置
    void updateenemybullets();//敌人子弹
    void enemyattack();//敌人攻击
    void updataplayerstate();//更新角色状态
    void updateenemystate();//更新敌人状态
    void checkbuff();//检查buff
    void updatefirepos();//旋转
    void updatefirebullets();//子弹追踪
    void spawnfireps();
    void dodge();//闪避
    void dodgerecovery();//冷却恢复
    void checkdefense();
    void updatemybloodpos();//更新血条位置（左上角）和血量,头像,道具提示
    void updatebloodspos();//更新敌人血条
    void updatecirclepos();//更新索敌标志位置
    void updatefa();//更新阻力
    void targetEnemy(const QPointF& clickPos); // 索敌函数

    void mousePressEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void switchanime(QMovie* newMovie);//切换人物动画
    void updaterandomspeed();//更新敌人随机移动方向
    int randnum = 0;
    void spawngrenade(QPointF destination);//掷出手雷
    void grenadeexplosion(QGraphicsPixmapItem* grenade);//手雷爆炸
    void smokerelease(QGraphicsPixmapItem* smokegrenade);//烟雾释放
    void spawnsmokegrenade(QPointF destination);//烟雾弹
    void updatebombspos();//更新投掷物位置
    void updatecursorpos();//更新提示光标位置
    void updatelizipos();//拖尾
    void spawnweapon(QGraphicsProxyWidget* character,Enemy* enemy);//为固定对象加武器
    void deathanime(int n, QPointF pos,int width,int height);//死亡动画
    void updatesize();
    QMovie* playerMovieLeft = nullptr;    // 向左的动画
    QMovie* playerMovieRight = nullptr;   // 向右的动画
    QMovie* playerMovieMoving = nullptr;  // 移动状态的动画
    QMovie* playerMovieMovingL = nullptr;
    QMovie* playerDodgeMovie = nullptr;
    QMovie* playerDodgeMovieL = nullptr;
    QMovie* enemymovieL = nullptr;
    QMovie* enemymovieR=nullptr;
    QMovie* currentPlayerMovie = nullptr; // 当前正在播放的动画
    QLabel* playerLabel;
    QPixmap originalmyblood;
    QPixmap originalblood;
    QPixmap headpicture;
    QPixmap mapImage;
    QGraphicsPixmapItem* mybloodItem;
    QGraphicsPixmapItem* myheadpic;
    QGraphicsPixmapItem* grenadeamount;
    QGraphicsTextItem* grenadeText;
    QGraphicsPixmapItem* smokeamount;
    QGraphicsPixmapItem* speedyamount;
    QGraphicsTextItem* smokeText;
    QGraphicsPixmapItem* circleitem = nullptr;
    QPixmap cursorpic;
    QGraphicsPixmapItem* cursoritem = nullptr;
    QPixmap transparentPixmap;
    QPushButton* spawn;
    QGraphicsProxyWidget* spawnwidget = nullptr;
    qreal mybloodW = 0;qreal mybloodH = 0;
    QMediaPlayer* fire;
    QAudioOutput* fireout;
    QMediaPlayer* aaa;
    QAudioOutput* aaaout;
    QMediaPlayer* fei;
    QAudioOutput* feiout;
    QMediaPlayer* man;
    QAudioOutput* manout;
    QMediaPlayer* amns;
    QAudioOutput* amnsout;
    QMediaPlayer* biu;
    QAudioOutput* biuout;
    QMediaPlayer* bgm;
    QAudioOutput* bgmout;
    QMediaPlayer* over;
    QAudioOutput* overout;
    QMediaPlayer* tool;
    QAudioOutput* toolout;
    void shoot();//玩家攻击
    void checkdeath();//玩家死亡或胜利
    QTime startTime;
};

#endif // NORMAL_MODE_H
