<?php

class SiteFeaturesBuilder extends FeaturesBuilderBase {

  protected $variables = array(
    'admin_theme',
    'block_cache',
    'cache',
    'cache_lifetime',
    'clean_url',
    'date_default_timezone',
    'dblog_row_limit',
    'default_nodes_main',
    'error_level',
    'features_builder_base_dir',
    'features_builder_ignore',
    'features_builder_prefix_label',
    'features_builder_prefix_name',
    'node_admin_theme',
    'page_cache_maximum_age',
    'page_compression',
    'preprocess_css',
    'preprocess_js',
    'site_default_country',
    'site_403',
    'site_404',
    'site_frontpage',
    'site_mail',
    'site_name',
    'site_slogan',
    'theme_default',
    'theme_settings',
    'update_notify_emails',
  );

  public static function listFeatures() {
    return array('site' => t('Site'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  protected function setComponents() {
    $this->setNamedComponents('variable', $this->variables);
    $this->setRegexComponents('variable', '/^theme_[a-z0-9_]*_settings$/');
    $this->setRegexComponents('variable', '/^date_format_[a-z0-9_]*$/');
    $this->setRegexComponents('variable', '/^date_views_[a-z0-9_]*$/');

    if (module_exists('admin_menu')) {
      $this->setNamedComponents('dependencies', array('admin_menu'));
      $this->setRegexComponents('variable', '/^admin_menu_/');
    }

    if (module_exists('environment_indicator')) {
      $this->setNamedComponents('dependencies', array('environment_indicator'));
      $this->setAllComponents('environment_indicator_environment');
    }

    if (module_exists('googleanalytics')) {
      $this->setNamedComponents('dependencies', array('googleanalytics'));
      $this->setRegexComponents('variable', '/^googleanalytics_/');
    }

    if (module_exists('honeypot')) {
      $this->setNamedComponents('dependencies', array('honeypot'));
      $this->setRegexComponents('variable', '/^honeypot_/');
    }

    if (module_exists('jquery_update')) {
      $this->setNamedComponents('dependencies', array('jquery_update'));
      $this->setRegexComponents('variable', '/^jquery_update_/');
    }

    if (module_exists('module_filter')) {
      $this->setNamedComponents('dependencies', array('module_filter'));
      $this->setRegexComponents('variable', '/^module_filter_/');
      if (!empty($this->components['variable']['module_filter_recent_modules'])) {
        unset($this->components['variable']['module_filter_recent_modules']);
      }
    }

    if (module_exists('scheduler')) {
      $this->setNamedComponents('dependencies', array('scheduler'));
      $this->setRegexComponents('variable', '/^scheduler_.*/');
    }

    if (module_exists('search')) {
      $this->setNamedComponents('dependencies', array('search'));
      $variables = array(
        'minimum_word_size',
        'node_rank_promote',
        'node_rank_recent',
        'node_rank_relevance',
        'node_rank_sticky',
        'overlap_cjk',
        'search_active_modules',
        'search_cron_limit',
        'search_default_module',
      );
      $this->setNamedComponents('variable', $variables);
    }

    if (module_exists('simplify')) {
      $this->setNamedComponents('dependencies', array('simplify'));
      $this->setRegexComponents('variable', '/^simplify_/');
    }

    if (module_exists('transliteration')) {
      $this->setNamedComponents('dependencies', array('transliteration'));
      $this->setRegexComponents('variable', '/^transliteration_/');
    }

    if (module_exists('webform')) {
      $this->setNamedComponents('dependencies', array('webform'));
      $this->setRegexComponents('variable', '/^webform_/');
    }
  }

}
