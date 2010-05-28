/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri May 28 10:33:41 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
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
    QAction *loadMatrixPath;
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
    QComboBox *pauseMatrixCombo;
    QComboBox *signalMatrixCombo;
    QLineEdit *PEdit;
    QLineEdit *pEdit;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *bpsEdit;
    QFrame *line_3;
    QWidget *compresPanel;
    QLabel *label_2;
    QFrame *line_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QPushButton *decompressBtn;
    QLabel *NpLabel;
    QLabel *RpLabel;
    QLabel *NsLabel;
    QLabel *RsLabel;
    QLabel *signalBpsLabel;
    QLabel *compressedBpsLabel;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
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
        loadMatrixPath = new QAction(MainWindow);
        loadMatrixPath->setObjectName(QString::fromUtf8("loadMatrixPath"));
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
        label->setGeometry(QRect(10, 10, 71, 16));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_3 = new QLabel(decompressPanel);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 111, 16));
        label_4 = new QLabel(decompressPanel);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 60, 31, 16));
        label_5 = new QLabel(decompressPanel);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 80, 181, 16));
        line = new QFrame(decompressPanel);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 20, 281, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        inSignalLengthLabel = new QLabel(decompressPanel);
        inSignalLengthLabel->setObjectName(QString::fromUtf8("inSignalLengthLabel"));
        inSignalLengthLabel->setGeometry(QRect(190, 40, 81, 20));
        inSignalBpsLabel = new QLabel(decompressPanel);
        inSignalBpsLabel->setObjectName(QString::fromUtf8("inSignalBpsLabel"));
        inSignalBpsLabel->setGeometry(QRect(190, 60, 81, 20));
        inSignalRateLabel = new QLabel(decompressPanel);
        inSignalRateLabel->setObjectName(QString::fromUtf8("inSignalRateLabel"));
        inSignalRateLabel->setGeometry(QRect(190, 80, 81, 20));
        deletePauseBtn = new QPushButton(decompressPanel);
        deletePauseBtn->setObjectName(QString::fromUtf8("deletePauseBtn"));
        deletePauseBtn->setGeometry(QRect(10, 270, 121, 23));
        compressBtn = new QPushButton(decompressPanel);
        compressBtn->setObjectName(QString::fromUtf8("compressBtn"));
        compressBtn->setGeometry(QRect(10, 300, 121, 23));
        pauseMatrixCombo = new QComboBox(decompressPanel);
        pauseMatrixCombo->setObjectName(QString::fromUtf8("pauseMatrixCombo"));
        pauseMatrixCombo->setGeometry(QRect(130, 110, 141, 22));
        signalMatrixCombo = new QComboBox(decompressPanel);
        signalMatrixCombo->setObjectName(QString::fromUtf8("signalMatrixCombo"));
        signalMatrixCombo->setGeometry(QRect(130, 140, 141, 22));
        PEdit = new QLineEdit(decompressPanel);
        PEdit->setObjectName(QString::fromUtf8("PEdit"));
        PEdit->setGeometry(QRect(40, 170, 231, 20));
        pEdit = new QLineEdit(decompressPanel);
        pEdit->setObjectName(QString::fromUtf8("pEdit"));
        pEdit->setGeometry(QRect(40, 200, 231, 20));
        label_6 = new QLabel(decompressPanel);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 113, 111, 16));
        label_7 = new QLabel(decompressPanel);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 144, 111, 16));
        label_8 = new QLabel(decompressPanel);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 173, 21, 16));
        label_9 = new QLabel(decompressPanel);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 202, 21, 16));
        label_10 = new QLabel(decompressPanel);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 232, 21, 16));
        bpsEdit = new QLineEdit(decompressPanel);
        bpsEdit->setObjectName(QString::fromUtf8("bpsEdit"));
        bpsEdit->setGeometry(QRect(40, 230, 231, 20));

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
        label_2->setGeometry(QRect(10, 10, 101, 16));
        label_2->setFont(font);
        line_2 = new QFrame(compresPanel);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 20, 281, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(compresPanel);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 40, 21, 16));
        label_12 = new QLabel(compresPanel);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 60, 21, 16));
        label_13 = new QLabel(compresPanel);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 80, 21, 16));
        label_14 = new QLabel(compresPanel);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 100, 21, 16));
        label_15 = new QLabel(compresPanel);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 120, 61, 16));
        label_16 = new QLabel(compresPanel);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 140, 61, 16));
        decompressBtn = new QPushButton(compresPanel);
        decompressBtn->setObjectName(QString::fromUtf8("decompressBtn"));
        decompressBtn->setGeometry(QRect(10, 170, 121, 23));
        NpLabel = new QLabel(compresPanel);
        NpLabel->setObjectName(QString::fromUtf8("NpLabel"));
        NpLabel->setGeometry(QRect(100, 40, 171, 16));
        RpLabel = new QLabel(compresPanel);
        RpLabel->setObjectName(QString::fromUtf8("RpLabel"));
        RpLabel->setGeometry(QRect(100, 60, 171, 16));
        NsLabel = new QLabel(compresPanel);
        NsLabel->setObjectName(QString::fromUtf8("NsLabel"));
        NsLabel->setGeometry(QRect(100, 80, 171, 16));
        RsLabel = new QLabel(compresPanel);
        RsLabel->setObjectName(QString::fromUtf8("RsLabel"));
        RsLabel->setGeometry(QRect(100, 100, 171, 16));
        signalBpsLabel = new QLabel(compresPanel);
        signalBpsLabel->setObjectName(QString::fromUtf8("signalBpsLabel"));
        signalBpsLabel->setGeometry(QRect(100, 120, 171, 16));
        compressedBpsLabel = new QLabel(compresPanel);
        compressedBpsLabel->setObjectName(QString::fromUtf8("compressedBpsLabel"));
        compressedBpsLabel->setGeometry(QRect(100, 140, 171, 16));

        horizontalLayout->addWidget(compresPanel);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(loadWav);
        menu->addAction(loadCwf);
        menu->addAction(exit);
        menu_2->addAction(loadMatrixPath);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\241\320\266\320\260\321\202\320\270\320\265 \321\200\320\265\321\207\320\265\320\262\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        loadWav->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\200\320\265\321\207\321\214", 0, QApplication::UnicodeUTF8));
        loadCwf->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\201\320\266\320\260\321\202\321\213\320\271 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        exit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        loadMatrixPath->setText(QApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\216 \320\274\320\260\321\202\321\200\320\270\321\206", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\320\241\320\266\320\260\321\202\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\320\224\320\273\320\270\320\275\320\260 \321\201\320\270\320\263\320\275\320\260\320\273\320\260:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "BPS:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\264\320\270\321\201\320\272\321\200\320\265\321\202\320\270\320\267\320\260\321\206\320\270\320\270:", 0, QApplication::UnicodeUTF8));
        inSignalLengthLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        inSignalBpsLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        inSignalRateLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        deletePauseBtn->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\260\321\203\320\267\321\213", 0, QApplication::UnicodeUTF8));
        compressBtn->setText(QApplication::translate("MainWindow", "\320\241\320\266\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 \320\264\320\273\321\217 \320\277\320\260\321\203\320\267", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 \320\264\320\273\321\217 \321\201\320\270\320\263.", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "P", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "p", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "BPS", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\260\320\272\320\276\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Np", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Rp", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Ns", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Rs", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "\320\270\321\201\321\205. BPS", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "\321\201\320\266. BPS", 0, QApplication::UnicodeUTF8));
        decompressBtn->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\266\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        NpLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        RpLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        NsLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        RsLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        signalBpsLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        compressedBpsLabel->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
