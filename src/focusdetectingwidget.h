#pragma once

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>

class FocusDetectingWidget : public QWidget {
  Q_OBJECT
public:
  FocusDetectingWidget(QWidget *parent = nullptr,
                       Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~FocusDetectingWidget() = default;

  virtual void enterEvent(QEvent *event) override;

  virtual void leaveEvent(QEvent *event) override;

  virtual void mousePressEvent(QMouseEvent *event) override;

signals:
  void mouseEnter();
  void mouseLeave();
  void mousePressed();
};
