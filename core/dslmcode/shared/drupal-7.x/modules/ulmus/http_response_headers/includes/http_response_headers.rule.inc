<?php
/**
 * @file
 * Class definitions for the HTTP response headers rule.
 */

/**
 * Defines HttpResponseHeadersRule
 */
class HttpResponseHeadersRule {

  /**
   * A string machine name.
   *
   * @var string
   */
  public $machine_name;

  /**
   * A string human readable description.
   *
   * @var string
   */
  public $description;

  /**
   * A string HTTP header.
   *
   * @var string
   */
  public $header;

  /**
   * HTTP header value.
   *
   * @var mixed
   */
  public $header_value;

  /**
   * Comma separated pages.
   *
   * @var string
   */
  public $pages;

  /**
   * Visibility of the page.
   *
   * Allowed values are HTTP_RESPONSE_HEADERS_VISIBILITY_NOTLISTED
   * and HTTP_RESPONSE_HEADERS_VISIBILITY_LISTED.
   *
   * @var int
   */
  public $visibility;

  /**
   * Comma separated content types.
   *
   * @var string
   */
  public $types;

  /**
   * Comma separated role IDs.
   *
   * @var string
   */
  public $roles;

  /**
   * Type of export.
   *
   * @var string
   */
  public $export_type;

  /**
   * Constructs new HttpResponseHeadersRule object.
   */
  public function __construct() {
    // Initialise defaults.
    $this->visibility = HTTP_RESPONSE_HEADERS_VISIBILITY_NOTLISTED;
  }

  /**
   * Sets machine name.
   *
   * @param string $machine_name
   *   A string machine name.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setMachineName($machine_name) {
    $this->machine_name = $machine_name;

    return $this;
  }

  /**
   * Gets machine name.
   *
   * @return mixed
   *   A string description.
   */
  public function getMachineName() {
    return $this->machine_name;
  }

  /**
   * Sets description.
   *
   * @param string $description
   *   A string rule description.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setDescription($description) {
    $this->description = $description;

    return $this;
  }

  /**
   * Gets description.
   *
   * @return mixed
   *   A string description.
   */
  public function getDescription() {
    return $this->description;
  }

  /**
   * Sets export type.
   *
   * @param string $export_type
   *   A string of rule export type.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setExportType($export_type) {
    $this->export_type = $export_type;

    return $this;
  }

  /**
   * Gets export type.
   *
   * @return string
   *   A string export type.
   */
  public function getExportType() {
    return $this->export_type;
  }

  /**
   * Sets header.
   *
   * @param mixed $header
   *   A header.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setHeader($header) {
    $this->header_value = $header;

    return $this;
  }

  /**
   * Gets header value.
   *
   * @return mixed
   *   Header value.
   */
  public function getHeader() {
    return $this->header;
  }

  /**
   * Sets header value.
   *
   * @param mixed $header_value
   *   Header value.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setHeaderValue($header_value) {
    $this->header_value = $header_value;

    return $this;
  }

  /**
   * Gets header value.
   *
   * @return mixed
   *   Header value.
   */
  public function getHeaderValue() {
    return $this->header_value;
  }

  /**
   * Sets pages.
   *
   * @param string $pages
   *   A string of page lists.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setPages($pages) {
    $this->pages = $pages;

    return $this;
  }

  /**
   * Gets pages.
   *
   * @return string
   *   A string of page paths.
   */
  public function getPages() {
    return $this->pages;
  }

  /**
   * Sets roles.
   *
   * @param string $roles
   *   A comma separated string of user roles.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setRoles($roles) {
    $this->roles = $roles;

    return $this;
  }

  /**
   * Gets the roles.
   *
   * @return string
   *   A comma separated list of role IDs.
   */
  public function getRoles() {
    return $this->roles;
  }

  /**
   * Sets content types.
   *
   * @param string $types
   *   A string of comma separated content types.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setTypes($types) {
    $this->types = $types;

    return $this;
  }

  /**
   * Gets the types.
   *
   * @return mixed
   *   A string of comma separated content type.
   */
  public function getTypes() {
    return $this->types;
  }

  /**
   * Sets the visibility.
   *
   * @param int $visibility
   *   An integer page visibility flag.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function setVisibility($visibility) {
    $this->visibility = $visibility;

    return $this;
  }

  /**
   * Gets the visibility.
   *
   * @return int
   *   A integer visibility flag.
   */
  public function getVisibility() {
    return $this->visibility;
  }

  /**
   * Updates roles.
   *
   * @param array $roles
   *   An array of role with ID.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function updateRoles($roles = array()) {
    if (!empty($roles)) {
      $this->roles = implode(',', array_filter($roles));
    }

    return $this;
  }

  /**
   * Updates the content types.
   *
   * @param array $types
   *   An array of content type with key.
   *
   * @return HttpResponseHeadersRule
   *   The processed object.
   */
  public function updateTypes($types = array()) {
    if (!empty($types)) {
      $this->types = implode(',', array_filter($types));
    }

    return $this;
  }

  /**
   * Checks roles has set.
   *
   * @return bool
   *   TRUE if roles set, FALSE otherwise.
   */
  public function hasRoles() {
    return !empty($this->roles);
  }

  /**
   * Checks the roles against given $user_roles.
   *
   * @param array $user_roles
   *   An array of user role IDs.
   *
   * @return bool
   *   TRUE if exist, FALSE otherwise.
   */
  public function rolesExist(array $user_roles) {
    return !array_intersect(explode(',', $this->roles), array_keys($user_roles));
  }

  /**
   * Checks whether pages is set.
   *
   * @return bool
   *   TRUE if set, FALSE otherwise.
   */
  public function hasPages() {
    return !empty($this->pages);
  }

  /**
   * Checks whether pages is set.
   *
   * @return bool
   *   TRUE if set, FALSE otherwise.
   */
  public function hasTypes() {
    return !empty($this->types);
  }

  /**
   * Gets an array of types from string.
   *
   * @return array
   *   An array of content type names.
   */
  public function getTypeArray() {
    return $this->hasTypes() ? explode(',', $this->types) : array();
  }

}
