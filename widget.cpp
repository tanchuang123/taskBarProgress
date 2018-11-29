#include "widget.h"
#include "ui_widget.h"

#include <QtWidgets>
#include <QtWinExtras>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   menu = new QMenu(this);
  if (QtWin::isCompositionEnabled()) {
      QtWin::enableBlurBehindWindow(menu);
      QString css("QMenu { border: 1px solid %1; border-radius: 2px; background: transparent; }");
      menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
  } else {
      QtWin::disableBlurBehindWindow(menu);
      QString css("QMenu { border: 1px solid black; background: %1; }");
      menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
  }
   createTaskbar();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::seekForward()//滑块快进
{
    ui->horizontalSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void Widget::seekBackward()//滑块后退
{
   ui->horizontalSlider->triggerAction(QSlider::SliderPageStepSub);
}

void Widget::createTaskbar()
{
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(windowHandle());

    taskbarProgress = taskbarButton->progress();
    taskbarProgress->show();
    connect(ui->horizontalSlider, &QAbstractSlider::valueChanged, taskbarProgress, &QWinTaskbarProgress::setValue);
    connect(ui->horizontalSlider, &QAbstractSlider::rangeChanged, taskbarProgress, &QWinTaskbarProgress::setRange);

}
