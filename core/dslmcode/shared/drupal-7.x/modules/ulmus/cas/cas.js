(function ($) {
Drupal.behaviors.cas = {
  attach: function (context) {
    var loginElements = $('.form-item-name, .form-item-pass, li.cas-link, ul.openid-links');
    var casElements = $('#edit-cas-login-redirection-message, li.user-link, li.uncas-link');

    $(".form-item-cas-identifier").hide();
    if($("#edit-cas-identifier").attr("checked")) {
      loginElements.hide();
      // Use .css("display", "block") instead of .show() to be Konqueror friendly.
      casElements.css("display", "block");
    }
    else
    {
      loginElements.css("display", "block");
      // Use .css("display", "block") instead of .show() to be Konqueror friendly.
      casElements.hide();
    }

    $("li.cas-link", context)
      .click( function() {
        loginElements.hide();
        casElements.css("display", "block");
        $("#edit-cas-identifier").attr("checked", true);
        // Remove possible error message.
        $("#edit-name, #edit-pass").removeClass("error");
        $("div.messages.error").hide();
        return false;
      });
    $("li.uncas-link", context)
      .click(function() {
        loginElements.css("display", "block");
        casElements.hide();
        $("#edit-cas-identifier").attr("checked", false);
        // Clear cas Identifier field and remove possible error message.
        $("div.messages.error").css("display", "block");
        // Set focus on username field.
        $("#edit-name")[0].focus();
        return false;
      });
    // OpenID Compatibility
    $("li.openid-link", context)
      .click( function() {
        $("li.cas-link").hide();
      });
    $("li.user-link", context)
      .click( function() {
        $("li.cas-link").css("display", "block");
      });
    }
  };
})(jQuery);
