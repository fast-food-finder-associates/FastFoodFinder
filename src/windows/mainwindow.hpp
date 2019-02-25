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
    void on_actionLogout_triggered();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::MainWindow* m_ui;
    unsigned int m_selected;
};
