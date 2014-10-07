var H5PUtils = H5PUtils || {};

(function ($) {
  /**
   * Generic function for creating a table including the headers
   * 
   * @param {array} headers List of headers
   */
  H5PUtils.createTable = function (headers) {
    var $table = $('<table class="h5p-admin-table"></table>');
    
    if(headers) {
      var $thead = $('<thead></thead>');
      var $tr = $('<tr></tr>');
  
      $.each(headers, function (index, value) {
        $tr.append('<th>' + value + '</th>');
      });
      
      $table.append($thead.append($tr));
    }
    
    return $table;
  };
  
  /**
   * Generic function for creating a table row
   * 
   * @param {array} rows Value list. Object name is used as class name in <TD>
   */
  H5PUtils.createTableRow = function (rows) {
    var $tr = $('<tr></tr>');
    
    $.each(rows, function (index, value) {
      $tr.append('<td>' + value + '</td>');
    });
    
    return $tr;
  };
  
  /**
   * Generic function for creating a field containing label and value
   * 
   * @param {string} label The label displayed in front of the value 
   * @param {string} value The value
   */
  H5PUtils.createLabeledField = function (label, value) {
    var $field = $('<div class="h5p-labeled-field"></div>');
    
    $field.append('<div class="h5p-label">' + label + '</div>');
    $field.append('<div class="h5p-value">' + value + '</div>');
    
    return $field;
  };
  
  /**
   * Replaces placeholder fields in translation strings
   * 
   * @param {string} template The translation template string in the following format: "$name is a $sex"
   * @param {array} replacors An js object with key and values. Eg: {'$name': 'Frode', '$sex': 'male'}
   */
  H5PUtils.translateReplace = function (template, replacors) {
    $.each(replacors, function (key, value) {
      template = template.replace(new RegExp('\\'+key, 'g'), value);
    });
    return template;
  };
  
  /**
   * Get throbber with given text.
   * 
   * @param {String} text
   * @returns {$}
   */
  H5PUtils.throbber = function (text) {
    return $('<div/>', {
      class: 'h5p-throbber',
      text: text
    });
  };
  
  /**
   * Makes it possbile to rebuild all content caches from admin UI.
   * @param {Object} notCached
   * @returns {$}
   */
  H5PUtils.getRebuildCache = function (notCached) {
    var $container = $('<div class="h5p-admin-rebuild-cache"><p>' + notCached.message + '</p></div>');
    var $button = $('<button>' + notCached.button + '</button>').appendTo($container).click(function () {
      var $spinner = $('<div/>', {class: 'h5p-spinner'}).replaceAll($button);
      var parts = ['|', '/', '-', '\\'];
      var current = 0;
      var spinning = setInterval(function () {
        $spinner.text(parts[current]);
        current++;
        if (current === parts.length) current = 0;
      }, 100);
      
      var $counter = $container.find('.placeholder');
      var build = function () {
        $.post(notCached.url, function (left) {
          if (left === '0') {
            clearInterval(spinning);
            $container.remove();
            location.reload();
          }
          else {
            var counter = $counter.text().split(' ', 2);
            $counter.text(left + ' ' + counter[1]);
            build();
          }
        });
      };
      build();
    });
    
    return $container;
  };
  
})(H5P.jQuery);