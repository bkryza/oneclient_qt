#include "focusdetectingwidget.h"

FocusDetectingWidget::FocusDetectingWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f) {}

void FocusDetectingWidget::enterEvent(QEvent *event) {
  emit mouseEnter();
  QWidget::enterEvent(event);
}

void FocusDetectingWidget::leaveEvent(QEvent *event) {
  emit mouseLeave();
  QWidget::leaveEvent(event);
}

void FocusDetectingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit mousePressed();
    } else {
        // pass on other buttons to base class
        QWidget::mousePressEvent(event);
    }
}
