#include <iostream>
#include <string>
#include <vector>

#include <windows.h>



struct Display {
    std::wstring name;
    int width;
    int height;
    int x;
    int y;
    bool isPrimary;
};

BOOL CALLBACK MonitorCallback(
    HMONITOR monitor,
    HDC deviceContext,
    LPRECT rectangle,
    LPARAM data
)
{
    auto* displays = reinterpret_cast<std::vector<Display>*>(data);

    MONITORINFOEXW info{};

    info.cbSize = sizeof(MONITORINFOEXW);

    if (!GetMonitorInfoW(monitor, &info)) {
        return TRUE;
    }

    Display display;

    display.name = info.szDevice;

    display.width = info.rcMonitor.right - info.rcMonitor.left;
    display.height = info.rcMonitor.bottom - info.rcMonitor.top;

    display.x = info.rcMonitor.left;
    display.y = info.rcMonitor.top;

    display.isPrimary = (info.dwFlags & MONITORINFOF_PRIMARY) != 0;

    displays->push_back(display);

    return TRUE;
}

int main() {

    std::vector<Display> displays;

    std::wcout << "Lumaire\n";
    std::wcout << "..........\n\n";

    // std::cout << "Windows displaay detection is ready.\n";
    EnumDisplayMonitors(
        nullptr,
        nullptr,
        MonitorCallback,
        reinterpret_cast<LPARAM>(&displays)
    );

    // std::wcout << L"Detected displays: "
    //           << displays.size() << L"\n\n";
    for (const Display& display : displays)
    {
        std::wcout << L"Monitor: "
                << display.name << L"\n";

        std::wcout << L"Resolution: "
                << display.width << L" x "
                << display.height << L"\n";

        std::wcout << L"Position: "
                << display.x << L", "
                << display.y << L"\n";

        std::wcout << L"Primary: "
                << (display.isPrimary ? L"YES" : L"NO")
                << L"\n\n";
    }

    return 0;
}