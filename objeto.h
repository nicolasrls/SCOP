#ifndef OBJETO_H
#define OBJETO_H
#include "cadastro.h"
#include <QVector>
#include <algorithm>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>


class Objeto
{

private:
    QVector <Cadastro> objetos;

public:
    Objeto();
    void inserirObjeto(Cadastro a);
    bool objetoExiste(Cadastro a);
    void ordenarPorCodigo();
    void ordenarPorValor();
    void ordenarPorPeso();
    bool salvarArquivo(QString arquivo);
    bool carregarArquivo(QString arquivo);
    int size();
    Cadastro operator[](int indice);
    void eraseObj(QString txt);
    bool apagarObj(QString txt);
    void eraseCi(QString txt);
    void eraseData(QString txt);
    void eraseValor(QString txt);
    void erasePeso(QString txt);
    void eraseStatus(QString txt);
    void eraseDestino(QString txt);

};

#endif // OBJETO_H
