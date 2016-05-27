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

/**
 * Converts a string arg representation into an array of arg parts
 * @param  [type] $arg [description]
 * @return [type]      [description]
 */
function parseArg($arg)
{
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
	return $a;
}
/**
 * Extracts information regarding one class from the HTML docs
 * @param  [type] $class [description]
 * @param  [type] $url   [description]
 * @return [type]        [description]
 */
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
			$args[]=parseArg($arg);
		}
		// $args=array_map("trim", $args);
		if (!isset($methods[$name]))
			$methods[$name]=[];
		$methods[$name][]=["return"=>parseArg($return),"args"=>$args,"modifiers"=>$modifiers];
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

// function _methodInstanceCode($methodName,$methodInstance,$count)
// {
// 	$instance_code="";
// 	$argCount=count($methodInstance['args']);
// 	if ($count>1)
// 		$instance_code.="if ( params.size() == $argCount )\n\t\t\t";
// 	$instance_code.="return q->{$methodName}(";
// 	$args=[];
// 	if ($methodInstance['args'])
// 	{

// 		$instance_code.=" ";
// 		$index=0;
// 		//loop over arguments
// 		foreach ($methodInstance['args'] as $arg)
// 		{
// 			$type=$arg['type'];
// 			if ($type=="QString")
// 				$a="QString(params[$index])";
// 			elseif ($arg['pointer'] and strlen($type)>3 and $type[0]=="Q" and ctype_upper($type[1]))
// 				$a="PARAM_QTYPE($type, param[$index])";
// 			elseif ($arg['const'] and $arg['reference'] and strlen($type)>3 and $type[0]=="Q" and ctype_upper($type[1]))
// 				$a="{$type}(param[$index])";
// 			elseif ($type)
// 			{
// 				$a="({$type})params[$index]";
// 			}
// 			else
// 				$a="params[$index]";
// 			$args[]=$a;
// 			$index++;
// 		}
// 	}
// 	$instance_code.=implode(" , ",$args)." );";
// 	return $instance_code;
// }

/**
 * Determines whether a type is a QtType or not
 * @param  [type]  $type [description]
 * @return boolean       [description]
 */
function isQtType($type)
{
	return (strlen($type)>3 and $type[0]=="Q" and ctype_upper($type[1]));
}
/**
 * Typecasts a function argument (parameter)
 * @param  [type] $paramIndex [description]
 * @param  [type] $arg        [description]
 * @return [type]             [description]
 */
function typecastParam($paramIndex,$arg)
{
	$type=$arg['type'];
	if ($type=="QString")
		$a="QString(params[$paramIndex])";
	elseif ($arg['pointer'] and isQtType($type))
		$a="PARAM_QTYPE($type,param[$paramIndex])";
	elseif ($arg['const'] and $arg['reference'] and isQtType($type))
		$a="{$type}(param[$paramIndex])";
	elseif ($type)
	{
		$a="({$type})params[$paramIndex]";
	}
	else
		$a="params[$paramIndex]";
	return $a;
}
function typehintParam($paramIndex,$arg)
{

}
function typehint($arg)
{
	$Type=$arg['type'];
	$type=strtolower($Type);
	if ($type=="int" or $type=="long" or $type=="ulong" or $type=="ulong16" or $type=="ulong32" or $type=="uint"
		or $type=="uint16" or $type=="uint32" or $type=="short" or $type=="ushort")
		return "Numeric";
	elseif ($type=="qstring" or ($type=="char" and $arg['pointer']) or $type=="string")
		return "String";
	elseif (isQtType($Type))
		return "Object";
	elseif ($type=="float" or $type=="double")
		return "Float";
	elseif ($type=="qlist" or $type=="vector" or $type=="qvector")
		return "Array";
	else
		trigger_error("Could not find a suitable typehint for '{$Type} ({$arg['rawtype']}'.");
	return "Numeric";

// Php::Type::Null
// Php::Type::Bool
// Php::Type::Array
// Php::Type::Resource
// Php::Type::Constant
// Php::Type::ConstantArray
// Php::Type::Callable
}
/**
 * Prepares arguments of a function into a code line
 * @param  [type] $args     [description]
 * @param  [type] $argCount [description]
 * @return [type]           [description]
 */
function prepareArgs($args,$argCount)
{
	if ($argCount==0 or !$args) return "";
	$argz=[];
	for ($i=0;$i<$argCount;++$i)
		$argz[]=typecastParam($i,$args[$i]);
	return " ".implode(", ",$argz)." ";
}
/**
 * Generates the return statement of a method
 * @param  [type] $methodName [description]
 * @param  [type] $methodInfo [description]
 * @return [type]             [description]
 */
function generateReturn($methodName,$methodInfo,$argCount)
{
	$method=$methodInfo;
	$code="";
	if ($method['return']['type']!='void')
		$code.="return ";
	// $code.="\t\t\t";
	if (isQtType($method['return']['type']))
	{
		if ($method['return']['pointer'])	
			$code.="QNAME({$method['return']['type']})("; //construct another PhpQt from it
		else
			$code.="{$method['return']['type']}(";
	}

	$code.="q->{$methodName} (".prepareArgs($method['args'],$argCount).")";
	
	if (isQtType($method['return']['type']))
		$code.=")";
	if ($method['return']['type']=="void")
		$code.=", return nullptr";
	$code.=";";
	return $code;
}
/**
 * Generates code for all overrides of one method
 * @param  [type] $name            [description]
 * @param  [type] $methodInstances [description]
 * @return [type]                  [description]
 */
function generateMethodCode($name,$methodInstances)
{
	$methodsByArgCount=[];
	$count=count($methodInstances);
	//sort methods by argCount, toggling every optional value
	foreach($methodInstances as $k=>$methodInstance)
	{
		$mandatoryArgCount=0;
		foreach ($methodInstance['args'] as $args)
			if (!isset($args['default']))
				$mandatoryArgCount++;
		$methodInstance['mandatoryArgCount']=$mandatoryArgCount;
		//add all possible argcount combos of this method, 
		//e.g. 2 mandatory 3 optional = 2,3,4,5
		for ($i=$mandatoryArgCount;$i<=count($methodInstance['args']);++$i)
		{
			if (!isset($methodsByArgCount[$i]))
				$methodsByArgCount[$i]=[];
			$methodsByArgCount[$i]["method_".$k]=$methodInstance;
		}
	}
	ksort($methodsByArgCount);

	//generating code
	$code="";
	$else="";
	foreach ($methodsByArgCount as $argCount=>$methods)
	{
		$competition=count($methods)>1;
		$code.="{$else}if ( params.size()==$argCount )";
		if ($competition) $code.=" //competition (".count($methods).")";
		$code.="\n";
		if (!$else)	$else="else ";
		if ($competition) //competing methods: solve collisions
		{
			$code.="{\n";
			$else2="";
			foreach ($methods as $method)
			{
				$code.="\t {$else2}if ( ";
				if (!$else2) $else2="else ";
				$conds=[];
				for ($i=0;$i<$argCount;++$i)
				{
					$cond="";
					$typehint=typehint($method['args'][$i]);
					$cond="params[{$i}].type()==Php::Type::{$typehint}";
					if ($typehint=="Object")
						$cond.=" and GET_CLASS(params[{$i}])==\"{$method['args'][$i]['type']}\"";
					$conds[]=$cond;
				}
				$code.=implode(" and ",$conds);
				$code.=" )\n";
			
				$code.="\t\t";
				$code.=generateReturn($name,$method,$argCount);
				$code.="\n";

			}
			$code.="}\n";
		}
		else
		{
			$code.="\t";
			$code.=generateReturn($name,end($methods),$argCount);
			$code.="\n";
		}

	}
	return $code;
	// usort($methodInstances, function($x,$y){return $x['mandatoryArgCount']>$y['mandatoryArgCount'];});


}
function indent($code,$count=1)
{
	return substr(str_repeat("\t",$count).str_replace("\n", "\n".str_repeat("\t",$count),$code),0,-$count);
}
function generateWrapper($class)
{
	$info=include "out/class_{$class}.txt";
	$constructor_code="";
	$methods_code="";
	//loop over methods
	foreach ($info['methods'] as $method_name=>$method_overrides)
	{
		$t="else if ( name==\"{$method_name}\" )\n";
		$t.="{\n";
		$t.=indent(generateMethodCode($method_name,$method_overrides));
		$t.="}\n";
		if ($method_name==$class)
			$constructor_code.=$t;
		elseif ($method_name=="~{$class}");
		else
			$methods_code.=$t;
	}
	$constructor_code=str_replace("return q->","q = new ",$constructor_code);
	$constructor_code=substr($constructor_code,strpos($constructor_code,"\n")+2,-2); //remove { } and name check
	$methods_code=indent(substr($methods_code,5)); //remove the else
	$code=<<<X
#include "phpqtng.h"
#define QtParentClass	{$info['parent']}
#define QtClass		{$info['name']}

#define ME		QNAME(QtClass)
#define PARENT		QNAME(QtParentClass)

void ME::__construct(Php::Parameters &params)
{   
	{$constructor_code}
    else
    	Php::error <<"Arguments not matching any constructor of '{$info['name']}'.";
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
	@file_put_contents("out/Qt/{$class}.cpp.txt", $code);
	return $code;
}
// findAllClasses($url);
// $r=findClass("Q3CacheIterator","$url/q3cacheiterator.html");
// var_dump($r);
// findClass("Q3Action","$url/q3action.html");
// findClass("Q3Http","$url/q3http.html");
// $r=findClass("QWidget","$url/qwidget.html");
generateWrapper("QWidget");

