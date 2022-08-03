#ifndef MODLISTWIDGETITEM_H
#define MODLISTWIDGETITEM_H
#include <QListWidgetItem>
#include <QMouseEvent>

class ModListWidgetItem : public QListWidgetItem, public QObject
{
    Q_OBJECT
public:
    ModListWidgetItem(const QIcon &icon, const QString &text, QListWidget *parent = nullptr, int type = Type) :
        QListWidgetItem(icon, text, parent, type){}
    ModListWidgetItem(const QListWidgetItem &other) : QListWidgetItem(other){}
    ModListWidgetItem(const QString &text, QListWidget *parent = nullptr, int type = Type) :
        QListWidgetItem(text, parent, type){}
    ModListWidgetItem(QListWidget *parent = nullptr, int type = Type) :
        QListWidgetItem(parent, type){}
private slots:
    void mousePressEvent(QMouseEvent* e);
public:
signals:
    void onRightClicked(ModListWidgetItem* item);
};

#endif // MODLISTWIDGETITEM_H
