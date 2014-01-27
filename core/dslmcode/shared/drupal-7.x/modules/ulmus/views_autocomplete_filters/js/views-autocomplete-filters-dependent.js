(function ($) {

/**
 * Overrides function from misc/autocomplete.js to send full form values instead
 * of just autocomplete value.
 */
Drupal.ACDB.prototype.search = function (searchString) {
  var db = this;
  this.searchString = searchString;

  // See if this string needs to be searched for anyway.
  searchString = searchString.replace(/^\s+|\s+$/, '');
  if (searchString.length <= 0 ||
    searchString.charAt(searchString.length - 1) == ',') {
    return;
  }

  // See if this key has been searched for before.
  if (this.cache[searchString]) {
    return this.owner.found(this.cache[searchString]);
  }

  // Fill data with form values if we're working with dependent autocomplete
  var data = '';
  if (this.owner.isDependent()) {
    data = this.owner.serializeOuterForm();
  }

  // Initiate delayed search.
  if (this.timer) {
    clearTimeout(this.timer);
  }
  this.timer = setTimeout(function () {
    db.owner.setStatus('begin');

    // Ajax GET request for autocompletion. We use Drupal.encodePath instead of
    // encodeURIComponent to allow autocomplete search terms to contain slashes.
    $.ajax({
      type: 'GET',
      url: db.uri + '/' + Drupal.encodePath(searchString),
      data: data,
      dataType: 'json',
      success: function (matches) {
        if (typeof matches.status == 'undefined' || matches.status != 0) {
          db.cache[searchString] = matches;
          // Verify if these are still the matches the user wants to see.
          if (db.searchString == searchString) {
            db.owner.found(matches);
          }
          db.owner.setStatus('found');
        }
      },
      error: function (xmlhttp) {
        alert(Drupal.ajaxError(xmlhttp, db.uri));
      }
    });
  }, this.delay);
};

/**
 * Function which checks if autocomplete depends on other filter fields.
 */
Drupal.jsAC.prototype.isDependent = function() {
  return $(this.input).hasClass('views-ac-dependent-filter');
};

/**
 * Returns serialized input values from form except autocomplete input.
 */
Drupal.jsAC.prototype.serializeOuterForm = function() {
  return $(this.input)
    .parents('form:first')
    .find('select[name], textarea[name], input[name][type!=submit]')
    .not(this.input)
    .serialize();
};

})(jQuery);