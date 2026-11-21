#include "heads/Game_mode.h"

Game_mode::Game_mode(QWidget *parent)
    : QWidget{parent}{}
void Game_mode::setplayer(int code) {
	switch (code)
	{
	case(1):
		player = new player1(nullptr);
		break;
	}
}
Game_mode::~Game_mode() {
}
