<?php
var_dump(class_exists("QApplication"));


$app=new QApplication($argc,$argv);

$label = new QLabel("Qt is wonderful");
$button = new QPushButton("&Quit");
$layout=new QVBoxLayout;
$layout->addWidget($label);
$layout->addWidget($button);
$r=$button->connect($button,"clicked()",$app,"quit()");
var_dump($r);
$r=$button->connect($button,"clicked()",$app,"quit()");
var_dump($r);

$window = new QWidget;
$window->setLayout($layout);
$window->show();

$app->exec();

echo "all done";

/*
 6
 7          QLabel *textEdit = new QLabel;
 8          QPushButton *quitButton = new QPushButton("&Quit");
 9
10          QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
11
12          QVBoxLayout *layout = new QVBoxLayout;
13          layout->addWidget(textEdit);
14          layout->addWidget(quitButton);
15
16          QWidget window;
17          window.setLayout(layout);
18
19          window.show();
20
21          return app.exec();

*/