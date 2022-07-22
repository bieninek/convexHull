#ifndef GRAHAM_ALGORITHM_H
#define GRAHAM_ALGORITHM_H

#include <QObject>
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <QFile>
#include <QTextStream>
#include <QStack>
#include <QVector>
#include <QMessageBox>

#include "widget.h"

class grahamAlgorithm : public QObject
{
    Q_OBJECT
    QPoint p0; // initial point, used to estimate distances
    QVector<QPoint> points;

public:
    explicit grahamAlgorithm(QObject *parent = nullptr);
    static void clearTextFile(QString);
    void addPoint(QString, int, int);
    void createHull();
    QPoint nextToTop(QStack<QPoint>&);
    int dist(QPoint, QPoint);
    int orientation(QPoint, QPoint, QPoint);
    bool sortRule(QPoint, QPoint);
    void swap(QPoint &, QPoint &);

signals:

};

#endif // GRAHAM_ALGORITHM_H
