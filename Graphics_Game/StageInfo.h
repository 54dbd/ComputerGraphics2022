#pragma once
class StageInfo{
public:
    int _stageNo;
    long _updateCount;

    QVector<QPen> _brush;

    QVector<QRect> _rects;
    QVector<QRect> _line;

    QVector<QPoint> _fills;

    StageInfo(int StageNo, long UpdateCount){
        _stageNo = StageNo;
        _updateCount = UpdateCount;
        if (_stageNo == 1){
            // 平台
            QPen tempPen;
            tempPen.setWidth(5);
            tempPen.setColor(Qt::black);

            _rects.append(QRect(170, 200, 100, 50)); // 右边移动矩形（填充）
            _brush.append(tempPen);
            _rects.append(QRect(330 + sin(_updateCount/17.0)*50, 100, 100, 50)); // 左边移动矩形（填充）
            _brush.append(tempPen);
            _rects.append(QRect(0, 300, 150, 50)); // 左边矩形
            _brush.append(tempPen);
            _rects.append(QRect(500, 100, 150, 50)); // 右边矩形
            _brush.append(tempPen);

            // 平台填充（点）
            for (int i = 0; i < 2; ++i) {
                QRect tempRect = _rects[i];
                _fills.append(QPoint(tempRect.left() + tempRect.width() / 2, tempRect.top() + tempRect.height() / 2));
                _brush.append(tempPen);
            }
        } else if (_stageNo == 2){
            // 关卡2物体
            // 平台
            QPen tempPen;
            tempPen.setWidth(5);
            tempPen.setColor(Qt::black);

            _rects.append(QRect(170, 200, 100, 50)); // 右边移动矩形（填充）
            _brush.append(tempPen);
            _rects.append(QRect(330, 100, 100, 50)); // 左边移动矩形（填充）
            _brush.append(tempPen);
            _rects.append(QRect(0, 300, 150, 50)); // 左边矩形
            _brush.append(tempPen);
            _rects.append(QRect(500, 100, 150, 50)); // 右边矩形
            _brush.append(tempPen);

            // 平台填充（点）
            for (int i = 0; i < 2; ++i) {
                QRect tempRect = _rects[i];
                _fills.append(QPoint(tempRect.left() + tempRect.width() / 2, tempRect.top() + tempRect.height() / 2));
                _brush.append(tempPen);
            }
        }
    }
private:
};
