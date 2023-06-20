#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void buttonClicked();
private:
    QPushButton *buttons[3][3];
    void computerMove();
    bool checkWin();
};

#endif // MAINWINDOW_H
