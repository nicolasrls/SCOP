#include "objeto.h"

//QString local = "C:/Users/nicol/Documents/codigos/Projetos QT/SCOP/Arquivo/";
//QString nome = "dados_SCOP.csv";


void Objeto::inserirObjeto(Cadastro a)
{
    objetos.push_back(a);
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

void Objeto::salvarArquivo(QString file)
{
    QFile arquivo(file);

    arquivo.open(QIODevice::WriteOnly);
    for(auto a:objetos){
        QString linha = a.getObj() + "." + a.getCi() + "." + a.getValor() + "." + a.getData() + "." + a.getEstado() +"."+ a.getDestino() + "." + a.getPeso() +"\n";
        arquivo.write(linha.toLocal8Bit());
    }
    arquivo.close();
}

bool Objeto::carregarArquivo(QString file)
{

    QFile arquivo(file);
    if(arquivo.isOpen() == 1){
         return 1;
    }
    arquivo.open(QIODevice::ReadOnly);
    QString linha;
    QStringList dados;
    while(!arquivo.atEnd()){
            Cadastro temp;
            linha = arquivo.readLine();
            dados = linha.split(".");
            temp.setObj(dados[0]);
            temp.setCi(dados[1]);
            temp.setValor(dados[2]);
            temp.setData(dados[3]);
            temp.setEstado(dados[4]);
            temp.setDestino(dados[5]);
            temp.setPeso(dados[6]);
            inserirObjeto(temp);
    }
    return 0;
}

int Objeto::size()
{
    return objetos.size();
}

Cadastro Objeto::operator[](int indice)
{
    return objetos[indice];
}

void Objeto::eraseObj(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getObj() != txt){
            objetos.erase(objetos.begin()+i);
        }
    }
}

void Objeto::apagarObj(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getObj() == txt){
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
        if(objetos[i].getPeso() != txt){
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

void Objeto::eraseValor(QString txt)
{
    for(int i = 0; i < objetos.size(); i++){
        if(objetos[i].getValor() != txt){
            objetos.erase(objetos.begin()+i);
        }
    }
}


