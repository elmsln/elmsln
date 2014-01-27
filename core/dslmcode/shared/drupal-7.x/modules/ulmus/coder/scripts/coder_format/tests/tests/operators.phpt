<?php
TEST: Operators

--INPUT--
function foo() {
  $foo = $bar ? -1 : 0;
  $foo = (-1 + 1);
  return ($a_weight < $b_weight) ? -1 : 1;
}

--INPUT--
function file_download() {
  if (in_array(-1, $headers)) {
    return drupal_access_denied();
  }
}

--INPUT--
$a = ($b = 4) + 5;
--INPUT--
$a = 3;
--INPUT--
$a += 5;
--INPUT--
$b = "Hello world";
$b .= "foo";
--INPUT--
$c = $a + $b;
$c = 1 + 2;
--INPUT--
$c = $a - $b;
$c = 1 - 2;
--INPUT--
$c = $a * $b;
$c = 1 * 2;
--INPUT--
$c = $a / $b;
$c = 1 / 2;
--INPUT--
$c = $a % $b;
$c = 1 % 2;

--INPUT--
$c = $a & $b;
$c = $a | $b;
$c = $a ^ $b;
$c = ~$a;
$c = $a << $b;
$c = $a >> $b;

--INPUT--
$c = $a == $b;
$c = $a === $b;
$c = $a != $b;
$c = $a <> $b;
$c = $a !== $b;
$c = $a < $b;
$c = $a > $b;
$c = $a <= $b;
$c = $a >= $b;

--INPUT--
$c = @imagettftext($file, $foo);

--INPUT--
$output = `ls -al`;

--INPUT--
$c = ++$a;
$c = $a++;
$c = --$a;
$c = $a--;

--INPUT--
$c = $a and $b;
$c = $a or $b;
$c = $a xor $b;
$c = !$a;
$c = $a && $b;
$c = $a || $b;

--INPUT--
$c = $a . $b;
$c = $a .'foo';
$c = 'foo'. $a;
$c = 'foo'. $a . $b .'bar';
$c = 'foo' . 'bar';

--INPUT--
$c = $a + $b;
$c = $a == $b;
$c = $a === $b;
$c = $a != $b;
$c = $a <> $b;
$c = $a !== $b;

--INPUT--
class A {}

$foo = new A;

if ($foo instanceof A) {
  return;
}

