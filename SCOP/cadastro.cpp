#include "cadastro.h"



QString Cadastro::getObj() const
{
    return obj;
}

void Cadastro::setObj(const QString &value)
{
    obj = value;
}

QString Cadastro::getCi() const
{
    return ci;
}

void Cadastro::setCi(const QString &value)
{
    ci = value;
}

QString Cadastro::getValor() const
{
    return valor;
}

void Cadastro::setValor(const QString &value)
{
    valor = value;
}

QString Cadastro::getData() const
{
    return data;
}

void Cadastro::setData(const QString &value)
{
    data = value;
}

QString Cadastro::getEstado() const
{
    return estado;
}

void Cadastro::setEstado(const QString &value)
{
    estado = value;
}

QString Cadastro::getDestino() const
{
    return destino;
}

void Cadastro::setDestino(const QString &value)
{
    destino = value;
}

QString Cadastro::getPeso() const
{
    return peso;
}

void Cadastro::setPeso(const QString &value)
{
    peso = value;
}

Cadastro::Cadastro()
{

}
