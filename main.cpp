#include "HDMConfigWindow.h"
#include "MainWindow.h"
#include "SDKSettings.h"
#include "xml.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // std::wstring path(L"C:\\Users\\MRV\\Desktop\\test.ini");
    //SDKSettings sdk(path);
    //sdk.show();
    MainWindow main_window;
    main_window.show();
    return a.exec();
}
