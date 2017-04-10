#pragma once

#include <QWidget>

class FocusDetectingWidget : public QWidget {
  Q_OBJECT
public:
  FocusDetectingWidget(QWidget *parent = nullptr,
                       Qt::WindowFlags f = Qt::WindowFlags());

  void enterEvent(QEvent *event) override;

  void leaveEvent(QEvent *event) override;

signals:
  void mouseEnter();
  void mouseLeave();
};
