#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogparamview.h"
#include<QMessageBox>
// for debug output only
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    dbfile = "lab2.dblite";
    open_DB();

    // fill Tables tab
    QStringList listTables;
    listTables << "";
    listTables << "Players" << "CharacterClasses" << "Characters" << "Teams" << "CharacterTeamConnections" << "Matches";
    ui->comboBoxTables->addItems(listTables);
    QStringList listEmptyTables;
    listEmptyTables << "Select table.";
    modelEmptyTables.setStringList(listEmptyTables);
    tabTables_changeView(listTables[0]);
    connect(ui->comboBoxTables, &QComboBox::currentTextChanged, this, &MainWindow::tabTables_changeView);

    // fill Views tab
    QStringList listViews;
    listViews << "";
    listViewsSQL << "";
    listViews << "команди, які приймали участь в матчі, їх бали";
    listViewsSQL << "SELECT A.teamname, B.teamname, score1, score2 FROM Matches, Teams AS A, Teams AS B ON team1id = A.ID AND team2id= B.ID;";
    listViews << "імена гравців, персонажі які приймали участь в матчах";
    listViewsSQL << "SELECT Players.name FROM Players WHERE ID IN (SELECT Characters.playerid FROM Characters WHERE Characters.ID IN (SELECT characterid FROM CharacterTeamConnections WHERE teamid IN (SELECT team1id FROM Matches) OR teamid IN (SELECT team2id FROM Matches)))";
    listViews << "унікальні пари персонажів з однаковим рівнем"; // (A.id < B.id щоб персонажі не повторювались)
    listViewsSQL << "SELECT A.ID, A.Name, B.ID, B.Name FROM Characters AS A, Characters AS B WHERE A.level = B.level AND A.id < B.id;";

    ui->comboBoxViews->addItems(listViews);
    QStringList listEmptyViews;
    listEmptyViews << "Select view.";
    modelEmptyViews.setStringList(listEmptyViews);
    tabViews_changeView(0);
    //connect(ui->comboBoxViews, &QComboBox::currentIndexChanged, this, &MainWindow::tabViews_changeView);
    //https://doc.qt.io/qt-5/qcombobox.html#currentIndexChanged
    connect(ui->comboBoxViews,
	    QOverload<int>::of(&QComboBox::currentIndexChanged),
	    this, &MainWindow::tabViews_changeView);

    // fill ParamViews tab
    QStringList listParamViews;
    listParamViews << "";
    listParamViewsSQL << "";
    vectorParamViewsIntParams.push_back(0);
    vectorParamViewsStrParams.push_back(0);
    listParamViews << "імена персонажів, які належать гравцям з поштою @TEXT0@";
    listParamViewsSQL << "SELECT Characters.name FROM Players LEFT JOIN Characters ON playerid = Players.ID WHERE Players.email = @TEXT0@";
    vectorParamViewsIntParams.push_back(0);
    vectorParamViewsStrParams.push_back(1);
    listParamViews << "імена гравців які мають персонажів з іменем @TEXT0@";
    listParamViewsSQL << "SELECT Players.name FROM Characters LEFT JOIN Players ON playerid = Players.ID WHERE Characters.name=@TEXT0@;";
    vectorParamViewsIntParams.push_back(0);
    vectorParamViewsStrParams.push_back(1);
    listParamViews << "пари імен персонажів рівень яких вище або дорівнює @INTEGER0@, та імена гравцім яким ці персонажі належать";
    listParamViewsSQL << "SELECT Players.name, Characters.name FROM Characters LEFT JOIN Players ON playerid = Players.ID WHERE Characters.level>=@INTEGER0@;";
    vectorParamViewsIntParams.push_back(1);
    vectorParamViewsStrParams.push_back(0);
    listParamViews << "імена гравців, які мають персонажів у команді з назвою @TEXT0@";
    listParamViewsSQL << "SELECT Players.name FROM Players WHERE ID IN (SELECT Characters.playerid FROM Characters WHERE Characters.ID IN (SELECT characterid FROM CharacterTeamConnections WHERE teamid IN (SELECT ID FROM Teams WHERE teamname=@TEXT0@)));";
    vectorParamViewsIntParams.push_back(0);
    vectorParamViewsStrParams.push_back(1);
    listParamViews << "імена гравців які мають персонажів з такими же классами як хоч один з персонажів гравця з ідом @INTEGER0@";
    listParamViewsSQL << "SELECT Players.name FROM Characters LEFT JOIN Players ON playerid=Players.ID WHERE classid IN ( SELECT classid FROM Characters WHERE playerid=@INTEGER0@ );";
    vectorParamViewsIntParams.push_back(1);
    vectorParamViewsStrParams.push_back(0);
    listParamViews << "імена гравців які мають персонажів з такими же классами як хоч один з персонажів гравця з ідом @INTEGER0@";
    listParamViewsSQL << "SELECT Players.name FROM Characters LEFT JOIN Players ON playerid=Players.ID WHERE classid IN ( SELECT classid FROM Characters WHERE playerid=@INTEGER0@ );";
    vectorParamViewsIntParams.push_back(1);
    vectorParamViewsStrParams.push_back(0);
    listParamViews << "ід та назви гравців, у яких кількість персонажів така сама як у гравця з ідом @INTEGER0@";
    listParamViewsSQL << "SELECT Players.ID, Players.name FROM Characters LEFT JOIN Players ON Players.id = playerid GROUP BY playerid HAVING COUNT(Characters.ID) in ( SELECT COUNT(ID) FROM Characters WHERE playerid = 1 );";
    vectorParamViewsIntParams.push_back(1);
    vectorParamViewsStrParams.push_back(0);

    ui->comboBoxParamViews->addItems(listParamViews);
    QStringList listEmptyParamViews;
    listEmptyParamViews << "Select view.";
    modelEmptyParamViews.setStringList(listEmptyParamViews);
    tabParamViews_changeView(0);
    //connect(ui->comboBoxParamViews, &QComboBox::currentIndexChanged, this, &MainWindow::tabParamViews_changeView);
    //https://doc.qt.io/qt-5/qcombobox.html#currentIndexChanged
    connect(ui->comboBoxParamViews,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &MainWindow::tabParamViews_changeView);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_DB()
{
    if(!QFile::exists(dbfile)) {
	QMessageBox::warning(this,"DB ","no DB file: " + dbfile ,QMessageBox::Ok,Qt::NoButton,Qt::NoButton);
	//QApplication::quit();
	return;
    }
    sdb.setDatabaseName(dbfile);
    if (!sdb.open()) {
	qDebug() << sdb.lastError().text();
	QMessageBox::warning(this,"DB ","Could not open DB file: " + dbfile + ". Error: " + sdb.lastError().text(),QMessageBox::Ok,Qt::NoButton,Qt::NoButton);
	QApplication::quit();
    }
    //modelViews = new QSqlTableModel();
    //modelParamViews = new QSqlTableModel();
}



void MainWindow::tabTables_changeView(const QString& tablename)
{
    if (!tablename.size()) {
	//std::cout << "got empty " << tablename.toStdString() << std::endl;
	ui->tableViewTables->setModel(&modelEmptyTables);
	ui->tableViewTables->show();
    } else {
	//std::cout << "got table " << tablename.toStdString() << std::endl;
	modelTables = new QSqlTableModel();
	modelTables->setTable(tablename);
	modelTables->select();
	modelTables->setEditStrategy(QSqlTableModel::OnFieldChange);

	ui->tableViewTables->setModel(modelTables);
	ui->tableViewTables->show();
    }
}

void MainWindow::tabViews_changeView(int index)
{
    //std::cout << "tabViews_changeView: got " << index << std::endl;
    if (!index) {
	//std::cout << "got empty " << index << std::endl;
	ui->tableViewViews->setModel(&modelEmptyViews);
	ui->tableViewViews->show();
    } else {
	modelViews = new QSqlQueryModel();
	QString SQL = listViewsSQL[index];
	modelViews->setQuery(SQL);
	ui->labelSQLTextViews->setText(SQL);
	ui->tableViewViews->setModel(modelViews);
	ui->tableViewViews->show();
    }
}

void MainWindow::tabParamViews_changeView(int index)
{
    if (!index) {
	//std::cout << "got empty " << index << std::endl;
	ui->tableViewParamViews->setModel(&modelEmptyParamViews);
	ui->tableViewParamViews->show();
    } else {
	//std::cout << "got p " << index << std::endl;
	QString ParamSQL = listParamViewsSQL[index];
	ui->labelSQLTextParamViews->setText(ParamSQL);
	QString SQL = tabParamViews_fillSQLParamsDialog(ParamSQL, vectorParamViewsIntParams[index], vectorParamViewsStrParams[index]);
	modelParamViews = new QSqlQueryModel();
	modelParamViews->setQuery(SQL);
	ui->tableViewParamViews->setModel(modelParamViews);
	ui->tableViewParamViews->show();
    }
}

QString MainWindow::tabParamViews_fillSQLParamsDialog(QString& param_sql, int num_Int, int num_Str)
{
    if (0 == num_Str && 0 == num_Int) {
	// nothing to do
	return param_sql;
    } else {
	DialogParamView *dialog = new DialogParamView(this, num_Int, num_Str);
	dialog->exec();
	QString SQL = dialog->substParams(param_sql);
	//delete dialog;
	return SQL;
    }
}
