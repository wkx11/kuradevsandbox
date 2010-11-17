#pragma once

namespace HelloWorld {

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
	private: System::Windows::Forms::Button^  btn_hello;
	protected: 

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
			this->btn_hello = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_hello
			// 
			this->btn_hello->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->btn_hello->Location = System::Drawing::Point(12, 12);
			this->btn_hello->Name = L"btn_hello";
			this->btn_hello->Size = System::Drawing::Size(98, 39);
			this->btn_hello->TabIndex = 0;
			this->btn_hello->Text = L"Hello";
			this->btn_hello->UseVisualStyleBackColor = true;
			this->btn_hello->Click += gcnew System::EventHandler(this, &Form1::btn_hello_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(122, 63);
			this->Controls->Add(this->btn_hello);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Hello, World!";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btn_hello_Click(System::Object^  sender, System::EventArgs^  e) {
				 System::Windows::Forms::MessageBox::Show("Hello, World!!");
			 }
	};
}

