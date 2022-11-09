#include <windows.h>
#include <tchar.h>
#include <ctime>
#include "resource.h"
using namespace std;

HWND hBut[9];
HBITMAP hBtm[2];

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
    srand(time(0));
    switch (message)
    {
    case WM_INITDIALOG:
    {
        for (int i = 0; i < 9; i++)
        {
            hBut[i] = GetDlgItem(hWnd, IDC_BUTTON1 + i);   //кнопки
        }
        hBtm[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));  //нолик
        hBtm[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));  //крестик
        return TRUE;
    }
    case WM_COMMAND:
    {
        for (int i = 0; i < 9; i++)
        {
            if (wp == IDC_BUTTON1 + i)
            {
                SendMessage(hBut[i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBtm[1]));  //устанавливаем картинку на нажатую кнопку
                EnableWindow(hBut[i], FALSE);

                while (1)
                {
                    int r = rand() % 9;
                    if (IsWindowEnabled(hBut[r]) == TRUE)
                    {
                        SendMessage(hBut[r], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBtm[0]));  //устанавливаем картинку на другую кнопку
                        EnableWindow(hBut[r], FALSE);
                        break;
                    }
                }                
                break;
            }            
        }
        if (wp == IDC_BUTTON10)  //если нажата кнопка "новая игра"
        {
            for (int i = 0; i < 9; i++)
            {
                SendMessage(hBut[i], BM_SETIMAGE, NULL, LPARAM(NULL));  //убираем все картинки
                EnableWindow(hBut[i], TRUE);                            //даём доступ для нажатия на кнокпи
            }
        }
        return TRUE;
    }
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}