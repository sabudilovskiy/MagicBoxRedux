#ifndef HDMCONFIGWINDOW_H
#define HDMCONFIGWINDOW_H

#include "qcheckbox.h"
#include <QWidget>
#include <qspinbox.h>
#include <qtextedit.h>
#include <vector>
namespace Ui {
class HDMConfigWindow;
}

class HDMConfigWindow : public QWidget
{
    Q_OBJECT
    QString path;
    std::vector<QSpinBox*> spin_boxes;
    std::vector<QCheckBox*> check_boxes;
    std::vector<QTextEdit*> text_edits;
    std::vector<QDoubleSpinBox*> double_spin_boxes;
public:
    HDMConfigWindow(QString path, QWidget *parent = nullptr);
    ~HDMConfigWindow();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_load_clicked();

private:
    Ui::HDMConfigWindow *ui;
};

#endif // HDMCONFIGWINDOW_H
