<?php

/**
 * @file
 * Internationalization (i18n) class.
 */

/**
 * Path Breadcrumbs i18n object.
 */
class i18n_path_breadcrumbs_object extends i18n_string_object_wrapper {

  public function __construct($type, $object) {
    $this->type = $type;
    $this->object = is_scalar($object) ? $this->load_object($object) : $object;
  }

  /**
   * Translation mode for object.
   *
   * @return int
   *   Constant showing translate mode.
   */
  public function get_translate_mode() {
    if (!empty($this->object->translatable)) {
      return I18N_MODE_TRANSLATE;
    }
    return I18N_MODE_NONE;
  }

  /**
   * Access to object translation. This should check object properties and permissions.
   *
   * @return bool
   *   Param showing whether path breadcrumb is translatable or not.
   */
  protected function translate_access() {
    return user_access('translate interface') && user_access('administer path breadcrumbs') && $this->object->translatable;
  }

  /**
   * Get object strings for translation.
   *
   * @return mixed
   *   Translated properties.
   */
  protected function build_properties() {
    $properties = parent::build_properties();
    list($string_type, $object_id) = $this->get_string_context();
    foreach ($this->object->titles as $key => $title) {
      $properties[$this->get_textgroup()][$string_type][$object_id]['titles:' . $key] = array(
        'string' => $title,
        'title' => t('Title: @title (path: @path)', array('@title' => $title, '@path' => $this->object->paths[$key])),
      );
    }

    return $properties;
  }
}
