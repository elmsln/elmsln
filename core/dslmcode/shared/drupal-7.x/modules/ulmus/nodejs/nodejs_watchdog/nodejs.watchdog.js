
(function ($) {

Drupal.Nodejs.callbacks.nodejsWatchdog = {
  callback: function (message) {
    Drupal.nodejs_ajax.runCommands(message);
    $("#admin-dblog tr:even").removeClass('odd').addClass('even');
    $("#admin-dblog tr:odd").removeClass('even').addClass('odd');
  }
};

}(jQuery));

