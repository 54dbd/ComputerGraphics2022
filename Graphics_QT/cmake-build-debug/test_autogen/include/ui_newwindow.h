/********************************************************************************
** Form generated from reading UI file 'newwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWINDOW_H
#define UI_NEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newWindow
{
public:
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QLabel *width;
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *red;
    QRadioButton *blue;
    QRadioButton *yellow;
    QRadioButton *green;
    QRadioButton *black;
    QCheckBox *dashLine;
    QLabel *label_2;

    void setupUi(QWidget *newWindow)
    {
        if (newWindow->objectName().isEmpty())
            newWindow->setObjectName(QString::fromUtf8("newWindow"));
        newWindow->resize(286, 176);
        horizontalSlider = new QSlider(newWindow);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(70, 50, 160, 16));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(20);
        horizontalSlider->setPageStep(5);
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton = new QPushButton(newWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(100, 130, 80, 24));
        width = new QLabel(newWindow);
        width->setObjectName(QString::fromUtf8("width"));
        width->setGeometry(QRect(240, 40, 31, 31));
        label = new QLabel(newWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 51, 51));
        horizontalLayoutWidget = new QWidget(newWindow);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 90, 271, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        red = new QRadioButton(horizontalLayoutWidget);
        red->setObjectName(QString::fromUtf8("red"));
        red->setMaximumSize(QSize(15, 16777215));
        red->setStyleSheet(QString::fromUtf8("width:10px;\n"
"background:red;\n"
""));

        horizontalLayout->addWidget(red);

        blue = new QRadioButton(horizontalLayoutWidget);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setMaximumSize(QSize(15, 16777215));
        blue->setStyleSheet(QString::fromUtf8("width:10px;\n"
"background:blue;\n"
""));

        horizontalLayout->addWidget(blue);

        yellow = new QRadioButton(horizontalLayoutWidget);
        yellow->setObjectName(QString::fromUtf8("yellow"));
        yellow->setMaximumSize(QSize(15, 16777215));
        yellow->setStyleSheet(QString::fromUtf8("width:10px;\n"
"background:yellow;\n"
""));

        horizontalLayout->addWidget(yellow);

        green = new QRadioButton(horizontalLayoutWidget);
        green->setObjectName(QString::fromUtf8("green"));
        green->setMaximumSize(QSize(15, 16777215));
        green->setStyleSheet(QString::fromUtf8("width:10px;\n"
"background:green;\n"
""));

        horizontalLayout->addWidget(green);

        black = new QRadioButton(horizontalLayoutWidget);
        black->setObjectName(QString::fromUtf8("black"));
        black->setMaximumSize(QSize(15, 16777215));
        black->setStyleSheet(QString::fromUtf8("width:10px;\n"
"background:black;\n"
""));

        horizontalLayout->addWidget(black);

        dashLine = new QCheckBox(newWindow);
        dashLine->setObjectName(QString::fromUtf8("dashLine"));
        dashLine->setGeometry(QRect(240, 130, 16, 22));
        label_2 = new QLabel(newWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 130, 31, 21));

        retranslateUi(newWindow);

        QMetaObject::connectSlotsByName(newWindow);
    } // setupUi

    void retranslateUi(QWidget *newWindow)
    {
        newWindow->setWindowTitle(QCoreApplication::translate("newWindow", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("newWindow", "\347\241\256\345\256\232", nullptr));
        width->setText(QCoreApplication::translate("newWindow", "1px", nullptr));
        label->setText(QCoreApplication::translate("newWindow", "\347\254\224\345\210\267\345\244\247\345\260\217", nullptr));
        red->setText(QString());
        blue->setText(QString());
        yellow->setText(QString());
        green->setText(QString());
        black->setText(QString());
        dashLine->setText(QString());
        label_2->setText(QCoreApplication::translate("newWindow", "\350\231\232\347\272\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newWindow: public Ui_newWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWINDOW_H
