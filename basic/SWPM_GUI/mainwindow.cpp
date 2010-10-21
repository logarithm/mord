#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	compressor = new SWPM();

	ui->setupUi(this);

	clearCompressPanel();
	clearDecompressPanel();
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

void MainWindow::clearCompressPanel() {
	this->ui->inSignalLengthLabel->setText("-");
	this->ui->inSignalBpsLabel->setText("-");
	this->ui->inSignalRateLabel->setText("-");

	this->ui->PEdit->setText("5");
	this->ui->pEdit->setText("0");
	this->ui->bpsEdit->setText("3");

	this->ui->pauseMatrixCombo->clear();
	this->ui->signalMatrixCombo->clear();

	this->ui->compressBtn->setEnabled(false);
}

void MainWindow::clearDecompressPanel() {
	this->ui->NpLabel->setText("-");
	this->ui->RpLabel->setText("-");
	this->ui->NsLabel->setText("-");
	this->ui->RsLabel->setText("-");
	this->ui->signalBpsLabel->setText("-");
	this->ui->compressedBpsLabel->setText("-");

	this->ui->decompressBtn->setEnabled(false);
}

void MainWindow::loadCombos() {
	QDir dir(matrixDir);
	QStringList dirList = dir.entryList();
	dirList = dirList.filter("AA_");

	this->ui->pauseMatrixCombo->clear();
	this->ui->signalMatrixCombo->clear();

	this->ui->pauseMatrixCombo->addItems(dirList);
	this->ui->signalMatrixCombo->addItems(dirList);
}

void MainWindow::on_exit_triggered()
{
	close();
}

void MainWindow::on_loadWav_triggered()
{
	QFileDialog::Options options;
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
								trUtf8("Загрузка сигнала"),
								"",
								trUtf8("Звуковые файлы (*.wav)"),
								&selectedFilter,
								options);
	if (!fileName.isEmpty()) {
		clearCompressPanel();
		clearDecompressPanel();

		compressor->LoadSignalFile(fileName.toAscii().data());
		this->ui->inSignalLengthLabel->setText(QString::number(compressor->GetSignalLenght()));
		this->ui->inSignalBpsLabel->setText(QString::number(compressor->GetSignalBps()));
		this->ui->inSignalRateLabel->setText(QString::number(compressor->GetSignalRate()));

		this->ui->compressBtn->setEnabled(true);
		loadCombos();
	}
}

void MainWindow::on_loadCwf_triggered()
{
	QFileDialog::Options options;
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
								trUtf8("Загрузка сжатого файла"),
								"",
								trUtf8("Сжатые файлы (*.cwf)"),
								&selectedFilter,
								options);
	if (!fileName.isEmpty()) {
		clearCompressPanel();
		clearDecompressPanel();

		compressor->LoadCompressedFile(fileName.toAscii().data());

		this->ui->NpLabel->setText(QString::number(compressor->GetNp()));
		this->ui->RpLabel->setText(QString::number(compressor->GetRp()));
		this->ui->NsLabel->setText(QString::number(compressor->GetNs()));
		this->ui->RsLabel->setText(QString::number(compressor->GetRs()));
		this->ui->signalBpsLabel->setText(QString::number(compressor->GetSignalBps()));
		this->ui->compressedBpsLabel->setText(QString::number(compressor->GetCompressedBps()));

		this->ui->decompressBtn->setEnabled(true);
	}
}

void MainWindow::on_loadMatrixPath_triggered()
{
	QString dirName = QFileDialog::getExistingDirectory(this,
								trUtf8("Выбор директории с файлами матриц"));
	if (!dirName.isEmpty()) {
		matrixDir = dirName;
		loadCombos();
	}
}

void MainWindow::on_compressBtn_clicked()
{
	if (matrixDir.length() <= 0) {
		QMessageBox::warning(this, trUtf8("Ошибка"),trUtf8("Директория с матрицами не выбрана"));
		return;
	}

	QFileDialog::Options options;
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this,
								trUtf8("Сохранение сжатого файла"),
								"",
								trUtf8("Сжатые файлы (*.cwf)"),
								&selectedFilter,
								options);
	if (!fileName.isEmpty()) {
		QString pauseMatrix = this->ui->pauseMatrixCombo->itemText(this->ui->pauseMatrixCombo->currentIndex());
		QStringList pauseParams = pauseMatrix.split("_");
		USHORT Rp = ((QString)pauseParams.takeAt(1)).toShort();
		USHORT Np = ((QString)((QString)pauseParams.takeAt(1)).split(".").takeAt(0)).toShort();

		QString compressMatrix = this->ui->signalMatrixCombo->itemText(this->ui->signalMatrixCombo->currentIndex());
		QStringList compressParams = compressMatrix.split("_");
		USHORT Rs = ((QString)compressParams.takeAt(1)).toShort();
		USHORT Ns = ((QString)((QString)compressParams.takeAt(1)).split(".").takeAt(0)).toShort();

		compressor->SetCompressParams(Np, Rp, this->ui->PEdit->text().toShort(), this->ui->pEdit->text().toShort(), Ns, Rs, this->ui->bpsEdit->text().toShort());
		compressor->matrixDir = matrixDir.toAscii().data();
		compressor->FullCompressData();
		compressor->SaveCompressedFile(fileName.toAscii().data());

		QMessageBox::information(this, trUtf8("Выполнено"),trUtf8("Сжатие завершено"));
	}
}

void MainWindow::on_decompressBtn_clicked()
{
	if (matrixDir.length() <= 0) {
		QMessageBox::warning(this, trUtf8("Ошибка"),trUtf8("Директория с матрицами не выбрана"));
		return;
	}

	QFileDialog::Options options;
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this,
								trUtf8("Сохранение восстановленного файла"),
								"",
								trUtf8("Звуковые файлы (*.wav)"),
								&selectedFilter,
								options);
	if (!fileName.isEmpty()) {
		compressor->matrixDir = matrixDir.toAscii().data();
		compressor->FullDecompressData();
		compressor->SaveSignalData(fileName.toAscii().data());

		QMessageBox::information(this, trUtf8("Выполнено"),trUtf8("Восстановление завершено"));
	}
}
