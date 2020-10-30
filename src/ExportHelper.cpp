#include "ExportHelper.hpp"

#include <QAbstractItemModel>
#include <QWidget>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QTextCursor>

ExportHelper::ExportHelper()
{

}

void ExportHelper::exportToCsv(QAbstractItemModel* model, const QString& filename)
{
    if( !model )
        return;


    QString textData = QString{"%1, %2, %3\n"}.arg(model->headerData(0, Qt::Horizontal).toString())
            .arg(model->headerData(1, Qt::Horizontal).toString()
                 .arg(model->headerData(2, Qt::Horizontal).toString()));

    int rows = model->rowCount();
    int columns = model->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            textData += model->data(model->index(i,j)).toString();
            textData += ", ";      // for .csv file format
        }
        textData += "\n";             // (optional: for new line segmentation)
    }

    QFile csvFile(filename);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}

void ExportHelper::exportToPdf(QWidget* widget, const QString &filename)
{
    QPixmap pix(widget->size());
    QPainter painter(&pix);
    widget->render(&painter);
    painter.end();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(filename); // will be in build folder

    painter.begin(&printer);
    double xscale = printer.pageRect().width() / double(pix.width());
    double yscale = printer.pageRect().height() / double(pix.height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                      printer.paperRect().y() + printer.pageRect().height() / 2);
    painter.scale(scale, scale);
    painter.translate(-widget->width() / 2, -widget->height() / 2);
    painter.drawPixmap(0, 0, pix);

    QTextDocument doc;

    //doc.setHtml("htmlcontent");
    doc.drawContents(&painter);

    painter.end();
}
