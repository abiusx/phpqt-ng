<?php
function grep_r($str,$find)
{
	return substr($str,$r=strpos($str,$find)+strlen($find),strpos($str,PHP_EOL,$r)-1-$r);
}
function curl($url,$postparams=[],$additional_opts=[])
{
	$opts=[
		CURLOPT_COOKIEJAR => 'stdlib.cookie',
		CURLOPT_COOKIEFILE => 'stdlib.cookie',
    	CURLOPT_RETURNTRANSFER => 1,
    	CURLOPT_URL => $url,
    	CURLOPT_TIMEOUT => 5,
    	CURLOPT_CONNECTTIMEOUT => 1,
    	CURLOPT_USERAGENT => 'cURL'
	];
	foreach ($additional_opts as $k=>$v)
		$opts[$k]=$v;
	if ($postparams)
	{
		$opts[CURLOPT_POST]=1;
		$opts[CURLOPT_POSTFIELDS]=http_build_query($postparams);
	}
	$curl = curl_init();
	curl_setopt_array($curl, $opts);
	$res = curl_exec($curl);
	curl_close($curl);
	return $res;
}
function scanf($formatStr)
{
	$args = array(STDIN,$formatStr); 
	$argCount=substr_count($formatStr,"%");
	for ($i=0;$i<$argCount;++$i)
		$args[]=0;
	$Args=array();
	foreach($args as $k => &$arg)
            $Args[$k] = &$arg; 
	call_user_func_array("fscanf", $Args);
	if (count($args)==3)
		return $args[2];
	else
	{
		array_shift($args);
		array_shift($args);	
		return $args;
	}
}
function gets($length=null)
{
	if (!$length)
		return fgets(STDIN);
	else
		return fgets(STDIN,$length);
}

function input()
{
	return gets();
}
/**
 * Creates a lambda function based on the definition given
 * @param  string $definition function arguments are denoted with _
 *  __ means second arg, ___ means third, and so on
 * @return Closure             
 */
function f($definition,$parameter_placeholder='_')
{
	$code=$definition;
	if (strpos($code,";")===false)
		$code="return {$code};";

	$arg_count_max=ceil(sqrt(2*substr_count($code,$parameter_placeholder))); //cuz to have X args, we need X*(X+1)/2 _s.
	$argCount=0;
	for ($i=$arg_count_max;$i>=1;--$i)
		if (strpos($code, str_repeat($parameter_placeholder,$i))!==false)
		{
			$argCount=$i;
			break;
		}
	$args=[];
	if ($argCount)
		$args=array_map(function($t) {return '$arg'.($t+1);},range(0,$argCount-1));
	$argString=implode(",",$args);
	for ($i=$argCount;$i>=1;--$i)
		$code=str_replace(str_repeat($parameter_placeholder,$i), '$arg'.$i, $code);


	$eval_code="return function ({$argString}) { {$code} };";
	//var_dump($eval_code);
	$f=eval($eval_code);
	if ($f===false)
		trigger_error("Can not create anonymous function: '{$eval_code}'",E_USER_ERROR);
	// var_dump($f);
	return $f;
}
/**
 * Alias for f
 * @return Closure
 */
function lambda()
{
	$args=func_get_args();
	return call_user_func_array("f", $args);
}
$t=array_map(lambda("_[0]+_[1]"),[[1,2],[2,3],[3,4]]);
$t=lambda("1");
$a=([1,2,3]);

