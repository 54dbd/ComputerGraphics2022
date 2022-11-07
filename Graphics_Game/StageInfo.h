#pragma once
class StageInfo{
public:
    int _stageNo;
    long _updateCount;

    QVector<QPen> _brush;

    QVector<QRect> _rects;
    QVector<QRect> _line;
    QVector<QVector<QPoint>> _polygon;
    vector<vector<QPoint>> _bspline;

    QVector<QPoint> _fills;

    StageInfo(int StageNo, long UpdateCount){
        _stageNo = StageNo;
        _updateCount = UpdateCount;
        if (_stageNo == 1){
            QPen tempPen;
            /*********************矩形*********************/
            // 平台
            tempPen.setWidth(5);
            tempPen.setColor(Qt::black);

            _rects.append(QRect(170, 200, 100, 50));
            _brush.append(tempPen);
            _rects.append(QRect(330 + sin(_updateCount/17.0)*50, 100, 100, 50));
            _brush.append(tempPen);
            _rects.append(QRect(0, 300, 150, 50));
            _brush.append(tempPen);
            _rects.append(QRect(500, 100, 150, 50));
            _brush.append(tempPen);
            /*********************直线*********************/
//            _line.append(QRect(300, 300, 400, 600));
//            _brush.append(tempPen);
            /*********************多边形*********************/
            /*********************B样条*********************/
            // 性能差 不建议和移动的方块一起使用
//            vector<QPoint> tempCurve;
//            tempCurve.emplace_back(200, 325);
//            tempCurve.emplace_back(250, 350);
//            tempCurve.emplace_back(225, 325);
//            tempCurve.emplace_back(275, 350);
//            _bspline.push_back(tempCurve);
//            _brush.append(tempPen);
            /*********************填充*********************/
            for (int i = 0; i < 2; ++i) {
                QRect tempRect = _rects[i];
                _fills.append(QPoint(tempRect.left() + tempRect.width() / 2, tempRect.top() + tempRect.height() / 2));
                _brush.append(tempPen);
            }
        } else if (_stageNo == 2){
            // 关卡2物体
            QPen tempPen;
            /*********************矩形*********************/
            // 平台
            tempPen.setWidth(5);
            tempPen.setColor(Qt::black);

            _rects.append(QRect(0, 100, 150, 300));
            _brush.append(tempPen);
            _rects.append(QRect(200, 0, 150, 300));
            _brush.append(tempPen);

            /*********************直线*********************/

            //平台
            _line.append(QRect(200, 350, 400, 1));
            _brush.append(tempPen);
            _line.append(QRect(350, 150, 100, 1));
            _brush.append(tempPen);
            _line.append(QRect(500, 250, 100, 1));
            _brush.append(tempPen);
            _line.append(QRect(180, 240, 20, 1));
            _brush.append(tempPen);
            /*********************多边形*********************/
            //陷阱
            QPen redPen(tempPen);
            redPen.setColor(Qt::red);
            QVector<QPoint> newPolygon;
            newPolygon.append(QPoint(150, 350));
            newPolygon.append(QPoint(200, 350));
            newPolygon.append(QPoint(175, 300));
            _polygon.append(newPolygon);
            _brush.append(redPen);
            QVector<QPoint> newPolygon2;
            newPolygon2.append(QPoint(500, 250));
            newPolygon2.append(QPoint(525, 250));
            newPolygon2.append(QPoint(512, 228));
            _polygon.append(newPolygon2);
            _brush.append(redPen);
            QVector<QPoint> newPolygon3;
            newPolygon3.append(QPoint(575, 250));
            newPolygon3.append(QPoint(600, 250));
            newPolygon3.append(QPoint(589, 228));
            _polygon.append(newPolygon3);
            _brush.append(redPen);
            QVector<QPoint> newPolygon4;
            newPolygon4.append(QPoint(430, 155));
            newPolygon4.append(QPoint(455, 155));
            newPolygon4.append(QPoint(442, 178));
            _polygon.append(newPolygon4);
            _brush.append(redPen);

            /*********************B样条*********************/

            /*********************填充*********************/

        }else if (_stageNo == 3){
            // 关卡3物体
            QPen tempPen;
            /*********************矩形*********************/
            // 平台
            tempPen.setWidth(5);
            tempPen.setColor(Qt::black);

//            _rects.append(QRect(0, 100, 150, 300));
//            _brush.append(tempPen);
//            _rects.append(QRect(200, 0, 150, 300));
//            _brush.append(tempPen);

            /*********************直线*********************/
            QPen redPen(tempPen);
            redPen.setColor(Qt::red);
            //平台

            //陷阱
            _line.append(QRect(150, 180+sin(_updateCount/20.0)*120, 1, 50));
            _brush.append(redPen);
            _line.append(QRect(450, 180+cos(_updateCount/20.0)*120, 1, 50));
            _brush.append(redPen);
            /*********************多边形*********************/
//            QVector<QPoint> newPolygon;
//            newPolygon.append(QPoint(300, 200));
//            newPolygon.append(QPoint(400, 200));
//            newPolygon.append(QPoint(400, 300));
//            newPolygon.append(QPoint(300, 300));
//            _polygon.append(newPolygon);
            /*********************B样条*********************/
            vector<QPoint> level1;
            level1.push_back(QPoint(-100,150));
            level1.push_back(QPoint(0,100));
            level1.push_back(QPoint(100,150));
            level1.push_back(QPoint(200,100));
            level1.push_back(QPoint(300,150));
            level1.push_back(QPoint(400,100));
            level1.push_back(QPoint(500,150));
            level1.push_back(QPoint(600,100));
            _bspline.push_back(level1);
            _brush.append(tempPen);

            vector<QPoint> level2;
            level2.push_back(QPoint(100,250));
            level2.push_back(QPoint(200,200));
            level2.push_back(QPoint(300,250));
            level2.push_back(QPoint(400,200));
            level2.push_back(QPoint(500,250));
            level2.push_back(QPoint(600,200));
            level2.push_back(QPoint(700,250));
            _bspline.push_back(level2);
            _brush.append(tempPen);

            vector<QPoint> level3;
            level3.push_back(QPoint(-100,350));
            level3.push_back(QPoint(0,300));
            level3.push_back(QPoint(100,350));
            level3.push_back(QPoint(200,300));
            level3.push_back(QPoint(300,350));
            level3.push_back(QPoint(400,300));
            level3.push_back(QPoint(500,350));
            level1.push_back(QPoint(600,300));

            _bspline.push_back(level3);
            _brush.append(tempPen);

            vector<QPoint> level4;
            level4.push_back(QPoint(100,450));
            level4.push_back(QPoint(200,400));
            level4.push_back(QPoint(300,450));
            level4.push_back(QPoint(400,400));
            level4.push_back(QPoint(500,450));
            level4.push_back(QPoint(600,400));
            level1.push_back(QPoint(600,100));

            _bspline.push_back(level4);
            _brush.append(tempPen);
            /*********************填充*********************/

        }else if (_stageNo == 4){
            // 关卡4 物体
            QPen tempPen;
            /*********************矩形*********************/
            // 平台
            tempPen.setWidth(5);
            tempPen.setColor(Qt::black);
            //陷阱
//            QPen redPen(tempPen);
//            redPen.setColor(Qt::red);
//            _rects.append(QRect(300+cos(_updateCount/20.0)*150, 200+sin(_updateCount/20.0)*150, sin(_updateCount/20.0)*25+50, cos(_updateCount/20.0)*20+50));
//            _brush.append(redPen);
//            _rects.append(QRect(0, 100, 150, 300));
//            _brush.append(tempPen);
//            _rects.append(QRect(200, 0, 150, 300));
//            _brush.append(tempPen);

            /*********************直线*********************/

            //平台
            _line.append(QRect(0, 100, 50, 1));
            _brush.append(tempPen);
            _line.append(QRect(550, 375, 50, 1));
            _brush.append(tempPen);

            _line.append(QRect(150+cos(_updateCount/20.0)*50, 140+sin(_updateCount/20.0)*10, 50, 1));
            _brush.append(tempPen);

            _line.append(QRect(250+cos(_updateCount/20.0+2)*50, 240+sin(_updateCount/20.0+2)*10, 50, 1));
            _brush.append(tempPen);

            _line.append(QRect(350+cos(_updateCount/20.0+1)*50, 300+sin(_updateCount/20.0+1)*10, 50, 1));
            _brush.append(tempPen);

            _line.append(QRect(450+cos(_updateCount/20.0+4)*50, 240+sin(_updateCount/20.0+4)*10, 50, 1));
            _brush.append(tempPen);

            _line.append(QRect(450+cos(_updateCount/20.0+2)*50, 240+sin(_updateCount/20.0+2)*10, 50, 1));
            _brush.append(tempPen);

            _line.append(QRect(150+cos(_updateCount/20.0+1)*50, 300+sin(_updateCount/20.0+1)*10, 50, 1));
            _brush.append(tempPen);
//            _brush.append(redPen);
            /*********************多边形*********************/

            QPen redPen(tempPen);
            redPen.setColor(Qt::red);
            int x=300,y=200;
            int width=10;
            QVector<QPoint> ground;
            ground.append(QPoint(0,120));
            ground.append(QPoint(0,400));
            ground.append(QPoint(550,400));
            ground.append(QPoint(50,120));
            _polygon.append(ground);
            _brush.append(redPen);
            QVector<QPoint> newPolygon;
            newPolygon.append(QPoint(x+cos(_updateCount/20.0+1)*50, y+sin(_updateCount/20.0+1)*10));
            newPolygon.append(QPoint(x+width+cos(_updateCount/20.0+1)*50, y+sin(_updateCount/20.0+1)*10));
            newPolygon.append(QPoint(x+width/2+cos(_updateCount/20.0+1)*50, y-width+sin(_updateCount/20.0+1)*10));
            _polygon.append(newPolygon);
            _brush.append(redPen);
            x=400, y=150;
            QVector<QPoint> newPolygon2;
            newPolygon2.append(QPoint(x+cos(_updateCount/20.0+2)*50, y+sin(_updateCount/20.0+2)*10));
            newPolygon2.append(QPoint(x+width+cos(_updateCount/20.0+2)*50, y+sin(_updateCount/20.0+2)*10));
            newPolygon2.append(QPoint(x+width/2+cos(_updateCount/20.0+2)*50, y-width+sin(_updateCount/20.0+2)*10));
            _polygon.append(newPolygon2);
            _brush.append(redPen);
            x=500, y=300;
            QVector<QPoint> newPolygon3;
            newPolygon3.append(QPoint(x+cos(_updateCount/20.0+3)*50, y+sin(_updateCount/20.0+3)*10));
            newPolygon3.append(QPoint(x+width+cos(_updateCount/20.0+3)*50, y+sin(_updateCount/20.0+3)*10));
            newPolygon3.append(QPoint(x+width/2+cos(_updateCount/20.0+3)*50, y-width+sin(_updateCount/20.0+3)*10));
            _polygon.append(newPolygon3);
            _brush.append(redPen);
            x=450, y=105;
            QVector<QPoint> newPolygon4;
            newPolygon4.append(QPoint(x+cos(_updateCount/20.0+4)*50, y+sin(_updateCount/20.0+4)*10));
            newPolygon4.append(QPoint(x+width+cos(_updateCount/20.0+4)*50, y+sin(_updateCount/20.0+4)*10));
            newPolygon4.append(QPoint(x+width/2+cos(_updateCount/20.0+4)*50, y-width+sin(_updateCount/20.0+4)*10));
            _polygon.append(newPolygon4);


            _brush.append(redPen);
            /*********************B样条*********************/

            /*********************填充*********************/

        }else if (_stageNo == 5){
            // 关卡5物体

            QPen tempPen;
            /*********************矩形*********************/
            // 平台
            tempPen.setWidth(5);
            tempPen.setColor(Qt::black);
            //陷阱
            QPen redPen(tempPen);
            redPen.setColor(Qt::red);
            _rects.append(QRect(300+cos(_updateCount/20.0)*150, 200+sin(_updateCount/20.0)*150, sin(_updateCount/20.0)*25+50, cos(_updateCount/20.0)*20+50));
            _brush.append(redPen);
//            _rects.append(QRect(0, 100, 150, 300));
//            _brush.append(tempPen);
//            _rects.append(QRect(200, 0, 150, 300));
//            _brush.append(tempPen);

            /*********************直线*********************/
            //QPen redPen(tempPen);
            redPen.setColor(Qt::red);
            //平台
            _line.append(QRect(0, 100, 500, 1));
            _brush.append(tempPen);
            _line.append(QRect(100, 200, 500, 1));
            _brush.append(tempPen);
            _line.append(QRect(0, 300, 500, 1));
            _brush.append(tempPen);
            _line.append(QRect(0, 375, 600, 1));
            _brush.append(tempPen);


            _brush.append(redPen);
            /*********************多边形*********************/
//            QVector<QPoint> newPolygon;
//            newPolygon.append(QPoint(300, 200));
//            newPolygon.append(QPoint(400, 200));
//            newPolygon.append(QPoint(400, 300));
//            newPolygon.append(QPoint(300, 300));
//            _polygon.append(newPolygon);
            /*********************B样条*********************/

            /*********************填充*********************/

        }
    }
private:
};
