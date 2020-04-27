(function ($) {
  $(document).ready(function(){
    document.getElementById('hax-settings').addEventListener('submit', function(e) {
      var values = document.getElementsByTagName('hax-element-list-selector')[0].getAppstoreValues();
      // in-case they are in this place
      if (values.provider) {
        values.providers = values.provider;
      }
      // set location to match CDN
      document.querySelector('#hax-settings [name="webcomponents_project_location"]').value = values.providers.cdn;
      document.querySelector('#hax-settings [name="webcomponents_project_location_other"]').value = values.providers.other;
      document.querySelector('#hax-settings [name="hax_project_pk"]').value = values.providers.pk;
      // store autoloader as blob
      document.querySelector('#hax-settings [name="hax_autoload_element_list"]').value = JSON.stringify(values.autoloader, null, 2);
      // these already are blobs for now
      document.querySelector('#hax-settings [name="hax_stax"]').value = values.stax;
      document.querySelector('#hax-settings [name="hax_blox"]').value = values.blox;
      // loop through key values for popular providers
      for (var key in values.apps) {
        // sanity check per app
        if (document.querySelector('#hax-settings [name="hax_' + key + '_key"]')) {
          document.querySelector('#hax-settings [name="hax_' + key + '_key"]').value = values.apps[key];
        }
      }
    });
  });
})(jQuery);