#ifndef GRAPHICS_QT_POLYGON_H
#define GRAPHICS_QT_POLYGON_H

#include <iostream>
#include <QPainter>
#include <list>
#include <algorithm>
#include "Brush.h"

using namespace std;

class Edge {
public:
    int ymax, ymin;
    float x, deltax;

    Edge(int x1, int y1, int x2, int y2, Edge *next = nullptr) {
        ymax = (y2 > y1) ? y2 : y1;
        ymin = (y2 > y1) ? y1 : y2;
        x = float((y2 > y1) ? x1 : x2);
        deltax = float((x2 - x1)) / float((y2 - y1));
    }

    Edge(const Edge &e) {
        ymax = e.ymax;
        x = e.x;
        deltax = e.deltax;
    }
};

bool compareEdge(const Edge &e1, const Edge &e2) {
    if(e1.x == e2.x)
        return e1.deltax < e2.deltax;
    else
        return e1.x < e2.x;
}


class Polygon : public Brush {
private:
    list<Edge> *edgeTable, activeEdgeList;
//    Edge **edgeTable, *activeEdgeList;
    int ymax;

public:
    Polygon(int W, QPainter &p, int height) : Brush(W, p) {
        ymax = height;
        edgeTable = new list<Edge>[height];
    }

    ~Polygon() {
        delete[] edgeTable;
    }

    // 将边插入到ET中
    void addEdgeToET(Edge *e) {
        int y = e->ymin;
        edgeTable[y].push_back(*e);
        edgeTable[y].sort(compareEdge);
    }

    // 将ET的边插入到AEL中（由于ET中的边不做修改，因此在这里需要复制构造边，插入到AEL中）
    void addEdgeToAEL(Edge *edge) {
        activeEdgeList.push_back(*edge);
        activeEdgeList.sort(compareEdge);
    }

    // 将AEL中ymax=y的边删除
    void deleteEdgeFromAEL(int y) {
        for (auto it = activeEdgeList.begin(); it != activeEdgeList.end();) {
            if (it->ymax == y) {
                auto temp = it;
                it++;
                activeEdgeList.erase(temp);
                continue;
            } else {
                it++;
            }
        }
    }

    // 扫描线扫描
    void drawScanLine(int y) {
        auto it = activeEdgeList.begin();
        while (it != activeEdgeList.end()) {
            int x1 = int(it->x);
            auto prev = it;
            it++;
            int x2 = int(it->x);
            for (int i = x1; i < x2; i++) {
                drawPixel(i, y);
            }
            prev->x += prev->deltax;
            it->x += it->deltax;
            it++;
        }
    }

    void drawPolygon() {
        // 初始化活动边表
        activeEdgeList.clear();
        // 从扫描线的最低点开始扫描
        for (int y = 0; y < ymax; y++) {
            // 将ET表中的边插入到AEL中
            if (!edgeTable[y].empty()) {
                for (auto it = edgeTable[y].begin(); it != edgeTable[y].end(); it++) {
                    addEdgeToAEL(&(*it));
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
