<?php

/**
 * @file
 * Settings forms for the Expire module.
 */

/**
 * Settings form for actions with cached pages.
 */
function expire_admin_settings_form() {

  $form['tabs'] = array(
    '#type' => 'vertical_tabs',
  );

  // COMMON SETTINGS.
  $form['tabs']['status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Module status'),
    '#group' => 'tabs',
    '#weight' => 0,
  );

  $form['tabs']['status']['common'] = array(
    '#type' => 'fieldset',
    '#title' => t('Common settings'),
  );

  $form['tabs']['status']['common']['expire_status'] = array(
    '#type' => 'radios',
    '#title' => t('Status of implementation'),
    '#options' => array(
      EXPIRE_STATUS_DISABLED => t('Disabled'),
      EXPIRE_STATUS_ENABLED_INTERNAL => t('Internal expiration'),
      EXPIRE_STATUS_ENABLED_EXTERNAL => t('External expiration'),
    ),
    '#description' => theme('item_list', array('items' => array(
      t('Disabled: Module will not expire any data.'),
      t('Internal expiration: Use this option when you did not install additional contribs that implement hook_expire_cache(). Module will execute cache_clear_all() for expired URLs.'),
      t('External expiration: Use this option if you installed contrib (like Varnish, Boost, Purge, Acquia Purge) that implements this hook. Module will invoke hook_expire_cache() for expired URLs.'),
    ))),
    '#default_value' => variable_get('expire_status', EXPIRE_STATUS_DISABLED),
  );

  $modules = array();
  foreach (module_implements('expire_cache') as $module) {
    $modules[] = $module;
  }

  if (empty($modules)) {
    $help_message = t('You have no contribs that implement hook_expire_cache(). In this case you need to use Internal expiration to expire cached data.');
  }
  else {
    $help_message = t('You have contribs that implement hook_expire_cache(). This means that most likely you want to use External expiration to expire cached data.');
  }

  $form['tabs']['status']['common']['external_implementations'] = array(
    '#type' => 'item',
    '#title' => t('Modules that support external expiration'),
    '#description' => '<strong>' . $help_message . '</strong>',
    '#markup' => $modules ? theme('item_list', array('items' => $modules)) : t('There are no such modules.'),
  );

  $form['tabs']['status']['common']['expire_include_base_url'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include base URL in expires'),
    '#default_value' => variable_get('expire_include_base_url', EXPIRE_INCLUDE_BASE_URL),
    '#description' => t('Include the base URL in expire requests. Compatible with Domain Access.</br>Enabling this setting when <a href="@varnish">Varnish</a> or <a href="@acquia_purge">Acquia Purge</a> modules are used as a cache backend is not recommended.<br/>If you use internal expiration, this checkbox should be selected.',
      array('@varnish' => 'https://drupal.org/project/varnish', '@acquia_purge' => 'https://drupal.org/project/acquia_purge')),
  );

  $form['tabs']['status']['debug'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debug'),
  );

  $form['tabs']['status']['debug']['expire_debug'] = array(
    '#type' => 'radios',
    '#title' => t('Debug level'),
    '#options' => array(
      EXPIRE_DEBUG_DISABLED => t('Disabled'),
      EXPIRE_DEBUG_WATCHDOG => t('Watchdog'),
      EXPIRE_DEBUG_FULL => t('Watchdog + site message'),
    ),
    '#default_value' => variable_get('expire_debug', EXPIRE_DEBUG_DISABLED),
  );

  // NODE SETTINGS.
  $form['tabs']['node'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node expiration'),
    '#group' => 'tabs',
    '#weight' => 1,
  );

  $form['tabs']['node']['override'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node settings per type'),
  );

  $form['tabs']['node']['override']['info'] = array(
    '#type' => 'item',
    '#markup' => t('Please note that you may override this settings for each node type on the node type configuration page.'),
  );

  $form['tabs']['node']['actions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node actions'),
  );

  $form['tabs']['node']['actions']['expire_node_actions'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Page cache for node will be flushed after selected actions.'),
    '#options' => array(
      EXPIRE_NODE_INSERT => t('Node insert'),
      EXPIRE_NODE_UPDATE => t('Node update'),
      EXPIRE_NODE_DELETE => t('Node delete'),
    ),
    '#default_value' => variable_get('expire_node_actions', array()),
  );

  $form['tabs']['node']['expire'] = array(
    '#type' => 'fieldset',
    '#title' => t('What URLs should be expired when node action is triggered?'),
  );

  $form['tabs']['node']['expire']['expire_node_front_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Front page'),
    '#description' => t('Expire url of the site front page'),
    '#default_value' => variable_get('expire_node_front_page', EXPIRE_NODE_FRONT_PAGE),
  );

  $form['tabs']['node']['expire']['expire_node_node_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Node page'),
    '#description' => t('Expire url of the expiring node.'),
    '#default_value' => variable_get('expire_node_node_page', EXPIRE_NODE_NODE_PAGE),
  );

  if (module_exists('taxonomy')) {
    $form['tabs']['node']['expire']['expire_node_term_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Node term pages'),
      '#description' => t('Expire urls of terms that are selected in the expiring node.'),
      '#default_value' => variable_get('expire_node_term_pages', EXPIRE_NODE_TERM_PAGES),
    );
  }

  if (module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) {
    $form['tabs']['node']['expire']['expire_node_reference_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Node reference pages'),
      '#description' => t('Expire urls of entities which are referenced from the expiring node.'),
      '#default_value' => variable_get('expire_node_reference_pages', EXPIRE_NODE_REFERENCE_PAGES),
    );

    if (module_exists('field_collection')) {
      $form['tabs']['node']['expire']['expire_node_reference_field_collection_pages'] = array(
        '#type' => 'checkbox',
        '#title' => t('Traverse references attached to field collections'),
        '#description' => t('Expire urls of entities which are referenced from field collections attached to the expiring node.'),
        '#default_value' => variable_get('expire_node_reference_field_collection_pages', EXPIRE_NODE_REFERENCE_FC_PAGES),
        '#states' => array(
          'visible' => array(
            ':input[name="expire_node_reference_pages"]' => array('checked' => TRUE),
          ),
        ),
      );
    }
  }

  $form['tabs']['node']['expire']['expire_node_custom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom pages'),
    '#description' => t('Expire user-defined custom urls.'),
    '#default_value' => variable_get('expire_node_custom', EXPIRE_NODE_CUSTOM),
  );

  $form['tabs']['node']['expire']['expire_node_custom_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter custom URLs'),
    '#description' => t('Enter one relative URL per line. It can be the path of a node (e.g. !example1) or of any alias (e.g. !example2). However, it has to be the final URL, not a redirect (use the !link1 and !link2 modules).', array('!example1' => '<strong>node/[node:nid]</strong>', '!example2' => '<strong>my/path</strong>', '!link1' => l('Global Redirect', 'https://drupal.org/project/globalredirect'), '!link2' => l('Redirect', 'https://drupal.org/project/redirect'))) . '<br/>'
      . t('If you want to match a path with any ending, add "|wildcard" to the end of the line (see !link1 for details). Example: !example1 will match !example1a, but also !example1b, !example1c, etc.', array('!link1' => l('function cache_clear_all', 'https://api.drupal.org/api/drupal/includes%21cache.inc/function/cache_clear_all/7'), '!example1' => '<strong>my/path|wildcard</strong>', '!example1a' => '<strong>my/path</strong>', '!example1b' => '<strong>my/path/one</strong>', '!example1c' => '<strong>my/path/two</strong>')) . '<br/>'
      . t('You may use tokens here.'),
    '#states' => array(
      'visible' => array(
        ':input[name="expire_node_custom"]' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('expire_node_custom_pages'),
  );


  // COMMENT SETTINGS.
  if (module_exists('comment')) {
    $form['tabs']['comment'] = array(
      '#type' => 'fieldset',
      '#title' => t('Comment expiration'),
      '#group' => 'tabs',
      '#weight' => 2,
    );

    $form['tabs']['comment']['override'] = array(
      '#type' => 'fieldset',
      '#title' => t('Comment settings per node type'),
    );

    $form['tabs']['comment']['override']['info'] = array(
      '#type' => 'item',
      '#markup' => t('Please note that you may override this settings for each node type on the node type configuration page.'),
    );

    $form['tabs']['comment']['actions'] = array(
      '#type' => 'fieldset',
      '#title' => t('Comment actions'),
    );

    $form['tabs']['comment']['actions']['expire_comment_actions'] = array(
      '#type' => 'checkboxes',
      '#description' => t('Page cache for comment will be flushed after selected actions.'),
      '#options' => array(
        EXPIRE_COMMENT_INSERT => t('Comment insert'),
        EXPIRE_COMMENT_UPDATE => t('Comment update'),
        EXPIRE_COMMENT_DELETE => t('Comment delete'),
        EXPIRE_COMMENT_PUBLISH => t('Comment publish'),
        EXPIRE_COMMENT_UNPUBLISH => t('Comment unpublish'),
      ),
      '#default_value' => variable_get('expire_comment_actions', array()),
    );

    $form['tabs']['comment']['expire'] = array(
      '#type' => 'fieldset',
      '#title' => t('What URLs should be expired when comment action is triggered?'),
    );

    $form['tabs']['comment']['expire']['expire_comment_front_page'] = array(
      '#type' => 'checkbox',
      '#title' => t('Front page'),
      '#description' => t('Expire url of the site front page'),
      '#default_value' => variable_get('expire_comment_front_page', EXPIRE_COMMENT_FRONT_PAGE),
    );

    $form['tabs']['comment']['expire']['expire_comment_comment_page'] = array(
      '#type' => 'checkbox',
      '#title' => t('Comment page'),
      '#description' => t('Expire url of the expiring comment.'),
      '#default_value' => variable_get('expire_comment_comment_page', EXPIRE_COMMENT_COMMENT_PAGE),
    );

    if (module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) {
      $form['tabs']['comment']['expire']['expire_comment_reference_pages'] = array(
        '#type' => 'checkbox',
        '#title' => t('Comment\'s reference pages'),
        '#description' => t('Expire urls of entities which are referenced from the expiring comment.'),
        '#default_value' => variable_get('expire_comment_reference_pages', EXPIRE_COMMENT_REFERENCE_PAGES),
      );
    }

    $form['tabs']['comment']['expire']['expire_comment_node_page'] = array(
      '#type' => 'checkbox',
      '#title' => t('Comment\'s node page'),
      '#description' => t('Expire url of the node, to which expiring comment is related.'),
      '#default_value' => variable_get('expire_comment_node_page', EXPIRE_COMMENT_NODE_PAGE),
    );

    if (module_exists('taxonomy')) {
      $form['tabs']['comment']['expire']['expire_comment_node_term_pages'] = array(
        '#type' => 'checkbox',
        '#title' => t('Comment\'s node term pages'),
        '#description' => t('Expire urls of terms that are selected in the node, to which expiring comment is related.'),
        '#default_value' => variable_get('expire_comment_node_term_pages', EXPIRE_COMMENT_NODE_TERM_PAGES),
      );
    }

    if (module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) {
      $form['tabs']['comment']['expire']['expire_comment_node_reference_pages'] = array(
        '#type' => 'checkbox',
        '#title' => t('Comment\'s node reference pages'),
        '#description' => t('Expire urls of entities which are referenced from node, to which expiring comment is related.'),
        '#default_value' => variable_get('expire_comment_node_reference_pages', EXPIRE_COMMENT_NODE_REFERENCE_PAGES),
      );

      if (module_exists('field_collection')) {
        $form['tabs']['comment']['expire']['expire_comment_node_reference_field_collection_pages'] = array(
          '#type' => 'checkbox',
          '#title' => t('Traverse references attached to field collections'),
          '#description' => t('Expire urls of entities which are referenced from field collections attached to the expiring comment\'s node.'),
          '#default_value' => variable_get('expire_comment_node_reference_field_collection_pages', EXPIRE_COMMENT_NODE_REFERENCE_FC_PAGES),
          '#states' => array(
            'visible' => array(
              ':input[name="expire_comment_node_reference_pages"]' => array('checked' => TRUE),
            ),
          ),
        );
      }
    }

    $form['tabs']['comment']['expire']['expire_comment_custom'] = array(
      '#type' => 'checkbox',
      '#title' => t('Custom pages'),
      '#description' => t('Expire user-defined custom urls.'),
      '#default_value' => variable_get('expire_comment_custom', EXPIRE_COMMENT_CUSTOM),
    );

    $form['tabs']['comment']['expire']['expire_comment_custom_pages'] = array(
      '#type' => 'textarea',
      '#title' => t('Enter custom URLs'),
      '#description' => t('Enter one relative URL per line, e.g. !example1.', array('!example1' => '<strong>comment/[comment:cid]</strong>')) . '<br/>'
        . t('If you want to match a path with any ending, add "|wildcard" to the end of the line (see !link1 for details). Example: !example1 will match !example1a, but also !example1b, !example1c, etc.', array('!link1' => l('function cache_clear_all', 'https://api.drupal.org/api/drupal/includes%21cache.inc/function/cache_clear_all/7'), '!example1' => '<strong>comment/1</strong>', '!example1a' => '<strong>comment/1</strong>', '!example1b' => '<strong>comment/12</strong>', '!example1c' => '<strong>comment/123</strong>')) . '<br/>'
        . t('You may use tokens here.'),
      '#states' => array(
        'visible' => array(
          ':input[name="expire_comment_custom"]' => array('checked' => TRUE),
        ),
      ),
      '#default_value' => variable_get('expire_comment_custom_pages'),
    );
  }


  // USER SETTINGS.
  $form['tabs']['user'] = array(
    '#type' => 'fieldset',
    '#title' => t('User expiration'),
    '#group' => 'tabs',
    '#weight' => 3,
  );

  $form['tabs']['user']['actions'] = array(
    '#type' => 'fieldset',
    '#title' => t('User actions'),
  );

  $form['tabs']['user']['actions']['expire_user_actions'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Page cache for user will be flushed after selected actions.'),
    '#options' => array(
      EXPIRE_USER_INSERT => t('User insert'),
      EXPIRE_USER_UPDATE => t('User update'),
      EXPIRE_USER_DELETE => t('User delete'),
      EXPIRE_USER_CANCEL => t('User cancel'),
    ),
    '#default_value' => variable_get('expire_user_actions', array()),
  );

  $form['tabs']['user']['expire'] = array(
    '#type' => 'fieldset',
    '#title' => t('What URLs should be expired when user action is triggered?'),
  );

  $form['tabs']['user']['expire']['expire_user_front_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Front page'),
    '#description' => t('Expire url of the site front page'),
    '#default_value' => variable_get('expire_user_front_page', EXPIRE_USER_FRONT_PAGE),
  );

  $form['tabs']['user']['expire']['expire_user_user_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('User page'),
    '#description' => t('Expire url of the expiring user profile.'),
    '#default_value' => variable_get('expire_user_user_page', EXPIRE_USER_USER_PAGE),
  );

  if (module_exists('taxonomy')) {
    $form['tabs']['user']['expire']['expire_user_term_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('User term pages'),
      '#description' => t('Expire urls of terms that are selected in the expiring user profile.'),
      '#default_value' => variable_get('expire_user_term_pages', EXPIRE_USER_TERM_PAGES),
    );
  }

  if (module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) {
    $form['tabs']['user']['expire']['expire_user_reference_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('User reference pages'),
      '#description' => t('Expire urls of entities which are referenced from the expiring user profile.'),
      '#default_value' => variable_get('expire_user_reference_pages', EXPIRE_USER_REFERENCE_PAGES),
    );

    if (module_exists('field_collection')) {
      $form['tabs']['user']['expire']['expire_user_reference_field_collection_pages'] = array(
        '#type' => 'checkbox',
        '#title' => t('Traverse references attached to field collections'),
        '#description' => t('Expire urls of entities which are referenced from field collections attached to the expiring user.'),
        '#default_value' => variable_get('expire_user_reference_field_collection_pages', EXPIRE_USER_REFERENCE_FC_PAGES),
        '#states' => array(
          'visible' => array(
            ':input[name="expire_user_reference_pages"]' => array('checked' => TRUE),
          ),
        ),
      );
    }
  }

  $form['tabs']['user']['expire']['expire_user_custom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom pages'),
    '#description' => t('Expire user-defined custom urls.'),
    '#default_value' => variable_get('expire_user_custom', EXPIRE_USER_CUSTOM),
  );

  $form['tabs']['user']['expire']['expire_user_custom_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter custom URLs'),
    '#description' => t('Enter one relative URL per line. It can be the path of a node (e.g. !example1) or of any alias (e.g. !example2). However, it has to be the final URL, not a redirect (use the !link1 and !link2 modules).', array('!example1' => '<strong>user/[user:uid]</strong>', '!example2' => '<strong>my/path</strong>', '!link1' => l('Global Redirect', 'https://drupal.org/project/globalredirect'), '!link2' => l('Redirect', 'https://drupal.org/project/redirect'))) . '<br/>'
      . t('If you want to match a path with any ending, add "|wildcard" to the end of the line (see !link1 for details). Example: !example1 will match !example1a, but also !example1b, !example1c, etc.', array('!link1' => l('function cache_clear_all', 'https://api.drupal.org/api/drupal/includes%21cache.inc/function/cache_clear_all/7'), '!example1' => '<strong>my/path|wildcard</strong>', '!example1a' => '<strong>my/path</strong>', '!example1b' => '<strong>my/path/one</strong>', '!example1c' => '<strong>my/path/two</strong>')) . '<br/>'
      . t('You may use tokens here.'),
    '#states' => array(
      'visible' => array(
        ':input[name="expire_user_custom"]' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('expire_user_custom_pages'),
  );


  // FILE SETTINGS.
  if (module_exists('file')) {
    $form['tabs']['file'] = array(
      '#type' => 'fieldset',
      '#title' => t('File expiration'),
      '#group' => 'tabs',
      '#weight' => 4,
    );

    $form['tabs']['file']['actions'] = array(
      '#type' => 'fieldset',
      '#title' => t('File actions'),
    );

    $form['tabs']['file']['actions']['expire_file_actions'] = array(
      '#type' => 'checkboxes',
      '#description' => t('Page cache for file will be flushed after selected actions.'),
      '#options' => array(
        EXPIRE_FILE_UPDATE => t('File update'),
        EXPIRE_FILE_DELETE => t('File delete'),
      ),
      '#default_value' => variable_get('expire_file_actions', array()),
    );

    $form['tabs']['file']['expire'] = array(
      '#type' => 'fieldset',
      '#title' => t('What URLs should be expired when file action is triggered?'),
    );

    $form['tabs']['file']['expire']['expire_file_front_page'] = array(
      '#type' => 'checkbox',
      '#title' => t('Front page'),
      '#description' => t('Expire url of the site front page'),
      '#default_value' => variable_get('expire_file_front_page', EXPIRE_FILE_FRONT_PAGE),
    );

    $form['tabs']['file']['expire']['expire_file_file'] = array(
      '#type' => 'checkbox',
      '#title' => t('File url'),
      '#description' => t('Expire url of the expiring file.'),
      '#default_value' => variable_get('expire_file_file', EXPIRE_FILE_FILE),
    );

    $form['tabs']['file']['expire']['expire_file_custom'] = array(
      '#type' => 'checkbox',
      '#title' => t('Custom pages'),
      '#description' => t('Expire user-defined custom urls.'),
      '#default_value' => variable_get('expire_file_custom', EXPIRE_FILE_CUSTOM),
    );

    $form['tabs']['file']['expire']['expire_file_custom_pages'] = array(
      '#type' => 'textarea',
      '#title' => t('Enter custom URLs'),
      '#description' => t('Enter one relative URL per line, e.g. !example1.', array('!example1' => '<strong>file/[file:fid]</strong>')) . '<br/>'
        . t('If you want to match a path with any ending, add "|wildcard" to the end of the line (see !link1 for details). Example: !example1 will match !example1a, but also !example1b, !example1c, etc.', array('!link1' => l('function cache_clear_all', 'https://api.drupal.org/api/drupal/includes%21cache.inc/function/cache_clear_all/7'), '!example1' => '<strong>file/1</strong>', '!example1a' => '<strong>file/1</strong>', '!example1b' => '<strong>file/12</strong>', '!example1c' => '<strong>file/123</strong>')) . '<br/>'
        . t('You may use tokens here.'),
      '#states' => array(
        'visible' => array(
          ':input[name="expire_file_custom"]' => array('checked' => TRUE),
        ),
      ),
      '#default_value' => variable_get('expire_file_custom_pages'),
    );
  }


  // VOTINAPI SETTINGS.
  if (module_exists('votingapi')) {
    $form['tabs']['votingapi'] = array(
      '#type' => 'fieldset',
      '#title' => t('Votingapi expiration'),
      '#group' => 'tabs',
      '#weight' => 5,
    );

    $form['tabs']['votingapi']['actions'] = array(
      '#type' => 'fieldset',
      '#title' => t('Votingapi actions'),
    );

    $form['tabs']['votingapi']['actions']['expire_votingapi_actions'] = array(
      '#type' => 'checkboxes',
      '#description' => t('Page cache for votes will be flushed after selected actions.'),
      '#options' => array(
        EXPIRE_VOTINGAPI_INSERT => t('Vote insert'),
        EXPIRE_VOTINGAPI_DELETE => t('Vote delete'),
      ),
      '#default_value' => variable_get('expire_votingapi_actions', array()),
    );

    $form['tabs']['votingapi']['expire'] = array(
      '#type' => 'fieldset',
      '#title' => t('What URLs should be expired when votingapi action is triggered?'),
    );

    $form['tabs']['votingapi']['expire']['expire_votingapi_entity_page'] = array(
      '#type' => 'checkbox',
      '#title' => t('Voted entity page'),
      '#description' => t('Expire url of the voted entity.'),
      '#default_value' => variable_get('expire_votingapi_entity_page', EXPIRE_VOTINGAPI_ENTITY_PAGE),
    );

    $form['tabs']['votingapi']['expire']['expire_votingapi_entity'] = array(
      '#type' => 'checkbox',
      '#title' => t('Voted entity'),
      '#description' => t('Execute voted entity expiration. Note that will be executed expiration with expire settings for this entity type (user, node, etc).'),
      '#default_value' => variable_get('expire_votingapi_entity', EXPIRE_VOTINGAPI_ENTITY),
    );

    $form['tabs']['votingapi']['expire']['expire_votingapi_custom'] = array(
      '#type' => 'checkbox',
      '#title' => t('Custom pages'),
      '#description' => t('Expire user-defined custom urls.'),
      '#default_value' => variable_get('expire_votingapi_custom', EXPIRE_VOTINGAPI_CUSTOM),
    );

    $form['tabs']['votingapi']['expire']['expire_votingapi_custom_pages'] = array(
      '#type' => 'textarea',
      '#title' => t('Enter custom URLs'),
      '#description' => t('Enter one relative URL per line. It can be the path of a node (e.g. !example1) or of any alias (e.g. !example2). However, it has to be the final URL, not a redirect (use the !link1 and !link2 modules).', array('!example1' => '<strong>user/[user:uid]</strong>', '!example2' => '<strong>my/path</strong>', '!link1' => l('Global Redirect', 'https://drupal.org/project/globalredirect'), '!link2' => l('Redirect', 'https://drupal.org/project/redirect'))) . '<br/>'
        . t('If you want to match a path with any ending, add "|wildcard" to the end of the line (see !link1 for details). Example: !example1 will match !example1a, but also !example1b, !example1c, etc.', array('!link1' => l('function cache_clear_all', 'https://api.drupal.org/api/drupal/includes%21cache.inc/function/cache_clear_all/7'), '!example1' => '<strong>my/path|wildcard</strong>', '!example1a' => '<strong>my/path</strong>', '!example1b' => '<strong>my/path/one</strong>', '!example1c' => '<strong>my/path/two</strong>')) . '<br/>'
        . t('You may use tokens here.'),
      '#states' => array(
        'visible' => array(
          ':input[name="expire_votingapi_custom"]' => array('checked' => TRUE),
        ),
      ),
      '#default_value' => variable_get('expire_votingapi_custom_pages'),
    );
  }


  // MENU LINK SETTINGS.
  if (module_exists('menu')) {
    $form['tabs']['menu_links'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu links expiration'),
      '#group' => 'tabs',
      '#weight' => 6,
    );

    $form['tabs']['menu_links']['actions'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu link actions'),
    );

    $form['tabs']['menu_links']['actions']['expire_menu_link_actions'] = array(
      '#type' => 'checkboxes',
      '#description' => t('Page cache for user will be flushed after selected actions.'),
      '#options' => array(
        EXPIRE_MENU_LINK_INSERT => t('Menu link insert'),
        EXPIRE_MENU_LINK_UPDATE => t('Menu link update'),
        EXPIRE_MENU_LINK_DELETE => t('Menu link delete'),
      ),
      '#default_value' => variable_get('expire_menu_link_actions', array()),
    );

    $form['tabs']['menu_links']['expire_menu_link_override_menus'] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => t('What menus should expire their page urls (and at what depth) when menu is updated?'),
    );

    $options = array();
    for ($i = 0; $i <= MENU_MAX_DEPTH; $i++) {
      $options[$i] = $i ? t('@depth depth', array('@depth' => $i)) : t('None');
    }

    $menu_options = array_filter(variable_get('expire_menu_link_override_menus', array()));
    foreach (menu_get_menus() as $menu_name => $menu_label) {
      $form['tabs']['menu_links']['expire_menu_link_override_menus'][$menu_name] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => !empty($menu_options[$menu_name]) ? $menu_options[$menu_name] : 0,
        '#title' => check_plain($menu_label),
      );
    }
  }

  // Add the token tree UI.
  if (module_exists('token')) {

    $form['tabs']['node']['expire']['expire_node_custom_pages']['#description'] .= ' ' .
      theme('token_tree_link', array('text' => t('View available tokens.'), 'token_types' => array('node')));

    if (module_exists('comment')) {
      $form['tabs']['comment']['expire']['expire_comment_custom_pages']['#description'] .= ' ' .
        theme('token_tree_link', array('text' => t('View available tokens.'), 'token_types' => array('comment')));
    }

    $form['tabs']['user']['expire']['expire_user_custom_pages']['#description'] .= ' ' .
      theme('token_tree_link', array('text' => t('View available tokens.'), 'token_types' => array('user')));

    if (module_exists('file')) {
      $form['tabs']['file']['expire']['expire_file_custom_pages']['#description'] .= ' ' .
        theme('token_tree_link', array('text' => t('View available tokens.'), 'token_types' => array('file')));
    }

    if (module_exists('votingapi')) {
      $form['tabs']['votingapi']['expire']['expire_votingapi_custom_pages']['#description'] .= ' ' .
        theme('token_tree_link', array('text' => t('View available tokens.')));
    }
  }

  return system_settings_form($form);
}

/**
 * Settings form for a node type.
 */
function expire_node_settings_form(&$form) {

  if (empty($form['#node_type']->type)) {
    return;
  }

  $node_type = $form['#node_type']->type;

  $form['expire'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cache Expiration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
  );

  // NODE SETTINGS.
  $form['expire']['expire_node_override_defaults'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override default settings for this node type'),
    '#default_value' => variable_get('expire_node_override_defaults_' . $node_type),
  );

  // Copy here settings from default settings form.
  $settings_form = expire_admin_settings_form();
  $form['expire']['node_actions'] = $settings_form['tabs']['node']['actions'];
  $form['expire']['node_expires'] = $settings_form['tabs']['node']['expire'];

  // Display fieldsets with settings only if they should be overriden.
  $form['expire']['node_actions']['#states'] = array(
    'visible' => array(':input[name="expire_node_override_defaults"]' => array('checked' => TRUE)),
  );
  $form['expire']['node_expires']['#states'] = array(
    'visible' => array(':input[name="expire_node_override_defaults"]' => array('checked' => TRUE)),
  );

  // Change tab title to more suitable here.
  $form['expire']['node_expires']['#title'] = t('What pages should be expired when node action is triggered?');

  // COMMENT SETTINGS.
  if (module_exists('comment')) {

    $form['expire']['expire_comment_override_defaults'] = array(
      '#type' => 'checkbox',
      '#title' => t('Override default settings for comments to this node type'),
      '#default_value' => variable_get('expire_comment_override_defaults_' . $node_type),
    );

    $form['expire']['comment_actions'] = $settings_form['tabs']['comment']['actions'];
    $form['expire']['comment_expires'] = $settings_form['tabs']['comment']['expire'];

    // Display fieldsets with settings only if they should be overriden.
    $form['expire']['comment_actions']['#states'] = array(
      'visible' => array(':input[name="expire_comment_override_defaults"]' => array('checked' => TRUE)),
    );
    $form['expire']['comment_expires']['#states'] = array(
      'visible' => array(':input[name="expire_comment_override_defaults"]' => array('checked' => TRUE)),
    );
  }

  // Set default settings for this node type.
  $form['expire']['node_actions']['expire_node_actions']['#default_value'] =
    variable_get('expire_node_actions_' . $node_type, array());

  $form['expire']['node_expires']['expire_node_front_page']['#default_value'] =
    variable_get('expire_node_front_page_' . $node_type, EXPIRE_NODE_FRONT_PAGE);

  $form['expire']['node_expires']['expire_node_node_page']['#default_value'] =
    variable_get('expire_node_node_page_' . $node_type, EXPIRE_NODE_NODE_PAGE);

  if (module_exists('taxonomy')) {
    $form['expire']['node_expires']['expire_node_term_pages']['#default_value'] =
      variable_get('expire_node_term_pages_' . $node_type, EXPIRE_NODE_TERM_PAGES);
  }

  if (module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) {
    $form['expire']['node_expires']['expire_node_reference_pages']['#default_value'] =
      variable_get('expire_node_reference_pages_' . $node_type, EXPIRE_NODE_REFERENCE_PAGES);

    if (module_exists('field_collection')) {
      $form['expire']['node_expires']['expire_node_reference_field_collection_pages']['#default_value'] =
        variable_get('expire_node_reference_field_collection_pages_' . $node_type, EXPIRE_NODE_REFERENCE_FC_PAGES);
    }
  }

  $form['expire']['node_expires']['expire_node_custom']['#default_value'] =
    variable_get('expire_node_custom_' . $node_type, EXPIRE_NODE_CUSTOM);

  $form['expire']['node_expires']['expire_node_custom_pages']['#default_value'] =
    variable_get('expire_node_custom_pages_' . $node_type);

  // Set default values for comments to this node type.
  if (module_exists('comment')) {

    $form['expire']['comment_actions']['expire_comment_actions']['#default_value'] =
      variable_get('expire_comment_actions_' . $node_type, array());

    $form['expire']['comment_expires']['expire_comment_front_page']['#default_value'] =
      variable_get('expire_comment_front_page_' . $node_type, EXPIRE_COMMENT_FRONT_PAGE);

    $form['expire']['comment_expires']['expire_comment_comment_page']['#default_value'] =
      variable_get('expire_comment_comment_page_' . $node_type, EXPIRE_COMMENT_COMMENT_PAGE);

    $form['expire']['comment_expires']['expire_comment_node_page']['#default_value'] =
      variable_get('expire_comment_node_page_' . $node_type, EXPIRE_COMMENT_NODE_PAGE);

    if (module_exists('taxonomy')) {
      $form['expire']['comment_expires']['expire_comment_node_term_pages']['#default_value'] =
        variable_get('expire_comment_node_term_pages_' . $node_type, EXPIRE_COMMENT_NODE_TERM_PAGES);
    }

    if (module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) {
      $form['expire']['comment_expires']['expire_comment_reference_pages']['#default_value'] =
        variable_get('expire_comment_reference_pages_' . $node_type, EXPIRE_COMMENT_REFERENCE_PAGES);
    }

    if (module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) {
      $form['expire']['comment_expires']['expire_comment_node_reference_pages']['#default_value'] =
        variable_get('expire_comment_node_reference_pages_' . $node_type, EXPIRE_COMMENT_NODE_REFERENCE_PAGES);

      if (module_exists('field_collection')) {
        $form['expire']['comment_expires']['expire_comment_node_reference_field_collection_pages']['#default_value'] =
          variable_get('expire_comment_node_reference_field_collection_pages_' . $node_type, EXPIRE_COMMENT_NODE_REFERENCE_FC_PAGES);
      }
    }

    $form['expire']['comment_expires']['expire_comment_custom']['#default_value'] =
      variable_get('expire_comment_custom_' . $node_type, EXPIRE_COMMENT_CUSTOM);

    $form['expire']['comment_expires']['expire_comment_custom_pages']['#default_value'] =
      variable_get('expire_comment_custom_pages_' . $node_type);
  }

  // Attach js.
  $form['#attached']['js'][] = drupal_get_path('module', 'expire') . '/js/expire.admin.js';
}
