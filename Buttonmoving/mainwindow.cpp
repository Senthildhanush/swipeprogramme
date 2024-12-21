#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentButtonIndex(0)
    , swipeDirection(0) // Initialize swipeDirection
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize buttons
    buttons[0] = ui->pushButton_1;
    buttons[1] = ui->pushButton_2;
    buttons[2] = ui->pushButton_3;
    buttons[3] = ui->pushButton_4;

    // Set the initial button state
    updateButtonState();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();
    qDebug()<<"Mouse pressed";
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{


    // Detect swipe direction
    if (event->buttons() & Qt::LeftButton) {
        int deltaX = event->pos().x() - lastMousePosition.x();

        if (deltaX > 10) { // Swipe right

            swipeDirection = 1;
           qDebug()<<"swiped";

        } else if(deltaX < -10) { // Swipe left
            swipeDirection = -1;
              qDebug()<<"swiped";
        }
    }
    lastMousePosition = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Update button index based on swipe direction
    if (swipeDirection == 1) { // Swipe right
        if (currentButtonIndex < 3) {
            currentButtonIndex++;
               qDebug() << "Swiped right, new index:" << currentButtonIndex;
        }
    } else if (swipeDirection == -1) { // Swipe left
        if (currentButtonIndex > 0) {
            currentButtonIndex--;
             qDebug() << "Swiped left, new index:" << currentButtonIndex;
        }
    }

    updateButtonState();
    swipeDirection = 0; // Reset swipe direction
}

void MainWindow::updateButtonState()
{
    // Enable/disable buttons based on the current index
    for (int i = 0; i < 4; i++) {
        buttons[i]->setEnabled(i == currentButtonIndex);
         qDebug() << "Button" << i << "enabled:" << (i == currentButtonIndex);
    }

    buttons[currentButtonIndex]->click(); // Simulate button click
}
