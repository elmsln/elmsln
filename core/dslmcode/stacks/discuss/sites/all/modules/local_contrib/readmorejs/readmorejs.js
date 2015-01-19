Drupal.behaviors.readmorejs = {
  attach: function (context) {
    //jQuery(document).ready(function() {
      var selectors = Drupal.settings.readmorejs.selectors;
      delete Drupal.settings.readmorejs.selectors;
      jQuery(selectors, context).readmore(Drupal.settings.readmorejs);
    //});
  }
};
