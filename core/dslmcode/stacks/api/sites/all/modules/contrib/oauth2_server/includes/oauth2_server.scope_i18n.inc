<?php

/**
 * The i18n controller for oauth2_server_scope entities.
 */
class OAuth2ScopeI18nStringController extends EntityDefaultI18nStringController {

  /**
   * Overrides EntityDefaultI18nStringController::hook_object_info().
   *
   * Changes the paths used to match the ones used for scopes.
   * (Scopes have no "manage/" in the url because of Menu API limitations)
   */
  public function hook_object_info() {
    $info = parent::hook_object_info();
    $wildcard = $this->menuWildcard();
    $path = $this->menuBasePath() . '/' . $wildcard;

    $info['oauth2_server_scope']['title'] = 'Scope';
    $info['oauth2_server_scope']['placeholders']['%oauth2_server'] = 'server';
    $info['oauth2_server_scope']['edit path'] = $path;
    $info['oauth2_server_scope']['translate tab'] = $path . '/translate';
    $info['oauth2_server_scope']['string translation']['translate path'] = $path . '/translate/%i18n_language';

    return $info;
  }
}
