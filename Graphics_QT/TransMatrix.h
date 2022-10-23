//
// Created by mkkjit on 2022/10/19.
//
#include <iostream>
#include <QPoint>
#include <cmath>
using namespace std;

#ifndef UNTITLED1_TRANSMATRIX_H
#define UNTITLED1_TRANSMATRIX_H
#define     PI    3.1415926

/**自定义的转换矩阵类*
 *使用提要：该矩阵变换类可以与一个QPoint右乘进行变换，返回变换后的点，与矩阵相乘进行普通矩阵乘法，通过两个方括号访问对应位置元素
 *        可以设置变换参考点，设置变换（传入对应变换的关键参数，方法会自动完成计算与填充）。
 * 注意：施加多个变换的顺序与课程规定相同，先作用的在右侧。
 *      但不需要考虑参考点变换问题，相应变换已经在对应运算符重载中被处理
 *      假设若有三个变换矩阵，以1-3顺序对点Q施加变换，则无论矩阵参考点是否为原点，是否相同，都应形如：Q = M3*M2*M1*Q
 */
class transMatrix{

private:
    int reference_x = 0,reference_y = 0;   //参考点
    double tr[3][3] = {1,0,0,
                      0,1,0,   //变换矩阵
                      0,0,1};

public:
    /**构造与初始化函数**/
    transMatrix(int refer_X = 0,int refer_Y = 0){  //以参考点xy构造，默认都为0
        reference_x = refer_X;
        reference_y = refer_Y;
    }
    transMatrix(QPoint q){   //兼容用QPoint直接作为参考点构造，便于程序中与鼠标交互
        reference_x = q.x();
        reference_y = q.y();
    }
    void setReference(int refer_X = 0,int refer_Y = 0){  //以xy作为参数重新设置参考点
        reference_x = refer_X;
        reference_y = refer_Y;
    }
    void setReference(QPoint q){   //以QPoint设置参考点
        reference_x = q.x();
        reference_y = q.y();
    }

    /**功能函数**/
    void Reset(){   //将矩阵重置为没有任何变换效果的初值
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if(i!=j)
                    tr[i][j] = 0;
                else
                    tr[i][j] = 1;
            }
        }
    }

    void setRotateTrans(double angle){   //设置旋转功能，调用该函数传入一个角度值，自动将矩阵设置为对应的变换矩阵，并覆盖原内容
        Reset();
        angle = angle*PI/180;      //角度转弧度
        tr[0][0] = cos(angle);
        tr[0][1] = -sin(angle);
        tr[1][0] = -tr[0][1];
        tr[1][1] = tr[0][0];
    }

    void setZoomTrans(double z_X,double z_Y){   //设置缩放功能，与设置旋转类似，参数为x与y方向的缩放比例
        Reset();
        tr[0][0] = z_X;
        tr[1][1] = z_Y;
    }

    void setMoveTrans(double m_X,double m_Y){   //设置移动功能，与设置旋转类似，参数为x与y方向的移动距离
        Reset();
        tr[0][2] = m_X;
        tr[1][2] = m_Y;
    }
    void setMoveTrans(QPoint movevec){   //设置移动功能重载，使用一个Qpoint作为向量修改移动距离
        Reset();
        tr[0][2] = movevec.x();
        tr[1][2] = movevec.y();
    }



    /**运算符重载**/
    double* operator[](int index){    //下标符重载，调用一次返回一个行指针，需要再使用一次下标符取出指定位置矩阵，使用上和普通二维数组一致。
        return this->tr[index];
    }

    QPoint operator*(QPoint q){       //当右乘一个QPoint类时，定义为施加变换，返回一个变换后的QPoint
        float QMatrix[3] = {(float)-reference_x,(float)-reference_y,1};//准备点的向量
        float QTransed[3] = {(float)reference_x,(float)reference_y,0};//准备计算完后的点向量
        QMatrix[0] += q.x();          //这里是加而不是赋值，包括上文准备点向量时填入了参考点相关数据
        QMatrix[1] += q.y();          //这样做是为了满足根据某个参考点进行放缩和旋转，非原点做参考点需要进行两次移动变换，而这可以直接体现在加法上
        float sum = 0;                //因此正好可以用向初始与最终点向量中预设移动变换的方式简化指定参考点变换。
        for (int i = 0; i < 3; ++i) { //矩阵乘法
            sum = 0;
            for (int j = 0; j < 3; ++j) {
                sum += this->tr[i][j]*QMatrix[j];
            }
            QTransed[i] += sum;
        }
        q.rx() = (int)QTransed[0]+0.5;//将得到的结果取出，取整，修改QPoint并返回
        q.ry() = (int)QTransed[1]+0.5;
        return q;
    }

    transMatrix operator*(transMatrix t){  //当右乘同类矩阵时，进行普通矩阵乘法，但要考虑统一参考点
        float sum = 0;
        bool differRefer = false;
        transMatrix temp(t.reference_x,t.reference_y);//将最终返回的类中填入右侧变换矩阵的参考点，因为右侧矩阵可能最终与点类相乘
        if(t.reference_y!=reference_y||t.reference_x!=reference_x){   //如果参考点不同，需要做参考点统一
            differRefer = true;
            t.tr[0][2] -= reference_x;   //进行移动变换 相当于原先矩阵与点相乘时，参照点在乘法中被处理，而此处没有直接与点相乘
            t.tr[1][2] -= reference_y;   //因此参考矩阵乘法结合律定义,先对右矩阵乘移动矩阵，再对计算结果乘移动矩阵。这里直接简化为对应位置加法。
        }
        for (int i = 0; i < 3; ++i) {  //普通矩阵运算
            for (int j = 0; j < 3; ++j) {
                sum = 0;
                for (int k = 0; k < 3; ++k) {
                    sum+=this->tr[i][k]*t.tr[k][j];
                }
                temp[i][j] = sum;
            }
        }
        if(differRefer){  //进行移动变换
            temp.tr[0][2] += reference_x;
            temp.tr[1][2] += reference_y;
        }
        return temp;
    }
   // friend ostream& operator << (ostream & out,transMatrix &m);
};
/*ostream& operator << (ostream & out,transMatrix &m){
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            out<<m.tr[i][j]<<" ";
        }
        out<<endl;
    }
    return out;
}*/


#endif //UNTITLED1_TRANSMATRIX_H
