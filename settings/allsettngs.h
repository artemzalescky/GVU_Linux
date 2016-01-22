#ifndef ALLSETTNGS_H
#define ALLSETTNGS_H

#include <QWidget>

namespace Ui {
    class AllSettngs;
}

class AllSettngs : public QWidget
{
    Q_OBJECT

public:
    explicit AllSettngs(QWidget *parent = 0);
    ~AllSettngs();

private:
    Ui::AllSettngs *ui;
};

#endif // ALLSETTNGS_H
