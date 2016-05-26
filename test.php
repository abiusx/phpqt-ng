<?php
var_dump(class_exists("QApplication"));

//TODO: since PhpQtNg classes are not inherited from each other,
//we can't call the parent call,set,get to handle "keys" that correspond
//to the parent Qt class, and thus at the moment the code is duplicated.
//
//Possible solution is to pass it along with the this object to a static function
//that can take parent of the Qt class, but then those static functions expect PhpQtNgBase 
//instead of QObject or etc.
//Think of something.
//
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