#include "dialogparamview.h"
#include "ui_dialogparamview.h"
// for debug output only
#include <iostream>

DialogParamView::DialogParamView(QWidget *parent, int num_Int, int num_Str) :
    QDialog(parent),
    numIntParams { num_Int },
    numStrParams { num_Str },
    ui(new Ui::DialogParamView)
{
    ui->setupUi(this);
    //std::vector<QPlainTextEdit*> editInt;
    //std::vector<QPlainTextEdit*> editStr;
    /*
        plainTextEditParam1 = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditParam1->setObjectName(QString::fromUtf8("plainTextEditParam1"));
        plainTextEditParam1->setGeometry(QRect(130, 70, 231, 31));
        plainTextEditParam0 = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditParam0->setObjectName(QString::fromUtf8("plainTextEditParam0"));
        plainTextEditParam0->setGeometry(QRect(130, 30, 231, 31));
        labelParam0 = new QLabel(scrollAreaWidgetContents);
        labelParam0->setObjectName(QString::fromUtf8("labelParam0"));
        labelParam0->setGeometry(QRect(20, 30, 101, 16));
        labelParam1 = new QLabel(scrollAreaWidgetContents);
        labelParam1->setObjectName(QString::fromUtf8("labelParam1"));
        labelParam1->setGeometry(QRect(20, 70, 101, 20));
        scrollArea->setWidget(scrollAreaWidgetContents);
    */
    editInt.clear();
    editStr.clear();

    std::vector<QLabel*> labels;
    std::vector<QPlainTextEdit*> edits;
    labels.push_back(ui->labelParam0);
    labels.push_back(ui->labelParam1);
    labels.push_back(ui->labelParam2);
    labels.push_back(ui->labelParam3);
    labels.push_back(ui->labelParam4);
    edits.push_back(ui->plainTextEditParam0);
    edits.push_back(ui->plainTextEditParam1);
    edits.push_back(ui->plainTextEditParam2);
    edits.push_back(ui->plainTextEditParam3);
    edits.push_back(ui->plainTextEditParam4);
    int total_inputs = 5;
    //std::cout << "got inputs: " << num_Int + num_Str  << std::endl;

    for (int i = 0; i < num_Int; i++) {
	labels[i]->setText(QString::fromUtf8("@INTEGER") + QString::number(i) + QString::fromUtf8("@"));
	edits[i]->setEnabled(true);
        editInt.push_back(edits[i]);
    }

    for (int i = 0; i < num_Str; i++) {
	labels[num_Int + i]->setText(QString::fromUtf8("@TEXT") + QString::number(i) + QString::fromUtf8("@"));
	edits[num_Int + i]->setEnabled(true);
        editStr.push_back(edits[num_Int + i]);
    }

    for (int i = num_Int + num_Str; i < total_inputs; i++) {
	labels[i]->setText(QString::fromUtf8(""));
	edits[i]->setEnabled(false);
    }

}

/*
QPlainTextEdit* DialogParamView::addInput(QString labelText, int offset, QWidget *scrollAreaWidgetContents)
{
        QLabel* labelParam = new QLabel(scrollAreaWidgetContents);
        labelParam->setObjectName(QString::fromUtf8("labelParam") + QString::number(offset));
        labelParam->setGeometry(QRect(20, 30 + 40 * offset, 101, 20));
	labelParam->setText(labelText);
        QPlainTextEdit* plainTextEditParam = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditParam->setObjectName(QString::fromUtf8("plainTextEditParam") + QString::number(offset));
        plainTextEditParam->setGeometry(QRect(130, 30 + 40 * offset, 231, 31));
	return plainTextEditParam;
}
*/

DialogParamView::~DialogParamView()
{
    delete ui;
}

QString DialogParamView::substParams(QString& sql) {
    for (int i = 0; i < numIntParams; i++) {
	//editInt[i]->getDocument()->toPlainText();
	sql.replace(QString::fromUtf8("@INTEGER") + QString::number(i) + QString::fromUtf8("@"), QString::number(1));
    }

    for (int i = 0; i < numStrParams; i++) {
	sql.replace(QString::fromUtf8("@TEXT") + QString::number(i) + QString::fromUtf8("@"), QString::fromUtf8(""));
    }

    return sql;
}
