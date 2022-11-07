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
            _line.append(QRect(0, 100, 500, 1));
            _brush.append(tempPen);
            _line.append(QRect(100, 200, 500, 1));
            _brush.append(tempPen);
            _line.append(QRect(0, 300, 500, 1));
            _brush.append(tempPen);
            _line.append(QRect(0, 375, 600, 1));
            _brush.append(tempPen);
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

            /*********************填充*********************/

        }else if (_stageNo == 4){
            // 关卡4 物体
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

        }else if (_stageNo == 5){
            // 关卡5物体
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
            QPen redPen(tempPen);
            redPen.setColor(Qt::red);
            //陷阱
            _line.append(QRect(150, 350, 50, 1));
            _brush.append(redPen);
            //平台
            _line.append(QRect(200, 350, 400, 1));
            _brush.append(tempPen);
            _line.append(QRect(350, 150, 100, 1));
            _brush.append(tempPen);
            _line.append(QRect(500, 250, 100, 1));
            _brush.append(tempPen);
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
