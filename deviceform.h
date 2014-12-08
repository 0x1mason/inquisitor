#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QWidget>

namespace Ui {
class DeviceForm;
}

class DeviceForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceForm(QWidget *parent = 0);
    ~DeviceForm();

private:
    Ui::DeviceForm *ui;
};

#endif // DEVICEFORM_H
