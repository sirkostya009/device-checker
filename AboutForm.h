#pragma once

namespace ldc {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class AboutForm : public System::Windows::Forms::Form
	{
	public:
		AboutForm(void)
		{
			InitializeComponent();
		}

	protected:
		~AboutForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pbIcon;
	protected:

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::GroupBox^ gbInfo;
			System::Windows::Forms::Label^ lblInfo;
			System::Windows::Forms::Label^ lblRights;
			System::Windows::Forms::Label^ lblAuthor;
			System::Windows::Forms::Label^ lblVersion;
			System::Windows::Forms::Label^ lblName;
			System::Windows::Forms::Button^ btnClose;
			this->pbIcon = (gcnew System::Windows::Forms::PictureBox());
			gbInfo = (gcnew System::Windows::Forms::GroupBox());
			lblInfo = (gcnew System::Windows::Forms::Label());
			lblRights = (gcnew System::Windows::Forms::Label());
			lblAuthor = (gcnew System::Windows::Forms::Label());
			lblVersion = (gcnew System::Windows::Forms::Label());
			lblName = (gcnew System::Windows::Forms::Label());
			btnClose = (gcnew System::Windows::Forms::Button());
			gbInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbIcon))->BeginInit();
			this->SuspendLayout();
			// 
			// gbInfo
			// 
			gbInfo->Controls->Add(lblInfo);
			gbInfo->Location = System::Drawing::Point(20, 173);
			gbInfo->Name = L"gbInfo";
			gbInfo->Size = System::Drawing::Size(411, 149);
			gbInfo->TabIndex = 14;
			gbInfo->TabStop = false;
			// 
			// lblInfo
			// 
			lblInfo->AutoSize = true;
			lblInfo->Location = System::Drawing::Point(11, 22);
			lblInfo->Name = L"lblInfo";
			lblInfo->Size = System::Drawing::Size(321, 104);
			lblInfo->TabIndex = 7;
			lblInfo->Text = L"Тема роботи \'\'\r\nЗастосунок виконано відповідно до індивідуального завдання\r\nЗасто"
				L"сунок дозволяє\r\n1. бла бла\r\n2. бла бла\r\n3. бла бла\r\n4. бла бла\r\n5. бла бла";
			// 
			// lblRights
			// 
			lblRights->AutoSize = true;
			lblRights->Location = System::Drawing::Point(173, 126);
			lblRights->Name = L"lblRights";
			lblRights->Size = System::Drawing::Size(104, 13);
			lblRights->TabIndex = 13;
			lblRights->Text = L"Всі права захищені";
			// 
			// lblAuthor
			// 
			lblAuthor->AutoSize = true;
			lblAuthor->Location = System::Drawing::Point(173, 98);
			lblAuthor->Name = L"lblAuthor";
			lblAuthor->Size = System::Drawing::Size(155, 13);
			lblAuthor->TabIndex = 12;
			lblAuthor->Text = L"Розробник: ст. гр. ПІ-21б ПІБ";
			// 
			// lblVersion
			// 
			lblVersion->AutoSize = true;
			lblVersion->Location = System::Drawing::Point(173, 68);
			lblVersion->Name = L"lblVersion";
			lblVersion->Size = System::Drawing::Size(70, 13);
			lblVersion->TabIndex = 11;
			lblVersion->Text = L"Версія: 1.0.0";
			// 
			// lblName
			// 
			lblName->AutoSize = true;
			lblName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			lblName->Location = System::Drawing::Point(173, 39);
			lblName->Name = L"lblName";
			lblName->Size = System::Drawing::Size(98, 13);
			lblName->TabIndex = 10;
			lblName->Text = L"Device Checker";
			// 
			// btnClose
			// 
			btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
			btnClose->Location = System::Drawing::Point(183, 349);
			btnClose->Name = L"btnClose";
			btnClose->Size = System::Drawing::Size(75, 23);
			btnClose->TabIndex = 8;
			btnClose->Text = L"Закрити";
			btnClose->UseVisualStyleBackColor = true;
			btnClose->Click += gcnew System::EventHandler(this, &AboutForm::btnClose_Click);
			// 
			// pbIcon
			// 
			this->pbIcon->Location = System::Drawing::Point(20, 39);
			this->pbIcon->Name = L"pbIcon";
			this->pbIcon->Size = System::Drawing::Size(128, 128);
			this->pbIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbIcon->TabIndex = 9;
			this->pbIcon->TabStop = false;
			// 
			// AboutForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(450, 407);
			this->Controls->Add(gbInfo);
			this->Controls->Add(lblRights);
			this->Controls->Add(lblAuthor);
			this->Controls->Add(lblVersion);
			this->Controls->Add(lblName);
			this->Controls->Add(this->pbIcon);
			this->Controls->Add(btnClose);
			this->Name = L"AboutForm";
			this->Text = L"Про застосунок";
			this->Load += gcnew System::EventHandler(this, &AboutForm::AboutForm_Load);
			gbInfo->ResumeLayout(false);
			gbInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbIcon))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Hide();
		}

		private: System::Void AboutForm_Load(System::Object^ sender, System::EventArgs^ e) {
			this->pbIcon->Image = Image::FromFile("device-checker.png");
		}
	};
}
