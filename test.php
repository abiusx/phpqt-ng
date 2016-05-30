<?php
assert(class_exists("QApplication"));

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
$r=connect($button,"clicked",function(){echo "hello there!\n";});
var_dump($r);
$r=connect($button,"clicked",'f',[1,2,3,'k'=>'v']);
var_dump($r);


$window = new QWidget;
$window->setLayout($layout);
$window->show();

$app->exec();

echo "all done";

function f($args)
{
	echo "F called with: ";
	var_dump($args);
}

