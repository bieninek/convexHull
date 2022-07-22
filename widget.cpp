#include "widget.h"
#include "ui_widget.h"
#include "graham_algorithm.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    pt_flag = false;
    m_flag = false;
    hull_flag = false;
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setHull(bool newFlag)
{
    hull_flag = newFlag;
}


void Widget::on_pushButtonDraw_clicked()
{
    int amount = ui->lineEditNumPoint->text().toInt();
    qDebug() << "points number: " << amount;

    grahamAlgorithm::clearTextFile("points.txt");
    grahamAlgorithm::clearTextFile("hull_pt.txt");

    m_flag = true;
    this->num_amount = amount;
    this->update();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    grahamAlgorithm obj;

    // ======================
    // write initial points
    // ======================
    if (m_flag)
    {
        painter.setPen(QPen(QColor(0,50,250, 200), 10, Qt::SolidLine, Qt::RoundCap));
        painter.setCompositionMode(QPainter::CompositionMode_Source);

        int temp_x, temp_y;
        while (num_amount > 0)
        {
            temp_x = rand() % 540 + 50;
            temp_y = rand() % 540 + 50;

            painter.drawPoint(temp_x, temp_y);
            obj.addPoint("points.txt", temp_x, temp_y);

            --num_amount;
        }
        m_flag = false;
        obj.createHull();
    }

    // ======================
    // write convex hull and points
    // ======================
    if (hull_flag)
    {
        // ======================
        // write only convex hull
        // ======================
        QVector<QPoint> pts; // keeps vertexes of the polygon

        // open from file
        QFile file("hull_pt.txt");
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

        QTextStream in(&file);
        while(!in.atEnd()) {
            int pt_x = in.readLine().toInt();
            int pt_y = in.readLine().toInt();
            pts.push_back(QPoint(pt_x, pt_y));
        }
        file.close();

        // print points to debug
        qDebug() << pts;

        // convert to array...
        QPoint pts_arr[pts.size()];
        for (int i{}; i < pts.size(); i++)
            pts_arr[i] = pts[i];

        // draw convex hull
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.drawConvexPolygon(pts_arr, pts.size());

        // ======================
        // write initial points
        // ======================

        // open from file
        QFile file2("points.txt");
        if(!file2.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

        QTextStream in2(&file2);
        while(!in2.atEnd()) {
            int pt_x = in2.readLine().toInt();
            int pt_y = in2.readLine().toInt();
            pts.push_back(QPoint(pt_x, pt_y));
        }
        file2.close();

        // set pen to proper display format
        painter.setPen(QPen(QColor(0,50,250, 200), 10, Qt::SolidLine, Qt::RoundCap));

        // draw points
        for(QVector<QPoint>::Iterator it = pts.begin(); it != pts.end(); ++it)
            painter.drawPoint(it->x(), it->y());

        // prevent from executing again
        hull_flag = false;
    }

}


void Widget::on_pushButtonConvex_clicked()
{
    hull_flag = true;
    this->update();
}

