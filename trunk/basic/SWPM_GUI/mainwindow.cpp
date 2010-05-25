#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	compressor = new SWPM();
	compressor->matrixDir = "d:/svn/trunk/basic/files/matrix/";
	compressor->SetCompressParams(60, 10, 5, 0, 128, 20, 3);
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_exit_triggered()
{
	close();
}

void MainWindow::on_loadWav_triggered()
{
	QFileDialog::Options options;
	//options |= QFileDialog::DontUseNativeDialog;
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
								trUtf8("Выберите файл для сжатия"),
								"",
								trUtf8("Звуковые файлы (*.wav)"),
								&selectedFilter,
								options);
	if (!fileName.isEmpty()) {
		compressor->LoadSignalFile(fileName.toAscii().data());
		this->ui->inSignalLengthLabel->setText(QString::number(compressor->GetSignalLenght()));
		this->ui->inSignalBpsLabel->setText(QString::number(compressor->GetSignalBps()));
		this->ui->inSignalRateLabel->setText(QString::number(compressor->GetSignalRate()));
	}
}

void MainWindow::on_loadCwf_triggered()
{
	QFileDialog::Options options;
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
								trUtf8("Выберите файл для декодирования"),
								"",
								trUtf8("Сжатые файлы (*.cwf)"),
								&selectedFilter,
								options);
	if (!fileName.isEmpty())
		QMessageBox::information(this, "11", fileName);
}

void MainWindow::on_deletePauseBtn_clicked()
{
	compressor->DeletePause();
	QFileDialog::Options options;
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this,
								trUtf8("Сохранение сигнала без пауз"),
								"",
								trUtf8("Звуковые файлы (*.wav)"),
								&selectedFilter,
								options);
	if (!fileName.isEmpty()) {
		compressor->SaveSignalWithoutPauseData(fileName.toAscii().data());
	}
}

void MainWindow::on_compressBtn_clicked()
{
	compressor->FullCompressData();
	QFileDialog::Options options;
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this,
								trUtf8("Сохранение сжатого файла"),
								"",
								trUtf8("Сжатые файлы (*.cwf)"),
								&selectedFilter,
								options);
	if (!fileName.isEmpty()) {
		compressor->SaveSignalWithoutPauseData(fileName.toAscii().data());
	}
}
