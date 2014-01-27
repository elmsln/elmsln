(function ($) {

function lightbox2_login() {

  $("a[href*='/user/login'], a[href*='?q=user/login']").each(function() {
    $(this).attr({
      href: this.href.replace(/user\/login?/,"user/login/lightbox2"),
      rel: 'lightmodal[|width:250px; height:210px;]'
    });
    $(this).addClass('lightmodal-login');
  });
}

function lightbox2_contact() {
  $("a[href$='/contact'], a[href$='?q=contact']").each(function() {
    if (!this.href.match('admin/build/contact')) {
      $(this).attr({
        href: this.href.replace(/contact?/,"contact/lightbox2"),
        rel: 'lightmodal[|width:450px; height:450px;]'
      });
      $(this).addClass('lightmodal-contact');
    }
  });
}

Drupal.behaviors.initLightboxModal = {
  attach: function(context, settings) {
    if (settings.lightbox2.enable_login) {
      lightbox2_login();
    }
    if (settings.lightbox2.enable_contact) {
     lightbox2_contact();
    }
  }
};
//End jQuery block
}(jQuery));
