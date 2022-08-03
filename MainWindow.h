#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include <vector>
#include "Mod.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
protected:
    Q_OBJECT
    Ui::MainWindow *ui;
    std::vector<Mod> mods_db, mods_sdk;
    std::wstring path_game = L"C:\\Program Files (x86)\\Steam\\steamapps\\common\\SuperPower 2";
    void install_mods(int db_id, int sdk_id);
    bool exists_mods(int db_id, int sdk_id);
    void run_game();
    std::wstring get_name_folder(int db_id, int sdk_id);
    void update_mod(int db_id, int sdk_id);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void reload_mods();
protected slots:
    void on_rightClicked_db(const QPoint&pos);
    void on_rightClicked_sdk(const QPoint&pos);
private slots:
    void on_pushButton_reinstall_clicked();\
    void on_pushButton_start_clicked();
};
#endif // MAINWINDOW_H
