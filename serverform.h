#ifndef SERVERFORM_H
#define SERVERFORM_H

#include <QWidget>

namespace Ui {
class ServerForm;
}

class ServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ServerForm(QWidget *parent = 0);
    ~ServerForm();

private:
    Ui::ServerForm *ui;
};

#endif // SERVERFORM_H
