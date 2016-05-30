<?php
require "config.php";

$url=qt_doc_url();


/**
 * Retrieves a list of all Qt classes and their html file name (keys)
 * @param  [type] $url [description]
 * @return [type]      [description]
 */
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
	$a['virtual']=strpos($a['type'],"virtual")!==false;
	$a['const']=strpos($a['type'], "const")!==false;
	$a['pointer']=substr($a['type'],-1)=="*";
	$a['reference']=substr($a['type'],-1)=="&";
	$a['rawtype']=$a['type'];
	if (($r1=strpos($a['type'],"<"))!==false) //templated type
	{
		$r2=strrpos($a['type'], ">");
		$a['template']=parseArg(substr($a['type'],$r1+1,$r2-$r1-1));
		$a['type']=substr($a['type'],0,$r1).substr($a['type'],$r2+1);
	}
	if ($a['virtual'])
		$a['type']=substr($a['type'],0,strpos($a['type'],"virtual")).substr($a['type'],strpos($a['type'],"virtual")+8);
	if ($a['const'])
		$a['type']=substr($a['type'],0,strpos($a['type'],"const")).substr($a['type'],strpos($a['type'],"const")+6);
	if ($a['pointer'] or $a['reference'])
		$a['type']=substr($a['type'],0,-2);
	return $a;
}
/**
 * Extracts information regarding one Qt class from the HTML docs
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
	if (!preg_match('/<h2 id="public-slots.*?<table(.*?)<\/table>/ims',$res,$rest2))
		$rest2="";
	else
		$rest2=$rest2[1];

	$rest=htmlspecialchars_decode($rest[1].$rest2);
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
		$return=str_replace("<code>(preliminary) </code>", "", $return);
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

/**
 * Determines whether a type is a QtType or not
 * @param  [type]  $type [description]
 * @return boolean       [description]
 */
function isQtType($type)
{
	return (strlen($type)>3 and $type[0]=="Q" and ctype_upper($type[1]));
}
function isQtEnum($type)
{
	return strlen($type)>5 and substr($type,0,4)=="Qt::";
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
		$a="PARAM_QTYPE($type,params[$paramIndex])";
	elseif ($arg['const'] and $arg['reference'] and isQtType($type))
		$a="{$type}(params[$paramIndex])";
	elseif (isQtEnum($type))
		$a="{$type}((int)params[$paramIndex])";
	elseif ($type)
		$a="({$type})params[$paramIndex]";
	else
		$a="params[$paramIndex]";
	return $a;
}
/**
 * Returns Php::Type compatible type based on C++/Qt type
 * @param  [type] $arg [description]
 * @return [type]      [description]
 */
function typehint($arg)
{
	$Type=$arg['type'];
	$type=strtolower($Type);
	if ($type=="int" or $type=="long" or $type=="ulong" or $type=="ulong16" or $type=="ulong32" or $type=="uint"
		or $type=="uint16" or $type=="uint32" or $type=="short" or $type=="ushort")
		return "Numeric";
	elseif ($type=="bool")
		return "Bool";
	elseif ($type=="qstring" or ($type=="char" and $arg['pointer']) or $type=="string")
		return "String";
	elseif (isQtType($Type))
		return "Object";
	elseif ($type=="float" or $type=="double" or $type=="qreal")
		return "Float";
	elseif ($type=="qlist" or $type=="vector" or $type=="qvector" or $type=="list")
		return "Array";
	elseif (isQtEnum($Type))
		return "Numeric";
	elseif ($Type=="WId") //window ID
		return "Numeric";
	elseif ($Type=="void" or $Type=="")
		return "Null";
	else
	{
		trigger_error("Could not find a suitable typehint for '{$Type} ({$arg['rawtype']})'.");
		// var_dump($arg); ///DEBUG
	}
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
 * Casts the return type from Qt/C++ to something compatible with PHP(CPP)
 * @param  [type] $typeinfo [description]
 * @return [type]           [description]
 */
function typecastReturn($value,$typeinfo)
{
	$type=$typeinfo['type'];
	$typehint=typehint($typeinfo);
	if ($type=="QString")
		$out="{$value}.toStdString()";
	elseif ($type=="QList" and isset($typeinfo['template']))
		$out="{$value}.toStdList()";
	elseif ($typehint=="String")
		$a="string";
	elseif ($typehint=="Numeric")
		$a="int";
	elseif ($typehint=="Float")
		$a=$type;
	elseif ($typehint=="Bool")
		$a=$type;
	elseif ($typehint=="Array")
		$a="list";
	elseif ($typehint=="Object" and $typeinfo['pointer'])
		$a="QNAME({$type})";
	else
		$a="";
	if (!isset($out))
		if ($a)
			$out=$a."({$value})";
		else
			$out=$value;
	return $out;
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
	$void=($method['return']['type']=='void');
	if (!$void)
		$code.="return ";
	else
		$code.= "{ ";
	// $code.="\t\t\t";

	$value="q->{$methodName} (".prepareArgs($method['args'],$argCount).")";
	$code.=typecastReturn($value,$method['return']);
	$code.=";";
	if ($void)
		$code.=" return nullptr; }";

	$code.=" //rtype: {$method['return']['rawtype']}";
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
	return $code;
}
function generateClassWrapper($class)
{
	$code=generateWrapper($class);
	file_put_contents("../Qt/{$class}.cpp", $code);
	return true;
}
// findAllClasses($url);
// $r=findClass("Q3CacheIterator","$url/q3cacheiterator.html");
// var_dump($r);
// findClass("Q3Action","$url/q3action.html");
// findClass("Q3Http","$url/q3http.html");
// $r=findClass("QWidget","$url/qwidget.html");
// generateWrapper("QWidget");

// generateClassWrapper("QWidget");
