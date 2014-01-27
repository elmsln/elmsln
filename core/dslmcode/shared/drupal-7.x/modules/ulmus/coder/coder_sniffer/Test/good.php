<?php

/**
 * @file
 * This file contains all the valid notations for the drupal coding standard.
 *
 * The goal is to create a style checker that validates all of this
 * constructs.
 *
 * Theme files often have lists in their file block:
 * - item 1
 * - item 2
 * - sublist:
 *   - sub item 1
 *   - sub item2
 */

// Singleline comment before a code line.
$foo = 'bar';

/**
 * Doxygen comment style is allowed before define() statements.
 */
define('FOO_BAR', 5);

// Global variable names.
global $user, $is_https, $_mymodule_myvar;

/*
 * Multiline comment
 *
 * @see my_function()
 */

// PHP Constants must be written in CAPITAL letters.
TRUE;
FALSE;
NULL;

// Has whitespace at the end of the line.
$whitespaces = 'Yes, Please';

// Operators - have a space before and after.
$i = 0;
$i += 0;
$i -= 0;
$i == 0;
$i != 0;
$i > 0;
$i < 0;
$i >= 0;
$i <= 0;

// Unary operators must not have a space.
$i--;
--$i;
$i++;
++$i;
$i = -1;
array('i' => -1);
$i = (1 == -1);
$i = (1 === -1);
range(-50, -45);
$i[0] + 1;
$x->{$i} + 1;
REQUEST_TIME + 42;
!$x;
!($x + $y);

// Operator line break for long lines.
$x = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 +
  1 + 1;

$x = $test ? -1 : 1;
$x = $test ? 1 : -1;

// Casting has a space.
(int) $i;

// The last item in an multiline array should be followed by a comma.
// But not in a inline array.
$a = array();
$a = array('1', '2', '3');
$a = array(
  '1',
  '2',
  '3',
);
$a = array('1', '2', array('3'));
$a = array('1', '2',
  array(
    'one',
    'two',
    'three',
    array(
      'key' => $value,
      'title' => 'test',
    ),
  ),
);

// Array indentation.
$x = array(
  'foo' => 'bar',
  'fi' => long_function_call('hsdfsdmfsldkfnmdflkngdfngfg',
    'fghfghfghfghfgh', $z),
  'a' => 'b',
  'foo' => array(
    'blu' => 1,
    'f' => x(1) + array(
      'h' => 'x',
    ),
  ),
);

// Arrays in function calls.
foo(
  array(
    'value' => 0,
    'description' => t('xyz @url',
      array(
        '@url' => 'http://example.com',
      )
    ),
  )
);

// Pretty array layout.
$a = array(
  'title'    => 1,
  'weight'   => 2,
  'callback' => 3,
);

// Arrays with multi line strings.
$query = db_query("
  SELECT * FROM {foobar} WHERE nid IN (1, 2, 3)
  AND date BETWEEN '%s' AND '%s'
  ", array(
    ':from_date' => $from_date,
    ':to_date' => $to_date,
  )
);

// Array with multi line comments.
$query = db_query("
  SELECT * FROM {foobar} WHERE nid IN (1, 2, 3)
  AND date BETWEEN '%s' AND '%s'", /* comment
  in here */ array(
    ':from_date' => $from_date,
    ':to_date' => $to_date,
  )
);

// Item assignment operators must be prefixed and followed by a space.
$a = array('one' => '1', 'two' => '2');
foreach ($a as $key => $value) {
}

// If conditions have a space before and after the condition parenthesis.
if (TRUE || TRUE) {
  $i;
}
elseif (TRUE && TRUE) {
  $i;
}
// Commenting is allowed here.
else {
  $i;
}

while (1 == 1) {
  if (TRUE || TRUE) {
    $i;
  }
  else {
    $i;
  }
}

switch ($condition) {
  case 1:
    $i;
    break;

  case 2:
    $i;
    break;

  // Blank line after the case statement is allowed.
  case 3:

    $i;
    break;

  default:
    $i;
}

// Empty case statements are allowed.
switch ($code) {
  case 200:
  case 304:
    break;

  case 301:
  case 302:
  case 307:
    call_function();
    break;

  default:
    $result->error = $status_message;
}

/**
 * Allowed switch() statement in a function without breaks.
 */
function foo() {
  switch ($x) {
    case 1:
      return 5;

    case 2:
      return 6;
  }
}

do {
  $i;
} while ($condition);

/**
 * Short description.
 *
 * We use doxygen style comments.
 * What's sad because eclipse PDT and
 * PEAR CodeSniffer base on phpDoc comment style.
 * Makes working with drupal not easier :|
 *
 * @param string $field1
 *   Doxygen style comments.
 * @param int $field2
 *   Doxygen style comments.
 * @param bool $field3
 *   Doxygen style comments.
 * @param bool $field4
 *   Don't check for & in docblock of referenced variable.
 *
 * @return array
 *   Doxygen style comments.
 *
 * @see example_reference()
 * @see Example::exampleMethod()
 * @see http://drupal.org
 */
function foo_bar($field1, $field2, $field3 = NULL, &$field4 = NULL) {
  $system["description"] = t("This module inserts funny text into posts randomly.");
  return $system[$field];
}

// Function call.
$var = foo($i, $i, $i);

// Multiline function call.
$var = foo(
  $i,
  $i,
  $i
);

// Multiline function call with array.
$var = foo(
  array(
    $i,
    $i,
    $i,
  ),
  $i,
  $i
);

// Multiline function call with only one array.
$var = foo(
  array(
    $i,
    $i,
    $i,
  )
);

/**
 * Class declaration
 *
 * Classes always have a multiline comment
 */
class Bar {

  // Public properties don't have a prefix.
  protected $foo = 1;

  // Longer properties use camelCase naming.
  public $barProperty = 1;

  // Public static variables use camelCase, too.
  public static $basePath = NULL;

  /**
   * Enter description here ...
   */
  public function foo() {

  }

  /**
   * Enter description here ...
   */
  protected function barMethod() {

  }
}

/**
 * Enter description here ...
 */
function _private_foo() {

}

// When calling class constructors with no arguments, always include
// parentheses.
$bar = new Bar();

$bar = new Bar($arg1, $arg2);

$bar = 'Bar';
$foo = new $bar();
$foo = new $bar($i, $i);

// Static class variables use camelCase.
Bar::$basePath = '/foo';

// Concatenation - there has to be a space.
$i . "test";
$i . 'test';
$i . $i;
$i . NULL;

// It is allowed to have the closing "}" on the same line if the class is empty.
class MyException extends Exception {}

// Nice alignment is allowed for assignments.
class MyExampleLog {
  const INFO      = 0;
  const WARNING   = 1;
  const ERROR     = 2;
  const EMERGENCY = 3;

  /**
   * Empty method implementation is allowed.
   */
  public function emptyMethod() {}

  /**
   * Protected functions are allowed.
   */
  protected function protectedTest() {

  }
}

/**
 * Nice allignment in functions.
 */
function test_test2() {
  $a   = 5;
  $aa  = 6;
  $aaa = 7;
}

/**
 * Example of chained method invocations in a function.
 */
function test3() {
  // Uses the Rules API as example.
  $rule = rule();
  $rule->condition('rules_test_condition_true')
       ->condition('rules_test_condition_true')
       ->condition(rules_or()
         // Inline test comment that continues on a
         // second line.
         ->condition(rules_condition('rules_test_condition_true')->negate())
         ->condition('rules_test_condition_false')
         ->condition(rules_and()
           ->condition('rules_test_condition_false')
           ->condition('rules_test_condition_true')
           ->negate()
         )
       );
}

// Test usages of t().
t('special character: \"');
t("special character: \'");
// Escaping is allowed here because we make use of the other quote type, too.
t('Link to Drupal\'s <a href="@url">admin pages</a>.', array('@url' => url('admin')));

// Test inline comment style.
// Comment one.
t('x');
// Comment two
// @todo this is valid!
t('x');
// Goes on?
t('x');
/* Longer comment
 * bla bla
 * end!
 */
t('x');
// @see http://example.com
t('x');
// @see my_function()
t('x');
// t() refers to a function name and should not be capitalized.
t('x');
// rules_admin is a fancy machine name word with underscores and should not be
// capitalized and ignored.
t('x');
// {} this comment start should not be flagged.
t('x');
// Some code examples in inline comments:
// @code
//   function mymodule_menu() {
//     $items['abc/def'] = array(
//       'page callback' => 'mymodule_abc_view',
//     );
//     return $items;
//   }
// @endcode
// @todo A long description what is left to be done. Exceeds the first line and
//   is indented on the second line.
// Now follows a list:
// - item 1
//   additional description line.
// - item 2
// - item 3 comes with a sub list:
//   - sub item 1
//   - sub item 2
//     description of sub item 2.
// List is closed, normal indentation here. Now comes a paragraph empty line.
//
// And here continues the long comment.
t('x');

/**
 * Doc block with some code tags.
 *
 * Some description and here comes the code:
 * @code
 *   $options = drupal_parse_url($_GET['destination']);
 *   $my_url = url($options['path'], $options);
 *   $my_link = l('Example link', $options['path'], $options);
 * @endcode
 *
 * Some more description here. And now the parameters.
 *
 * @param int $x
 *   Parameter comment here.
 */
function test1($x) {

}

/**
 * Variable amount of parameters is allowed with the "..." notation.
 *
 * Example:
 * @code
 *   test_invoke_all('node_view', $node, $view_mode);
 * @endcode
 *
 * @param string $hook
 *   The name of the hook to invoke.
 * @param ...
 *   Arguments to pass to the hook.
 */
function test_invoke_all($hook) {

}

// Test string concatenation.
$x = 'This string is very long and thus it can and should be concatenated.' .
     'Othverwise the string will be very hard to maintain and or read';
$x = 'This string should be concatenated. Even if it is just a little bit ' .
     'longer';
$x = (1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1) . 'This is initially ' .
     'short but since it has a lot of code before the real text it can be ' .
     'concatenated';

// Requiring files conditionally is allowed.
if ($a == TRUE) {
  require_once 'good.tpl.php';
}

/**
 * This is not an implementation of hook_foobar().
 */
function hook_foobar() {

}


/**
 * Implements hook_foo().
 *
 * @link http://example.com/long-link-here-whatever Some long documentation link @endlink
 */
function mymodule_foo() {

}

/**
 * Implements hook_foo_BAR_ID_bar() for some_type_bar().
 */
function mymodule_foo_some_type_bar() {

}

/**
 * Implements hook_foo_bar() for foo_bar.tpl.php.
 */
function mymodule_foo_bar() {

}

/**
 * Not documenting all parameters is allowed.
 *
 * @param Node $node
 *   The loaded node entity that we will use to do whatever.
 */
function mymodule_form_callback($form, &$form_state, Node $node) {

}

$x = 'Some markup text<br />';

// Inline if statements with ?: are allowed.
$x = $y == $z ? 23 : 42;

// Standard watchdog message.
watchdog('mymodule', 'Log message here.');

// For assigning by reference it is allowed that there is no space after the
// "=" oeprator.
$batch =& batch_get();

// Security issue: http://drupal.org/node/750148
preg_match('/.+/i', 'subject');
preg_match('/.+/imsuxADSUXJ', 'subject');
preg_filter('/.+/i', 'replacement', 'subject');
preg_replace('/.+/i', 'replacement', 'subject');
// Use a not so common delimiter.
preg_match('@.+@i', 'subject');
preg_match('@.+@imsuxADSUXJ', 'subject');
preg_filter('@.+@i', 'replacement', 'subject');
preg_replace('@.+@i', 'replacement', 'subject');
preg_match("/test(\d+)/is", 'subject');

interface MyWellNamedInterface {
}

// Correctly formed try/catch block.
try {
  do_something();
}
catch (Exception $e) {
  scream();
}

$result = $x ?: FALSE;

class Foo implements FooInterface {

  /**
   * {@inheritdoc}
   */
  public function test() {}

  /**
   * {@inheritdoc}
   *
   * Some additional documentation here.
   */
  public function test2() {}
}
