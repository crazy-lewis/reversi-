#include "startsettingswidget.h"
#include "ui_startsettingswidget.h"

StartSettingsWidget::StartSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartSettingsWidget)
{
    ui->setupUi(this);

    connect(ui->HumanVSHumanButton,&QPushButton::clicked,this,[=]()
            {
        emit setMode(2);
        close();
    });
    connect(ui->HumanVSAiButton,&QPushButton::clicked,this,[=](){
        emit setMode(0);
        close();
    });
    connect(ui->AiVSHumanButton,&QPushButton::clicked,this,[=](){
        emit setMode(1);
        close();
    });
}

StartSettingsWidget::~StartSettingsWidget()
{
    delete ui;
}
