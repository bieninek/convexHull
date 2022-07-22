#include "graham_algorithm.h"

grahamAlgorithm::grahamAlgorithm(QObject *parent) : QObject(parent)
{

}

void grahamAlgorithm::clearTextFile(QString filename)
{
    QFile file (filename);
        file.remove();
}

void grahamAlgorithm::addPoint(QString filename, int a, int b)
{
    QFile file(filename);
    if (file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        stream << a << endl;
        stream << b << endl;
    }
}

void grahamAlgorithm::createHull()
{
    // read from file
    QFile file("points.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        int pt_x = in.readLine().toInt();
        int pt_y = in.readLine().toInt();
        points.push_back(QPoint(pt_x, pt_y));
    }
    file.close();

    qDebug() << points;


   // the bottom point
   int ymin = points.at(0).y(), min = 0;
   for (int i{1}; i < points.size(); i++)
   {
     int y = points.at(i).y();

     // bottomest or the most left
     if ((y < ymin) || (ymin == y && points.at(i).x() < points.at(min).x()))
        ymin = points.at(i).y(), min = i;
   }
   swap(const_cast<QPoint&>(points.at(0)), const_cast<QPoint&>(points.at(min)));


   // my bubble sort
   this->p0 = points.at(0);
   for (int i{0}; i < points.size() - 1; i++)
       for (int j{0}; j < points.size() - i - 1; j++)
           if (sortRule(points.at(j), points.at(j + 1)))
               swap(const_cast<QPoint&>(points.at(j)), const_cast<QPoint&>(points.at(j + 1)));

   int m{1};
   for (int i{1}; i < points.size(); i++)
   {
       while (i < points.size()-1 && orientation(this->p0, points.at(i), points.at(i + 1)) == 0)
          i++;

       const_cast<QPoint&>(points.at(m)) = points.at(i);
       m++;
   }

   // exception?
   if (m < 3) return;

   QStack<QPoint> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   for (int i{3}; i < m; i++)
   {
      while (S.size()>1 && orientation(nextToTop(S), S.top(), points.at(i)) != 2)
         S.pop();
      S.push(points.at(i));
   }

   while (!S.empty())
   {
       QPoint p = S.top();
       qDebug() << p;
       addPoint("hull_pt.txt", p.x(), p.y());
       S.pop();
   }
}

QPoint grahamAlgorithm::nextToTop(QStack<QPoint> &S)
{
    QPoint p = S.top();
    S.pop();
    QPoint res = S.top();
    S.push(p);
    return res;
}

int grahamAlgorithm::dist(QPoint p1, QPoint p2)
{
    return (p1.x() - p2.x())*(p1.x() - p2.x()) +
            (p1.y() - p2.y())*(p1.y() - p2.y());
}


int grahamAlgorithm::orientation(QPoint p, QPoint q, QPoint r)
{
    int val = (q.y() - p.y()) * (r.x() - q.x()) -
                  (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;  // collinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool grahamAlgorithm::sortRule(QPoint p1, QPoint p2)
{
   // Find orientation
   int o = orientation(p0, p1, p2);
   if (o == 0)
     return (dist(p0, p2) >= dist(p0, p1))? false : true;

   return (o == 2)? false : true;
}


void grahamAlgorithm::swap(QPoint &p1, QPoint &p2)
{
    QPoint temp = p1;
    p1 = p2;
    p2 = temp;
}


