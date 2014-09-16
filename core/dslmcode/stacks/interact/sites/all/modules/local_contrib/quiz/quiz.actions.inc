<?php
/**
 * @file
 * Example Action Implementation.
 *
 * This does not provide functional code, but is an illustration of how actions can be created for
 * Quiz.
 *
 * This file was created with the intent of providing
 * some documentation for a good starting point when creating actions for utilization with
 * the quiz module.  Most of this documentation was taken from http://api.drupal.org, the API
 * documentation provided by Drupal.  For more understanding of these functions and hooks, please
 * see that Drupal API documentation for further reading.
 * @file
 */


/**
 * Implementation of hook_action_info().
 * An action consists of two or three parts:
 * (1) an action definition (returned by this hook),
 * (2) a function which does the action
 *   (which by convention is named module + '_' + description of what the function does + '_action'),
 * (3) and an optional form definition function that defines a configuration form
 *   (which has the name of the action with '_form' appended to it.)
 *
 */
function quiz_action_info() {
  /*
  //this is the name of your function to execute (custom_action)
  //whatever your name here is you MUST have a function that matches
  $info['custom_action'] = array(
    //this is how we can filter the dropdown box on the quiz create page there will be an
    //admin setting that will allow you to filter your dropdown results by 'type'
    'type' => 'quiz',
    //self explainatory
    'description' => t('Custom Desription'),
    //This allows you to configure your action with parameters through the admin
    //If set to TRUE then you will need a custom form function for your options
    'configurable' => TRUE,
    //this will filter out actions based hooks, You will only use this if your going to get
    //extremely advanced.
    'hooks' => array(
      'any' => TRUE,
    ),
  );
  */
  //return your array of actions
  return $info;
}
/**
 * This will be your custom action to perform.  What do you want to happen?
 * When creating your quiz and you select your custom_action you defined in quiz_action_info()
 * then this function will be called to perform whatever you want to happen.
 *
 */
function quiz_custom_action() {
  //perform your action here
}
/**
 * Form for configurable Drupal action.
 * This form will be called when you choose the 'Make a new advanced action available' from the
 * actions page in the admin.  An example of utilizing this type of dynamics would be if you were
 * giving away playing cards.  You could create a custom function that would take an 'id' as a parameter
 * to query the playing card database by.  So you would have ONE function that could give away any
 * playing card based on the parameter (id).  So you create a new action and this form will come
 * up.  In your form you select the playing card to give away, then click save and your new action
 * that gives away the playing card is created.  Then you just select that new action from the
 * dropdown when creating/editing the quiz.
 *
 * @param array $context
 * @return $form
 */
function quiz_custom_action_form($context) {
  /*
   $options = get_a_list_of_playing_cards();  //you would need to create an option list from a function
   $form['playing_card_id'] = array(
   '#title' => t('Playing Card'),
   '#type' => 'select',
   '#description' => t('Please select the playing card to give away.'),
   '#options' => $options,
   '#default_value' => isset($context['playing_card_id']) ? $context['playing_card_id'] : '',
   );
   $form['submit'] = array(
   '#type' => 'sumbit',
   '#value' => t('Submit')
   );
   */
  return $form;
}
/**
 * Validates the custom action form to make sure they have selected a playing card
 * when creating a new action
 *
 * @param array $form
 * @param array $form_state
 */
function quiz_custom_action_validate($form, $form_state) {
  /*
   $playing_card = $form_state['values']['playing_card_id'];
   if(empty($playing_card)) {
   form_set_error('playing_card_id', t('Please select the pllaying card to give away.'));
   }
   */
}
/**
 * Custom submit handler when creating a new action for a playing card.
 *
 * @param array $form
 * @param array $form_state
 * @return array
 */
function quiz_custom_action_submit($form, $form_state) {
  /*
   return array('playing_card_id' => (int) $form_state['values']['playing_card_id']);
   */
}
