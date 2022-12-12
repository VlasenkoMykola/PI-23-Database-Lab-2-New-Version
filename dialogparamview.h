#ifndef DIALOGPARAMVIEW_H
#define DIALOGPARAMVIEW_H

#include <QDialog>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class DialogParamView;
}
QT_END_NAMESPACE

class DialogParamView : public QDialog
{
    Q_OBJECT

public:
    explicit DialogParamView(QWidget *parent = nullptr, int num_Int = 0, int num_Str = 0);
    ~DialogParamView();
    QString substParams(QString& sql);
    /*
    QPlainTextEdit* addInput(QString labelText, int offset, QWidget *scrollAreaWidgetContents);
    */
private:
    int numIntParams;
    int numStrParams;
    std::vector<QPlainTextEdit*> editInt;
    std::vector<QPlainTextEdit*> editStr;
    Ui::DialogParamView *ui;
};

#endif // DIALOGPARAMVIEW_H
