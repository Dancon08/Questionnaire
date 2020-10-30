#ifndef ExportHelper_HPP
#define ExportHelper_HPP

#include <QString>

class QAbstractItemModel;
class QWidget;

class ExportHelper
{
public:
    ExportHelper();

    static void exportToCsv(QAbstractItemModel* model, const QString& filename);
    static void exportToPdf(QWidget *widget, const QString& filename);
private:
};

#endif // ExportHelper_HPP
