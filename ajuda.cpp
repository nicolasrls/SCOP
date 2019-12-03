#include "ajuda.h"
#include "ui_ajuda.h"

Ajuda::Ajuda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ajuda)
{
    ui->setupUi(this);
}

Ajuda::~Ajuda()
{
    delete ui;
}
