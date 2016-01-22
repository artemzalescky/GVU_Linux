#ifndef MODULENAVIGATOR_H
#define MODULENAVIGATOR_H

#include <QWidget>
#include <QFrame>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
    class ModuleNavigator;
}

struct ModuleButton
{
public:
    QFrame* moduleFrame;
    int left;
    int right;
    int top;
    int bottom;

    ModuleButton()
    {
        moduleFrame = NULL;
    }
    ModuleButton(QFrame* mF)
    {
        moduleFrame = mF;
        left = moduleFrame->geometry().left();
        right = moduleFrame->geometry().right();
        top = moduleFrame->geometry().top();
        bottom = moduleFrame->geometry().bottom();
    }
    bool contains(int x, int y)
    {
        return x > left && x < right && y > top && y < bottom;
    }
};

class ModuleNavigator : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleNavigator(QWidget *parent = 0);
    ~ModuleNavigator();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void DefineModuleButtons();

private:
    Ui::ModuleNavigator *ui;
    ModuleButton moduleButtons[6];
};

#endif // MODULENAVIGATOR_H
