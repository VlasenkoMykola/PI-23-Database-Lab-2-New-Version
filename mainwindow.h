#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void open_DB();
    QString tabParamViews_fillSQLParamsDialog(QString& sql, int num_Int, int num_Str);

public slots:
    void tabTables_changeView(const QString& tablename);
    void tabViews_changeView(int index);
    void tabParamViews_changeView(int index);

private:
    Ui::MainWindow *ui;
    QSqlDatabase sdb;
    QString dbfile;

    QSqlTableModel* modelTables;
    QStringListModel modelEmptyTables;
    QSqlQueryModel* modelViews;
    QStringListModel modelEmptyViews;
    QStringList listViewsSQL;
    QSqlQueryModel* modelParamViews;
    QStringListModel modelEmptyParamViews;
    QStringList listParamViewsSQL;
    std::vector<int> vectorParamViewsIntParams;
    std::vector<int> vectorParamViewsStrParams;
};
#endif // MAINWINDOW_H
