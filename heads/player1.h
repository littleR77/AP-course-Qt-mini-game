#ifndef PLAYER1_H
#define PLAYER1_H
#include<QString>
#include "player.h"

class player1 : public Player
{
    Q_OBJECT
public:
    bool invisible=false;
    qreal aspeed = 400;
    qreal xspeed = 0;
    qreal yspeed = 0;
    qreal maxspeed = 500;
    const QString ppos = ":/resources/bocchi_r.gif";
    const QString lpos = ":/resources/bocchi_l.gif";
    const QString mpos = ":/resources/bocchi.gif";
    const QString lmpos = ":/resources/leftbocchi.gif";
    const QString dpos = ":/resources/slidebocchi_r.gif";
    const QString ldpos = ":/resources/slidebocchi_l.gif";
    explicit player1(QObject *parent = nullptr);
    void shoot();
    qreal myr = 0;
    bool dodgestate = false;
    bool untouchable = false;
};

#endif // PLAYER1_H
