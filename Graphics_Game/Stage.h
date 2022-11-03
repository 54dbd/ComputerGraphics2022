//
// Created by Administrator on 3/11/2022.
//

#ifndef GRAPHICSGAME_STAGE_H
#define GRAPHICSGAME_STAGE_H
#include "Brush.h"
#include "Coin.h"
#include "Player.h"
class Stage :public Brush{
private:
    QPoint pos;//玩家位置 窗口交互与player传递用
    moveState& _state;
    Coin* _coin;
    Player* _player;
    long& _updateCount;
    QPainter& _painter;
    QPen& _pen;
public:
    Stage(int W, QPainter& P, QPen& Pen,int playerX, int playerY, moveState &state,long CT):Brush(W,P,Pen),_updateCount(CT),_state(state),_painter(P),_pen(Pen){
        _updateCount++;
        _player = new Player(1,_painter,_pen, pos.x(), pos.y());
        setPos(playerX,playerY);
        _player->generate(_updateCount,_state);
        _coin = new Coin(W,P,Pen,200,300);
        _coin->generate(_updateCount);
    }

    void setPos(int x, int y){
        pos.setY(y);
        pos.setX(x);
        _player->update(x,y);
    }


};


#endif //GRAPHICSGAME_STAGE_H
