#pragma once

namespace OpenCVTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  button2;


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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"メイリオ", 72, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(128)));
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(640, 479);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(640, 480);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"標準", L"グレースケール"});
			this->comboBox1->Location = System::Drawing::Point(12, 497);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 20);
			this->comboBox1->TabIndex = 2;
			this->comboBox1->Text = L"標準";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(577, 495);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Save";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(664, 529);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Text = L"CapTest";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private:
	// CmboBoxのインデックス値(アクセス制限回避用)
	int cboxIndex;

	// イメージをPictureBoxへ表示させる
	System::Void Image(cv::Mat *img)
	{
		this->pictureBox1->Image = UFOHunt::Lib::ImageConverter::Mat2DotNetBMP(
			UFOHunt::Lib::ImageConverterData_cvMat::Create(img->rows, img->cols, img->flags, img->data));
	}

private: 
	// .NETのスレッドクラス
	System::Threading::Thread^ th;
	// スレッドクラスから呼ばれるコールバック関数
	static void th_callback(System::Object^ obj) 
	{
		// スレッドのオーナーインスタンスを取得
		Form1^ owner = dynamic_cast<Form1^>(obj);

		// キャプチャデバイスの準備
		cv::VideoCapture cap(0);
		if (!cap.isOpened())
			MessageBox::Show("Cam Open Error");
		
		// カメラ設定
		cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
		//cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480); // ←何故か省略可能。詳細はcvcap_dshow.cppの156行あたり(Ver2.1.0時)参照

		// キャプチャ処理
		try {
			while (1) { 
				cv::Mat frame;
				cap >> frame;
				cv::Mat filterd;
				// フィルタ処理
				switch (owner->cboxIndex) {
					case 0:  // 標準
					default: // 標準と等価
						break;
					case 1: // グレースケール
						cvtColor(frame, filterd, CV_RGB2GRAY);
						break;
				}
				if (filterd.empty())
					owner->Image(&frame);
				else
					owner->Image(&filterd);
			}
		} catch (System::Threading::ThreadAbortException^ e) {
			System::Diagnostics::Trace::WriteLine("映像スレッド終了なう。\n" + e->ToString());
		}
	}

	// Startボタンクリックイベント
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		// 邪魔なボタンを非表示にする
		this->button1->Visible = false;

		// スレッド作成して起動
		th = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(&Form1::th_callback));
		th->Start(this);
	}

	// フォームを閉じる直前に呼ばれるイベント
	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (nullptr != th) {
			th->Abort();
			th->Join();
		}
	}
	// スレッド間アクセス制限を回避するための代入処理
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		cboxIndex = comboBox1->SelectedIndex;
	}
	// 保存ボタン処理(おまけ)
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		// ビデオ再生前は実行しない
		if (button1->Visible == true) return;

		// 出力ディレクトリパス
		String^ saveDir = ".\\Save\\";
		// 出力ファイル番号
		int saveNo = 0;

		ArrayList^ files = gcnew ArrayList();

		// 出力ディレクトリの存在チェック
		if (IO::Directory::Exists(saveDir)) {
			// 出力ディレクトリ内のファイルリスト取得
			files->AddRange(IO::Directory::GetFiles(saveDir, "Save????.jpg"));
			// 出力ファイル番号の最大値を取得
			if (files->Count > 0) {
			files->Sort();
			saveNo = Int32::Parse(dynamic_cast<String^>(files[files->Count - 1])->Substring(saveDir->Length + 4, 4)) + 1;
			}
		} else {
			IO::Directory::CreateDirectory(saveDir);
		}
		// jpgでファイルを保存
		System::Diagnostics::Trace::WriteLine("SaveName => " + String::Format(saveDir + "Save{0:D4}.jpg", saveNo));
		pictureBox1->Image->Save(String::Format(saveDir + "Save{0:D4}.jpg", saveNo), System::Drawing::Imaging::ImageFormat::Jpeg);
	}
};

	
}

