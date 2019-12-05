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
    double valor;
    QString data;
    QString estado;
    QString destino;
    double peso;


public:
    Cadastro();

    QString getObj() const;
    void setObj(const QString &value);
    QString getCi() const;
    void setCi(const QString &value);
    double getValor() const;
    void setValor(const double &value);
    QString getData() const;
    void setData(const QString &value);
    QString getEstado() const;
    void setEstado(const QString &value);
    QString getDestino() const;
    void setDestino(const QString &value);
    double getPeso() const;
    void setPeso(const double &value);
};

#endif // CADASTRO_H
