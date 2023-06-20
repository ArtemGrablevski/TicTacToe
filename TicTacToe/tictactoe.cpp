#include <QGridLayout>
#include <QMessageBox>

#include <cstdlib>
#include <ctime>

#include "tictactoe.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QGridLayout *layout = new QGridLayout();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            buttons[i][j] = new QPushButton(this);
            buttons[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttons[i][j]->setFont(QFont("Arial", 70));
            buttons[i][j]->setFixedSize(150, 150);
            layout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::buttonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    bool isEnd;
    if (button) {
        button->setText("X");
        button->setStyleSheet("color: #16dbff; font-weight: bold;");
        button->setEnabled(false);
        isEnd = checkWin();
        if (!isEnd) {
            computerMove();
            checkWin();
        }
    }
}

void MainWindow::computerMove() {
    srand(time(0));
    QVector<QPushButton*> freeButtons;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (buttons[i][j]->text() == "") {
                freeButtons.push_back(buttons[i][j]);
            }
        }
    }
    int computerChoice = rand() % freeButtons.size();
    freeButtons[computerChoice]->setText("O");
    freeButtons[computerChoice]->setStyleSheet("color: #FF0062; font-weight: bold;");
    freeButtons[computerChoice]->setEnabled(false);
}

bool MainWindow::checkWin() {
    QString message;
    const int winCoordinates[8][3] = {
        {0, 1, 2},
        {0, 3, 6},
        {3, 4, 5},
        {6, 7, 8},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    for (const auto& coordinates : winCoordinates) {
        const QString& text1 = buttons[coordinates[0] / 3][coordinates[0] % 3]->text();
        const QString& text2 = buttons[coordinates[1] / 3][coordinates[1] % 3]->text();
        const QString& text3 = buttons[coordinates[2] / 3][coordinates[2] % 3]->text();

        if (text1 == text2 && text2 == text3 && !text1.isEmpty()) {
            message = text1 + " wins!";
            break;
        }
    }

    if (message.isEmpty()) {
        bool full = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (buttons[i][j]->text().isEmpty()) {
                    full = false;
                    break;
                }
            }
            if (!full) {
                break;
            }
        }
        if (full) {
            message = "It's a tie!";
        }
    }

    if (!message.isEmpty()) {
        QMessageBox::information(this, "Game Over", message);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                buttons[i][j]->setText("");
                buttons[i][j]->setEnabled(true);
            }
        }
        return true;
    }
    return false;
}
