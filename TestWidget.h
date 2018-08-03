#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QScopedPointer>

namespace Ui {
class TestWidget;
}

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QWidget *parent = 0);
    ~TestWidget();

    void readAllSampleFile();

public slots:
    void playVideoWall();

private:
    struct TestWidgetImpl;
    QScopedPointer<TestWidgetImpl> impl;
};

#endif // TESTWIDGET_H
