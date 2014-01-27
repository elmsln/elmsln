<?php
TEST: Multiline arrays

--INPUT--
$va = array('foo' => 'bar',
            2 => '23',
            '32' => 'asd'
);

--EXPECT--
$va = array('foo' => 'bar',
  2 => '23',
  '32' => 'asd',
);

-- INPUT --
$var = array(
  'install_page' => array(
    'foo' => NULL,),
);

-- EXPECT --
$var = array(
  'install_page' => array(
    'foo' => NULL,
  ),
);

--INPUT--
$var = array(
  'install_page' => array(
    'arguments' => array(
      'content' => NULL),
  ),
);

--EXPECT--
$var = array(
  'install_page' => array(
    'arguments' => array(
      'content' => NULL,
    ),
  ),
);

--INPUT--
$array = array(
  'foo' => 'bar',
  2 => $foo,
  0x000000 => 'asdf',
  "CRIVENS" => 3,
  $bar => 'asdf',
);

--INPUT--
$deep = array(
  'foo' => array(
    'croon' => 'asdf',
    'f' => 'a'
  ),
  'barasdfsadf' => array(
    'asdfasdfasdf' => 'd',
    'fsd' => 23
  )
);

--EXPECT--
$deep = array(
  'foo' => array(
    'croon' => 'asdf',
    'f' => 'a',
  ),
  'barasdfsadf' => array(
    'asdfasdfasdf' => 'd',
    'fsd' => 23,
  ),
);

--INPUT--
drupal_add_link(array('rel' => 'alternate',
                      'type' => 'application/rss+xml',
                      'title' => $title,
                      'href' => $url));

--EXPECT--
drupal_add_link(array('rel' => 'alternate',
    'type' => 'application/rss+xml',
    'title' => $title,
    'href' => $url,
  ));

--INPUT--
function node_theme() {
  return array(
    'node' => array(
      'arguments' => array('node' => NULL, 'teaser' => FALSE, 'page' => FALSE),
      'template' => 'node',
    ),
    'node_list' => array(
      'arguments' => array('items' => NULL, 'title' => NULL),
    ),
    'node_search_admin' => array(
      'arguments' => array('form' => NULL),
    ),
    'node_filters' => array(
      'arguments' => array('form' => NULL),
      'file' => 'node.admin.inc'
    ),
    'node_form' => array(
      'arguments' => 123,
      'file' => 'node.pages.inc',
    ),
    'node_preview' => array('arguments' => array('node' => NULL), 'file' => 'node.pages.inc'),
    'node_log_message' => array(
      'arguments' => array('log' => NULL)
    )
  );
}

-- EXPECT --
function node_theme() {
  return array(
    'node' => array(
      'arguments' => array('node' => NULL, 'teaser' => FALSE, 'page' => FALSE),
      'template' => 'node',
    ),
    'node_list' => array(
      'arguments' => array('items' => NULL, 'title' => NULL),
    ),
    'node_search_admin' => array(
      'arguments' => array('form' => NULL),
    ),
    'node_filters' => array(
      'arguments' => array('form' => NULL),
      'file' => 'node.admin.inc',
    ),
    'node_form' => array(
      'arguments' => 123,
      'file' => 'node.pages.inc',
    ),
    'node_preview' => array('arguments' => array('node' => NULL), 'file' => 'node.pages.inc'),
    'node_log_message' => array(
      'arguments' => array('log' => NULL),
    ),
  );
}

