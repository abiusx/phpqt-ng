<?php
var_dump(class_exists("QApplication"));

class QA extends QApplication
{
	public $alive=false;
	public $dead=true;
}

$x=new QA($argc,$argv);
var_dump($x->alive);
$x->exec();

echo "all done";
