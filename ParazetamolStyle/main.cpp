#pragma once
#include "main.h"

using namespace std;



#include "ImGui/imgui_internal.h"

#include "ImGui/Fonts/icons.h"
#include "ImGui/Fonts/font.h"

#include <stdio.h>
#include "stb_image.h"
#include <string>
#include <iostream>
#include <fstream>  
#include "TextEditor.h"
#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <random>
#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <d3d9.h>
#include <tchar.h>

#include <strsafe.h>
#pragma comment(lib, "urlmon.lib")
#define UNLEN 64

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
using namespace std;

// connect username and password
char key[255] = ICON_FA_SEARCH" Key";

std::vector<const char*> FreeMenus = {
"KomazycaCheats",
"PajacerkaMenu",
"Lynx.10",
"Krasnolud_Skid",
"Absolute",
"Fallout",
"Synapse",
"Whipear",
"SugarMenu",
"Lynx_Enterprise"
};


#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")

struct ImDrawPaint
{
    ImVec4 Col0;
    ImVec4 Col1;
    ImVec2 Start;
    ImVec2 Extent;

    void SetLinearGradient(const ImVec2& start, const ImVec2& end, const ImVec4& col0, const ImVec4& col1)
    {
        Col0 = col0;
        Col1 = col1;
        Start = start;
        Extent.x = end.x - start.x;
        Extent.y = end.y - start.y;
    }
    ImU32 Calc(const ImVec2& pos) const;
};


static int selectedResource = NULL;
std::vector<const char*> resources = {
    "_cfx_internal","fivem","hardcap","anti-cheese","esx_mafia","esx_gopostal","esx_jail","mysql-async","es_admin2",
    "async","es_extended","esx_barbershop","esx_clotheshop","esx_datastore","esx_garage","esx_identity","esx_lscustom",
    "esx_menu_default","esx_menu_dialog","esx_menu_list","esx_property","esx_shops","esx_sit","esx_vehicleshop","esx_weashops",
    "es_camera","instance","skinchanger","mellotrainer","bob74_ipl","coordsaver","loadingscreen"
};

namespace komazyca
{

    void Line(int newId)
    {
        std::string id = ("imguipp_line_" + std::to_string(newId));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
        {
            ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
            ImGui::Separator();
            ImGui::EndChild();
        }
        ImGui::PopStyleColor();
    }

    void Linevertical()
    {
        ImGui::SameLine();
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::SameLine();
    }

    void CenterText(const char* text, int lineId, bool separator)
    {
        if (text == nullptr)
            return;

        ImGui::Spacing();
        ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
        ImGui::Text(text);
        ImGui::Spacing();

        if (true == separator)
            Line(lineId);
    }

    void CenterTextEx(const char* text, float width, int lineId, bool separator)
    {
        if (text == nullptr)
            return;

        ImGui::Spacing();
        ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
        ImGui::Text(text);
        ImGui::Spacing();

        if (true == separator)
            Line(lineId);
    }

    void DrawTextImGui(ImVec2 position, ImColor color, const char* format, ...)
    {
        if (format == nullptr)
            return;

        char buffer[512];

        va_list  args;
        va_start(args, format);
        vsnprintf_s(buffer, sizeof(buffer), format, args);
        va_end(args);

        ImGui::GetBackgroundDrawList()->AddText(position, color, format, buffer);
    }

    void DrawCircle(ImVec2 windowSize, ImColor color, float radius, float thickness = 1)
    {
        ImGui::GetBackgroundDrawList()->AddCircle(windowSize, radius, color, 100, thickness);
    }

    float GetX()
    {
        return ImGui::GetContentRegionAvail().x;
    }

    float GetY()
    {
        return ImGui::GetContentRegionAvail().y;
    }



    void LoadingIndicatorCircle(const char* label, const float indicator_radius,
        const ImVec4& main_color, const ImVec4& backdrop_color,
        const int circle_count, const float speed) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems) {
            return;
        }

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        const ImVec2 pos = window->DC.CursorPos;
        const float circle_radius = indicator_radius / 10.0f;
        const ImRect bb(pos, ImVec2(pos.x + indicator_radius * 2.0f,
            pos.y + indicator_radius * 2.0f));
        ImGui::ItemSize(bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id)) {
            return;
        }
        const float t = g.Time;
        const auto degree_offset = 2.0f * IM_PI / circle_count;
        for (int i = 0; i < circle_count; ++i) {
            const auto x = indicator_radius * std::sin(degree_offset * i);
            const auto y = indicator_radius * std::cos(degree_offset * i);
            const auto growth = max(0.0f, std::sin(t * speed - i * degree_offset));
            ImVec4 color;
            color.x = main_color.x * growth + backdrop_color.x * (1.0f - growth);
            color.y = main_color.y * growth + backdrop_color.y * (1.0f - growth);
            color.z = main_color.z * growth + backdrop_color.z * (1.0f - growth);
            color.w = 1.0f;
            window->DrawList->AddCircleFilled(ImVec2(pos.x + indicator_radius + x,
                pos.y + indicator_radius - y),
                circle_radius + growth * circle_radius,
                ImGui::GetColorU32(color));
        }
    }

    bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ImGui::ItemSize(bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        // Render
        window->DrawList->PathClear();

        int num_segments = 30;
        int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

        const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
        const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

        const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

        for (int i = 0; i < num_segments; i++) {
            const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
            window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
                centre.y + ImSin(a + g.Time * 8) * radius));
        }

        window->DrawList->PathStroke(color, false, thickness);
    }

}


// Simple helper function to load an image into a DX9 texture with common settings

bool GetProcessEntryByName(string name, PROCESSENTRY32* pe) {
    auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        cerr << "Tool helper cannot be created" << endl;
        return false;
    }

    if (!Process32First(snapshot, pe)) {
        cerr << "Tool helper cannot retrieve the first entry of process list" << endl;
        return false;
    }

    do {
        if (pe->szExeFile == name) {
            snapshot ? CloseHandle(snapshot) : 0;
            return true;
        }
    } while (Process32Next(snapshot, pe));

    snapshot ? CloseHandle(snapshot) : 0;
    return false;
}



std::string random_stringExec()
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

using std::cout;
using std::endl;



void sukabl(const std::string random_stringExec)
{
    std::string buffer;

}

void MenuStyle()
{
    ImGui::GetMouseCursor();
    ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);



    auto& style = ImGui::GetStyle();
    style.WindowMinSize = ImVec2(875, 600);

    style.TabRounding = 10;
    style.ScrollbarRounding = 0;
    style.ChildRounding = 6;
    style.WindowRounding = 7;
    style.FramePadding = ImVec2(8, 6);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);



    style.Colors[ImGuiCol_WindowBg] = ImColor(18, 17, 19);

    style.Colors[ImGuiCol_TitleBg] = ImColor(255, 237, 0);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 237, 0);
    style.Colors[ImGuiCol_TitleBgActive] = ImColor(255, 237, 0);



    style.Colors[ImGuiCol_Separator] = ImColor(36, 171, 223);

    style.Colors[ImGuiCol_ButtonHovered] = ImColor(24, 24, 24);
    style.Colors[ImGuiCol_ButtonActive] = ImColor(30, 29, 30);
    style.Colors[ImGuiCol_Button] = ImColor(15, 15, 15);

    style.Colors[ImGuiCol_Border] = ImColor(25, 24, 26);

    style.Colors[ImGuiCol_Header] = ImColor(22, 22, 22);
    style.Colors[ImGuiCol_ChildBg] = ImColor(31, 30, 31);

    style.Colors[ImGuiCol_CheckMark] = ImColor(129, 113, 217);

    style.Colors[ImGuiCol_HeaderActive] = ImColor(105, 105, 105);
    style.Colors[ImGuiCol_HeaderHovered] = ImColor(105, 105, 105);
    style.Colors[ImGuiCol_FrameBg] = ImColor(22, 22, 22);
    style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200);
    style.Colors[ImGuiCol_FrameBgActive] = ImColor(22, 22, 22);
    style.Colors[ImGuiCol_FrameBgHovered] = ImColor(22, 22, 22);

    style.Colors[ImGuiCol_SliderGrab] = ImColor(50, 50, 50);
    style.Colors[ImGuiCol_SliderGrabActive] = ImColor(55, 55, 55);
}

#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")

// Simple helper function to load an image into a DX9 texture with common settings
bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
    // Load texture from disk
    PDIRECT3DTEXTURE9 texture;
    HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filename, &texture);
    if (hr != S_OK)
        return false;

    // Retrieve description of the texture surface so we can access its size
    D3DSURFACE_DESC my_image_desc;
    texture->GetLevelDesc(0, &my_image_desc);
    *out_texture = texture;
    *out_width = (int)my_image_desc.Width;
    *out_height = (int)my_image_desc.Height;
    return true;
}


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // create windows
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, LOADER_BRAND, NULL };
    RegisterClassEx(&wc);
    main_hwnd = CreateWindow(wc.lpszClassName, LOADER_BRAND, WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);


    if (!CreateDeviceD3D(main_hwnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(main_hwnd, SW_HIDE);
    UpdateWindow(main_hwnd);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr; 
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 

    ImGui::StyleColorsDark();

    ShowWindow(main_hwnd, SW_HIDE);
    UpdateWindow(main_hwnd);

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        


        



        ImGui_ImplWin32_Init(main_hwnd);
        ImGui_ImplDX9_Init(g_pd3dDevice);
        ImGui::CreateContext();
    }



    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;

    ImFontConfig CustomFont;
    CustomFont.FontDataOwnedByAtlas = false;



    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Bahnschrift.ttf", 22);
    io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 21.0f, &icons_config, icons_ranges);
    io.Fonts->AddFontDefault();
    ImFont* font1 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Bahnschrift.ttf", 30);
    ImFont* font2 = io.Fonts->AddFontFromFileTTF("C:\\font\\d\\futur.ttf", 35);


    int my_image_width = 0;
    int my_image_height = 0;
    PDIRECT3DTEXTURE9 my_texture = NULL;
    bool Result = LoadTextureFromFile("D:/rE.png", &my_texture, &my_image_width, &my_image_height);
    IM_ASSERT(Result);

    PDIRECT3DTEXTURE9 ELLOA = NULL;
    bool AAS = LoadTextureFromFile("D:/EDA.png", &ELLOA, &my_image_width, &my_image_height);
    IM_ASSERT(AAS);




    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto x = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
    auto y = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;



    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }


        static int item = 0; //Cael is the one and only.

        static char password[25];
        static char username[25];

        static int menu = 0; //Cael is the one and only.

        static int alfonso = 1; //Cael is the one and only.

        static bool showui = true;

        static int tab = 0;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        MenuStyle();

        auto& style = ImGui::GetStyle();

        auto size = ImGui::GetWindowSize();

        static bool dump = false;

        static bool dumpof = false;

        static char InputTextWithHintDemo[256] = "C:/CLOUDDUMPS/";

        static bool dumpload = false;

        static bool isolated = false;

        static bool blockac = false;

        static bool voip = false;

        static bool pass = false;

        static bool lua = false;

        static bool html = false;

        static bool meta = false;

        //                    static TextEditor		 editor;
        //editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
        //editor.SetShowWhitespaces(false);
        //editor.SetPalette(TextEditor::GetFakePalette());
        //editor.SetReadOnly(false);
        //editor.Render("TextEditor", ImVec2(685, 520), false);


        if (showui)
        {
            ImGui::Begin("##PARAZETAMOLREMAKE", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

            float wysokoaa_distance = 13;

            float szerokoaad_distance = 22;
            float szerokoaaddd_distance = -6;

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokoaa_distance);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaad_distance);
            ImGui::PushFont(font2);
            ImGui::Text("DarkPanel");
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaaddd_distance);
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(127, 91, 244, 255));
            ImGui::Text(".ml");
            ImGui::PopStyleColor();
            ImGui::PopFont();



            float szerokoda_distance = 385;
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoda_distance);
            ImGui::Button(ICON_FA_SHARE"", ImVec2(40,40));
            ImGui::SameLine();
            ImGui::Button(ICON_FA_COG"", ImVec2(40, 40));



            float szeroko_distance = 20;
            float wysoko_distance = 13;

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysoko_distance);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szeroko_distance);

            if (ImGui::Button(ICON_FA_CLOUD" Scripting", ImVec2(125,40))) {
                tab = 1;
            }
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_CROSSHAIRS" PVP", ImVec2(125, 40))) {
                tab = 2;
            }
            ImGui::SameLine();

            if (ImGui::Button(ICON_FA_MALE" Self", ImVec2(125, 40))) {
                tab = 3;
            }
            ImGui::SameLine();

            if (ImGui::Button(ICON_FA_COG" Misc", ImVec2(125, 40))) {
                tab = 4;
            }
            //780 x 755

            if (tab == 1) {
                float szerokodd_distance = 155;

                float wysookdd_distance = 10;


                ImGui::SameLine();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokodd_distance);
                ImGui::Button(ICON_FA_CODE" Lua", ImVec2(125, 40));


                float szerokodad_distance = 20;
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokodad_distance);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysookdd_distance);

                ImGui::BeginChild("##leftSide", ImVec2(814,444), true);

                float szerokooood_distance = 10;
                float wysokooood_distance = 5;
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokooood_distance);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokooood_distance);

                ImGui::PushFont(font1);
                ImGui::Text("Executor");
                ImGui::PopFont();

                float szerokoooo_distance = 7;
                float wysokoooo_distance = 3;
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooo_distance);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokoooo_distance);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(25, 24, 26, 255));
                ImGui::BeginChild("##CHUJ", ImVec2(780 , 345), true);
                ImGui::PopStyleColor();
                ImGui::EndChild();
                
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(40, 40, 40, 255));
                float szerokoooodd_distance = 7;
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodd_distance);
                ImGui::Button(" Run", ImVec2(385, 33));
                ImGui::SameLine();
                ImGui::Button(" Menu", ImVec2(385, 33));
                ImGui::PopStyleColor();






                ImGui::EndChild();

            
            }


            if (tab == 4)
            {
                float szerokoooodaad_distance = 50;
                float wysokowccda_distance = 75;

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokowccda_distance);

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaad_distance);

                ImGui::BeginChild("##HAdhashdad", ImVec2(500, 135), true);

                float szerokooooddaa_distance = 7;
                float wysokooooddaa_distance = 3;
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokooooddaa_distance);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokooooddaa_distance);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(25, 24, 26, 255));
                ImGui::BeginChild("##asdasjdiajsd", ImVec2(450, 115), true);

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokoaa_distance);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaad_distance);
                ImGui::PushFont(font1);
                ImGui::Text("DarkPanel");
                ImGui::SameLine();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaaddd_distance);
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(127, 91, 244, 255));
                ImGui::Text(".ml");
                ImGui::PopStyleColor();
                ImGui::PopFont();
                ImGui::SameLine();
                ImGui::Text(" Thanks For Choosing Us");

                ImGui::PopStyleColor();
                ImGui::EndChild();

                ImGui::EndChild();
            }

            if (tab == 2)
            {

                float wysokowcc_distance = 20;

                float szerokoddd_distance = 300;

                ImGui::SameLine();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + wysokowcc_distance);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoddd_distance);
                ImGui::Button(ICON_FA_MALE" ESP", ImVec2(125, 40));

                   static bool en = false;
                   static bool box = false;
                   static bool name = false;
                   static bool ske = false;
                   static bool health = false;
                   static bool snap = false;
                   static bool aim = false;
                   static bool inc = false;
                
                float szerokooooddda_distance = 30;

                float szerokooood_distance = 19;
                float wysokooood_distance = 7;
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokooood_distance);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokooood_distance);

                ImGui::BeginChild("##CHUJadasd", ImVec2(390, 430), true);

                float szerokoooodaa_distance = 15;

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);

                ImGui::PushFont(font1);
                ImGui::Text("ESP");
                ImGui::PopFont();

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);
                ImGui::Checkbox("Enabled", &en);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);
                ImGui::Checkbox("Box", &box);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);
                ImGui::Checkbox("Name", &name);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);
                ImGui::Checkbox("Skeleton", &ske);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);
                ImGui::Checkbox("Healthbar", &health);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);
                ImGui::Checkbox("Snaplines", &snap);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);
                ImGui::Checkbox("Aimbot", &aim);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);
                ImGui::Checkbox("Include Self", &inc);


                ImGui::EndChild();
                ////asd
                ImGui::SameLine();
                ///dd
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokooooddda_distance);
                ImGui::BeginChild("##CHUJadasddadasd", ImVec2(390, 430), true);

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoooodaa_distance);

                ImGui::PushFont(font1);
                ImGui::Text("Aimbot");
                ImGui::PopFont();

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();

                ImGui::EndChild();

            }
            ImGui::End();
        }

    

        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!loader_active) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(main_hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    return 0;
}

BOOL InjectDllLoadLibrary(const DWORD& processId, const std::string& dllName)
{
    if (!processId)
        return false;

    const HANDLE hProc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, processId);

    if (!hProc)
    {
        cout << "OpenProcess() failed: " << GetLastError() << endl;
        return false;
    }

    const LPVOID loadLibrary{ static_cast<LPVOID>(GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA")) };
    if (!loadLibrary)
    {
        cout << "GetProcAddress() failed: " << GetLastError() << endl;
        return false;
    }

    const LPVOID remoteStringAllocatedMem{ static_cast<LPVOID>(VirtualAllocEx(hProc, NULL, dllName.length(), MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE)) };
    if (!remoteStringAllocatedMem)
    {
        cout << "VirtualAllocEx() failed: " << GetLastError() << endl;
        return false;
    }

    if (!WriteProcessMemory(hProc, static_cast<LPVOID>(remoteStringAllocatedMem), dllName.c_str(), dllName.length(), NULL))
    {
        cout << "WriteProcessMemory() failed: " << GetLastError() << endl;
        return false;
    }

    const HANDLE hRemoteThread{ CreateRemoteThread(hProc, NULL, NULL, static_cast<LPTHREAD_START_ROUTINE>(loadLibrary), static_cast<LPVOID>(remoteStringAllocatedMem), NULL, NULL) };
    if (!hRemoteThread)
    {
        cout << "CreateRemoteThread() failed: " << GetLastError() << endl;
        return false;
    }

    CloseHandle(hProc);
    CloseHandle(hRemoteThread);

    return true;
}

DWORD GetTargetProcessIdFromProcessName(const std::string& procName)
{
    PROCESSENTRY32 pe;
    HANDLE thSnapshot;
    BOOL retval, ProcFound = false;

    thSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (thSnapshot == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, "Error: unable to create toolhelp snapshot", "Loader", NULL);
        return false;
    }

    pe.dwSize = sizeof(PROCESSENTRY32);

    retval = Process32First(thSnapshot, &pe);

    while (retval)
    {
        if (procName == pe.szExeFile)
        {
            ProcFound = true;
            break;
        }

        retval = Process32Next(thSnapshot, &pe);
        pe.dwSize = sizeof(PROCESSENTRY32);
    }

    return pe.th32ProcessID;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    return true;

    switch (msg)
    {
    case WM_SIZE:
    if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
    {
    g_d3dpp.BackBufferWidth = LOWORD(lParam);
    g_d3dpp.BackBufferHeight = HIWORD(lParam);
    ResetDevice();
    }
    return 0;
    case WM_SYSCOMMAND:
    if ((wParam & 0xfff0) == SC_KEYMENU)
    return 0;
    break;
    case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}