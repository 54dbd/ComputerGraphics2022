#pragma once
class StageInfo{
public:
    int _stageNo;
    long _updateCount;

    QVector<QPen> _brush;

    QVector<QRect> _rects;
    QVector<QRect> _line;
    QVector<QVector<QPoint>> _polygon;
    vector<vector<QPoint>> _bezierCurve;

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
            _line.append(QRect(300, 300, 400, 600));
            _brush.append(tempPen);
            /*********************多边形*********************/
            /*********************贝塞尔*********************/
            // 性能差 不建议和移动的方块一起使用
//            vector<QPoint> tempCurve;
//            tempCurve.emplace_back(200, 325);
//            tempCurve.emplace_back(250, 350);
//            tempCurve.emplace_back(225, 325);
//            tempCurve.emplace_back(275, 350);
//            _bezierCurve.push_back(tempCurve);
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

            _rects.append(QRect(170, 200, 100, 50));
            _brush.append(tempPen);
            _rects.append(QRect(330 + sin(_updateCount/17.0)*50, 100, 100, 50));
            _brush.append(tempPen);
            _rects.append(QRect(0, 300, 150, 50));
            _brush.append(tempPen);
            _rects.append(QRect(500, 100, 150, 50));
            _brush.append(tempPen);

            /*********************直线*********************/
            _line.append(QRect(300, 300, 400, 600));
            _brush.append(tempPen);
            /*********************多边形*********************/
            QVector<QPoint> newPolygon;
            newPolygon.append(QPoint(300, 200));
            newPolygon.append(QPoint(400, 200));
            newPolygon.append(QPoint(400, 300));
            newPolygon.append(QPoint(300, 300));
            _polygon.append(newPolygon);
            /*********************贝塞尔*********************/

            /*********************填充*********************/

        }
    }
private:
};
