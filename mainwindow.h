#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QFile>
#include <QPixmap>
#include <QApplication>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include "cadastro.h"
#include "objeto.h"
#include "ajuda.h"
#include <QDesktopServices>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void inserirNaTabela(Cadastro a, int linha);
    void on_btncadastrar_clicked();
    void on_ordmenorcodigo_clicked();
    void on_ordmaiorvalor_clicked();
    void on_ordpeso_clicked();
    void on_actionAbrir_triggered();
    void on_actionSalvar_triggered();
    void on_actionSair_triggered();
    void on_tabela_cellDoubleClicked(int row, int column);
    void on_actionExcluir_triggered();
    void on_actionLimpar_Tabela_triggered();
    void on_limpartab_clicked();

    void on_actionAtualizar_Tabela_triggered();

    void on_btnAjuda_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
