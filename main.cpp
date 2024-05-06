#include <AppCore/AppCore.h>
#include <iostream>
#include "hwinfo/hwinfo.h"
#include <shobjidl.h>
#include <fstream>

#pragma comment(lib, "wbemuuid.lib")

auto GetCpuTemperature(LPLONG pTemperature) -> HRESULT {
    if (pTemperature == NULL)
        return E_INVALIDARG;

    *pTemperature = -1;
    HRESULT ci = CoInitialize(NULL);
    HRESULT hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
    if (SUCCEEDED(hr)) {
        IWbemLocator *pLocator;
        hr = CoCreateInstance(CLSID_WbemAdministrativeLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
        if (SUCCEEDED(hr)) {
            IWbemServices *pServices;
            BSTR ns = SysAllocString(L"root\\WMI");
            hr = pLocator->ConnectServer(ns, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
            pLocator->Release();
            SysFreeString(ns);
            if (SUCCEEDED(hr)) {
                BSTR query = SysAllocString(L"SELECT * FROM MSAcpi_ThermalZoneTemperature");
                BSTR wql = SysAllocString(L"WQL");
                IEnumWbemClassObject *pEnum;
                hr = pServices->ExecQuery(wql, query, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
                SysFreeString(wql);
                SysFreeString(query);
                pServices->Release();
                if (SUCCEEDED(hr)) {
                    IWbemClassObject *pObject;
                    ULONG returned;
                    hr = pEnum->Next(WBEM_INFINITE, 1, &pObject, &returned);
                    pEnum->Release();
                    if (SUCCEEDED(hr)) {
                        BSTR temp = SysAllocString(L"CurrentTemperature");
                        VARIANT v;
                        VariantInit(&v);
                        hr = pObject->Get(temp, 0, &v, NULL, NULL);
                        pObject->Release();
                        SysFreeString(temp);
                        if (SUCCEEDED(hr)) {
                            *pTemperature = V_I4(&v);
                        }
                        VariantClear(&v);
                    }
                }
            }
            if (ci == S_OK) {
                CoUninitialize();
            }
        }
    }
    return hr;
}

namespace ul = ultralight;

class Info : public ul::WindowListener, public ul::LoadListener, public ul::ViewListener {
    ul::RefPtr<ul::Window> window;
    ul::RefPtr<ul::Overlay> overlay;

    std::function<void()> onClose;
public:
    Info(ul::Monitor* monitor, std::function<void()> onClose)
    : window{ ul::Window::Create(monitor, 640, 560, false, ul::kWindowFlags_Titled) }
    , overlay{ ul::Overlay::Create(window, 1, 1, 0, 0) }
    , onClose{ std::move(onClose) }
    {
        window->set_listener(this);
        overlay->view()->set_load_listener(this);
        overlay->view()->set_view_listener(this);

        window->MoveToCenter();
        overlay->Resize(window->width(), window->height());
#include "resources/info.inl"
        overlay->view()->LoadHTML((char*)rawData);
        overlay->Focus();
    }

    void OnResize(ul::Window *, uint32_t width_px, uint32_t height_px) override {
        overlay->Resize(width_px, height_px);
    }

    void OnDOMReady(ul::View *caller, uint64_t frame_id, bool is_main_frame, const ul::String &url) override {
        auto ctx = caller->LockJSContext();
        ul::SetJSContext(ctx->ctx());
        auto global = ul::JSGlobalObject();

        global["closeInfo"] = ul::JSCallback([this](const ul::JSObject&, const ul::JSArgs&) {
            OnClose(window.get());
        });
    }

    void OnChangeTitle(ul::View *caller, const ul::String &title) override {
        window->SetTitle(title.utf8().data());
    }

    void OnClose(ul::Window *w) override {
        w->Close();
        onClose();
    }

    bool OnKeyEvent(const ul::KeyEvent &evt) override {
        switch (evt.virtual_key_code) {
            case 27: // Escape
                OnClose(window.get());
                break;
        }
        return true;
    }
};

class App : public ul::AppListener, public ul::WindowListener, public ul::LoadListener, public ul::ViewListener {
    ul::RefPtr<ul::App> app;
    ul::RefPtr<ul::Window> window;
    ul::RefPtr<ul::Overlay> overlay;

    Info* info_ptr{};
    bool inf = false;
public:
    App()
    : app{ ul::App::Create() }
    , window{ ul::Window::Create(app->main_monitor(), 800, 600, false, ul::kWindowFlags_Resizable | ul::kWindowFlags_Maximizable) }
    , overlay{ ul::Overlay::Create(window, 1, 1, 0, 0) }
    {
        app->set_listener(this);
        window->set_listener(this);
        overlay->view()->set_load_listener(this);
        overlay->view()->set_view_listener(this);

        window->MoveToCenter();
        overlay->Resize(window->width(), window->height());
#include "resources/app.inl"
        overlay->view()->LoadHTML((char*)rawData);
        overlay->Focus();
    }

    inline void run() {
        app->Run();
    }

    void OnUpdate() override {
        if (inf) {
            delete info_ptr;
            inf = false;
        }
    }

    void OnClose(ul::Window*) override {
        std::exit(0);
    }

    void OnResize(ul::Window*, uint32_t width, uint32_t height) override {
        overlay->Resize(width, height);
    }

    inline void set(const std::string& property, const std::string& value) {
        ul::JSEval((property + ".innerText = '" + value + "';").c_str());
    }

    void OnDOMReady(ul::View *caller, uint64_t frame_id, bool is_main_frame, const ul::String &url) override {
        using ul::JSCallback, ul::JSCallbackWithRetval;
        ul::SetJSContext(caller->LockJSContext()->ctx());
        auto global = ul::JSGlobalObject();

        global["getCpuTemp"] = JSCallbackWithRetval([](const ul::JSObject&, const ul::JSArgs&) -> ul::JSValue {
            long temp;
            GetCpuTemperature(&temp);
            return (double)temp / 10 - 273.15;
        });
        global["openInfo"] = BindJSCallback(&App::openInfo);
        global["downloadInfo"] = BindJSCallback(&App::downloadInfo);
        global["exit"] = JSCallback([](const ul::JSObject&, const ul::JSArgs&) { std::exit(0); });

        auto cpu = hwinfo::getAllCPUs()[0];

        set("cpucores", std::to_string(cpu.numPhysicalCores()));
        set("cputhreads", std::to_string(cpu.numLogicalCores()));
        set("cpuspeed", std::to_string(cpu.regularClockSpeed_MHz()) + " MHz");
        set("cpucache", std::to_string(cpu.L2CacheSize_Bytes() / 1024) + " KB");
        set("cpumanufacturer", cpu.vendor());
        set("cpuname", cpu.modelName());

        auto memory = hwinfo::Memory();
        set("ramamount", std::to_string(memory.total_Bytes() / 1024.0 / 1024.0));
        auto moduleCallback = global["addMemoryModule"].ToFunction();
        for (int i = 0; i < memory.modules().size(); i++) {
            auto module = memory.modules()[i];
            moduleCallback({
                module.total_Bytes / 1024.0 / 1024.0,
                module.vendor.c_str(),
                module.name.c_str(),
                module.frequency_Hz,
                module.model.c_str(),
                module.serial_number.c_str(),
                i
            });
        }

        auto disks = hwinfo::getAllDisks();
        auto diskCallback = global["addDisk"].ToFunction();
        for (int i = 0; i < disks.size(); i++) {
            auto disk = disks[i];
            diskCallback({
                disk.model().c_str(),
                disk.serialNumber().c_str(),
                disk.size_Bytes() / 1024.0 / 1024.0 / 1024.0,
                disk.vendor().c_str(),
                i
            });
        }
    }

    void OnChangeCursor(ul::View *caller, ul::Cursor cursor) override {
        window->SetCursor(cursor);
    }

    void OnChangeTitle(ul::View *caller, const ul::String &title) override {
        window->SetTitle(title.utf8().data());
    }

    void OnAddConsoleMessage(ul::View*, ul::MessageSource, ul::MessageLevel, const ul::String &message,
                             uint32_t line_number, uint32_t column_number, const ul::String &) override {
        std::cout << "Console: " << message.utf8().data() << " at line: " << line_number << ", column: " << column_number << std::endl;
    }

    void openInfo(const ul::JSObject&, const ul::JSArgs&) {
        info_ptr = new Info(app->main_monitor(), [this] { inf = true; });
    }

    void downloadInfo(const ul::JSObject&, const ul::JSArgs& args) {
        CoInitialize(nullptr);
        IFileSaveDialog* dialog;
        auto hr = CoCreateInstance(
                CLSID_FileSaveDialog,
                nullptr,
                CLSCTX_ALL,
                IID_IFileSaveDialog,
                reinterpret_cast<LPVOID*>(&dialog)
        );
        if (FAILED(hr)) {
            return;
        }

        auto handle = (HWND) window->native_handle();

        auto filterSpec = COMDLG_FILTERSPEC{L"All Files", L"*.*"};
        dialog->SetFileTypes(1, &filterSpec);

        hr = dialog->Show(handle);
        if (FAILED(hr)) {
            goto dialog_release;
        }

        IShellItem* item;
        hr = dialog->GetResult(&item);
        if (FAILED(hr)) {
            goto dialog_release;
        }

        LPWSTR filePath;
        hr = item->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
        if (FAILED(hr)) {
            goto item_release;
        }

        std::ofstream(filePath) << ((ul::String) args[0]).utf8().data();

        CoTaskMemFree(filePath);

        item_release:
        item->Release();

        dialog_release:
        dialog->Release();
    }
};

auto main() -> int {
    CoInitialize(nullptr);
    App().run();
}
