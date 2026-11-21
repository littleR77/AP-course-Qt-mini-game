#include "heads/player1.h"

player1::player1(QObject* parent)
    : Player{ parent }
{
    Hp = 50;damage = 10;
    weapon = new Weapon1();
}
void player1::shoot(){

}
