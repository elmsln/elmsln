(function ($) {
  Drupal.prettyJson = {
   replacer: function(match, pIndent, pKey, pVal, pEnd) {
      var key = '<span class="json-key">';
      var val = '<span class="json-value>"';
      var str = '<span class="json-string">';
      var r = pIndent || '';
      if (pKey)
         r = r + key + pKey.replace(/[": ]/g, '') + '</span>: ';
      if (pVal)
         r = r + (pVal[0] == '"' ? str : val) + pVal + '</span>';
      return r + (pEnd || '');
      },
   prettyPrint: function(obj) {
      var jsonLine = /^( *)("[\w]+": )?("[^"]*"|[\w.+-]*)?([,[{])?$/mg;
      return JSON.stringify(obj, null, 3)
         .replace(/&/g, '&amp;').replace(/\\"/g, '&quot;')
         .replace(/</g, '&lt;').replace(/>/g, '&gt;')
         .replace(jsonLine, Drupal.prettyJson.replacer);
      }
  };
  $(document).ready(function(){
    // when an xapi statement is expanded, make it more readable
    $('.elmsln-core-lrs-data-display .xapi-statement-raw').click(function(){
      if (!$(this).hasClass('xapi-colorization')) {
        $(this).addClass('xapi-colorization');
        var json = jQuery.parseJSON($(this).siblings('.collapsible-body').children('pre').html());
        $(this).siblings('.collapsible-body').children('pre').html(Drupal.prettyJson.prettyPrint(json));
      }
    });
  });
})(jQuery);


