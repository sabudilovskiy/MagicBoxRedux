#ifndef SDKSETTINGS_H
#define SDKSETTINGS_H

#include "xmlnode.h"
#include <unordered_map>
#include "MyTab.h"
namespace Ui {
class SDKSettings;
}

class UnknownTypeSettings : public std::exception{

};
class UnknownTab : public std::exception{

};

class SDKSettings : public QWidget
{
    Q_OBJECT
    std::vector<QSpinBox*> spin_boxes;
    std::vector<QCheckBox*> check_boxes;
    std::vector<QTextEdit*> text_edits;
    std::vector<QDoubleSpinBox*> double_spin_boxes;
    std::unordered_map<std::wstring, MyTab> tabs;
public:
    explicit SDKSettings(std::wstring path, QWidget *parent = nullptr);
    ~SDKSettings();
    void add_elem(const std::wstring& name, XMLNode& node);
    MyTab* add_tab(std::wstring name, XMLNode& node);
    MyTab* find_tab(const std::wstring& key);
private slots:
    void on_load_button_clicked();

    void on_save_button_clicked();

private:
    Ui::SDKSettings *ui;
};

#endif // SDKSETTINGS_H
