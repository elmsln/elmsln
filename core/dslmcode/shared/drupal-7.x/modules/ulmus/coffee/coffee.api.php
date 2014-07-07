<?php

/**
 * @file
 * Hooks provided by Coffee module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Extend the Coffee functionallity with your own commands and items.
 *
 * Here's an example of how to add content to Coffee.
 */
function hook_coffee_commands($op) {
  $commands = array();

  // Basic example, for 1 result.
  $commands[] = array(
    'value' => 'Simple',
    'label' => 'node/example',
    // Every result should include should include a command.
    'command' => ':simple',
  );


  // More advanced example to include a view.
  $view = views_get_view('my_entities_view');

  if ($view) {
    $view->set_display('default');
    $view->pre_execute();
    $view->execute();
  
    if (count($view->result) > 0) {
      foreach ($view->result as $row) {
        $commands[] = array(
          'value' => ltrim(url('node/' . $row->nid), '/'),
          'label' => check_plain('Pub: ' . $row->node_title),
          // You can also specify commands that if the user enters, this command should show.
          'command' => ':x',
        );
      }
    }
  }

  return $commands;
}

/**
 * @} End of "addtogroup hooks"
 */
