<?php
var_dump(class_exists("QApplication"));


$x=new QApplication($argc,$argv);
$label = new QLabel("Qt is wonderful");
//app.setMainWidget(label);
$label->show();
$x->exec();

echo "all done";
