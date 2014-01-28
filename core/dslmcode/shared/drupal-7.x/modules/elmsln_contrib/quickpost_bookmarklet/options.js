(function ($) {

  Drupal.behaviors.quickpost_bookmarklet = {
    attach: function (context, settings) {
      // Get references to the form and elements
      var settings_form = $('.quickpost_bookmarklet_settings_form', context);
      var content_type_element = settings_form.find('#edit-content-type');
      var title_element = settings_form.find(':input[name=title_template]');
      var body_element = settings_form.find(':input[name=body_template]');
      
      // Add click event to the Generate Bookmarklet button
      settings_form.find('#edit-generate-bookmarklet').click(function(e) {
        e.preventDefault();
        
        // Scroll up to make sure they can see the bookmarklet box
        $("html, body").animate({ scrollTop: 0 }, "slow");
        
        // Remove the old bookmarklet, if they have already generated one
        settings_form.find('.bookmarklet_container').empty().text(Drupal.t('Compressing Javascript, hang tight...'));
        
        // Get the template
        var title_template = title_element.val();
        var body_template = body_element.val();
        
        // Replace the tokens
        title_template = quickpost_bookmarklet_replace_tokens(title_template);
        body_template = quickpost_bookmarklet_replace_tokens(body_template);
        
        // Get the additional options (or defaults, if not set)
        var bookmarklet_label = settings_form.find(':input[name=bookmarklet_label]').val() || Drupal.t('QuickPost');
        var window_option = settings_form.find(':radio[name=open_in]:checked').val() || 'popup';
              
        // Build the JS that will be used for the bookmarklet
        var url_separator = parseInt(Drupal.settings.bookmarklet_clean_url) ? '?' : '&';
        var js = "var nodeaddpath='" + Drupal.settings.bookmarklet_base_path + "/" + content_type_element.val() + "', d=document, w=window, e=w.getSelection, k=d.getSelection, x=d.selection, s=(e?e():(k)?k():(x?x.createRange().text:0)), \
          l=d.location, e=encodeURIComponent, \
          title='" + title_template + "',\
          body='" + body_template + "',\
          url = nodeaddpath + '" + url_separator + "edit[title]=' + e(title) + '&edit[body][und][0][value]=' + e(body); \
          nourl = function(){w.location = nodeaddpath;}; \
          a = function(){";
          
          // The window opening will differ
          if (window_option == 'window') {
            // Full window
            js += "if(!w.open(url))";
          }
          else {
            // Default: pop-up
            js += "if(!w.open(url,'quickpost','toolbar=0,resizable=1,scrollbars=1,status=1,width=1024,height=570'))";
          }
          
          js += "l.href=url;};\
          if (/Firefox/.test(navigator.userAgent)) { if(l=='about:blank') setTimeout(nourl, 0); else setTimeout(a, 0); } \
          else { if(l=='about:blank') nourl(); else a(); }";
        
        // Build options for the minifier
        var options = {
          output_format: 'text',
          output_info: 'compiled_code',
          js_code: js
        };
        
        // Use the Google Closure Compiler to minify the JS
        $.post("http://closure-compiler.appspot.com/compile", options, function(data) {
          // Create the bookmarklet and explanation, and append to the page
          var bookmarklet = $('<a></a>').attr('href', 'javascript:' + data + ';void(0);').text(bookmarklet_label);
          var explanation = $('<div>Drag the link above into your bookmark toolbar</div>');
          settings_form.find('.bookmarklet_container').empty().append(bookmarklet).append(explanation);
        });           
      });
    }
  };
  
  // Function to replace 
  quickpost_bookmarklet_replace_tokens = function(str) {
    return str.replace(/'/g, '"')
      .replace(/\[title\]/gi, "' + d.title + '")
      .replace(/\[url\]/gi, "' + d.location + '")
      .replace(/\[selection\]/gi, "' + s + '")
      .replace(/\n/g, "\\n");
  }
  
}(jQuery));


