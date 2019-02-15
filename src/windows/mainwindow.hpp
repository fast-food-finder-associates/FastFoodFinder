#pragma once
#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* Constructors */
    MainWindow();

    /* Destructor */
    ~MainWindow() override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow* m_ui;
};
