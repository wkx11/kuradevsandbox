#pragma once

namespace OpenMovie {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Form1 の概要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ファイルToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  開くToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  閉じるToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  終了ToolStripMenuItem;
	private: System::Windows::Forms::Label^  label3;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Label^  loadFileName;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  playRealtime;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ファイルToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->開くToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->閉じるToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->終了ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->loadFileName = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->playRealtime = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(8, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(420, 302);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(434, 37);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(22, 12);
			this->label1->TabIndex = 1;
			this->label1->Text = L"X ：";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(434, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(22, 12);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Y ：";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ファイルToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(560, 26);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ファイルToolStripMenuItem
			// 
			this->ファイルToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->開くToolStripMenuItem, 
				this->閉じるToolStripMenuItem, this->終了ToolStripMenuItem});
			this->ファイルToolStripMenuItem->Name = L"ファイルToolStripMenuItem";
			this->ファイルToolStripMenuItem->Size = System::Drawing::Size(68, 22);
			this->ファイルToolStripMenuItem->Text = L"ファイル";
			// 
			// 開くToolStripMenuItem
			// 
			this->開くToolStripMenuItem->Name = L"開くToolStripMenuItem";
			this->開くToolStripMenuItem->Size = System::Drawing::Size(112, 22);
			this->開くToolStripMenuItem->Text = L"開く";
			this->開くToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::開くToolStripMenuItem_Click);
			// 
			// 閉じるToolStripMenuItem
			// 
			this->閉じるToolStripMenuItem->Name = L"閉じるToolStripMenuItem";
			this->閉じるToolStripMenuItem->Size = System::Drawing::Size(112, 22);
			this->閉じるToolStripMenuItem->Text = L"閉じる";
			// 
			// 終了ToolStripMenuItem
			// 
			this->終了ToolStripMenuItem->Name = L"終了ToolStripMenuItem";
			this->終了ToolStripMenuItem->Size = System::Drawing::Size(112, 22);
			this->終了ToolStripMenuItem->Text = L"終了";
			this->終了ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::終了ToolStripMenuItem_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(13, 338);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(69, 12);
			this->label3->TabIndex = 4;
			this->label3->Text = L"再生ファイル：";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker1_RunWorkerCompleted);
			// 
			// loadFileName
			// 
			this->loadFileName->AutoSize = true;
			this->loadFileName->Location = System::Drawing::Point(88, 338);
			this->loadFileName->Name = L"loadFileName";
			this->loadFileName->Size = System::Drawing::Size(0, 12);
			this->loadFileName->TabIndex = 5;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->playRealtime);
			this->groupBox1->Location = System::Drawing::Point(436, 229);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(114, 100);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"再生設定";
			// 
			// playRealtime
			// 
			this->playRealtime->AutoSize = true;
			this->playRealtime->Checked = true;
			this->playRealtime->CheckState = System::Windows::Forms::CheckState::Checked;
			this->playRealtime->Enabled = false;
			this->playRealtime->Location = System::Drawing::Point(6, 18);
			this->playRealtime->Name = L"playRealtime";
			this->playRealtime->Size = System::Drawing::Size(84, 16);
			this->playRealtime->TabIndex = 0;
			this->playRealtime->Text = L"実時間再生";
			this->playRealtime->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(560, 360);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->loadFileName);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

	private: System::Void 開くToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 // ファイル選択ダイアログ
				 OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
				 System::Windows::Forms::DialogResult^ dr = openFileDialog->ShowDialog();
				 if( dr = System::Windows::Forms::DialogResult::OK ){
					 // TODO: ファイル取得時の処理(動画読み込み等)
					 //MessageBox::Show(openFileDialog->FileName, "caption");

					 // バックグラウンドスレッドの停止
					 if (this->backgroundWorker1->IsBusy) {
						 this->backgroundWorker1->CancelAsync();
						 while (this->backgroundWorker1->IsBusy) {
							 Application::DoEvents();
						 }
					 }
					 if (System::IO::File::Exists(openFileDialog->FileName)) {
						 // バックグラウンドスレッドで再生処理開始
						 this->backgroundWorker1->RunWorkerAsync(openFileDialog->FileName);
						 this->loadFileName->Text = openFileDialog->FileName;
					 }
				 }
			 }

	private: System::Void 終了ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 // TODO: 終了時の処理
				 this->Close();
			 }
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 BackgroundWorker^ worker = safe_cast<BackgroundWorker^>(sender);

				 // ファイルから読み込み
				 char *path = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(safe_cast<String^>(e->Argument)).ToPointer();

				 cv::VideoCapture cap(path);
				 if (!cap.isOpened()) {
					 MessageBox::Show(safe_cast<String^>(e->Argument), "Don't open");
					 return;
				 }
				 // フレーム取得用変数
				 cv::Mat frame;
				 // 再生時間管理
				 DateTime start = DateTime::Now;
				 while (1) {
					 if (worker->CancellationPending)
						 break;

					 // 実時間再生時再生タイミング調整(失敗コード)
					 /*
					 if (this->playRealtime->Checked) {
						 TimeSpan ts = DateTime::Now - start;
						 cap.set(CV_CAP_PROP_POS_MSEC, ts.TotalMilliseconds);
					 }
					 */

					 // フレーム取得
					 cap >> frame;
					 if (frame.empty())
						 break;

					 // リサイズ
					 cv::Mat resized(this->pictureBox1->Width * frame.rows / frame.cols, this->pictureBox1->Width, frame.type());
					 cv::resize(frame, resized, resized.size());

					 // 画面に表示
					 this->pictureBox1->Image = UFOHunt::Lib::ImageConverter::Mat2DotNetBMP(
							UFOHunt::Lib::ImageConverterData_cvMat::Create(resized.rows, resized.cols, resized.flags, resized.data));
				 }
				 
				 // ヒープに確保されたファイルパスを解放
				 System::Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr(path));
			 }
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			 this->loadFileName->Text = "";
			 this->pictureBox1->Image = nullptr;
		 }
};
}

