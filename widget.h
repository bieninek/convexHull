#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    bool m_flag;
    bool hull_flag;
    bool pt_flag;
    int num_amount;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setHull(bool);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButtonDraw_clicked();

    void on_pushButtonConvex_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
