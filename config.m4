PHP_ARG_ENABLE(phpqt,
  [Whether to enable the "phpqt" extension],
  [  enable-phpqt        Enable "php-qt" extension support])

if test $PHP_PHPQT != "no"; then
  AC_DEFINE(HAVE_PHPQT, 1, [Whether you have PHP-Qt])
  PHP_SUBST(PHPQT_SHARED_LIBADD)
  PHP_NEW_EXTENSION(phpqt, phpqt.c qtcore.c, $ext_shared)
fi
