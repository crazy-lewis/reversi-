#ifndef STARTSETTINGSWIDGET_H
#define STARTSETTINGSWIDGET_H

#include <QWidget>
#include<QPushButton>

namespace Ui {
class StartSettingsWidget;
}

class StartSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartSettingsWidget(QWidget *parent = nullptr);
    ~StartSettingsWidget();

signals:void setMode(int mode);

private:
    Ui::StartSettingsWidget *ui;
};

#endif // STARTSETTINGSWIDGET_H
