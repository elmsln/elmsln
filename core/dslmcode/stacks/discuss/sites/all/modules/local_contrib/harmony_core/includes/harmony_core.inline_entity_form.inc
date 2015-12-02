<?php

/**
 * @file
 * Defines the inline entity form controller for Nodes.
 */

class HarmonyPostInlineEntityFormController extends EntityInlineEntityFormController {

  /**
  * Overrides EntityInlineEntityFormController::labels().
   */
  public function labels() {
    $labels = array(
      'singular' => t('post'),
      'plural' => t('posts'),
    );
    return $labels;
  }

  /**
   * Overrides EntityInlineEntityFormController::tableFields().
   */
  /*public function tableFields($bundles) {
    $fields = parent::tableFields($bundles);
    $fields['status'] = array(
      'type' => 'property',
      'label' => t('Status'),
      'weight' => 100,
    );

    return $fields;
  }*/

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($form, &$form_state) {
    global $user;

    $post_defaults = array(
      'title' => '',
      'uid' => $user->uid,
      'language' => LANGUAGE_NONE,
      'created' => REQUEST_TIME,
      'updated' => REQUEST_TIME,
    );

    $post = (object) array_merge($post_defaults, (array) $form['#entity']);

    $post->is_new = empty($post->post_id);

    $form['post'] = array(
      '#type' => 'value',
      '#value' => $post,
    );

    if (empty($post->is_new)) {
      $post->is_new = FALSE;
      $wrapper = entity_metadata_wrapper('harmony_post', $post);

      if ($wrapper->field_harmony_thread->value()) {
        // Prevent users from editing within a locked thread.
        $thread = harmony_thread_load($wrapper->field_harmony_thread->thread_id->value());

        if ($thread->locked == HARMONY_LOCKED && !harmony_core_thread_access_callback('update', $thread)) {
          drupal_access_denied();
        }
      }
    }

    // Basic post information.
    // These elements are just values so they are not even sent to the client.
    foreach (array('post_id', 'uid', 'is_new') as $key) {
      $form[$key] = array(
        '#type' => 'value',
        '#value' => isset($post->$key) ? $post->$key : NULL,
      );
    }

    $form['title'] = array(
      '#type' => 'value',
      '#title' => t('Post title'),
      '#default_value' => $post->title,
    );

    $langcode = entity_language('harmony_post', $post);
    field_attach_form('harmony_post', $post, $form, $form_state, $langcode);

    $text_lang = $form['field_harmony_text']['#language'];
    $form['field_harmony_text'][$text_lang][0]['#title_display'] = 'invisible';
    $form['field_harmony_text'][$text_lang][0]['#attributes']['placeholder'] = t('Type here...');

    // Thread continued from stuff.
    if ($post->is_new && !empty($_GET['field_harmony_thread_cont_from']) && ctype_digit((string) $_GET['field_harmony_thread_cont_from']) && user_access('reply as new harmony_thread')) {
      $post_to_quote_id = $_GET['field_harmony_thread_cont_from'];
      $post_to_quote = entity_load_single('harmony_post', $post_to_quote_id);

      if ($post_to_quote && harmony_core_post_access_callback('view', $post_to_quote)) {
        $post_to_quote_wrapper = entity_metadata_wrapper('harmony_post', $post_to_quote);

        // Figure out the thread type to grab the "reply as a new thrad" setting.
        $thread_type = $post_to_quote_wrapper->field_harmony_thread->type->value();
        $quote_action = variable_get('harmony_core_bundle__' . $thread_type . '__reply_as_new_thread', 0);

        if ($quote_action > 0) {
          $content = NULL;

          // Quote original post.
          if ($quote_action == 1) {
            $quote_content = $post_to_quote_wrapper->field_harmony_text->value();

            if ($quote_content) {
              $content = "[quote post={$post_to_quote_id}]" . $quote_content['value'] . '[/quote]' . "\n\n";
            }
          }
          // Link back to the post.
          elseif ($quote_action == 2) {
            $content = t('This thread continues from a post in [@title](!url "View the post")', array(
              '@title' => $post_to_quote_wrapper->field_harmony_thread->title->value(array('sanitize' => TRUE)),
              '!url' => url('thread/' . $post_to_quote_wrapper->field_harmony_thread->thread_id->value(), array('absolute' => TRUE)),
            )) . "\n\n";
          }

          if ($content) {
            // Set default value.
            $form['field_harmony_text'][$text_lang][0]['#default_value'] = $content . $form['field_harmony_text'][$text_lang][0]['#default_value'];
            $form['field_harmony_text'][$text_lang][0]['#format'] = variable_get('harmony_core_default_input_format', 'harmony_filtered');
          }
        }
      }
    }

    // Add in the log for revisions, if not new.
    if (empty($post->is_new) || !empty($post->is_new) && !$post->is_new) {
      $form['revisions'] = array(
        '#type' => 'fieldset',
        '#access' => user_access('administer harmony forum content'),
        '#title' => t('Revision options'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#group' => 'additional_settings',
        '#attributes' => array(
          'class' => array('post-form-options'),
        ),
      );

      $form['revisions']['log'] = array(
        '#type' => 'textarea',
        '#title' => t('Reason for edit'),
        '#rows' => 4,
      );

      $form['revisions']['log_show'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show reason for edit to the public?'),
        '#default_value' => 0,
      );
    }
    else {
      $form['revisions']['log'] = array(
        '#type' => 'value',
        '#value' => NULL,
      );
      $form['revisions']['log_show'] = array(
        '#type' => 'value',
        '#value' => 0,
      );
    }

    // Hide the thread entity reference field.
    $form['field_harmony_thread']['#access'] = FALSE;
    // Hide the "Post is reply to" entity reference field.
    $form['field_harmony_post_is_reply_to']['#access'] = FALSE;

    // Hide the redirect fieldset if present as they'll appear for the thread.
    if (!empty($form['redirect'])) {
      $form['redirect']['#access'] = FALSE;
    }

    return $form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$form, &$form_state) {
    parent::entityFormSubmit($form, $form_state);

    $post = $form['#entity'];
    $wrapper = entity_metadata_wrapper('harmony_post', $post);

    if ($post->is_new) {
      $wrapper->first_post->set(TRUE);
      $wrapper->last_post->set(TRUE);
    }

    $wrapper->title->set($form_state['values']['title']);
    // Published or unpublished shouldn't propogate to the post.
    //$wrapper->status->set($form_state['values']['status']);
    $wrapper->locked->set($form_state['values']['locked']);
    $wrapper->log->set($post->revisions['log']);
    $wrapper->log_show->set($post->revisions['log_show']);

    field_attach_submit('harmony_post', $post, $form, $form_state);
  }

  /**
   * Overrides EntityInlineEntityFormController::save().
   */
  public function save($entity, $context) {
    harmony_post_save($entity);
  }
}
