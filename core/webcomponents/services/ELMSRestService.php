<?php

abstract class ELMSRestService {

  /**
   * This function adds filtering and pager functionality to the standard
   * entity field query.
   * 
   * @param object $query  the un-executed entity field query
   * @param array $options  (optional) a list of options returned from the url query params
   *      - @param int limit  (optional) how many results per page
   *      - @param page number  (optional) what page would you like to start
   *      - @param string order  (optional) either ASC or DESC
   */
  public function executeQuery($query, array $options = NULL) {
    $return = array();

    // order by most recent node changed
    $_order = (isset($options['order']) ? $options['order'] : 'DESC');
    $query->propertyOrderBy('changed', $order);

    $_limit = (isset($options['limit']) ? $options['limit'] : 10);
    // the pager will automatically look at the 'page' query param to see
    // what the specified page should be
    // https://api.drupal.org/api/drupal/includes%21pager.inc/function/pager_find_page/7.x
    $query->pager($_limit);
    $results = $query->execute();

    // add the pageing information to the return array in the form of JSON spec
    // http://jsonapi.org/format/#fetching-pagination
    // print_r($query);
    if (isset($query->pager['total'])) {
      // if we have a pager total then use that information
      $return['total'] = round($query->pager['total']);
      $return['count'] = count($results['node']);
      $return['first'] = round('0');
      // find the last page based on total results and limit, account for pager starting at zero
      $return['last'] = round($query->pager['total'] / $_limit);
      $return['current'] = pager_find_page();
    }
    else {
      // if we don't have pager info then we'll assume that we have the full listing
      $return['total'] = count($results['node']);
      $return['count'] = count($results['node']);
      $return['first'] = round('0');
      $return['last'] = round('0');
      $return['current'] = pager_find_page();
    }
    // add the results to the 'list' property
    $return['list'] = $results;
    return $return;
  }

}