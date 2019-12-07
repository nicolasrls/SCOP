#include "mainwindow.h"
#include "ui_mainwindow.h"

Cadastro temp;
Objeto a;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
        temp.setValor(ui->valorobj->text().toDouble());
        temp.setEstado(ui->estadoatual->currentText());
        temp.setDestino(ui->destinoObj->text());
        temp.setPeso(ui->pesoobj->text().toDouble());
        int quantidade_linhas = ui->tabela->rowCount();
        if(a.objetoExiste(temp) == 1){
            QMessageBox::critical(this,"Erro","O objeto já existe, favor inserir um objeto diferente");
        }else{
            a.inserirObjeto(temp);
            ui->tabela->insertRow(quantidade_linhas);
            inserirNaTabela(temp,quantidade_linhas);
            QMessageBox::information(this,"Cadastro","Cadastrado com sucesso!");
            ui->tabela->setColumnWidth(0,195);
            ui->tabela->setColumnWidth(3,199);
            ui->tabela->setColumnWidth(4,250);
            atualizarEstatisticas();
            ui->inputCi->clear();
            ui->inputObjeto->clear();
            ui->destinoObj->clear();
            ui->valorobj->clear();
            ui->pesoobj->clear();
        }
    }else{
        QMessageBox::critical(this,"Erro","Um dos parâmetros estão vazios, favor preencher e tentar novamente.");
    }
}

void MainWindow::inserirNaTabela(Cadastro a, int linha)
{
    ui->tabela->setItem(linha,0, new QTableWidgetItem(a.getObj()));
    ui->tabela->setItem(linha,1, new QTableWidgetItem(a.getCi()));
    ui->tabela->setItem(linha,2, new QTableWidgetItem(QString::number(a.getValor())));
    ui->tabela->setItem(linha,3, new QTableWidgetItem(a.getData()));
    ui->tabela->setItem(linha,4, new QTableWidgetItem(a.getEstado()));
    ui->tabela->setItem(linha,5, new QTableWidgetItem(a.getDestino()));
    ui->tabela->setItem(linha,6, new QTableWidgetItem(QString::number(a.getPeso())));
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
    filename = QFileDialog::getOpenFileName(this, "Abrir Arquivo","","Arquivo separado por vírgulas(*.csv)");
    if(a.carregarArquivo(filename) == 1){
        QMessageBox::critical(this,"Arquivo"," O arquivo já foi lido, favor cheque a tabela!");
    }else{
        ui->tabela->clearContents();
        on_actionLimpar_Tabela_triggered();
        for(int i=0;i<a.size();i++){
            ui->tabela->insertRow(i);
            inserirNaTabela(a[i],i);
        }
        atualizarEstatisticas();
        ui->tabela->setColumnWidth(0,195);
        ui->tabela->setColumnWidth(3,199);
        ui->tabela->setColumnWidth(4,250);
        QMessageBox::information(this,"Arquivo"," O arquivo foi lido, cheque a tabela!");
    }
}

void MainWindow::on_actionSalvar_triggered(){

    QString filename;
    filename = QFileDialog::getSaveFileName(this,"Salvar Arquivo","","*.csv");
    if(a.salvarArquivo(filename) == 1)QMessageBox::information(this,"Salvo","Arquivo salvo com sucesso!");
    else QMessageBox::critical(this,"Erro", "O arquivo não foi salvo.");

}

void MainWindow::on_actionSair_triggered()
{
    //para fechar o programa.
    QApplication::quit();
}

void MainWindow::on_tabela_cellClicked(int row, int column)
{
    if(column == 0){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
        if(resp == QMessageBox::Yes){
            bool ok;
            QString txt = QInputDialog::getText(this, "Alterar Objeto", "Digite o novo objeto", QLineEdit::Normal,"",&ok);
            if(ok and !txt.isEmpty()){
                temp.setObj(txt);
                temp.setCi(a[row].getCi());
                temp.setData(a[row].getData());
                temp.setValor(a[row].getValor());
                temp.setEstado(a[row].getEstado());
                temp.setDestino(a[row].getDestino());
                temp.setPeso(a[row].getPeso());
                a.eraseObj(txt);
                if(a.objetoExiste(temp) == 0){
                    a.inserirObjeto(temp);
                    ui->tabela->setItem(row, column, new QTableWidgetItem(temp.getObj()));
                    atualizarEstatisticas();
                }else
                    QMessageBox::critical(this,"Erro","O Objeto a ser editado já existe!");

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
                atualizarEstatisticas();
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
                temp.setObj(a[row].getObj());
                temp.setCi(a[row].getCi());
                temp.setData(a[row].getData());
                temp.setValor(txt.toDouble());
                temp.setEstado(a[row].getEstado());
                temp.setDestino(a[row].getDestino());
                temp.setPeso(a[row].getPeso());
                a.eraseCi(txt);
                a.inserirObjeto(temp);
                ui->tabela->setItem(row, column, new QTableWidgetItem(QString::number(temp.getValor())));
                atualizarEstatisticas();
            }else{
                QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
    if(column == 3){
        QMessageBox::StandardButton resp = QMessageBox::question(this, "Editar Itens", "Você deseja editar este item?");
        if(resp == QMessageBox::Yes){
            bool ok;
            QString txt = QInputDialog::getText(this, "Alterar Data de Postagem", "Digite a nova data:",QLineEdit::Normal,"",&ok);
            if(ok and !txt.isEmpty()){
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
                atualizarEstatisticas();
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
                atualizarEstatisticas();
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
                atualizarEstatisticas();
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
                temp.setObj(a[row].getObj());
                temp.setCi(a[row].getCi());
                temp.setData(a[row].getData());
                temp.setValor(a[row].getValor());
                temp.setEstado(a[row].getEstado());
                temp.setDestino(a[row].getDestino());
                temp.setPeso(txt.toDouble());
                a.eraseDestino(txt);
                a.inserirObjeto(temp);
                ui->tabela->setItem(row, column, new QTableWidgetItem(QString::number(temp.getPeso())));
                atualizarEstatisticas();
            }else{
                QMessageBox::critical(this, "Erro", "O objeto a ser editado está vazio.");
            }
        }
    }
}

void MainWindow::on_actionExcluir_triggered()
{
    QMessageBox::StandardButton resp = QMessageBox::question(this, "Excluir Itens", "Você deseja excluir um item?");
    if(resp == QMessageBox::Yes){
        bool ok;
        QString txt = QInputDialog::getText(this, "Excluir Itens", "Qual item deseja excluir", QLineEdit::Normal,"",&ok);
        qDebug() << txt;
        if(ok and !txt.isEmpty()){
            if(a.apagarObj(txt) != 0){
                on_actionLimpar_Tabela_triggered();
                for(int j=0; j < a.size(); j++){
                    ui->tabela->insertRow(ui->tabela->rowCount());
                    inserirNaTabela(a[j],j);
                }
                QMessageBox::information(this,"OK","O objeto foi excluído");
                atualizarEstatisticas();
            }else{
                QMessageBox::warning(this,"Erro","O objeto não existe.");
            }
        }else{
            QMessageBox::warning(this,"Erro","O texto está vazio");
        }
    }
}

void MainWindow::on_actionLimpar_Tabela_triggered()
{
    int qtdeLinhas = ui->tabela->rowCount();
    for(int i = 0; i < qtdeLinhas ; i++)ui->tabela->removeRow(0);

}

void MainWindow::on_limpartab_clicked()
{
    on_actionLimpar_Tabela_triggered();
    a.limparTudo();
    atualizarEstatisticas();
    QMessageBox::information(this,"Limpo","A tabela foi resetada com sucesso");
}


void MainWindow::on_actionAtualizar_Tabela_triggered()
{
    on_actionLimpar_Tabela_triggered();
    for(int j=0; j < a.size(); j++){
        ui->tabela->insertRow(ui->tabela->rowCount());
        inserirNaTabela(a[j],j);
    }
    QMessageBox::information(this,"Atualizada","A tabela foi atualizada com sucesso.");
    atualizarEstatisticas();
}

void MainWindow::on_btnAjuda_clicked()
{
    QString url = "https://github.com/nicolasrls/SCOP/blob/master/README.md";
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::atualizarEstatisticas()
{
    ui->labelTotalVal->setText(QString::number(a.somaVal()));
    ui->labelTotalPeso->setText(QString::number(a.somaPeso()));
    ui->labelTotalObj->setText(QString::number(a.somaTotal()));
}


