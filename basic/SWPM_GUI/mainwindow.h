#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "compressing/SWPM.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
	SWPM* compressor;

private slots:
 void on_compressBtn_clicked();
 void on_deletePauseBtn_clicked();
 void on_loadCwf_triggered();
 void on_loadWav_triggered();
 void on_exit_triggered();
};

#endif // MAINWINDOW_H
