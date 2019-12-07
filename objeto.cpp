#include "objeto.h"

void Objeto::inserirObjeto(Cadastro a)
{
    objetos.push_back(a);
}

bool Objeto::objetoExiste(Cadastro a)
{
    if(objetos.size() >= 1){
        for(int i = 0; i < objetos.size(); i++){
            if(a.getObj() == objetos[i].getObj()){
                return 1;
            }
        }
    }
    return 0;
}

Objeto::Objeto()
{

}

void Objeto::ordenarPorCodigo()
{
    std::sort(objetos.begin(),objetos.end(),[](Cadastro a, Cadastro b){
        return a.getCi()<b.getCi();
    });
}

void Objeto::ordenarPorValor()
{
    std::sort(objetos.begin(),objetos.end(),[](Cadastro a, Cadastro b){
        return a.getValor()>b.getValor();
    });
}

void Objeto::ordenarPorPeso()
{
    std::sort(objetos.begin(),objetos.end(),[](Cadastro a, Cadastro b){
        return a.getPeso()<b.getPeso();
    });
}

double Objeto::somaPeso()
{
    double soma = 0;
    for(auto a: objetos){
        soma += a.getPeso();
    }
    return soma;
}

int Objeto::somaTotal()
{
    return objetos.size();
}

double Objeto::somaVal()
{
    double soma = 0;
    for(auto a: objetos){
        soma += a.getValor();
    }
    return soma;
}

bool Objeto::salvarArquivo(QString file)
{
    QFile arquivo(file);
    arquivo.open(QIODevice::WriteOnly);
    if(arquivo.isOpen() == 1){
        for(auto a:objetos){
            QString linha = a.getObj() + "," + a.getCi() + "," + QString::number(a.getValor()) + "," + a.getData() + "," + a.getEstado() +","+ a.getDestino() + "," + QString::number(a.getPeso()) +"\n";
            arquivo.write(linha.toLocal8Bit());
        }
        arquivo.close();
        return 1;
    }else{
        return 0;
    }

}

bool Objeto::carregarArquivo(QString file)
{

    QFile arquivo(file);
    if(arquivo.isOpen() == 1)return 1;
    else{
        arquivo.open(QIODevice::ReadOnly);
        QString linha;
        QStringList dados;
        while(!arquivo.atEnd()){
            Cadastro temp;
            linha = arquivo.readLine();
            dados = linha.split(",");
            temp.setObj(dados[0]);
            temp.setCi(dados[1]);
            temp.setValor(dados[2].toDouble());
            temp.setData(dados[3]);
            temp.setEstado(dados[4]);
            temp.setDestino(dados[5]);
            temp.setPeso(dados[6].toDouble());
            if(objetoExiste(temp) == 0)
                inserirObjeto(temp);
        }
        arquivo.close();
        return 0;
    }

}
int Objeto::size()
{
    return objetos.size();
}

Cadastro Objeto::operator[](int indice)
{
    return objetos[indice];
}

bool Objeto::apagarObj(QString txt)
{
    for(int i = 0; i<objetos.size(); i++){
        if(objetos[i].getObj() == txt){
            objetos.erase(objetos.begin()+i);
        }
    }return 1;
}

void Objeto::eraseObj(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getObj() != txt){
            objetos.erase(objetos.begin()+i);
        }
    }
}

void Objeto::eraseCi(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getCi() != txt){
            objetos.erase(objetos.begin()+i);
        }
    }
}

void Objeto::eraseData(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getData() != txt){
            objetos.erase(objetos.begin()+i);
        }
    }
}

void Objeto::erasePeso(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getPeso() != txt.toDouble()){
            objetos.erase(objetos.begin()+i);
        }
    }
}

void Objeto::eraseStatus(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getEstado() != txt){
            objetos.erase(objetos.begin()+i);
        }
    }
}

void Objeto::eraseDestino(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getDestino() != txt){
            objetos.erase(objetos.begin()+i);
        }
    }
}

void Objeto::limparTudo()
{
    objetos.erase(objetos.begin(),objetos.end());
}

void Objeto::eraseValor(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getValor() != txt.toDouble()){
            objetos.erase(objetos.begin()+i);
        }
    }
}


