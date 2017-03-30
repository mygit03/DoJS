#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueList>
#include <QScriptEngineDebugger>        //调试类
#include <QMainWindow>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit_var1->setText("12");
    ui->lineEdit_var2->setText("0.5");
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
        qWarning() << "TransCal.js open failed";
        return;
    }
    QTextStream out(&scriptFile);
    QString contents = out.readAll();
    scriptFile.close();

    QScriptEngine engine;
    //启动调试JS脚本
    QScriptEngineDebugger *debug =  new QScriptEngineDebugger;
    debug->attachTo(&engine);
#if 0
    debug->standardWindow();
#else
    QMainWindow *win = debug->standardWindow();
//    win->resize(900,600);
    win->showMaximized();
#endif
    //end
    QScriptValue js = engine.evaluate(contents);        //个人理解：加载js文本到操作引擎
    QScriptValue ai = engine.newArray(10);
    QScriptValue bi = engine.newArray(10);
    for(int i = 0; i < 10; i++){
        ai.setProperty(i,i+2);
    }
    QScriptValueList args;      //调用js方法时传入的参数
    args << ai << bi;
    QScriptValue func;
    func = engine.globalObject().property("trans2wCal");   //调用js方法
    result = func.call(QScriptValue(), args).toString();
    qDebug() << "var1:" << ai.toString() << bi.toString();
    QStringList strList = result.split(',');
    for(int i = 0; i < strList.size(); ++i){
        QString tmp = strList.at(i);
        qDebug() << tmp.toDouble();
    }
//    func.call(QScriptValue(), args);
//    QScriptEngine enginesss;
//    QScriptValue func1 = enginesss.globalObject();
//    QScriptValue ddd = func1.property("result");
    QList<int> list22 = qscriptvalue_cast<QList<int>>(bi);
    for(int i = 0; i < list22.size(); ++i){
        qDebug() << "qqq:" << list22.at(i);
    }
    qDebug() << "result:" << result << bi.toString();
    ui->lineEdit_sub->setText(result);

    double var1 = ui->lineEdit_var1->text().toDouble();
    double var2 = ui->lineEdit_var2->text().toDouble();
    qDebug() << "var1:" << var1 << "var2:" << var2;

    args.clear();
    args << var1 << var2;
    func = engine.globalObject().property("trans3wCal");   //调用js方法
    result = func.call(QScriptValue(), args).toString();
    qDebug() << "result:" << result;
    ui->lineEdit_mul->setText(result);

    func = engine.globalObject().property("pdAdd");   //调用js方法
    args.clear();
    args << "JG";
    result = func.call(QScriptValue(), args).toString();
    qDebug() << "result:" << result;
    ui->lineEdit_mul->setText(result);
}

void Widget::on_btn_cal_clicked()
{
    readJS();
}
