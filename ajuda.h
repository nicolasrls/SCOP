#ifndef AJUDA_H
#define AJUDA_H

#include <QDialog>

namespace Ui {
class Ajuda;
}

class Ajuda : public QDialog
{
    Q_OBJECT

public:
    explicit Ajuda(QWidget *parent = nullptr);
    ~Ajuda();

private:
    Ui::Ajuda *ui;
};

#endif // AJUDA_H
