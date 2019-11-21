#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cadastro.h"
#include "objeto.h"
#include <QPixmap>
#include <QTextStream>
#include <QFileDialog>


Cadastro temp;
Objeto a;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap logo("C:/Users/nicol/Documents/codigos/Projetos QT/SCOP/scopimg.png");
    ui->labelimg->setPixmap(logo.scaled(151,141,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btncadastrar_clicked()
{
    if((ui->inputCi->text())!= "" and (ui->inputObjeto->text())!="" and (ui->valorobj->text())!="" and (ui->destinoObj->text())!= "" and (ui->pesoobj->text())!=""){
        temp.setCi(ui->inputCi->text());
        temp.setObj(ui->inputObjeto->text());
        temp.setData(ui->edicaodata->text());
        temp.setValor(ui->valorobj->text());
        temp.setEstado(ui->estadoatual->currentText());
        temp.setDestino(ui->destinoObj->text());
        temp.setPeso(ui->pesoobj->text());
        a.inserirObjeto(temp);
        int quantidade_linhas = ui->tabela->rowCount();

        ui->tabela->insertRow(quantidade_linhas);

        inserirNaTabela(temp,quantidade_linhas);
        QMessageBox::information(this,"Cadastro:","Cadastrado com sucesso!");

    }else{
        QMessageBox::critical(this,"Erro","Um dos parâmetros estão vazios, favor preencher e tentar novamente.");
    }
    ui->inputCi->clear();
    ui->inputObjeto->clear();
    ui->destinoObj->clear();
    ui->valorobj->clear();
    ui->pesoobj->clear();

}

void MainWindow::inserirNaTabela(Cadastro a, int linha)
{
    ui->tabela->setItem(linha,0, new QTableWidgetItem(a.getObj()));
    ui->tabela->setItem(linha,1, new QTableWidgetItem(a.getCi()));
    ui->tabela->setItem(linha,2, new QTableWidgetItem(a.getValor()));
    ui->tabela->setItem(linha,3, new QTableWidgetItem(a.getData()));
    ui->tabela->setItem(linha,4, new QTableWidgetItem(a.getEstado()));
    ui->tabela->setItem(linha,5, new QTableWidgetItem(a.getDestino()));
    ui->tabela->setItem(linha,6, new QTableWidgetItem(a.getPeso()));
}

void MainWindow::on_ordmenorcodigo_clicked()
{
    a.ordenarPorCodigo();
    ui->tabela->clearContents();
    for(int i=0; i<a.size();i++){
        inserirNaTabela(a[i],i);
    }
    QMessageBox::information(this,"Ordenado","Ordenado com sucesso!");
}

void MainWindow::on_ordmaiorvalor_clicked()
{
    a.ordenarPorValor();
    ui->tabela->clearContents();
    for(int i=0; i<a.size();i++){
        inserirNaTabela(a[i],i);
    }
    QMessageBox::information(this,"Ordenado","Ordenado com sucesso!");
}

void MainWindow::on_ordpeso_clicked()
{
    a.ordenarPorPeso();
    ui->tabela->clearContents();
    for(int i=0; i<a.size();i++){
        inserirNaTabela(a[i],i);
    }
    QMessageBox::information(this,"Ordenado","Ordenado com sucesso!");
}

void MainWindow::on_actionAbrir_triggered()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Abrir Arquivo","","*.csv");
    ui->tabela->clearContents();
    if(a.carregarArquivo(filename) == 1){
        QMessageBox::critical(this,"Arquivo"," O arquivo já foi lido, favor cheque a tabela!");
    }else{
        for(int i=0;i<a.size();i++){
            ui->tabela->insertRow(i);
            inserirNaTabela(a[i],i);
        }
    }
    QMessageBox::information(this,"Arquivo"," O arquivo foi lido, cheque a tabela!");
}

void MainWindow::on_actionSalvar_triggered(){

    QString filename;
    filename = QFileDialog::getSaveFileName(this,"Salvar Arquivo","","*.csv");
    a.salvarArquivo(filename);
    QMessageBox::information(this,"Salvo","Arquivo salvo com sucesso!");

}

void MainWindow::on_actionSair_triggered()
{
   //para fechar o programa.
   QApplication::quit();
}



void MainWindow::on_tabela_cellDoubleClicked(int row, int column)
{
    if(column == 0){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
    if(resp == QMessageBox::Yes){
        bool ok;
        QString txt = QInputDialog::getText(this, "Alterar Objeto", "Digite o novo objeto", QLineEdit::Normal,"",&ok);
        if(ok and !txt.isEmpty()){
            qDebug() << txt;
            temp.setObj(txt);
            temp.setCi(a[row].getCi());
            temp.setData(a[row].getData());
            temp.setValor(a[row].getValor());
            temp.setEstado(a[row].getEstado());
            temp.setDestino(a[row].getDestino());
            temp.setPeso(a[row].getPeso());
            qDebug() << temp.getObj() << temp.getData() << temp.getCi() << temp.getEstado() << temp.getDestino() << temp.getValor() << temp.getPeso();
            a.eraseObj(txt);
            a.inserirObjeto(temp);
            ui->tabela->setItem(row, column, new QTableWidgetItem(temp.getObj()));
        }else{
           QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
    if(column == 1){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
    if(resp == QMessageBox::Yes){
        bool ok;
        QString txt = QInputDialog::getText(this, "Alterar CI", "Digite o novo CI", QLineEdit::Normal,"",&ok);
        if(ok and !txt.isEmpty()){
            qDebug() << txt;
            temp.setObj(a[row].getObj());
            temp.setCi(txt);
            temp.setData(a[row].getData());
            temp.setValor(a[row].getValor());
            temp.setEstado(a[row].getEstado());
            temp.setDestino(a[row].getDestino());
            temp.setPeso(a[row].getPeso());
            a.eraseCi(txt);
            a.inserirObjeto(temp);
            ui->tabela->setItem(row, column, new QTableWidgetItem(temp.getCi()));
        }else{
           QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
    if(column == 2){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
    if(resp == QMessageBox::Yes){
        bool ok;
        QString txt = QInputDialog::getText(this, "Alterar Valor", "Digite o novo valor", QLineEdit::Normal,"",&ok);
        if(ok and !txt.isEmpty()){
            qDebug() << txt;
            temp.setObj(a[row].getObj());
            temp.setCi(a[row].getCi());
            temp.setData(a[row].getData());
            temp.setValor(txt);
            temp.setEstado(a[row].getEstado());
            temp.setDestino(a[row].getDestino());
            temp.setPeso(a[row].getPeso());
            a.eraseCi(txt);
            a.inserirObjeto(temp);
            ui->tabela->setItem(row, column, new QTableWidgetItem(temp.getValor()));
        }else{
           QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
    if(column == 3){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
    if(resp == QMessageBox::Yes){
        bool ok;
        QString txt = QInputDialog::getText(this, "Alterar Data de Postagem", "Digite a nova data:", QLineEdit::Normal,"",&ok);
        if(ok and !txt.isEmpty()){
            qDebug() << txt;
            temp.setObj(a[row].getObj());
            temp.setCi(a[row].getCi());
            temp.setData(txt);
            temp.setValor(a[row].getValor());
            temp.setEstado(a[row].getEstado());
            temp.setDestino(a[row].getDestino());
            temp.setPeso(a[row].getPeso());
            a.eraseData(txt);
            a.inserirObjeto(temp);
            ui->tabela->setItem(row, column, new QTableWidgetItem(temp.getData()));
        }else{
           QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
    if(column == 4){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
    if(resp == QMessageBox::Yes){
        bool ok;
        QString txt = QInputDialog::getText(this, "Alterar Status do objeto", "Digite o novo status:", QLineEdit::Normal,"",&ok);
        if(ok and !txt.isEmpty()){
            qDebug() << txt;
            temp.setObj(a[row].getObj());
            temp.setCi(a[row].getCi());
            temp.setData(a[row].getData());
            temp.setValor(a[row].getValor());
            temp.setEstado(txt);
            temp.setDestino(a[row].getDestino());
            temp.setPeso(a[row].getPeso());
            a.eraseStatus(txt);
            a.inserirObjeto(temp);
            ui->tabela->setItem(row, column, new QTableWidgetItem(temp.getEstado()));
        }else{
           QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
    if(column == 5){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
    if(resp == QMessageBox::Yes){
        bool ok;
        QString txt = QInputDialog::getText(this, "Alterar Destino", "Digite o novo destino", QLineEdit::Normal,"",&ok);
        if(ok and !txt.isEmpty()){
            qDebug() << txt;
            temp.setObj(a[row].getObj());
            temp.setCi(a[row].getCi());
            temp.setData(a[row].getData());
            temp.setValor(a[row].getValor());
            temp.setEstado(a[row].getEstado());
            temp.setDestino(txt);
            temp.setPeso(a[row].getPeso());
            a.eraseDestino(txt);
            a.inserirObjeto(temp);
            ui->tabela->setItem(row, column, new QTableWidgetItem(temp.getDestino()));
        }else{
           QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
    if(column == 6){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
    if(resp == QMessageBox::Yes){
        bool ok;
        QString txt = QInputDialog::getText(this, "Alterar Valor", "Digite o novo valor", QLineEdit::Normal,"",&ok);
        if(ok and !txt.isEmpty()){
            qDebug() << txt;
            temp.setObj(a[row].getObj());
            temp.setCi(a[row].getCi());
            temp.setData(a[row].getData());
            temp.setValor(a[row].getValor());
            temp.setEstado(a[row].getEstado());
            temp.setDestino(a[row].getDestino());
            temp.setPeso(txt);
            a.eraseDestino(txt);
            a.inserirObjeto(temp);
            ui->tabela->setItem(row, column, new QTableWidgetItem(temp.getPeso()));
        }else{
           QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
}

void MainWindow::on_btnAjuda_clicked()
{

}

void MainWindow::on_actionExcluir_triggered()
{
    QMessageBox::StandardButton resp = QMessageBox::question(this, "Excluir Itens", "Você deseja excluir um item?");
    if(resp == QMessageBox::Yes){
    bool ok;
    QString txt = QInputDialog::getText(this, "Excluir Itens", "Qual item deseja excluir", QLineEdit::Normal,"",&ok);
    if(ok and !txt.isEmpty()){
        a.apagarObj(txt);
        }
    }
}

void MainWindow::on_actionLimpar_Tabela_triggered()
{
    ui->tabela->clearContents();
}
