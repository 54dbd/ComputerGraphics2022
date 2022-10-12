#ifndef GRAPHICS_QT_POLYGON_H
#define GRAPHICS_QT_POLYGON_H
#define YMAX 400

#include <iostream>
#include <QPainter>
#include "Brush.h"

using namespace std;

class Edge {
public:
    int ymax, ymin;
    float x, deltax;
    Edge *nextEdge;

    Edge(int x1, int y1, int x2, int y2, Edge *next = nullptr) {
        ymax = (y2 > y1) ? y2 : y1;
        ymin = (y2 > y1) ? y1 : y2;
        x = float((y2 > y1) ? x1 : x2);
        deltax = float((x2 - x1)) / float((y2 - y1));
        nextEdge = next;
    }

    Edge(const Edge &e) {
        ymax = e.ymax;
        x = e.x;
        deltax = e.deltax;
        nextEdge = nullptr;
    }
};


class Polygon : public Brush {
private:
    Edge *edgeTable[YMAX], *activeEdgeList;
    COLORREF color;

public:
    Polygon(int W, QPainter &p) : Brush(W, p) {
        for (int i = 0; i < YMAX; ++i) {
            edgeTable[i] = nullptr;
        }
    }

    // 将边插入到ET中
    void addEdgeToET(Edge *e) {
        int y = e->ymin;
        // 如果为空，则直接作为头节点
        if (edgeTable[y] == nullptr) {
            edgeTable[y] = e;
        } else {
            Edge *p = edgeTable[y];
            // 如果新边的x值小于当前边的x值，则将新边插入到当前边之前，并且其作为新的头节点
            if (e->x < p->x) {
                e->nextEdge = p;
                edgeTable[y] = e;
            } else {
                // 如果新边的x值小于当前边的x值，并且下一条边不为空，则继续向后遍历
                while (p->nextEdge != nullptr && p->nextEdge->x < e->x) {
                    p = p->nextEdge;
                }
                // 如果x的值相等，则比较deltax的值
                while (p->nextEdge != nullptr && p->nextEdge->x == e->x && p->nextEdge->deltax < e->deltax) {
                    p = p->nextEdge;
                }
                // 将新边插入到当前边之后
                e->nextEdge = p->nextEdge;
                p->nextEdge = e;
            }
        }
    }

    // 将ET的边插入到AEL中（由于ET中的边不做修改，因此在这里需要复制构造边，插入到AEL中）
    void addEdgeToAEL(Edge *edge) {
        if (activeEdgeList == nullptr) {
            // 如果为空，则直接作为AEL的头节点
            Edge *e = new Edge(*edge);
            activeEdgeList = e;
        } else {
            Edge *p = activeEdgeList;
            if (edge->x < p->x) {
                // 如果插入的边的x值最小，则作为新的头节点，他的next指针指向原来的头指针
                Edge *e = new Edge(*edge);
                e->nextEdge = p;
                activeEdgeList = e;
            } else {
                // 如果插入的边的x值不是最小的，则遍历AEL，找到合适的位置插入
                // 先判断x的值
                while (p->nextEdge != nullptr && p->nextEdge->x < edge->x) {
                    p = p->nextEdge;
                }
                // 如果x的值相等，则比较deltax的值
                while (p->nextEdge != nullptr && p->nextEdge->x == edge->x && p->nextEdge->deltax < edge->deltax) {
                    p = p->nextEdge;
                }
                // 找到了对应的位置，新建节点，并插入
                Edge *e = new Edge(*edge);
                e->nextEdge = p->nextEdge;
                p->nextEdge = e;
            }
        }
    }

    // 将AEL中ymax=y的边删除
    void deleteEdgeFromAEL(int y) {
        Edge *e = activeEdgeList;
        while (e != nullptr) {
            // 满足条件，需要删除
            if (e->ymax == y) {
                // 保存需要删除的节点
                Edge *temp = e;
                // 如果是头节点，则直接将头节点指向下一个节点
                if (e == activeEdgeList) {
                    e = e->nextEdge;
                    activeEdgeList = e;
                    delete temp;
                } else {
                    // 如果不是头节点，则遍历AEL，找到对应的节点的上一个指针
                    Edge *p = activeEdgeList;
                    while (p->nextEdge != e) {
                        p = p->nextEdge;
                    }
                    e = e->nextEdge;
                    p->nextEdge = e;
                    delete temp;
                }
            } else {
                // 如果不满足条件，则继续遍历
                e = e->nextEdge;
            }
        }
    }

    // 扫描线扫描
    void drawScanLine(int y) {
        Edge *e = activeEdgeList, *n;
        while (e != nullptr && e->nextEdge != nullptr) {
            // 从AEL中取出两个边
            n = e->nextEdge;
            // 从x1到x2之间进行填充
            for (int i = int(e->x); i < int(n->x); i++) {
                drawPixel(i, y);
            }
            // 更新x的值
            e->x += e->deltax;
            n->x += n->deltax;
            // 迭代边
            e = n->nextEdge;
        }
    }

    void drawPolygon() {
        // 初始化活动边表
        activeEdgeList = nullptr;
        // 从扫描线的最低点开始扫描
        for (int y = 0; y < YMAX; y++) {
            // 将ET表中的边插入到AEL中
            if (edgeTable[y] != nullptr) {
                Edge *p = edgeTable[y];
                while (p != nullptr) {
                    addEdgeToAEL(p);
                    p = p->nextEdge;
                }
            }
            // 删除AEL中的边
            deleteEdgeFromAEL(y);
            // 绘制扫描线
            drawScanLine(y);
        }
    }


};


#endif //GRAPHICS_QT_POLYGON_H
