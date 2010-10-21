#pragma once

#include <windows.h>
#include "compressing/SWPM.h"

namespace SWPM_NET_GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			compressor = new SWPM();
			clearCompressPanel();
			clearDecompressPanel();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  mainMenu;
	protected: 

	private: System::Windows::Forms::ToolStripMenuItem^  menuFile;
	private: System::Windows::Forms::ToolStripMenuItem^  menuLoadWav;
	private: System::Windows::Forms::ToolStripMenuItem^  menuLoadCwf;
	private: System::Windows::Forms::ToolStripMenuItem^  menuExit;
	private: System::Windows::Forms::ToolStripMenuItem^  menuSettings;
	private: System::Windows::Forms::ToolStripMenuItem^  menuLoadMatrix;
	private:
		SWPM* compressor;
		String^ matrixDir;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::FolderBrowserDialog^  openDirDialog;
	private: System::Windows::Forms::Panel^  compressPanel;
	private: System::Windows::Forms::Panel^  decompressPanel;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  labelSignalRate;
	private: System::Windows::Forms::Label^  labelSignalBPS;
	private: System::Windows::Forms::Label^  labelSignalLength;
	private: System::Windows::Forms::Button^  btnCompress;
	private: System::Windows::Forms::Label^  labelRp;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  labelNp;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  labelWavBPS;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  labelCompressedBPS;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  labelRs;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  labelNs;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Button^  btnDecompress;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  editBPS;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  editPauseFetch;
	private: System::Windows::Forms::TextBox^  editPauseLength;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::ComboBox^  comboSignalMatrix;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::ComboBox^  comboPauseMatrix;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->mainMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->menuFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuLoadWav = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuLoadCwf = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSettings = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuLoadMatrix = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openDirDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->compressPanel = (gcnew System::Windows::Forms::Panel());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->comboSignalMatrix = (gcnew System::Windows::Forms::ComboBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->comboPauseMatrix = (gcnew System::Windows::Forms::ComboBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->editBPS = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->editPauseFetch = (gcnew System::Windows::Forms::TextBox());
			this->editPauseLength = (gcnew System::Windows::Forms::TextBox());
			this->btnCompress = (gcnew System::Windows::Forms::Button());
			this->labelSignalRate = (gcnew System::Windows::Forms::Label());
			this->labelSignalBPS = (gcnew System::Windows::Forms::Label());
			this->labelSignalLength = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->decompressPanel = (gcnew System::Windows::Forms::Panel());
			this->btnDecompress = (gcnew System::Windows::Forms::Button());
			this->labelWavBPS = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->labelCompressedBPS = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->labelRs = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->labelNs = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->labelRp = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->labelNp = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->mainMenu->SuspendLayout();
			this->compressPanel->SuspendLayout();
			this->decompressPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainMenu
			// 
			this->mainMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->menuFile, this->menuSettings});
			this->mainMenu->Location = System::Drawing::Point(0, 0);
			this->mainMenu->Name = L"mainMenu";
			this->mainMenu->Size = System::Drawing::Size(584, 24);
			this->mainMenu->TabIndex = 0;
			this->mainMenu->Text = L"mainMenu";
			// 
			// menuFile
			// 
			this->menuFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->menuLoadWav, 
				this->menuLoadCwf, this->menuExit});
			this->menuFile->Name = L"menuFile";
			this->menuFile->Size = System::Drawing::Size(48, 20);
			this->menuFile->Text = L"&Файл";
			// 
			// menuLoadWav
			// 
			this->menuLoadWav->Name = L"menuLoadWav";
			this->menuLoadWav->Size = System::Drawing::Size(222, 22);
			this->menuLoadWav->Text = L"Загрузить речевые данные";
			this->menuLoadWav->Click += gcnew System::EventHandler(this, &Form1::menuLoadWav_Click);
			// 
			// menuLoadCwf
			// 
			this->menuLoadCwf->Name = L"menuLoadCwf";
			this->menuLoadCwf->Size = System::Drawing::Size(222, 22);
			this->menuLoadCwf->Text = L"Загрузить сжатый файл";
			this->menuLoadCwf->Click += gcnew System::EventHandler(this, &Form1::menuLoadCwf_Click);
			// 
			// menuExit
			// 
			this->menuExit->Name = L"menuExit";
			this->menuExit->Size = System::Drawing::Size(222, 22);
			this->menuExit->Text = L"Выход";
			this->menuExit->Click += gcnew System::EventHandler(this, &Form1::menuExit_Click);
			// 
			// menuSettings
			// 
			this->menuSettings->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->menuLoadMatrix});
			this->menuSettings->Name = L"menuSettings";
			this->menuSettings->Size = System::Drawing::Size(79, 20);
			this->menuSettings->Text = L"&Настройки";
			// 
			// menuLoadMatrix
			// 
			this->menuLoadMatrix->Name = L"menuLoadMatrix";
			this->menuLoadMatrix->Size = System::Drawing::Size(251, 22);
			this->menuLoadMatrix->Text = L"Установить директорию матриц";
			this->menuLoadMatrix->Click += gcnew System::EventHandler(this, &Form1::menuLoadMatrix_Click);
			// 
			// compressPanel
			// 
			this->compressPanel->Controls->Add(this->label14);
			this->compressPanel->Controls->Add(this->comboSignalMatrix);
			this->compressPanel->Controls->Add(this->label12);
			this->compressPanel->Controls->Add(this->comboPauseMatrix);
			this->compressPanel->Controls->Add(this->label10);
			this->compressPanel->Controls->Add(this->editBPS);
			this->compressPanel->Controls->Add(this->label8);
			this->compressPanel->Controls->Add(this->label6);
			this->compressPanel->Controls->Add(this->editPauseFetch);
			this->compressPanel->Controls->Add(this->editPauseLength);
			this->compressPanel->Controls->Add(this->btnCompress);
			this->compressPanel->Controls->Add(this->labelSignalRate);
			this->compressPanel->Controls->Add(this->labelSignalBPS);
			this->compressPanel->Controls->Add(this->labelSignalLength);
			this->compressPanel->Controls->Add(this->label4);
			this->compressPanel->Controls->Add(this->label3);
			this->compressPanel->Controls->Add(this->label2);
			this->compressPanel->Controls->Add(this->label1);
			this->compressPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->compressPanel->Location = System::Drawing::Point(0, 24);
			this->compressPanel->Name = L"compressPanel";
			this->compressPanel->Size = System::Drawing::Size(289, 300);
			this->compressPanel->TabIndex = 1;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(5, 116);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(119, 13);
			this->label14->TabIndex = 17;
			this->label14->Text = L"Матрица для сигнала:";
			// 
			// comboSignalMatrix
			// 
			this->comboSignalMatrix->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboSignalMatrix->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboSignalMatrix->FormattingEnabled = true;
			this->comboSignalMatrix->Location = System::Drawing::Point(129, 113);
			this->comboSignalMatrix->Name = L"comboSignalMatrix";
			this->comboSignalMatrix->Size = System::Drawing::Size(148, 21);
			this->comboSignalMatrix->TabIndex = 16;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(5, 89);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(101, 13);
			this->label12->TabIndex = 15;
			this->label12->Text = L"Матрица для пауз:";
			// 
			// comboPauseMatrix
			// 
			this->comboPauseMatrix->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboPauseMatrix->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboPauseMatrix->FormattingEnabled = true;
			this->comboPauseMatrix->Location = System::Drawing::Point(129, 86);
			this->comboPauseMatrix->Name = L"comboPauseMatrix";
			this->comboPauseMatrix->Size = System::Drawing::Size(148, 21);
			this->comboPauseMatrix->TabIndex = 14;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(5, 205);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(31, 13);
			this->label10->TabIndex = 13;
			this->label10->Text = L"BPS:";
			// 
			// editBPS
			// 
			this->editBPS->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->editBPS->Location = System::Drawing::Point(52, 202);
			this->editBPS->Name = L"editBPS";
			this->editBPS->Size = System::Drawing::Size(225, 20);
			this->editBPS->TabIndex = 12;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(5, 179);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(16, 13);
			this->label8->TabIndex = 11;
			this->label8->Text = L"p:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(5, 153);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(17, 13);
			this->label6->TabIndex = 10;
			this->label6->Text = L"P:";
			// 
			// editPauseFetch
			// 
			this->editPauseFetch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->editPauseFetch->Location = System::Drawing::Point(52, 176);
			this->editPauseFetch->Name = L"editPauseFetch";
			this->editPauseFetch->Size = System::Drawing::Size(225, 20);
			this->editPauseFetch->TabIndex = 9;
			// 
			// editPauseLength
			// 
			this->editPauseLength->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->editPauseLength->Location = System::Drawing::Point(52, 150);
			this->editPauseLength->Name = L"editPauseLength";
			this->editPauseLength->Size = System::Drawing::Size(225, 20);
			this->editPauseLength->TabIndex = 8;
			// 
			// btnCompress
			// 
			this->btnCompress->Location = System::Drawing::Point(7, 265);
			this->btnCompress->Name = L"btnCompress";
			this->btnCompress->Size = System::Drawing::Size(75, 23);
			this->btnCompress->TabIndex = 7;
			this->btnCompress->Text = L"Сжать";
			this->btnCompress->UseVisualStyleBackColor = true;
			this->btnCompress->Click += gcnew System::EventHandler(this, &Form1::btnCompress_Click);
			// 
			// labelSignalRate
			// 
			this->labelSignalRate->AutoSize = true;
			this->labelSignalRate->Location = System::Drawing::Point(153, 60);
			this->labelSignalRate->Name = L"labelSignalRate";
			this->labelSignalRate->Size = System::Drawing::Size(10, 13);
			this->labelSignalRate->TabIndex = 6;
			this->labelSignalRate->Text = L"-";
			// 
			// labelSignalBPS
			// 
			this->labelSignalBPS->AutoSize = true;
			this->labelSignalBPS->Location = System::Drawing::Point(153, 47);
			this->labelSignalBPS->Name = L"labelSignalBPS";
			this->labelSignalBPS->Size = System::Drawing::Size(10, 13);
			this->labelSignalBPS->TabIndex = 5;
			this->labelSignalBPS->Text = L"-";
			// 
			// labelSignalLength
			// 
			this->labelSignalLength->AutoSize = true;
			this->labelSignalLength->Location = System::Drawing::Point(153, 33);
			this->labelSignalLength->Name = L"labelSignalLength";
			this->labelSignalLength->Size = System::Drawing::Size(10, 13);
			this->labelSignalLength->TabIndex = 4;
			this->labelSignalLength->Text = L"-";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(5, 60);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(132, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Частота дискретизации:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(4, 47);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(31, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"BPS:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(4, 34);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(87, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Длина сигнала:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(4, 4);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(73, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Сжатие";
			// 
			// decompressPanel
			// 
			this->decompressPanel->Controls->Add(this->btnDecompress);
			this->decompressPanel->Controls->Add(this->labelWavBPS);
			this->decompressPanel->Controls->Add(this->label17);
			this->decompressPanel->Controls->Add(this->labelCompressedBPS);
			this->decompressPanel->Controls->Add(this->label15);
			this->decompressPanel->Controls->Add(this->labelRs);
			this->decompressPanel->Controls->Add(this->label13);
			this->decompressPanel->Controls->Add(this->labelNs);
			this->decompressPanel->Controls->Add(this->label11);
			this->decompressPanel->Controls->Add(this->labelRp);
			this->decompressPanel->Controls->Add(this->label9);
			this->decompressPanel->Controls->Add(this->labelNp);
			this->decompressPanel->Controls->Add(this->label7);
			this->decompressPanel->Controls->Add(this->label5);
			this->decompressPanel->Dock = System::Windows::Forms::DockStyle::Right;
			this->decompressPanel->Location = System::Drawing::Point(295, 24);
			this->decompressPanel->Name = L"decompressPanel";
			this->decompressPanel->Size = System::Drawing::Size(289, 300);
			this->decompressPanel->TabIndex = 2;
			// 
			// btnDecompress
			// 
			this->btnDecompress->Location = System::Drawing::Point(7, 265);
			this->btnDecompress->Name = L"btnDecompress";
			this->btnDecompress->Size = System::Drawing::Size(89, 23);
			this->btnDecompress->TabIndex = 17;
			this->btnDecompress->Text = L"Восстановить";
			this->btnDecompress->UseVisualStyleBackColor = true;
			this->btnDecompress->Click += gcnew System::EventHandler(this, &Form1::btnDecompress_Click);
			// 
			// labelWavBPS
			// 
			this->labelWavBPS->AutoSize = true;
			this->labelWavBPS->Location = System::Drawing::Point(153, 85);
			this->labelWavBPS->Name = L"labelWavBPS";
			this->labelWavBPS->Size = System::Drawing::Size(10, 13);
			this->labelWavBPS->TabIndex = 16;
			this->labelWavBPS->Text = L"-";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(4, 86);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(54, 13);
			this->label17->TabIndex = 15;
			this->label17->Text = L"исх. BPS:";
			// 
			// labelCompressedBPS
			// 
			this->labelCompressedBPS->AutoSize = true;
			this->labelCompressedBPS->Location = System::Drawing::Point(153, 98);
			this->labelCompressedBPS->Name = L"labelCompressedBPS";
			this->labelCompressedBPS->Size = System::Drawing::Size(10, 13);
			this->labelCompressedBPS->TabIndex = 14;
			this->labelCompressedBPS->Text = L"-";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(4, 99);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(51, 13);
			this->label15->TabIndex = 13;
			this->label15->Text = L"сж. BPS:";
			// 
			// labelRs
			// 
			this->labelRs->AutoSize = true;
			this->labelRs->Location = System::Drawing::Point(153, 72);
			this->labelRs->Name = L"labelRs";
			this->labelRs->Size = System::Drawing::Size(10, 13);
			this->labelRs->TabIndex = 12;
			this->labelRs->Text = L"-";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(4, 73);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(23, 13);
			this->label13->TabIndex = 11;
			this->label13->Text = L"Rs:";
			// 
			// labelNs
			// 
			this->labelNs->AutoSize = true;
			this->labelNs->Location = System::Drawing::Point(153, 59);
			this->labelNs->Name = L"labelNs";
			this->labelNs->Size = System::Drawing::Size(10, 13);
			this->labelNs->TabIndex = 10;
			this->labelNs->Text = L"-";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(4, 60);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(23, 13);
			this->label11->TabIndex = 9;
			this->label11->Text = L"Ns:";
			// 
			// labelRp
			// 
			this->labelRp->AutoSize = true;
			this->labelRp->Location = System::Drawing::Point(153, 46);
			this->labelRp->Name = L"labelRp";
			this->labelRp->Size = System::Drawing::Size(10, 13);
			this->labelRp->TabIndex = 8;
			this->labelRp->Text = L"-";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(4, 47);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(24, 13);
			this->label9->TabIndex = 7;
			this->label9->Text = L"Rp:";
			// 
			// labelNp
			// 
			this->labelNp->AutoSize = true;
			this->labelNp->Location = System::Drawing::Point(153, 33);
			this->labelNp->Name = L"labelNp";
			this->labelNp->Size = System::Drawing::Size(10, 13);
			this->labelNp->TabIndex = 6;
			this->labelNp->Text = L"-";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(4, 34);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(24, 13);
			this->label7->TabIndex = 5;
			this->label7->Text = L"Np:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(3, 4);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(150, 20);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Восстановление";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 324);
			this->Controls->Add(this->decompressPanel);
			this->Controls->Add(this->compressPanel);
			this->Controls->Add(this->mainMenu);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MainMenuStrip = this->mainMenu;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Сжатие речевых данных";
			this->mainMenu->ResumeLayout(false);
			this->mainMenu->PerformLayout();
			this->compressPanel->ResumeLayout(false);
			this->compressPanel->PerformLayout();
			this->decompressPanel->ResumeLayout(false);
			this->decompressPanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: 
	void clearCompressPanel() {
		labelSignalLength->Text = "-";
		labelSignalBPS->Text = "-";
		labelSignalRate->Text = "-";

		comboPauseMatrix->SelectedIndex = -1;
		comboSignalMatrix->SelectedIndex = -1;
		
		editPauseLength->Text = "5";
		editPauseFetch->Text = "0";
		editBPS->Text = "3";

		btnCompress->Enabled = false;
	}

	void clearDecompressPanel() {
		labelNp->Text = "-";
		labelRp->Text = "-";
		labelNs->Text = "-";
		labelRs->Text = "-";
		labelWavBPS->Text = "-";
		labelCompressedBPS->Text = "-";

		btnDecompress->Enabled = false;
	}

	void loadCombos() {
		DirectoryInfo^ dir = gcnew DirectoryInfo(matrixDir);
		cli::array<FileInfo ^>^ files = dir->GetFiles();

		for (int i = 0; i < files.Length; i++) {
			comboPauseMatrix->Items->Add(files[i]);
			comboSignalMatrix->Items->Add(files[i]);
		}
	}

private: System::Void menuExit_Click(System::Object^  sender, System::EventArgs^  e) {
				 Application::Exit();
			 }

private: System::Void menuLoadWav_Click(System::Object^  sender, System::EventArgs^  e) {
			 clearCompressPanel();
			 clearDecompressPanel();

			 System::Windows::Forms::DialogResult result;
			 result = openFileDialog->ShowDialog();

			 if ((int)result == IDOK)
			 {
				 String^ fileName = openFileDialog->FileName;
				 compressor->LoadSignalFile((char *)Marshal::StringToHGlobalAnsi(fileName).ToPointer());
				 
				 labelSignalLength->Text = Convert::ToString(gcnew Int64(compressor->GetSignalLenght()));
				 labelSignalBPS->Text = Convert::ToString(gcnew Int32(compressor->GetSignalBps()));
				 labelSignalRate->Text = Convert::ToString(gcnew Int32(compressor->GetSignalRate()));

				 btnCompress->Enabled = true;
			 }
		 }

private: System::Void menuLoadCwf_Click(System::Object^  sender, System::EventArgs^  e) {
			 clearCompressPanel();
			 clearDecompressPanel();

			 System::Windows::Forms::DialogResult result;
			 result = openFileDialog->ShowDialog();

			 if ((int)result == IDOK)
			 {
				 String^ fileName = openFileDialog->FileName;
				 compressor->LoadCompressedFile((char *)Marshal::StringToHGlobalAnsi(fileName).ToPointer());

				 labelNp->Text = Convert::ToString(gcnew Int32(compressor->GetNp()));
				 labelRp->Text = Convert::ToString(gcnew Int32(compressor->GetRp()));
				 labelNs->Text = Convert::ToString(gcnew Int32(compressor->GetNs()));
				 labelRs->Text = Convert::ToString(gcnew Int32(compressor->GetRs()));
				 labelWavBPS->Text = Convert::ToString(gcnew Int32(compressor->GetSignalBps()));
				 labelCompressedBPS->Text = Convert::ToString(gcnew Int32(compressor->GetCompressedBps()));

				 btnDecompress->Enabled = true;
			 }
		 }

private: System::Void menuLoadMatrix_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Windows::Forms::DialogResult result;
			 result = openDirDialog->ShowDialog();

			 if ((int)result == IDOK)
			 {
				 matrixDir = openDirDialog->SelectedPath;
				 loadCombos();
			 }
		 }

private: System::Void btnCompress_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (matrixDir == String::Empty) {
				 MessageBox::Show("Не установлена директория матриц",
					 "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);

				 return;
			 }
			 if (comboPauseMatrix->Text == String::Empty) {
				 MessageBox::Show("Не выбрано значение для матрицы пауз",
					 "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);

				 return;
			 }
			 if (comboSignalMatrix->Text == String::Empty) {
				 MessageBox::Show("Не выбрано значение для матрицы сигнала",
					 "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);

				 return;
			 }

			 saveFileDialog->DefaultExt = "cwf";
			 System::Windows::Forms::DialogResult result;
			 result = saveFileDialog->ShowDialog();

			 if ((int)result == IDOK)
			 {
				 cli::array<String ^>^ pauseMatrixSplit = comboPauseMatrix->SelectedItem->ToString()->Split('_');
				 USHORT Rp = Convert::ToInt16(pauseMatrixSplit[1]);
				 USHORT Np = Convert::ToInt16(pauseMatrixSplit[2]->Split('.')[0]);

				 cli::array<String ^>^ signalMatrixSplit = comboSignalMatrix->SelectedItem->ToString()->Split('_');
				 USHORT Rs = Convert::ToInt16(signalMatrixSplit[1]);
				 USHORT Ns = Convert::ToInt16(signalMatrixSplit[2]->Split('.')[0]);

				 compressor->SetCompressParams(Np, Rp, Convert::ToInt16(editPauseLength->Text), Convert::ToInt16(editPauseFetch->Text), Ns, Rs, Convert::ToInt16(editBPS->Text));
				 compressor->matrixDir = (char *)Marshal::StringToHGlobalAnsi(matrixDir).ToPointer();
				 compressor->FullCompressData();
				 compressor->SaveCompressedFile((char *)Marshal::StringToHGlobalAnsi(saveFileDialog->FileName).ToPointer());

				 MessageBox::Show("Сжатие завершено",
					 "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Information);
			 }
		 }

private: System::Void btnDecompress_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (matrixDir == String::Empty) {
				 MessageBox::Show("Не установлена директория матриц",
					 "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);

				 return;
			 }

			 saveFileDialog->DefaultExt = "wav";
			 System::Windows::Forms::DialogResult result;
			 result = saveFileDialog->ShowDialog();

			 if ((int)result == IDOK)
			 {
				 compressor->matrixDir = (char *)Marshal::StringToHGlobalAnsi(matrixDir).ToPointer();
				 compressor->FullDecompressData();
				 compressor->SaveSignalData((char *)Marshal::StringToHGlobalAnsi(saveFileDialog->FileName).ToPointer());

				 MessageBox::Show("Восстановление завершено",
					 "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Information);
			 }
		 }
};
}