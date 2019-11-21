#ifndef CADASTRO_H
#define CADASTRO_H
#include <QString>
#include <QDebug>
#include <QDateEdit>

class Cadastro
{

private:
    QString obj;
    QString ci;
    QString valor;
    QString data;
    QString estado;
    QString destino;
    QString peso;


public:
    Cadastro();

    QString getObj() const;
    void setObj(const QString &value);
    QString getCi() const;
    void setCi(const QString &value);
    QString getValor() const;
    void setValor(const QString &value);
    QString getData() const;
    void setData(const QString &value);
    QString getEstado() const;
    void setEstado(const QString &value);
    QString getDestino() const;
    void setDestino(const QString &value);
    QString getPeso() const;
    void setPeso(const QString &value);
};

#endif // CADASTRO_H
