//
// Created by Administrator on 3/11/2022.
//

#ifndef GRAPHICSGAME_STAGE_H
#define GRAPHICSGAME_STAGE_H
#include "Brush.h"
#include "Coin.h"
#include "Player.h"
#include "StageInfo.h"
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
    StageInfo _stageInfo;
    Stage(int W, QPainter& P, QPen& Pen,int playerX, int playerY, moveState &state, long CT, int stageNo):Brush(W,P,Pen),_updateCount(CT),
                                                                                                          _stageInfo(stageNo, _updateCount),
                                                                                                          _state(state),
                                                                                                          _painter(P),
                                                                                                          _pen(Pen){
//        _updateCount++;
        _player = new Player(1,_painter,_pen, playerX, playerY);
        setPos(playerX,playerY);
        _player->generate(_updateCount,_state);
        if(stageNo==1||stageNo==2){
            _coin = new Coin(W,P,Pen,560,60);
        }else if(stageNo==3){
            _coin = new Coin(W,P,Pen,450,280);
        }else if(stageNo==4){
            _coin = new Coin(W,P,Pen,550,330);
        }else if(stageNo==5){
            _coin = new Coin(W,P,Pen,50,330);
        }
        _coin->generate(_updateCount);
    }

    void setPos(int x, int y){
        pos.setY(y);
        pos.setX(x);
        _player->update(x,y);
    }

    QPoint getCoinPos(){
        return _coin->getPos();
    }

};


#endif //GRAPHICSGAME_STAGE_H
