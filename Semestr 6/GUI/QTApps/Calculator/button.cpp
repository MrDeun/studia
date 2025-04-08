#include "button.h"
#include <qminmax.h>
#include <qsizepolicy.h>
#include <qtoolbutton.h>


Button::Button(const QString& text, QWidget* parent):QToolButton(parent){
    setText(text);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
}

QSize Button::sizeHint() const {
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(),size.height());
    return size;
}