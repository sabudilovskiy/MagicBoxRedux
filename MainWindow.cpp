#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "xml.h"
#include <string>
#include <sstream>
#include <codecvt>
#include <filesystem>
#include <fstream>
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
namespace fs = std::filesystem;

std::wstring utf_16_bom_to_utf_8(std::ifstream& file){
    std::stringstream ss;
    ss << file.rdbuf();
    std::wstring ws;
    ws.resize(ss.str().size() / sizeof (wchar_t ) - 1);
    std::memcpy(&ws[0], &ss.str()[2], ss.str().size() - 2);
    return ws;
}
void utf_8_to_utf_16_bom(const std::wstring& str, std::ofstream& file){
    wchar_t bom = -257;
    size_t wsize = sizeof(wchar_t);
    file.write((char*)(&bom), wsize);
    file.write((char*)str.c_str(), str.size() * wsize);
    file.close();
}
void MainWindow::install_mods(int db_id, int sdk_id)
{
    try{
    std::wstring path = this->path_game + L"\\MODS\\" + get_name_folder(db_id, sdk_id);
    std::wstring path_db = L"C:\\MagicBoxRedux\\mods\\db\\" + mods_db[db_id].get_id() + L"\\" + mods_db[db_id].get_version();
    std::wstring path_sdk = L"C:\\MagicBoxRedux\\mods\\sdk\\" + mods_sdk[sdk_id].get_id() + L"\\" + mods_sdk[sdk_id].get_version();
    fs::copy(path_db, path, fs::copy_options::overwrite_existing|fs::copy_options::recursive);
    fs::copy(path_sdk, path, fs::copy_options::overwrite_existing|fs::copy_options::recursive);
    }
    catch (const fs::filesystem_error& ex){
        QMessageBox message_box;
        message_box.critical(0, "Error", ex.what());
        message_box.setFixedSize(300, 200);
        return;
    }
}

bool MainWindow::exists_mods(int db_id, int sdk_id)
{
    std::wstring path = this->path_game + L"\\MODS\\" + get_name_folder(db_id, sdk_id);
    return fs::exists(path);
}

std::wstring MainWindow::get_name_folder(int db_id, int sdk_id)
{
    return mods_db[db_id].get_id() + L'_' + mods_db[db_id].get_version() + L'_' + mods_sdk[sdk_id].get_id() + L'_' + mods_sdk[sdk_id].get_version();
}

void MainWindow::update_mod(int db_id, int sdk_id)
{
    std::wstring name_folder = get_name_folder(db_id, sdk_id);
    std::wstring wpath(path_game + L"\\joshua.cfg");
    if (!std::filesystem::exists(wpath)){
        QMessageBox message_box;
        message_box.critical(0, "Не возможно открыть файл", "Файл не существует");
        message_box.setFixedSize(300, 200);
        return;
    }
    std::ifstream settings(wpath, std::ios::in|std::ios::binary);
    if (!settings.is_open()){
        QMessageBox message_box;
        message_box.critical(0, "Не возможно открыть файл", "Недостаточно прав");
        message_box.setFixedSize(300, 200);
        return;
    }
    std::wstring ws = utf_16_bom_to_utf_8(settings);
    std::wstringstream ss(ws);
    XML settings_xml(ss);
    settings_xml.get_child(L"MAIN_CONFIG")->get_child(L"MOD")->set_value(name_folder);
    settings.close();
    std::wstringstream settings_new_ss(wpath);
    settings.imbue(std::locale("ru_RU.UTF-8"));
    settings_xml.load_to_file(settings_new_ss);
    std::ofstream settings_new(wpath, std::ios::out|std::ios::binary);
    utf_8_to_utf_16_bom(settings_new_ss.str(), settings_new);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->db_listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->sdk_listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->db_listWidget,
                     SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(on_rightClicked_db(const QPoint&)));
    try {
        std::wstring wpath(L"C:\\MagicBoxRedux\\downloaded.ini");
        if (wpath.empty()){
            QMessageBox message_box;
            message_box.critical(0, "Не возможно открыть файл", "Вы не ввели путь");
            message_box.setFixedSize(300, 200);
            return;
        }
        if (!std::filesystem::exists(wpath)){
            QMessageBox message_box;
            message_box.critical(0, "Не возможно открыть файл", "Файл не существует");
            message_box.setFixedSize(300, 200);
            return;
        }
        std::wifstream file(wpath);
        if (!file.is_open()){
            QMessageBox message_box;
            message_box.critical(0, "Не возможно открыть файл", "Недостаточно прав");
            message_box.setFixedSize(300, 200);
            return;
        }
        std::wifstream downloaded_mods_file(wpath);
        downloaded_mods_file.imbue(std::locale("ru_RU.UTF-8"));
        XML downloaded_mods_xml(downloaded_mods_file);
        auto mods_node = downloaded_mods_xml.get_child(L"mods");
        if (mods_node){
            for (auto& cur_mod : *mods_node){
                Mod mod(cur_mod.first, *cur_mod.second);
                if (mod.get_type() == Mod::DB){
                    ui->db_listWidget->addItem(QString::fromStdWString(mod.get_name()));
                    mods_db.push_back(std::move(mod));
                }
                else {
                    ui->sdk_listWidget->addItem(QString::fromStdWString(mod.get_name()));
                    mods_sdk.push_back(std::move(mod));
                }
            }
        }
    }
    catch (std::exception& errc){
        QMessageBox message_box;
        message_box.critical(0, "Ошибка", errc.what());
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reload_mods()
{
    std::wstring wpath = L"downloaded_mods.ini";
    std::wofstream file(wpath);
}

void MainWindow::on_pushButton_start_clicked()
{
    const auto & db_sels = ui->db_listWidget->selectedItems();
    const auto & sdk_sels = ui->sdk_listWidget->selectedItems();
    if (db_sels.size() == 1 && sdk_sels.size() == 1){
        int db_id = ui->db_listWidget->row(db_sels[0]);
        int sdk_id = ui->sdk_listWidget->row(sdk_sels[0]);
        if (!exists_mods(db_id, sdk_id)){
            install_mods(db_id, sdk_id);
        }
        update_mod(db_id, sdk_id);
    }
}

void MainWindow::on_rightClicked_db(const QPoint& pos)
{
//    QMenu contextMenu(this);
//    QAction action_add("Добавить", this);
//    contextMenu.addAction(&action_add);
//    contextMenu.exec(mapToGlobal(pos));
//    contextMenu.show();
}

void MainWindow::on_rightClicked_sdk(const QPoint&pos)
{

}

void MainWindow::on_pushButton_reinstall_clicked()
{

}
