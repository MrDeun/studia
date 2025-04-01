// startEnableDisable.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <iostream>
#include <Windows.h>
#include <minwindef.h>
#include <string>
#include <synchapi.h>
#include <windef.h>
#include <winnls.h>
#include <winuser.h>
using namespace std;

HWND GetHandle(HWND parent, wstring class_name) {
    HWND hwnd = 0;
    hwnd = FindWindowExW(parent, NULL, class_name.c_str(), NULL);
    if (hwnd == 0) {
        printf("Handle of class %ls not found!\n", class_name.c_str());
    }
    else {
        printf("Found %ls handle at %x\n", class_name.c_str(), hwnd);
    }
    return hwnd;
}

void SendText(HWND dlg, const wchar_t* wstr, int wstr_size = 1024) {
    for (int i = 0;i < wstr_size;i++) {
        SendMessageW(dlg, WM_CHAR, wstr[i], NULL);
    }
}

int main()
{

    char txt[64];
    wchar_t wtxt[1024];
    wstring s;

    //    system("pause");


    HWND start = 0;
    HWND edit = 0;
    start = FindWindowW(NULL, L"Untitled - Notepad");

    if (start == NULL)
    {
        cout << "Notepad not found\n";
        //return 0;
    }
    cout << "Window handle: " << hex << start << endl;

    int n;
    while (1) {
        cout << "********************************************" << endl
            << "* options:" << endl
            << "* 1. end" << endl
            << "* 2. Find notepad using name" << endl
            << "* 3. Find notepad using class" << endl
            << "* 4. Hide notepad" << endl
            << "* 5. Show notepad" << endl
            << "* 6. Hide notepad window" << endl
            << "* 7. Show notepad window" << endl
            << "* 8. Send text to notepad" << endl
            << "* 9. Save" << endl
            << "* 10. Save As..." << endl
            << "********************************************" << endl
            << "selection: ";
        cin >> n;
        cin.getline(txt, 64);

        //cout << endl << endl << "wprowadz:";
        //cin.getline(txt, 64);
        //cout << txt << endl;


        switch (n)
        {
        case 0:
        case 1:
            return 0;

        case 2:
        {
            cout << "enter name: ";
            wcin.getline(wtxt, 64);
            wcout << wtxt << endl;
            //1 � Notatnik
            //1 - Notatnik
            start = FindWindowW(NULL, wtxt);
            //start = FindWindow(NULL, L"1 � Notatnik");
            cout << (start ? "sukcess!" : "failure") << endl;
            break;
        }
        case 3:
            start = FindWindowExW(NULL, NULL, L"Notepad", NULL);
            cout << (start ? "sukcess!" : "failure") << endl;
            edit = FindWindowExW(start, NULL, L"Edit", NULL);
            cout << (edit ? "sukcess!" : "failure") << endl;
            cout << "Window handle: " << hex << start << endl;
            cout << "Edit handle: " << hex << edit << endl;

            break;

        case 4:
            ShowWindow(edit, SW_HIDE);
            break;

        case 5:
            ShowWindow(edit, SW_SHOW);
            break;

        case 6:
            ShowWindow(start, SW_HIDE);
            break;

        case 7:
            ShowWindow(start, SW_SHOW);
            break;

        case 8:
            if (!edit)
                break;
            cout << "enter text: ";
            wcin.getline(wtxt, 1024);
            //SetWindowText(edit, wtxt);
            SendMessageW(edit, WM_SETTEXT, 0, (LPARAM)wtxt);
        case 9:
            SendMessageW(start, WM_COMMAND, 3, 0);
            break;
        case 10:
            PostMessageW(start, WM_COMMAND, 4, 0);
            Sleep(1000);

            HWND savedlg;
            HWND DUIView, DirectUI, FloatSink, ComboBox, Edit;
            savedlg = FindWindowW(NULL, L"Save As");
            if (savedlg) {
                DUIView = GetHandle(savedlg, L"DUIViewWndClassName");
                if (DUIView) {
                    DirectUI = GetHandle(DUIView, L"DirectUIHWND");
                    if (DirectUI) {
                        FloatSink = GetHandle(DirectUI, L"FloatNotifySink");
                        if (FloatSink) {
                            ComboBox = GetHandle(FloatSink, L"ComboBox");
                            if (ComboBox) {
                                Edit = GetHandle(ComboBox, L"Edit");
                                wstring full_path = L"";
                                cout << "Enter path where the file will be saved (need to be ended with '\\'): ";
                                wcin.getline(wtxt, 1024);
                                full_path.append(wtxt);
                                cout << "Enter a name of your file: ";
                                wcin.getline(wtxt, 1024);
                                full_path.append(wtxt);
                                wcout << full_path;
                                SendMessageW(Edit, WM_SETTEXT, 0, (LPARAM)full_path.c_str());
                                SendMessageW(savedlg, WM_COMMAND, IDOK, NULL);
                            }
                        }
                    }
                }
            }
            break;
        }
    }

    ShowWindow(start, SW_HIDE);
    system("pause");
    ShowWindow(start, SW_SHOW);
    system("pause");
    return 0;
}

//cin.getline(txt, 64);

