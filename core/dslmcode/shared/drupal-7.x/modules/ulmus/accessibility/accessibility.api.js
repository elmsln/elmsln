/**
 * These are samples of using the accessibility module's javascript API. To include
 * the accessibility API into a page, you should call accessibility_load() on the page as well.
 */

/**
 * The checkElement method takes a jQuery object and checks it against
 * your site's enabled tests. It will then call the testFailed and complete callbacks if supplied.
 */

Drupal.accessibility.checkElement($('#my-id'), function(event) { console.log(event); });

/**
 * The attachHint method takes the event object passed by QUAIL in a testFailed
 * callback and attaches a hint for the user to see the accessibility problem. 
 */

 Drupal.accessibility.checkElement($('#my-id'), function(event) {
 		 Drupal.accessibility.attachHint(event);
	 });