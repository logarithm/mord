/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 26. May 03:08:59 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *loadWav;
    QAction *loadCwf;
    QAction *exit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *decompressPanel;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QFrame *line;
    QLabel *inSignalLengthLabel;
    QLabel *inSignalBpsLabel;
    QLabel *inSignalRateLabel;
    QPushButton *deletePauseBtn;
    QPushButton *compressBtn;
    QFrame *line_3;
    QWidget *compresPanel;
    QLabel *label_2;
    QFrame *line_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        MainWindow->setMinimumSize(QSize(600, 400));
        MainWindow->setMaximumSize(QSize(600, 400));
        loadWav = new QAction(MainWindow);
        loadWav->setObjectName(QString::fromUtf8("loadWav"));
        loadWav->setCheckable(false);
        loadWav->setMenuRole(QAction::TextHeuristicRole);
        loadCwf = new QAction(MainWindow);
        loadCwf->setObjectName(QString::fromUtf8("loadCwf"));
        loadCwf->setCheckable(false);
        exit = new QAction(MainWindow);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setCheckable(false);
        exit->setMenuRole(QAction::QuitRole);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        decompressPanel = new QWidget(centralWidget);
        decompressPanel->setObjectName(QString::fromUtf8("decompressPanel"));
        label = new QLabel(decompressPanel);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 51, 16));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_3 = new QLabel(decompressPanel);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 79, 13));
        label_4 = new QLabel(decompressPanel);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 60, 22, 13));
        label_5 = new QLabel(decompressPanel);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 80, 126, 13));
        line = new QFrame(decompressPanel);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 20, 281, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        inSignalLengthLabel = new QLabel(decompressPanel);
        inSignalLengthLabel->setObjectName(QString::fromUtf8("inSignalLengthLabel"));
        inSignalLengthLabel->setGeometry(QRect(150, 40, 121, 16));
        inSignalBpsLabel = new QLabel(decompressPanel);
        inSignalBpsLabel->setObjectName(QString::fromUtf8("inSignalBpsLabel"));
        inSignalBpsLabel->setGeometry(QRect(150, 60, 121, 16));
        inSignalRateLabel = new QLabel(decompressPanel);
        inSignalRateLabel->setObjectName(QString::fromUtf8("inSignalRateLabel"));
        inSignalRateLabel->setGeometry(QRect(150, 80, 121, 16));
        deletePauseBtn = new QPushButton(decompressPanel);
        deletePauseBtn->setObjectName(QString::fromUtf8("deletePauseBtn"));
        deletePauseBtn->setGeometry(QRect(10, 100, 101, 23));
        compressBtn = new QPushButton(decompressPanel);
        compressBtn->setObjectName(QString::fromUtf8("compressBtn"));
        compressBtn->setGeometry(QRect(10, 130, 101, 23));

        horizontalLayout->addWidget(decompressPanel);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        compresPanel = new QWidget(centralWidget);
        compresPanel->setObjectName(QString::fromUtf8("compresPanel"));
        label_2 = new QLabel(compresPanel);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 79, 16));
        label_2->setFont(font);
        line_2 = new QFrame(compresPanel);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 20, 281, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(compresPanel);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(loadWav);
        menu->addAction(loadCwf);
        menu->addAction(exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\241\320\266\320\260\321\202\320\270\320\265 \321\200\320\265\321\207\320\265\320\262\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        loadWav->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\200\320\265\321\207\321\214", 0, QApplication::UnicodeUTF8));
        loadCwf->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\201\320\266\320\260\321\202\321\213\320\271 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        exit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\320\241\320\266\320\260\321\202\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\320\224\320\273\320\270\320\275\320\260 \321\201\320\270\320\263\320\275\320\260\320\273\320\260:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "BPS:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\264\320\270\321\201\320\272\321\200\320\265\321\202\320\270\320\267\320\260\321\206\320\270\320\270:", 0, QApplication::UnicodeUTF8));
        inSignalLengthLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        inSignalBpsLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        inSignalRateLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        deletePauseBtn->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\260\321\203\320\267\321\213", 0, QApplication::UnicodeUTF8));
        compressBtn->setText(QApplication::translate("MainWindow", "\320\241\320\266\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\260\320\272\320\276\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
