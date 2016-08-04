<?php

/**
 * @file
 * Additional functions.
 */

/**
 * ARRAY of all possible entry variables:
 * - Puzzler module variables:
 *   'api_endpoint' = API endpoint, with language code indicated as '@wplang'. Usually 'https://@wplang.wikipedia.org/w/api.php') but can be overriden using PHP snippets. Can be left empty.
 *   'todo' = What we ultimately want to retrieve (REQUIRED!)
 *   'timetocache' = How long should the API reply be cached in Drupal (puzzler_cache). Can be left empty.
 *   'imagestyle' = Name of the image style ... eg 'custom_400x___'
 * - Wikipedia API properties:
 *   'wppage' = Title of the Wikipedia entry. May keep spaces (no need for underscores).
 *   'wplang' = Two-letter code of the Wikipedia entry language.
 *   'wpaction' = 'action' attribute of the MediaWiki API, e.g. 'query'
 *   'wptitles' =
 *   'wpprop' =
 *   'wpformat' =
 *   'wpexintro' = If 1 then shows just the introduction (first section of an article). See https://www.mediawiki.org/wiki/Extension:TextExtracts
 *   'wpexplaintext' = Return extracts as plain text instead of limited HTML. See https://www.mediawiki.org/wiki/Extension:TextExtracts
 *   'wpredirects' =
 *   'wpdisablepp' =
 *   'wpsection' =
 *   'wpdisableeditsection' =
 *   'wpdisabletoc' =
 *   'wpiiprop' =
 *   'wptitle' =  // NB different usage from 'wptitles'
 * );
 */
function puzzler_wikipedia($puzzler_options) {

  // Trim all values first.
  $puzzler_options = array_map('trim', $puzzler_options);
  // Import array keys and values as variables.
  if (!is_array($puzzler_options) || empty($puzzler_options)) {
    watchdog('Puzzler', t('No valid array provided to ') . __FUNCTION__ . '.', NULL, WATCHDOG_ERROR);
    return;
  }
  else {
    extract($puzzler_options); // Watch out, extracted vars do not show in debugger, but they ARE set.
  }

  /*
   * Setting defaults and sanitization of input values
   */
  if (empty($api_endpoint)) {
    $api_endpoint = PUZZLER_FALLBACK_API_ENDPOINT;
  }

  if (empty($todo)) {
    watchdog('Puzzler', t('Input value for variable $todo is invalid.'), NULL, WATCHDOG_ERROR);
    return;
  }

  // @TODO $imagestyle

  // $timetocache
  if (!isset($timetocache) OR !is_numeric($timetocache)) $timetocache = check_plain(variable_get('puzzler_cache', PUZZLER_CACHE_DURATION));
  $timetocache = intval($timetocache); // Crucial because puzzler_cache does not like numbers as strings. Also, this usefully makes 0 from ''.

  // $wppage
  if (isset($wptitle)) { // If $wptitle is set (for action = render), then $wppage is useless.
    unset($wppage);
  }
  else {
    // We really require $wppage. Stop if there is none.
    if (empty($wppage)) {
      watchdog('Puzzler', t('Input value for variable $wppage is invalid.'), NULL, WATCHDOG_ERROR);
      return;
    }
  }

  // $wplang
  if (!isset($wplang) OR $wplang == '' OR $wplang == 'und' OR !is_string($wplang) OR strlen($wplang) <> 2) {
    // If $wplang is invalid, set it to the fallback value.
    $wplang = check_plain(variable_get('puzzler_fallback_language', PUZZLER_FALLBACK_LANGUAGE));
  }
  //dpm('lang set: ' . $wplang);

  // $wpaction @TODO provide even more alternatives
  if (!isset($wpaction) OR ($wpaction <> 'query' AND $wpaction <> 'render')) {
    $wpaction = 'query';
  }

  // $wptitles
  if ($wpaction == 'render') { // Action 'render' is special, most other ones must be off.
    unset($wptitles);
  }

  // $wpprop; Not strictly necessary, adds additional properties in the result object. @TODO provide more alternatives
  if (!isset($wpprop) OR ($wpprop <> 'info' AND $wpprop <> 'extracts' AND $wpprop <> 'pageimages')) {
    $wpprop = 'info';
  }
  if ($wpaction == 'render') { // Action 'render' is special, most other ones must be off.
    unset($wpprop);
  }

  // $wpformat @TODO provide more alternatives
  if (!isset($wpformat) OR ($wpformat <> 'json' AND $wpformat <> 'xml')) {
    $wpformat = 'json';
  }
  if ($wpaction == 'render') { // Action 'render' is special, most other ones must be off.
    unset($wpformat);
  }

  // $wpexintro can be either 0 or 1, otherwise unset.
  if (isset($wpexintro) AND $wpexintro <> 1 AND $wpexintro <> 0) unset($wpexintro);

  // $wpexplaintext can be either 0 or 1, otherwise unset.
  if (isset($wpexplaintext) AND $wpexplaintext <> 1 AND $wpexplaintext <> 0) unset($wpexplaintext);

  // $wpredirects can be either 0 or 1, otherwise set to 1.
  if (!isset($wpredirects) OR !is_numeric($wpredirects) OR ($wpredirects <> 1 AND $wpredirects <> 0)) {
    // Allow Wikipedia to follow redirects to the final result, if needed.
    $wpredirects = 1;
  }
  if ($wpaction == 'render') { // Action 'render' is special, most other ones must be off.
    unset($wpredirects);
  }

  // @TODO $wpdisablepp

  // @TODO $wpsection

  // @TODO $wpdisableeditsection

  // @TODO $wpdisabletoc

  // @TODO $wpiiprop
  if (isset($wpiiprop) AND $wpiiprop <> 'url') unset($wpiiprop);

  // @TODO $wptitle
  if (isset($wptitle)) $wptitle = $wptitle; // Rubbish, but otherwise PHP does not know the variable is set (bug in extract()?)!

  // Test if we have all necessary input for the various cases
  switch ($todo) {
    // Gets a WP article URL for the given language, taking into account redirects. Eg local title is Cock fighting and WP URL resolves to https://en.wikipedia.org/wiki/Cockfight
    case 'wikipedia-matching-url':
      if (!isset($wppage) OR !isset($wplang)) {
        watchdog('Puzzler', t('Some required parameters for %todo are missing or invalid.'), array('%todo' => $todo), WATCHDOG_ERROR);
        return;
      }
      break;
    // Gets a WP article title for the given language, taking into account redirects. Eg local title is Cock fighting and WP title resolves to Cockfight.
    case 'wikipedia-matching-title':
      if (!isset($wppage) OR !isset($wplang)) {
        watchdog('Puzzler', t('Some required parameters for %todo are missing or invalid.'), array('%todo' => $todo), WATCHDOG_ERROR);
        return;
      }
      break;
    // Gets a WP article HTML for the given language, taking into account redirects.
    case 'wikipedia-matching-html':
      if (!isset($wptitle) OR !isset($wplang)) {
        watchdog('Puzzler', t('Some required parameters for %todo are missing or invalid.'), array('%todo' => $todo), WATCHDOG_ERROR);
        return;
      }
      break;
    // Gets a WP article intro for the given language, taking into account redirects.
    case 'wikipedia-matching-intro':
      if (!isset($wppage) OR !isset($wplang)) {
        watchdog('Puzzler', t('Some required parameters for %todo are missing or invalid.'), array('%todo' => $todo), WATCHDOG_ERROR);
        return;
      }
      break;
    case 'wikipedia-matching-image-url':
      if (!isset($wppage) OR !isset($wplang)) {
        watchdog('Puzzler', t('Some required parameters for %todo are missing or invalid.'), array('%todo' => $todo), WATCHDOG_ERROR);
        return;
      }
      break;
    case 'wikipedia-matching-image-html':
      if (!isset($wppage) OR !isset($wplang)) {
        watchdog('Puzzler', t('Some required parameters for %todo are missing or invalid.'), array('%todo' => $todo), WATCHDOG_ERROR);
        return;
      }
      break;
  }

  $gotten_data_decoded = puzzler_wikipedia_request($api_endpoint, $timetocache, $wplang, @$wppage, @$wppage_prefix, @$wpprop, @$wpformat, @$wpredirects, $wpaction, @$wpexintro, @$wpexplaintext, @$wpiiprop, @$wptitle);
  if ($gotten_data_decoded === FALSE) {
    // No need to emit watchdog message here, we took care of it in puzzler_wikipedia_cacher().
    return;
  }

  // Test if we have all necessary input for the various cases
  switch ($todo) {
    // Gets a WP article URL for the given language, taking into account redirects (Eg local title is Cock fighting and WP title resolves to Cockfighting.)
    case 'wikipedia-matching-url':
      $gotten_wp_id = key((array)$gotten_data_decoded->query->pages);
      $wptitle = $gotten_data_decoded->query->pages->$gotten_wp_id->title;
      //dpm($wptitle);
      // Important because otherwise it pointed to https://en.wikipedia.org/wiki/Alzheimer%27s+disease (non-existing page) instead of https://en.wikipedia.org/wiki/Alzheimer%27s_disease!
      $wptitleunderlined = str_replace(' ', '_', $wptitle);
      $wppagelanguage = $gotten_data_decoded->query->pages->$gotten_wp_id->pagelanguage;
      //dpm($wppagelanguage);
      $wp_url_of_matching_article = 'https://' . $wppagelanguage . '.wikipedia.org/wiki/' . urlencode($wptitleunderlined);
      //dpm($wp_url_of_matching_article);
      return $wp_url_of_matching_article;
      break;
    case 'wikipedia-matching-title':
      $gotten_wp_id = key((array)$gotten_data_decoded->query->pages);
      $wp_title_of_matching_article = $gotten_data_decoded->query->pages->$gotten_wp_id->title;
      //dpm($wp_title_of_matching_article);
      return $wp_title_of_matching_article;
      break;
    case 'wikipedia-matching-html':
      // This is special - another URL and action is 'render', see https://www.mediawiki.org/wiki/API:FAQ#get_the_content_of_a_page_.28HTML.29.3F
      // @TODO try to harmonize this with the rest, with cleaner output, maybe iterate through sections (see extracts)?
      //dpm($gotten_data_decoded);
      //$wp_html_of_matching_article = $gotten_data_decoded->data;
      $wp_html_of_matching_article = $gotten_data_decoded;
      return $wp_html_of_matching_article;
      /*
      $apirequest = 'http://' . $wplang . '.wikipedia.org/w/index.php?action=' . $wpaction . '&title=' . urlencode($wppage); // NB "title" instead of "titles" in this case.
      //dpm($apirequest);
      $options = array(
        'apirequest' => $apirequest,
      );
      //dpm($options);
      $gotten = puzzler_wikipedia_cacher($options, $timetocache);
      if ($gotten === FALSE) {
        return FALSE;
      }
      //dpm($gotten);
      // $gotten->data contains the HTML of the page - no need for json_decode etc if working with action=render
      $wp_html_of_matching_article = trim($gotten->data);
      //dpm($wp_html_of_matching_article);
      return $wp_html_of_matching_article;
      */
      break;
    case 'wikipedia-matching-intro':
      $gotten_wp_id = key((array)$gotten_data_decoded->query->pages);
      if (property_exists($gotten_data_decoded->query->pages->$gotten_wp_id, 'extract')) { // property_exists() requires PHP 5.1+ see http://php.net/manual/en/function.property-exists.php
        $wp_intro_of_matching_article = $gotten_data_decoded->query->pages->$gotten_wp_id->extract;
        //dpm($wp_intro_of_matching_article);
      }
      else {
        watchdog('Puzzler', t('No introduction found for ') . $wppage . '.', NULL, WATCHDOG_INFO);
        return;
      }
      // Some HTML tag cleanup. @TODO Harmonize / cleanup approach and code. See http://stackoverflow.com/questions/7185288/how-to-get-wikipedia-content-using-wikipedias-api See what Google does: https://www.google.be/search?q=leaky+gut+syndrome vs https://en.wikipedia.org/wiki/Leaky_gut_syndrome
      $wp_intro_of_matching_article = strip_tags($wp_intro_of_matching_article, '<p><sup><sub>');
      $wp_intro_of_matching_article = str_replace("<p></p>", '', $wp_intro_of_matching_article); // Removes "<p></p>" that is at the end of the extract (see https://en.wikipedia.org/w/api.php?prop=extracts&format=xml&redirects=1&action=query&titles=Albert_einstein&exintro=1)
      $wp_intro_of_matching_article = trim($wp_intro_of_matching_article);
      //dpm($wp_intro_of_matching_article);
      return $wp_intro_of_matching_article;
      break;
    case 'wikipedia-matching-image-url':
      $gotten_wp_id = key((array)$gotten_data_decoded->query->pages);
      // Gets the first (meaningful) image of content from WP for the given language, taking into account redirects (Eg local title is Cock fighting and WP title resolves to Cockfighting.)
      // http://stackoverflow.com/questions/8363531/accessing-main-picture-of-wikipedia-page-by-api
      // or http://techslides.com/grab-wikipedia-pictures-by-api-with-php
      // E.g. https://en.wikipedia.org/w/api.php?action=query&titles=Albert%20Einstein&prop=images&redirects=1&format=json
      //$page_title = $gotten_data_decoded->query->pages->$gotten_wp_id->title; // Not needed we can get it using another token or call.
      //dpm($page_title);
      if (property_exists($gotten_data_decoded->query->pages->$gotten_wp_id, 'pageimage')) { // property_exists() requires PHP 5.1+ see http://php.net/manual/en/function.property-exists.php
        $pageimage_file_name = $gotten_data_decoded->query->pages->$gotten_wp_id->pageimage;
      }
      else {
        watchdog('Puzzler', t('No illustration found for ') . $wppage . '.', NULL, WATCHDOG_INFO);
        return;
      }
      //dpm($pageimage_file_name);
      // The image's file PAGE could be constructed like this http://en.wikipedia.org/wiki/File:Albert_Einstein_(Nobel).png but we do not need it.

      $wppage2 = $pageimage_file_name;
      $wppage_prefix2 = 'File:';
      $wpprop2 = 'imageinfo';
      $wpiiprop2 = 'url';
      $gotten_data_decoded2 = puzzler_wikipedia_request($api_endpoint, $timetocache, $wplang, $wppage2, @$wppage_prefix2, $wpprop2, $wpformat, $wpredirects, $wpaction, @$wpexintro, @$wpexplaintext, @$wpiiprop2, @$wptitle);
      if ($gotten_data_decoded2 === FALSE) {
        // No need to emit watchdog message here, we took care of it in puzzler_wikipedia_cacher().
        return;
      }
      //dpm($gotten_data_decoded2);
      $gotten_wp_id2 = key((array)$gotten_data_decoded2->query->pages);
      $pageimage_file_key = key((array)$gotten_data_decoded2->query->pages->$gotten_wp_id2->imageinfo);
      $wp_image_of_matching_article = $gotten_data_decoded2->query->pages->$gotten_wp_id2->imageinfo[$pageimage_file_key]->url;
      //dpm($wp_image_of_matching_article);
      return $wp_image_of_matching_article;
      break;
    case 'wikipedia-matching-image-html':
      /*
      'wppage' => $data['node']->title, // 'Albert_Einstein'
      'wplang' => $data['node']->language,
      'wpprop' => 'pageimages',
      */
      $puzzler_options_new = array(
        'wppage' => $puzzler_options['wppage'],
        'wplang' => $puzzler_options['wplang'],
        'todo' => 'wikipedia-matching-title',
      );
      $article_title = puzzler_wikipedia($puzzler_options_new);
      //dpm($article_title);
      $puzzler_options_new = array(
        'wppage' => $puzzler_options['wppage'],
        'wplang' => $puzzler_options['wplang'],
        'wpprop' => 'pageimages',
        'todo' => 'wikipedia-matching-image-url',
      );
      $image_url = puzzler_wikipedia($puzzler_options_new);
      //dpm($image_url);
      if ($article_title <> '' AND $image_url <> '') {
        $wp_image_html_of_matching_article = '<img alt="' . $article_title . '" src="' . $image_url . '" title="' . $article_title . '" />';
        return $wp_image_html_of_matching_article;
      }
      break;
    }

}

/**
 * @param $api_endpoint
 * @param $timetocache
 * @param $wplang
 * @param $wppage
 * @param $wppage_prefix
 * @param $wpprop
 * @param $wpformat
 * @param $wpredirects
 * @param $wpaction
 * @param $wpexintro
 * @param $wpexplaintext
 * @param $wpiiprop
 * @param $wptitle
 * @return bool|mixed
 */
function puzzler_wikipedia_request($api_endpoint, $timetocache, $wplang, $wppage, $wppage_prefix, $wpprop, $wpformat, $wpredirects, $wpaction, $wpexintro, $wpexplaintext, $wpiiprop, $wptitle) {

  $api_endpoint = str_replace('@wplang', $wplang, $api_endpoint);

  if (isset($wppage)) $wppage_prefixed = $wppage_prefix . $wppage; // No need to urlencode $wppage.
  $api_urlproperties = array(
    'prop' => @$wpprop,
    'format' => @$wpformat,
    'redirects' => @$wpredirects,
    'action' => $wpaction,
    'titles' => @$wppage_prefixed,
    'exintro' => $wpexintro,
    'explaintext' => $wpexplaintext,
    'iiprop' => $wpiiprop,
    'title' => $wptitle,
  );
  $apirequest = $api_endpoint . '?' . http_build_query($api_urlproperties);
  //dpm($apirequest);
  $options = array( // Keep options (as it were) open, now caching only on basis of $apirequest, but other items may be added to the array in some cases to make an unique cache ID.
    'apirequest' => $apirequest,
  );
  $gotten = puzzler_wikipedia_cacher($options, $timetocache);
  if ($gotten === FALSE) {
    return FALSE;
  }

  if ($wpaction <> 'render') {
    $gotten_data_decoded = json_decode($gotten->data);
    //dpm($gotten_data_decoded);
  }
  else {
    $gotten_data_decoded = $gotten->data;
    //dpm($gotten_data_decoded);
  }

  /*
   * @TODO:
   *   -1 in key of query->pages means "not found" - see https://www.mediawiki.org/wiki/API:Query#Missing_and_invalid_titles
   *   BUT for image URLs (prop=imageinfo)
   *   whilst many requests are non-negative eg https://en.wikipedia.org/w/api.php?prop=imageinfo&format=jsonfm&redirects=1&action=query&titles=File%3AEinstein_1921_by_F_Schmutzer_-_restoration.jpg&iiprop=url
   *   many other ones have -1 but are still valid eg https://en.wikipedia.org/w/api.php?prop=imageinfo&format=jsonfm&redirects=1&action=query&titles=File%3ASoviet_famine_children.jpg&iiprop=url or https://en.wikipedia.org/w/api.php?prop=imageinfo&format=jsonfm&redirects=1&action=query&titles=File%3APaul_Otlet_%C3%A0_son_bureau_(cropped).jpg&iiprop=url
   *   So for the time being exit at negative values except in case of prop = imageinfo!
   */
  if (@$wpprop <> 'imageinfo' AND $wpaction <> 'render') {

    $gotten_wp_id = key((array)$gotten_data_decoded->query->pages);
    //dpm($gotten_wp_id);

    if ($gotten_wp_id < 0 ) {
      watchdog('Puzzler', t('No valid Wikipedia data retrieved from ') . $apirequest, NULL, WATCHDOG_ERROR);
      return FALSE;
    }

  }

  return $gotten_data_decoded;
}

/**
 * @param $options to serve as an unique cache key
 * @param $timetocache
 * @return object
 */
function puzzler_wikipedia_cacher($options, $timetocache) {
  // Import array keys and values as variables, e.g. $apirequest
  extract($options);

  //dpm($apirequest);
  //dpm($timetocache);
  //dpm($options);

  $urlencoded_hash = md5(serialize($options));
  //dpm($urlencoded_hash);

  if (puzzler_cache_has($urlencoded_hash)) {
    $gotten_serialized = gzuncompress(puzzler_cache_get($urlencoded_hash));
    $gotten = unserialize($gotten_serialized);
    //dpm($gotten);
    //dpm('CACHE');
  }
  else {
    if (module_exists('httprl')) {
      //dpm('using httprl');
      $httprl_options = array(
        'timeout' => 90,
        // We are using BLOCKING requests so as not to strain the target website with parallel requests.
        'blocking' => TRUE,
        // Accept-Encoding is crucial - this is how most browsers, but also GoogleBot, request content.
        'headers' => array('Accept-Encoding' => 'gzip'),
      );
      httprl_request($apirequest, $options);
      // Execute request.
      $gotten = httprl_send_request();
      $gotten = $gotten[$apirequest]; // Now gotten contains property 'code' as well as property 'data' just like the result of drupal_http_request().
      //dpm($gotten);
    }
    else {
      //dpm('using drupal_http_request');
      $gotten = drupal_http_request($apirequest);
      //dpm($gotten);
    }
    if ($gotten->code <> 200) {
      // Important to test for an error immediately here. If no response from WP or other error, end immediately.
      watchdog('Puzzler', t('Invalid Wikipedia API query %apirequest (response code was: %gottencode).'), array('%apirequest' => $apirequest, '%gottencode' => $gotten->code), WATCHDOG_ERROR);
      return FALSE;
    }
    if ($timetocache <> 0) {
      $gotten_serialized = serialize($gotten);
      $gotten_gzipped = gzcompress($gotten_serialized, 9); // Need to compress this because the puzzler_cache column is small ('blob') ... see https://www.drupal.org/node/2384637
      puzzler_cache_set($urlencoded_hash, $gotten_gzipped, $timetocache);
    }
    //dpm('NO CACHE');
  }

  return $gotten;
}

/**
 * Provide information about our custom tokens.
 *
 * @see http://api.drupal.org/api/drupal/modules--system--system.api.php/function/hook_token_info/7
 * @see http://www.benmarshall.me/drupal-custom-tokens
 * @return array
 *   An associative array of available tokens and token types.
 */
function puzzler_token_info() {
  $info['types']['puzzler'] = array(
    'name' => t('Puzzler tokens'),
    'description' => t('Tokens provided by the Puzzler module.'),
    //'needs-data' => 'node',
  );
  $info['tokens']['puzzler']['wikipedia-matching-url'] = array(
    'name' => t('Wikipedia - URL of article with matching title'),
    'description' => t('URL of the Wikipedia article whose title matches the title of the given node.'),
  );
  $info['tokens']['puzzler']['wikipedia-matching-title'] = array(
    'name' => t('Wikipedia - title of article with matching title'),
    'description' => t('Title of the Wikipedia article whose title matches the title of the given node.'),
  );
  $info['tokens']['puzzler']['wikipedia-matching-html'] = array(
    'name' => t('Wikipedia - HTML of article with matching title'),
    'description' => t('HTML of the Wikipedia article whose title matches the title of the given node.'),
  );
  $info['tokens']['puzzler']['wikipedia-matching-intro'] = array(
    'name' => t('Wikipedia - introduction of article with matching title'),
    'description' => t('Introductory text of the Wikipedia article whose title matches the title of the given node.'),
  );
  $info['tokens']['puzzler']['wikipedia-matching-image-url'] = array(
    'name' => t('Wikipedia - image (URL) of article with matching title'),
    'description' => t('URL of the first image of the Wikipedia article whose title matches the title of the given node.'),
  );
  $info['tokens']['puzzler']['wikipedia-matching-image-html'] = array(
    'name' => t('Wikipedia - image (HTML) of article with matching title'),
    'description' => t('HTML code to show the first image of the Wikipedia article whose title matches the title of the given node.'),
  );
  return $info;
}

/**
 * Provide replacement values for placeholder tokens.
 *
 * @see http://api.drupal.org/api/drupal/modules--system--system.api.php/function/hook_tokens/7
 * @param string $type
 *   The machine-readable name of the type (group) of token being replaced, such
 *   as 'node', 'user', or another type defined by a hook_token_info()
 *   implementation.
 * @param array $tokens
 *   An array of tokens to be replaced. The keys are the machine-readable token
 *   names, and the values are the raw [type:token] strings that appeared in the
 *   original text.
 * @param array $data (optional)
 *   An associative array of data objects to be used when generating replacement
 *   values, as supplied in the $data parameter to token_replace().
 * @param array $options (optional)
 *   An associative array of options for token replacement; see token_replace()
 *   for possible values.
 * @return array
 *   An associative array of replacement values, keyed by the raw [type:token]
 *   strings from the original text.
 */
function puzzler_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);
  // Check for 'user' token type.
  if ($type == 'puzzler') {
    foreach ($tokens as $name => $original) {
      $puzzler_options = array();

      //dpm($name);
      $given_title = '';
      if (strpos($name, ':')) {
        $exploded = explode(':', $name);
        //dpm($exploded);
        if (sizeof($exploded) == 1) {
          // Nothing; there is no ":" in $name, so we just continue using $name.
        }
        elseif (sizeof($exploded) == 2)
          $name = trim($exploded[0]);
          $given_title = check_plain(trim($exploded[1]));
      }

      if ($given_title <> '') {
        // If there is a text provided after the $name, use it instead of the current node title!
        $title = $given_title;
      }
      else if (isset($data['node']) && property_exists($data['node'], 'title')) {
        // There was no specific title provided, let's look in the $node object.
        $title = $data['node']->title;
      }
      else {
        // No title given; this is an error.
        watchdog('Puzzler', t('No title found or given.'), NULL, WATCHDOG_ERROR);
        $title = '';
      }

      // If we have node information, let's try to derive language from it. If not, take the default language.
      if (isset($data['node']) && property_exists($data['node'], 'language') && $data['node']->language <> '' && $data['node']->language <> 'und') {
        $language = $data['node']->language;
      }
      else {
        $language = check_plain(variable_get('puzzler_fallback_language', PUZZLER_FALLBACK_LANGUAGE));
      }

      switch ($name) {
        // Define replacement for the 'session-status' token.
        case 'wikipedia-matching-url':
          $puzzler_options = array(
            'wppage' => $title,
            'wplang' => $language,
            'todo' => $name,
          );
          $value = puzzler_wikipedia($puzzler_options);
          $replacements[$original] = $value;
          break;
        case 'wikipedia-matching-title':
          $puzzler_options = array(
            'wppage' => $title,
            'wplang' => $language,
            'todo' => $name,
          );
          $value = puzzler_wikipedia($puzzler_options);
          $replacements[$original] = $value;
          break;
        case 'wikipedia-matching-html':
          $puzzler_options = array(
            'api_endpoint' => 'http://@wplang.wikipedia.org/w/index.php',
            //'wptitle' => urlencode($data['node']->title),
            'wptitle' => $title,
            'wpaction' => 'render',
            'wplang' => $language,
            'todo' => $name,
          );
          $value = puzzler_wikipedia($puzzler_options);
          $replacements[$original] = $value;
          break;
        case 'wikipedia-matching-intro':
          $puzzler_options = array(
            'wppage' => $title,
            'wpprop' => 'extracts',
            'wpexintro' => 1,
            //'wpexplaintext' => 1, // Not using because it also removed paragraphs.
            'wplang' => $language,
            'todo' => $name,
          );
          $value = puzzler_wikipedia($puzzler_options);
          $replacements[$original] = $value;
          break;
        case 'wikipedia-matching-image-url':
          $puzzler_options = array(
            'wppage' => $title,
            'wplang' => $language,
            'wpprop' => 'pageimages',
            'todo' => $name,
          );
          $value = puzzler_wikipedia($puzzler_options);
          $replacements[$original] = $value;
          break;
        case 'wikipedia-matching-image-html':
          $puzzler_options = array(
            'wppage' => $title,
            'wplang' => $language,
            'wpprop' => 'pageimages',
            'todo' => $name,
          );
          $value = puzzler_wikipedia($puzzler_options);
          $replacements[$original] = $value;
          break;
      }
    }
  }
  return $replacements;
}


/**
 * Information relevant to the Puzzler module activity on this site.
 */
function puzzler_dashboard() {
  $result = '';

  $result .= t('<p><h2>Puzzler module dashboard</h2>');

  $result .= '<p>' . t('Puzzler makes it easy to insert bits and pieces of Wikipedia content into Drupal, keeping the information fresh as improvements are done by the community of Wikipedia editors.');

  $cached_puzzles = db_query("SELECT count(*) FROM {puzzler_cache}")->fetchField();
  //dpm($cached_puzzles);
  $result .= '<p><h4>' . t('Total number of currently cached puzzles (results of API calls)') . ':</h4>';
  $result .= '<ul>';
  $result .= '<li>' . $cached_puzzles . '</li>';
  $result .= '</ul>';

  $result .= '<p><h4>' . t('Tokens available by the module') . ':</h4>';
  $puzzler_token_info = puzzler_token_info();
  foreach ($puzzler_token_info['tokens']['puzzler'] as $key => $arr) {
    $result .= '<ul>';
    $result .= '<li>[puzzler:' . $key . '] => ' . $arr['description'] . '</li>';
    $result .= '</ul>';
  }

  $result .= '<p>' . t('Any of the above tokens can be extended by one more parameter — a custom title. Depending on use case, sometimes you will want to show Wikipedia information from a particular entry that is not (exactly) matching the title of your page. All you need to do is to add another colon and set the requested title manually.');
  $result .= '<br />' . t('E.g. [puzzler:wikipedia-matching-intro:Richard Feynman] will retrieve the introduction section of the Wikipedia article on Richard Feynman regardless the title of your Drupal page.');
  /*
  $info['types']['puzzler'] = array(
    'name' => t('Puzzler module tokens'),
    'description' => t('Tokens provided by the Puzzler module.'),
  $info['tokens']['puzzler']['wikipedia-matching-url'] = array(
  */

  return $result;
}
