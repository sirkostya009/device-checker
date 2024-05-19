#pragma once

#using "LibreHardwareMonitorLib.dll"

namespace hw = LibreHardwareMonitor::Hardware;
namespace sw = LibreHardwareMonitor::Software;

ref class HardwareRepository {
private:
	hw::Computer computer{};
	hw::Cpu::GenericCpu^ cpu;
	hw::Gpu::GenericGpu^ gpu;
	hw::IHardware^ memory;
	hw::Motherboard::Motherboard^ motherboard;
	hw::Storage::AbstractStorage^ storage;
	hw::ISensor^ cpuLoadSensor;
	array<hw::ISensor^>^ cpuCoreLoadSensors;

	sw::OperatingSystem^ os;

public:
	HardwareRepository() {
		computer.IsCpuEnabled = true;
		computer.IsGpuEnabled = true;
		computer.IsMemoryEnabled = true;
		computer.IsMotherboardEnabled = true;
		computer.IsStorageEnabled = true;
		computer.Open();

		motherboard = cli::safe_cast<hw::Motherboard::Motherboard^>(computer.Hardware[0]);
		cpu = cli::safe_cast<hw::Cpu::GenericCpu^>(computer.Hardware[1]);
		memory = computer.Hardware[2];
		gpu = cli::safe_cast<hw::Gpu::GenericGpu^>(computer.Hardware[3]);
		cpuCoreLoadSensors = gcnew array<hw::ISensor^>(cpu->CpuId->Length);

		for each (auto hardware in computer.Hardware) {
			if (hardware->HardwareType == hw::HardwareType::Storage) {
				storage = cli::safe_cast<hw::Storage::AbstractStorage^>(hardware);
				break;
			}
		}

		int i = 0;
		for each (auto sensor in cpu->Sensors) {
			if (sensor->SensorType == hw::SensorType::Load && !sensor->Name->Contains("Core")) {
				cpuLoadSensor = sensor;
				break;
			} else if (sensor->SensorType == hw::SensorType::Load && sensor->Name->Contains("Core")) {
				cpuCoreLoadSensors[i++] = sensor;
			}
		}
	}

	property array<hw::ISensor^>^ CpuCoreSensors {
		array<hw::ISensor^>^ get() {
			return cpuCoreLoadSensors;
		}
	}

	property float CpuLoad {
		float get() {
			cpu->Update();
			return cpuLoadSensor->Value.GetValueOrDefault();
		}
	}

	property System::String^ CpuName {
		System::String^ get() {
			return cpu->Name;
		}
	}

	property System::String^ GpuName {
		System::String^ get() {
			return gpu->Name;
		}
	}

	property int CpuCoreCount {
		int get() {
			return cpu->CpuId->Length;
		}
	}

	property array<hw::ISensor^>^ MemorySensors {
		array<hw::ISensor^>^ get() {
			memory->Update();
			return memory->Sensors;
		}
	}

	property array<hw::ISensor^>^ ThermoSensors {
		array<hw::ISensor^>^ get() {
			cpu->Update();
			gpu->Update();
			auto result = gcnew array<hw::ISensor^>(cpu->Sensors->Length + gpu->Sensors->Length);
			for each (auto sensor in cpu->Sensors) {
				if (sensor->SensorType == hw::SensorType::Temperature) {
					result->SetValue(sensor, sensor->Index);
				}
			}
			for each (auto sensor in gpu->Sensors) {
				if (sensor->SensorType == hw::SensorType::Temperature) {
					result->SetValue(sensor, sensor->Index + cpu->Sensors->Length);
				}
			}
			return result;
		}
	}

	property hw::Motherboard::Motherboard^ Motherboard {
		hw::Motherboard::Motherboard^ get() {
			return motherboard;
		}
	}

	property hw::SMBios^ Bios {
		hw::SMBios^ get() {
			return computer.SMBios;
		}
	}

	~HardwareRepository() {
		computer.Close();
	}
};
