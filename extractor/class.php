<?php
require "config.php";

$url=qt_doc_url();




function findClasses($url)
{
	$res=curl($url."/classes.html");
	$classes=[];
	preg_match_all('/<dd><a\s+href="(.*?).html">(.*?)<\/a><\/dd>/', $res, $matches,PREG_SET_ORDER);
	foreach ($matches as $match)
		$classes[$match[1]]=$match[2];
	file_put_contents("out/classes.txt",'<'.'?php return'.PHP_EOL.var_export($classes,true).";");
}


function findClass($class,$url)
{
	$res=curl($url);

	if (!preg_match('/Inherits:.*?<a.*?">(.*?)<\/a>/ims', $res,$match))
		$parent="";
	else
		$parent=$match[1];
	// echo "Parent is: {$parent}",PHP_EOL;
	if (!preg_match('/<h2 id="public-functions.*?<table(.*?)<\/table>/ims',$res,$rest))
		return false;

	$rest=htmlspecialchars_decode($rest[1]);
	if (!preg_match_all('/<td class=".*?">(.*?)<\/td><td class=".*?"><b><a href="(.*?)">(.*?)<\/a><\/b>(.*?)<\/td>/ims',$rest,$matches,PREG_SET_ORDER))
		return false;
	#1 is return type
	#2 is url
	#3 is function name
	#4 is params and modifiers
	
	$methods=[];
	foreach ($matches as $match)
	{
		$name=trim($match[3]);
		$return=trim($match[1]);
		if (!preg_match("/\((.*?)\)(.*)/ims",$match[4],$res))
			return false;
		$args=$res[1];
		$argz=explode(",",$args);
		$modifiers=explode(" ",trim($res[2]));
		$modifiers=array_filter(array_map("trim",$modifiers));
		$args=[];
		foreach ($argz as $arg)
		{
			if (!$arg) continue;
			$a=[];
			if (preg_match("/<i>(.*?)<\/i>/i", $arg,$res))
				$a['name']=trim($res[1]);
			else
				$a['name']="";
			if (strpos($arg, "=")!==false)
				$a['default']=trim(substr($arg,strpos($arg,"=")+1));
			if ($a['name'])
				$a['type']=trim(substr($arg,0,strpos($arg,"<i>")));
			else
				$a['type']=trim($arg);

			$a['const']=strpos($a['type'], "const")===0;
			$a['pointer']=substr($a['type'],-1)=="*";
			$a['reference']=substr($a['type'],-1)=="&";
			$a['rawtype']=$a['type'];
			if ($a['const'])
				$a['type']=substr($a['type'],6);
			if ($a['pointer'] or $a['reference'])
				$a['type']=substr($a['type'],0,-2);
			$args[]=$a;
			// var_dump($name);
			// var_dump($arg);
			// var_dump($args);
			
		}
		// $args=array_map("trim", $args);
		if (!isset($methods[$name]))
			$methods[$name]=[];
		$methods[$name][]=["return"=>$return,"args"=>$args,"modifiers"=>$modifiers];
	}
	$all=["name"=>$class,"parent"=>$parent,"methods"=>$methods];
	// print_r($methods);
	$code='<'.'?php return '.var_export($all,true).';';
	file_put_contents("out/class_{$class}.txt", $code);

	return true;
}

function findAllClasses($url)
{

	file_exists(__DIR__."/out/classes.txt") or findClasses($url);

	$classes=include "out/classes.txt";
	$index=0;
	foreach ($classes as $key=>$class)
	{
		$index++;
		echo $index,"of",count($classes),". Fetching class '$class'... ";
		if (!file_exists("out/class_{$class}.txt"))
		{
			$r=findClass($class,"$url/$key.html");
			var_dump($r);
		}
		else
			echo "already available.",PHP_EOL;
	}
}

function _methodInstanceCode($methodName,$methodInstance,$count)
{
	$instance_code="";
	$argCount=count($methodInstance['args']);
	if ($count>1)
		$instance_code.="if ( params.size() == $argCount )\n\t\t\t";
	$instance_code.="return q->{$methodName}(";
	$args=[];
	if ($methodInstance['args'])
	{

		$instance_code.=" ";
		$index=0;
		//loop over arguments
		foreach ($methodInstance['args'] as $arg)
		{
			$type=$arg['type'];
			if ($type=="QString")
				$a="QString(params[$index])";
			elseif ($arg['pointer'] and strlen($type)>3 and $type[0]=="Q" and ctype_upper($type[1]))
				$a="PARAM_QTYPE($type, param[$index])";
			elseif ($arg['const'] and $arg['reference'] and strlen($type)>3 and $type[0]=="Q" and ctype_upper($type[1]))
				$a="{$type}(param[$index])";
			elseif ($type)
			{
				$a="({$type})params[$index]";
			}
			else
				$a="params[$index]";
			$args[]=$a;
			$index++;
		}
	}
	$instance_code.=implode(" , ",$args)." );";
	return $instance_code;
}
function generateWrapper($class)
{
	#TODO: handle constructors
	#TODO: consider default args
	$info=include "out/class_{$class}.txt";
	$constructor_code="";
	$methods_code="\t";
	//loop over methods
	foreach ($info['methods'] as $method_name=>$method_overrides)
	{
		if ($method_name=="~".$class) continue; //destructor
		if ($method_name!=$class) //not constructor
			$methods_code.="if ( name == '{$method_name}' )\n";
		$overrides_code=[];
		//loop over overrides of each method
		foreach ($method_overrides as $method_override)
			$overrides_code[]=_methodInstanceCode($method_name,$method_override,count($method_overrides));

		if ($method_name==$class)
			$constructor_code.=implode("\n\telse ",$overrides_code)."\n\telse ";
		else
			$methods_code.="\t\t".implode("\n\t\telse ",$overrides_code)."\n\telse ";
		// $methods_code[]=$method_code;
	}
	$methods_code=substr($methods_code,0,-6);
	$constructor_code=str_replace("return q->","q = new ",$constructor_code);
	$constructor_code=substr($constructor_code,0,-6);
	$code=<<<X
#include "phpqtng.h"
#define QtParentClass	{$info['parent']}
#define QtClass		{$info['name']}

#define ME		QNAME(QtClass)
#define PARENT		QNAME(QtParentClass)

void ME::__construct(Php::Parameters &params)
{   
	{$constructor_code}
    //q=new {$class}();

}
Php::Value ME::get(const Php::Value &name, QtClass *q)
{
    return PARENT::get(name,q);
}
void ME::set(const Php::Value &name, const Php::Value &value, QtClass *q)
{
    PARENT::set(name,value,q);
}
Php::Value ME::call(const string name, Php::Parameters &params, QtClass *q)
{
{$methods_code}
	return PARENT::call(name,params,q);
}
Php::Value ME::__callStatic(const char *_name, Php::Parameters &params)
{
    return nullptr;
}
X;
var_dump($code);
}
// findAllClasses($url);
// $r=findClass("Q3CacheIterator","$url/q3cacheiterator.html");
// var_dump($r);
// findClass("Q3Action","$url/q3action.html");
// findClass("Q3Http","$url/q3http.html");
// $r=findClass("QWidget","$url/qwidget.html");
generateWrapper("QWidget");

