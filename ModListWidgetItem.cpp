#include "ModListWidgetItem.h"


void ModListWidgetItem::mousePressEvent(QMouseEvent *e){
    if (e->button()==Qt::RightButton){
        emit(this);
    }
}
