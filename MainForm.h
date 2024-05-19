#pragma once
#include "HardwareRepository.h"
#include "AboutForm.h"

namespace ldc {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
		HardwareRepository^ repository;
	private: System::Windows::Forms::Label^ moboLabel;
	private: System::Windows::Forms::Label^ biosLabel;
	private: System::Windows::Forms::Label^ osLabel;
	private: System::Windows::Forms::ListView^ thermalList;

		   AboutForm^ aboutForm;

	public:
		MainForm(void)
		{
			InitializeComponent();
			repository = gcnew HardwareRepository();
			aboutForm = gcnew AboutForm();
		}

	protected:
		~MainForm() {
			if (components) {
				delete components;
			}
		}

	private: System::Windows::Forms::ToolStripStatusLabel^ cpuLoadLabel;
	private: System::Windows::Forms::ToolStripStatusLabel^ statusMainLabel;
	private: System::Windows::Forms::ToolStripMenuItem^ exportOption;
	private: System::Windows::Forms::ToolStripButton^ exportButton;
	private: System::Windows::Forms::ToolStripButton^ aboutButton;
	private: System::Windows::Forms::ListView^ threadsList;
	private: System::ComponentModel::BackgroundWorker^ statUpdater;
	private: System::Windows::Forms::ListView^ memoryList;
	private: System::Windows::Forms::Label^ totalRamLabel;
	private: System::Windows::Forms::Label^ cpuLabel;
	private: System::Windows::Forms::Label^ coresThreadLabel;
	private: System::Windows::Forms::Label^ gpuLabel;
	private: System::Windows::Forms::Label^ ramSpeedLabel;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::StatusStrip^ statusStrip;
			System::Windows::Forms::MenuStrip^ menu;
			System::Windows::Forms::ToolStripMenuItem^ topMenuFileItem;
			System::Windows::Forms::ToolStripSeparator^ separator;
			System::Windows::Forms::ToolStripMenuItem^ exitOption;
			System::Windows::Forms::ToolStripMenuItem^ tmsiInfo;
			System::Windows::Forms::ToolStripMenuItem^ aboutItem;
			System::Windows::Forms::ToolStrip^ toolStrip;
			System::Windows::Forms::ColumnHeader^ columnHeader1;
			System::Windows::Forms::ColumnHeader^ columnHeader2;
			System::Windows::Forms::ColumnHeader^ memorySensorName;
			System::Windows::Forms::ColumnHeader^ memorySensorValue;
			System::Windows::Forms::ColumnHeader^ name;
			System::Windows::Forms::ColumnHeader^ val;
			this->cpuLoadLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->statusMainLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->exportOption = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exportButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->aboutButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->cpuLabel = (gcnew System::Windows::Forms::Label());
			this->threadsList = (gcnew System::Windows::Forms::ListView());
			this->statUpdater = (gcnew System::ComponentModel::BackgroundWorker());
			this->memoryList = (gcnew System::Windows::Forms::ListView());
			this->totalRamLabel = (gcnew System::Windows::Forms::Label());
			this->coresThreadLabel = (gcnew System::Windows::Forms::Label());
			this->gpuLabel = (gcnew System::Windows::Forms::Label());
			this->ramSpeedLabel = (gcnew System::Windows::Forms::Label());
			this->moboLabel = (gcnew System::Windows::Forms::Label());
			this->biosLabel = (gcnew System::Windows::Forms::Label());
			this->osLabel = (gcnew System::Windows::Forms::Label());
			this->thermalList = (gcnew System::Windows::Forms::ListView());
			statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			menu = (gcnew System::Windows::Forms::MenuStrip());
			topMenuFileItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			separator = (gcnew System::Windows::Forms::ToolStripSeparator());
			exitOption = (gcnew System::Windows::Forms::ToolStripMenuItem());
			tmsiInfo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			aboutItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			toolStrip = (gcnew System::Windows::Forms::ToolStrip());
			columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			memorySensorName = (gcnew System::Windows::Forms::ColumnHeader());
			memorySensorValue = (gcnew System::Windows::Forms::ColumnHeader());
			name = (gcnew System::Windows::Forms::ColumnHeader());
			val = (gcnew System::Windows::Forms::ColumnHeader());
			statusStrip->SuspendLayout();
			menu->SuspendLayout();
			toolStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip
			// 
			statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->cpuLoadLabel, this->statusMainLabel });
			statusStrip->Location = System::Drawing::Point(0, 483);
			statusStrip->Name = L"statusStrip";
			statusStrip->Size = System::Drawing::Size(567, 22);
			statusStrip->TabIndex = 9;
			statusStrip->Text = L"statusStrip1";
			// 
			// cpuLoadLabel
			// 
			this->cpuLoadLabel->Name = L"cpuLoadLabel";
			this->cpuLoadLabel->Size = System::Drawing::Size(35, 17);
			this->cpuLoadLabel->Text = L"100%";
			// 
			// statusMainLabel
			// 
			this->statusMainLabel->Name = L"statusMainLabel";
			this->statusMainLabel->Size = System::Drawing::Size(0, 17);
			// 
			// menu
			// 
			menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { topMenuFileItem, tmsiInfo });
			menu->Location = System::Drawing::Point(0, 0);
			menu->Name = L"menu";
			menu->Size = System::Drawing::Size(567, 24);
			menu->TabIndex = 6;
			menu->Text = L"menuStrip1";
			// 
			// topMenuFileItem
			// 
			topMenuFileItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->exportOption,
					separator, exitOption
			});
			topMenuFileItem->Name = L"topMenuFileItem";
			topMenuFileItem->Size = System::Drawing::Size(48, 20);
			topMenuFileItem->Text = L"Файл";
			// 
			// exportOption
			// 
			this->exportOption->Name = L"exportOption";
			this->exportOption->Size = System::Drawing::Size(119, 22);
			this->exportOption->Text = L"Експорт";
			this->exportOption->Click += gcnew System::EventHandler(this, &MainForm::exportFile);
			// 
			// separator
			// 
			separator->Name = L"separator";
			separator->Size = System::Drawing::Size(116, 6);
			// 
			// exitOption
			// 
			exitOption->Name = L"exitOption";
			exitOption->Size = System::Drawing::Size(119, 22);
			exitOption->Text = L"Закрити";
			exitOption->Click += gcnew System::EventHandler(this, &MainForm::exitOption_Click);
			// 
			// tmsiInfo
			// 
			tmsiInfo->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { aboutItem });
			tmsiInfo->Name = L"tmsiInfo";
			tmsiInfo->Size = System::Drawing::Size(42, 20);
			tmsiInfo->Text = L"Про";
			// 
			// aboutItem
			// 
			aboutItem->Name = L"aboutItem";
			aboutItem->Size = System::Drawing::Size(161, 22);
			aboutItem->Text = L"Про застосунок";
			aboutItem->Click += gcnew System::EventHandler(this, &MainForm::aboutItem_Click);
			// 
			// toolStrip
			// 
			toolStrip->ImageScalingSize = System::Drawing::Size(32, 32);
			toolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->exportButton, this->aboutButton });
			toolStrip->Location = System::Drawing::Point(0, 24);
			toolStrip->Name = L"toolStrip";
			toolStrip->Size = System::Drawing::Size(567, 25);
			toolStrip->TabIndex = 10;
			// 
			// exportButton
			// 
			this->exportButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->exportButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->exportButton->Name = L"exportButton";
			this->exportButton->Size = System::Drawing::Size(23, 22);
			this->exportButton->Text = L"Експорт";
			this->exportButton->Click += gcnew System::EventHandler(this, &MainForm::exportFile);
			// 
			// aboutButton
			// 
			this->aboutButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->aboutButton->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->aboutButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->aboutButton->Name = L"aboutButton";
			this->aboutButton->Size = System::Drawing::Size(23, 22);
			this->aboutButton->Text = L"Інформація";
			this->aboutButton->Click += gcnew System::EventHandler(this, &MainForm::aboutButton_Click);
			// 
			// columnHeader1
			// 
			columnHeader1->Text = L"№ потоку";
			// 
			// columnHeader2
			// 
			columnHeader2->Text = L"Навантаження";
			columnHeader2->Width = 91;
			// 
			// memorySensorName
			// 
			memorySensorName->Text = L"Розмір";
			// 
			// memorySensorValue
			// 
			memorySensorValue->Text = L"Частота";
			// 
			// name
			// 
			name->Text = L"Назва";
			// 
			// val
			// 
			val->Text = L"значення";
			// 
			// cpuLabel
			// 
			this->cpuLabel->AutoSize = true;
			this->cpuLabel->Location = System::Drawing::Point(-3, 407);
			this->cpuLabel->Name = L"cpuLabel";
			this->cpuLabel->Size = System::Drawing::Size(51, 13);
			this->cpuLabel->TabIndex = 14;
			this->cpuLabel->Text = L"cpuLabel";
			// 
			// threadsList
			// 
			this->threadsList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { columnHeader1, columnHeader2 });
			this->threadsList->HideSelection = false;
			this->threadsList->Location = System::Drawing::Point(0, 64);
			this->threadsList->Name = L"threadsList";
			this->threadsList->Size = System::Drawing::Size(158, 330);
			this->threadsList->TabIndex = 11;
			this->threadsList->UseCompatibleStateImageBehavior = false;
			this->threadsList->View = System::Windows::Forms::View::Details;
			// 
			// statUpdater
			// 
			this->statUpdater->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::statUpdater_DoWork);
			// 
			// memoryList
			// 
			this->memoryList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { memorySensorName, memorySensorValue });
			this->memoryList->HideSelection = false;
			this->memoryList->Location = System::Drawing::Point(164, 64);
			this->memoryList->Name = L"memoryList";
			this->memoryList->Size = System::Drawing::Size(212, 153);
			this->memoryList->TabIndex = 12;
			this->memoryList->UseCompatibleStateImageBehavior = false;
			this->memoryList->View = System::Windows::Forms::View::Details;
			// 
			// totalRamLabel
			// 
			this->totalRamLabel->AutoSize = true;
			this->totalRamLabel->Location = System::Drawing::Point(164, 229);
			this->totalRamLabel->Name = L"totalRamLabel";
			this->totalRamLabel->Size = System::Drawing::Size(122, 13);
			this->totalRamLabel->TabIndex = 13;
			this->totalRamLabel->Text = L"Загалом пам\'яті: 16GB";
			// 
			// coresThreadLabel
			// 
			this->coresThreadLabel->AutoSize = true;
			this->coresThreadLabel->Location = System::Drawing::Point(-3, 435);
			this->coresThreadLabel->Name = L"coresThreadLabel";
			this->coresThreadLabel->Size = System::Drawing::Size(24, 13);
			this->coresThreadLabel->TabIndex = 15;
			this->coresThreadLabel->Text = L"2/4";
			// 
			// gpuLabel
			// 
			this->gpuLabel->AutoSize = true;
			this->gpuLabel->Location = System::Drawing::Point(382, 64);
			this->gpuLabel->Name = L"gpuLabel";
			this->gpuLabel->Size = System::Drawing::Size(67, 13);
			this->gpuLabel->TabIndex = 16;
			this->gpuLabel->Text = L"GenericGPU";
			// 
			// ramSpeedLabel
			// 
			this->ramSpeedLabel->AutoSize = true;
			this->ramSpeedLabel->Location = System::Drawing::Point(164, 255);
			this->ramSpeedLabel->Name = L"ramSpeedLabel";
			this->ramSpeedLabel->Size = System::Drawing::Size(49, 13);
			this->ramSpeedLabel->TabIndex = 17;
			this->ramSpeedLabel->Text = L"Частота";
			// 
			// moboLabel
			// 
			this->moboLabel->AutoSize = true;
			this->moboLabel->Location = System::Drawing::Point(164, 334);
			this->moboLabel->Name = L"moboLabel";
			this->moboLabel->Size = System::Drawing::Size(66, 13);
			this->moboLabel->TabIndex = 18;
			this->moboLabel->Text = L"motherboard";
			// 
			// biosLabel
			// 
			this->biosLabel->AutoSize = true;
			this->biosLabel->Location = System::Drawing::Point(164, 351);
			this->biosLabel->Name = L"biosLabel";
			this->biosLabel->Size = System::Drawing::Size(26, 13);
			this->biosLabel->TabIndex = 19;
			this->biosLabel->Text = L"bios";
			// 
			// osLabel
			// 
			this->osLabel->AutoSize = true;
			this->osLabel->Location = System::Drawing::Point(164, 368);
			this->osLabel->Name = L"osLabel";
			this->osLabel->Size = System::Drawing::Size(18, 13);
			this->osLabel->TabIndex = 20;
			this->osLabel->Text = L"os";
			// 
			// thermalList
			// 
			this->thermalList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { name, val });
			this->thermalList->HideSelection = false;
			this->thermalList->Location = System::Drawing::Point(385, 80);
			this->thermalList->Name = L"thermalList";
			this->thermalList->Size = System::Drawing::Size(182, 400);
			this->thermalList->TabIndex = 21;
			this->thermalList->UseCompatibleStateImageBehavior = false;
			this->thermalList->View = System::Windows::Forms::View::Details;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(567, 505);
			this->Controls->Add(this->thermalList);
			this->Controls->Add(this->osLabel);
			this->Controls->Add(this->biosLabel);
			this->Controls->Add(this->moboLabel);
			this->Controls->Add(this->ramSpeedLabel);
			this->Controls->Add(this->gpuLabel);
			this->Controls->Add(this->coresThreadLabel);
			this->Controls->Add(this->cpuLabel);
			this->Controls->Add(this->totalRamLabel);
			this->Controls->Add(this->memoryList);
			this->Controls->Add(this->threadsList);
			this->Controls->Add(toolStrip);
			this->Controls->Add(statusStrip);
			this->Controls->Add(menu);
			this->Name = L"MainForm";
			this->Text = L"Device Checker";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			statusStrip->ResumeLayout(false);
			statusStrip->PerformLayout();
			menu->ResumeLayout(false);
			menu->PerformLayout();
			toolStrip->ResumeLayout(false);
			toolStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: void updateCpuLoad() {
			cpuLoadLabel->Text = "CPU: " + repository->CpuLoad + "%";
		}

		private: void updateThreadsTable() {
			threadsList->Items->Clear();
			for each (auto id in repository->CpuCoreSensors) {
				auto item = gcnew ListViewItem();
				item->Text = id->Name;
				item->SubItems->Add(id->Value + "%");
				threadsList->Items->Add(item);
			}
		}

		private: void updateThermals() {
			thermalList->Items->Clear();
			for each (auto sensor in repository->ThermoSensors) {
				if (sensor == nullptr) {
					continue;
				}
				auto item = gcnew ListViewItem();
				item->Text = sensor->Name;
				item->SubItems->Add(sensor->Value + "°C");
				thermalList->Items->Add(item);
			}
		}

		private: void exportFile(System::Object^ sender, System::EventArgs^ e) {
			auto dialog = gcnew SaveFileDialog();
			dialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
			dialog->FilterIndex = 1;
			dialog->RestoreDirectory = true;

			if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				auto file = dialog->OpenFile();
				if (file != nullptr) {
					auto writer = gcnew IO::StreamWriter(file);
					writer->WriteLine("CPU: " + repository->CpuName);
					writer->WriteLine("GPU: " + repository->GpuName);
					writer->WriteLine("Motherboard: " + repository->Motherboard->Name);
					writer->WriteLine("BIOS: " + repository->Bios->Bios->Vendor + ' ' + repository->Bios->Bios->Version);
					writer->WriteLine("OS: " + repository->Motherboard->SMBios->SystemEnclosure->SerialNumber);
					writer->WriteLine("Total RAM: " + totalRamLabel->Text);
					writer->WriteLine("RAM Speed: " + ramSpeedLabel->Text);
					writer->WriteLine("Cores/Threads: " + coresThreadLabel->Text);
					writer->WriteLine("CPU Load: " + cpuLoadLabel->Text);
					writer->WriteLine("Threads:");
					for each (auto id in repository->CpuCoreSensors) {
						writer->WriteLine(id->Name + ": " + id->Value + "%");
					}
					writer->WriteLine("Memory:");
					for each (auto sensor in repository->MemorySensors) {
						writer->WriteLine(sensor->Name + ": " + sensor->Value + "°C");
					}
					writer->WriteLine("Thermals:");
					for each (auto sensor in repository->ThermoSensors) {
						if (sensor == nullptr) {
							continue;
						}
						writer->WriteLine(sensor->Name + ": " + sensor->Value + "°C");
					}
					writer->Close();
					file->Close();
				}
			}
		}

		private: System::Void aboutItem_Click(System::Object^ sender, System::EventArgs^ e) {
			aboutForm->ShowDialog();
		}

		private: System::Void aboutButton_Click(System::Object^ sender, System::EventArgs^ e) {
			aboutForm->ShowDialog();
		}

		private: System::Void exitOption_Click(System::Object^ sender, System::EventArgs^ e) {
			Application::Exit();
		}

		private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
			exportButton->Image = Image::FromFile("exportButton.Image.png");
			aboutButton->Image = Image::FromFile("aboutButton.Image.png");

			cpuLabel->Text = "CPU: " + repository->CpuName;
			auto mb = repository->Motherboard;
			coresThreadLabel->Text = String::Format(L"{0} ядра/{1} потоки", mb->SMBios->Processors[0]->CoreCount, mb->SMBios->Processors[0]->ThreadCount);

			gpuLabel->Text = repository->GpuName;

			for each (auto sensor in repository->MemorySensors) {
				auto item = gcnew ListViewItem();
				item->Text = sensor->Name;
				item->SubItems->Add("" + sensor->Value.GetValueOrDefault());
				memoryList->Items->Add(item);
			}

			int totalRam;
			int speed;
			for each (auto sensor in mb->SMBios->MemoryDevices) {
				totalRam += sensor->Size;
				speed = sensor->Speed;
			}

			totalRamLabel->Text = L"Загалом пам'яті: " + totalRam / 1024 + "GB";
			ramSpeedLabel->Text = L"Частота: " + speed + "MHz";

			auto bios = repository->Bios->Bios;
			moboLabel->Text = mb->Name;
			biosLabel->Text = bios->Vendor + ' ' + bios->Version;
			osLabel->Text = mb->SMBios->SystemEnclosure->SerialNumber;

			updateThermals();

			statUpdater->RunWorkerAsync();
		}

		private: System::Void statUpdater_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
			do {
				updateCpuLoad();
				updateThreadsTable();
				updateThermals();
				System::Threading::Thread::Sleep(1000);
			} while (true);
		}
	};
}
