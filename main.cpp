/*
  Autor: Fran Espino Mostacero.

  Email:fran_espino189@outlook.com

  Programa sencillo para convertir un numero entero a binario,
  incluyendo el manejo de interfaces graficas con la api Window32.

  10/09/2019

*/



#include <windows.h>
#include <iostream>
#include <stdlib.h>
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define AYUDA_PES 5
#define GENERAR_EDAD 4

using namespace std;

void AddMenus(HWND);
void AddControls(HWND);
void LoadImage();
char enteroAbinario(int);
char numeroBinario[20];
int i = 0;

 HWND hNombre,hAnio, hOutput,hlogito;
 HMENU hMenu;
 HBITMAP hlogoBinario, hgenerar;

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);//prototipo de la funcion

//en vez del int main usaremos este:
int WINAPI WinMain(HINSTANCE hIns,HINSTANCE hPrevInst,LPSTR args, int ncmdshow){

   // MessageBox(NULL,"Hola mundo","Da un click",MB_OK);
    WNDCLASSW wc = {0};

    wc.hbrBackground =(HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hIns;
    wc.lpszClassName = L"myWindowsClass";
    wc.lpfnWndProc= WindowProcedure;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+22);
    if(!RegisterClassW(&wc)){

        return -1;
    }


    CreateWindowW(L"myWindowsClass",L"Proyecto UNT",WS_OVERLAPPEDWINDOW | WS_VISIBLE ,100,100,500,500,
                  NULL,NULL,NULL,NULL);
    MSG msg = {0};
    while( GetMessage(&msg,NULL,NULL,NULL) ){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp ,LPARAM lp){
    switch (msg)
    {
    case WM_COMMAND:
        switch (wp)
        {

            case FILE_MENU_EXIT:
                DestroyWindow(hWnd);
                break;
            case AYUDA_PES:
                MessageBox(NULL,"\nEste programa nos ayudara a las conversiones de sistemas binarios, octales, hexadecimales, puedes ingresar un numero y presionando en generar te saldra el resultado.","ASISTENTE DE AYUDA",
                MB_ICONINFORMATION);
                break;

            case GENERAR_EDAD:
                char edad[10];
                GetWindowText(hAnio,edad,10);
                int nmr = atoi(edad);
                enteroAbinario(nmr);
                itoa(nmr,edad,10);
                LPCTSTR salida = (LPCTSTR)edad;
                SetWindowText(hOutput,salida);
                break;


        }
        break;

    case WM_CREATE:
        LoadImage();
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd,msg,wp,lp);

    }
}

void AddMenus(HWND hWnd){

    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hFileMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hFileMenu,MF_STRING,FILE_MENU_EXIT,"Salir");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenu,"Archivo");
    AppendMenu(hMenu,MF_STRING,AYUDA_PES,"Ayuda");
    SetMenu(hWnd,hMenu);
}

void AddControls(HWND hWnd){


    CreateWindowW(L"Static",L"CONVERSION DE NUMEROS ENTEROS A BINARIOS\n",WS_VISIBLE | WS_CHILD  | WS_BORDER, 0,0,500,40,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Ingrese un numero: ",WS_VISIBLE | WS_CHILD  | WS_BORDER, 80,60,150,25,hWnd,NULL,NULL,NULL);
    hAnio = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 250,60,100,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"Generar",WS_VISIBLE | WS_CHILD | WS_BORDER, 170,100,100,38,hWnd,(HMENU)GENERAR_EDAD,NULL,NULL);
    hOutput = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER, 80,150,270,40,hWnd,NULL,NULL,NULL);
    hlogito = CreateWindowW(L"Static",NULL,WS_VISIBLE | WS_CHILD | WS_BORDER | SS_BITMAP, 15,250,20,40,hWnd,NULL,NULL,NULL);
    SendMessageW(hlogito,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM) hlogoBinario);
}

void LoadImage(){
   hlogoBinario= (HBITMAP)LoadImageW(NULL,L"binaaa.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
}

char enteroAbinario(int numero){
if(numero==0){
    return numero;
}
if(numero>1){
enteroAbinario(numero/2);
}
cout<< numero%2;
}






