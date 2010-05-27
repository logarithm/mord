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
	void clearCompressPanel();
	void clearDecompressPanel();
	void loadCombos();

    Ui::MainWindow *ui;
	QString matrixDir;
	SWPM* compressor;

private slots:
 void on_decompressBtn_clicked();
 void on_compressBtn_clicked();
 void on_deletePauseBtn_clicked();
 void on_loadCwf_triggered();
 void on_loadWav_triggered();
 void on_exit_triggered();
 void on_loadMatrixPath_triggered();
};

#endif // MAINWINDOW_H
