#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit_var1->setText("12");
    ui->lineEdit_var2->setText("0.5");

//    readJS();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readJS()
{
    QString result = "";
    QFile scriptFile(":/TransCal.js");
    if (!scriptFile.open(QIODevice::ReadOnly))
    {
        result.clear();
        qWarning() << "encodePass.js open failed";
        return;
    }
    QTextStream out(&scriptFile);
    QString contents = out.readAll();
    scriptFile.close();

    double var1 = ui->lineEdit_var1->text().toDouble();
    double var2 = ui->lineEdit_var2->text().toDouble();
    qDebug() << "var1:" << var1 << "var2:" << var2;

    QScriptValueList args;      //调用js方法时传入的参数
    args << QScriptValue(var1) << QScriptValue(var2);
    QScriptEngine engine;
    QScriptValue js = engine.evaluate(contents);        //个人理解：加载js文本到操作引擎
    QScriptValue func;
    func = engine.globalObject().property("trans2wCal");   //调用js方法
    result = func.call(QScriptValue(), args).toString();
    qDebug() << "result:" << result;
    ui->lineEdit_sub->setText(result);

    func = engine.globalObject().property("trans3wCal");   //调用js方法
    result = func.call(QScriptValue(), args).toString();
    qDebug() << "result:" << result;
    ui->lineEdit_mul->setText(result);
}

void Widget::on_btn_cal_clicked()
{
    readJS();
}
