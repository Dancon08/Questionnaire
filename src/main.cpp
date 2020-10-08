#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

void setQSS(QApplication& app)
{
    app.setStyleSheet(R"(
                      QWidget {
                      font-family: Source Sans Pro;
                      }

                      QMainWindow{
                      background: #ffffff;
                      }

                      QRadioButton{
                      color: #000000;
                      }
                      QRadioButton::indicator::unchecked {
                      image: url(:/resources/radiobutton_unchecked.png);
                      }
                      QRadioButton::indicator::checked {
                      image: url(:/resources/radiobutton_checked.png);
                      }
                      QLineEdit{
                      background: #ffffff;
                      color: #000000;
                      }
                      QLabel{
                      color: #000000
                      }

                      QMainWindow::separator {
                      background: #ffffff;
                      width: 10px; /* when vertical */
                      height: 10px; /* when horizontal */
                      }
                      QDialog{
                      background: #ffffff;
                      }
                      QCheckBox{
                      color: white;
                      }
                      QGroupBox{
                      color: white;
                      }


                      #centralwidget {
                      background: #ffffff;
                      }
                      #startPage
                      {
                      background: #ffffff;
                      }
                      #questionsPage
                      {
                      background: #ffffff;
                      }
                      #resultsPage
                      {
                      background: #ffffff;
                      }

                      QScrollBar:horizontal {
                      /*border: 1px solid #313131;*/
                      background: #3f3f47;
                      height: 11px;
                      margin: 0px 20px 0 20px;
                      }
                      QScrollBar::handle:horizontal {
                      background: #545569;
                      width: 44px;
                      height: 11px;
                      /*border: 1px solid #313131;*/
                      border-radius: 5px;
                      }
                      QScrollBar::add-line:horizontal {
                      /*border: 1px solid 313131;*/
                      background: #3f3f47;
                      width: 20px;
                      subcontrol-position: right;
                      subcontrol-origin: margin;
                      }

                      QScrollBar::sub-line:horizontal {
                      /*border: 1px solid 313131;*/
                      background: #3f3f47;
                      width: 20px;
                      subcontrol-position: left;
                      subcontrol-origin: margin;
                      }

                      QScrollBar::sub-page:horizontal, QScrollBar::add-page:horizontal  {
                      background: #3f3f47;
                      }

                      QScrollBar::left-arrow:horizontal {
                      image: url(:/toolbar/mode/left);
                      }

                      QScrollBar::right-arrow:horizontal {
                      image: url(:/toolbar/mode/right);
                      }

                      QScrollBar:vertical {
                      /*border: 1px solid #313131;*/
                      background: #ffffff;
                      width: 11px;
                      }
                      QScrollBar::handle:vertical {
                      background: #686868;
                      width: 11px;
                      min-height: 20px;
                      /*border: 1px solid #313131;*/
                      border-radius: 5px;
                      }
                      QScrollBar::add-line:vertical {
                      /*border: 1px solid 313131;*/
                      background: #ffffff;
                      height: 20px;
                      subcontrol-position: bottom;
                      subcontrol-origin: margin;
                      }

                      QScrollBar::sub-line:vertical {
                      /*border: 1px solid 313131;*/
                      background: #ffffff;
                      height: 20px;
                      subcontrol-position: top;
                      subcontrol-origin: margin;
                      }

                      QScrollBar::sub-page:vertical, QScrollBar::add-page:vertical  {
                      background: #ffffff;
                      }




                      QTableView{
                      background: #ffffff;
                      color: #000000;
                      }

                      QHeaderView::section {
                      background-color: #ffffff;

                      color: #000000;

                      }
                      )");
}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication app(argc, argv);

    setQSS(app);

    MainWindow w;
    w.show();
    return app.exec();
}
