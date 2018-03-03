#include<QApplication>
#include<QObject>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QEvent>
#include<QDebug>

int main(int argc, char* argv[]){
    QApplication a(argc,argv);
    QWidget *window = new QWidget(nullptr);
    window->setWindowTitle("Bienvenido a Qt");
    QVBoxLayout *layout = new QVBoxLayout(window);
    layout->setMargin(20);
    window->setLayout(layout);
    QLabel *label = new QLabel(window);
    label->setText("Hola Mundo");
    layout->addWidget(label);
    QPushButton *button = new QPushButton(window);
    button->setText("Exit");
    layout->addWidget(button);
    button->connect(button,&QPushButton::clicked, [&](){a.exit(0);});
    window->setVisible(true);
    return a.exec();
}
