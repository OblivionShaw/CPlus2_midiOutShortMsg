// .cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
#include <iostream>
#include <Windows.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
enum Scale
{
    Rest = 0,
    A0 = 21, A0s = 22, B0 = 23,
    C1 = 24, C1s = 25, D1 = 26, D1s = 27, E1 = 28, F1 = 29, F1s = 30, G1 = 31, G1s = 32, A1 = 33, A1s = 34, B1 = 35,
    C2 = 36, C2s = 37, D2 = 38, D2s = 39, E2 = 40, F2 = 41, F2s = 42, G2 = 43, G2s = 44, A2 = 45, A2s = 46, B2 = 47,
    C3 = 48, C3s = 49, D3 = 50, D3s = 51, E3 = 52, F3 = 53, F3s = 54, G3 = 55, G3s = 56, A3 = 57, A3s = 58, B3 = 59,
    C4 = 60, C4s = 61, D4 = 62, D4s = 63, E4 = 64, F4 = 65, F4s = 66, G4 = 67, G4s = 68, A4 = 69, A4s = 70, B4 = 71,
    C5 = 72, C5s = 73, D5 = 74, D5s = 75, E5 = 76, F5 = 77, F5s = 78, G5 = 79, G5s = 80, A5 = 81, A5s = 82, B5 = 83,
    C6 = 84, C6s = 85, D6 = 86, D6s = 87, E6 = 88, F6 = 89, F6s = 90, G6 = 91, G6s = 92, A6 = 93, A6s = 94, B6 = 95,
    C7 = 96, C7s = 97, D7 = 98, D7s = 99, E7 = 100, F7 = 101, F7s = 102, G7 = 103, G7s = 104, A7 = 105, A7s = 106, B7 = 107,
    C8 = 108,  
};
enum Voice
{
    S1 = C2, S2 = D2, S3 = E2, S4 = F2, S5 = G2, S6 = A2, S7 = B2, //Subbass
    L1 = C3, L2 = D3, L3 = E3, L4 = F3, L5 = G3, L6 = A3, L7 = B3, //Low
    M1 = C4, M2 = D4, M3 = E4, M4 = F4, M5 = G4, M6 = A4, M7 = B4, //Middle
    H1 = C5, H2 = D5, H3 = E5, H4 = F5, H5 = G5, H6 = A5, H7 = B5, //High
    LOW_SPEED = 500, MIDDLE_SPEED = 400, HIGH_SPEED = 300,
    I = 0XF1, F = 0XF2, B = 0XF3
};

void OdeToJoy(int speed)
{

    HMIDIOUT handle;
    midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);
    int volume = 0x7f;
    int voice = 0x0;
    int interval = speed;
    int sheetmusic[] =
    {
        M3, M3, M4, M5,      M5, M4, M3, M2,      M1, M1, M2, M3,      M3, M2, M2, 175,
        M3, M3, M4, M5,      M5, M4, M3, M2,      M1, M1, M2, M3,      M2, M1, M1, 175,
        M2, M2, M3, M1,      M2,999175,M3,M4,M3,99975,999350,M1, M2,999175,M3, M4, M3,99975,999350,M2,      M1, M2, L5, 175,
        M3, M3, M4, M5,      M5, M4, M3, M2,      M1, M1, M2, M3,      M2, M1, M1,
    };

    for (auto i : sheetmusic)
    {
        if (i > 996) {
            int prefix = i / 1000;
            int suffix = i % 1000;
            if (prefix == 999)
            {
                // 處理999的情況
                // 使用suffix進行後續的處理
                printf("%d\n", suffix);
                interval = suffix;
                continue;
            }
            else if (prefix == 996)
            {
                // 處理996的情況
                // 使用suffix進行後續的處理
                printf("%d\n", suffix);
                Sleep(suffix);
                continue;
            }
        }
        if (i == I) { interval = speed; continue; }
        if (i == F) { Sleep(speed); continue; }

        voice = (volume << 16) + ((i) << 8) + 0x90;
        midiOutShortMsg(handle, voice);
        cout << voice << endl;
        Sleep(interval);
    }
    midiOutClose(handle);
}

void play()
{
    HMIDIOUT handle;
    midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);
    int volume = 0x7f;
    int voice = 0x0;

    char ch;
    while (1) {
        if (_kbhit()) { // 如果有鍵盤輸入
            ch = _getch(); // 獲取鍵盤輸入
            switch (ch) 
            {
            case '1': // 數字鍵1
                OdeToJoy(350);
                break;
            case '2': // 數字鍵2.
                return; // 強制中斷
            case 'a': // Do
                voice = (volume << 16) + (C4 << 8) + 0x90;
                break;
            case 's': // Re
                voice = (volume << 16) + (D4 << 8) + 0x90;
                break;
            case 'd': // Mi
                voice = (volume << 16) + (E4 << 8) + 0x90;
                break;
            case 'f': // Fa
                voice = (volume << 16) + (F4 << 8) + 0x90;
                break;
            case 'g': // Sol
                voice = (volume << 16) + (G4 << 8) + 0x90;
                break;
            case 'h': // La
                voice = (volume << 16) + (A4 << 8) + 0x90;
                break;
            case 'j': // Si
                voice = (volume << 16) + (B4 << 8) + 0x90;
                break;
            case 8: // BACKSPACE的ASCII值是8
                return;
            }
            midiOutShortMsg(handle, voice);
            cout << voice << endl;
        }
    }
}
int main()
{
    play();
    //OdeToJoy(350);
    //return 0;
}
// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
