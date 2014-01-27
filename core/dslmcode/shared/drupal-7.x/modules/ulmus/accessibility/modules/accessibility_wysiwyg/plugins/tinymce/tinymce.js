
(function($) {
  
  tinymce.create('tinymce.plugins.drupal_accessibility', {

    active : false,

    init : function(ed, url) {
      var that = this;
      ed.addCommand('drupal_accessibilityCheckContent', function() {
        if (that.active) {
          that.removeMarkup(ed);
          that.active = false;
        }
        else {
          that.checkContents(ed);
          that.active = true;
        }
      });

      ed.addButton('drupal_accessibility', {
        title : Drupal.t('Check accessibility'),
        cmd : 'drupal_accessibilityCheckContent',
        image : Drupal.settings.basePath + Drupal.settings.accessibility_wysiwyg.path + '/plugins/tinymce/img/quail.png'
      });

      ed.onNodeChange.add(function(ed, cm) {
        cm.setActive('drupal_accessibility', that.active);
      });
      
      ed.onSetContent.add(function() {
        that.removeMarkup(ed);
      });

      ed.onBeforeGetContent.add(function() {
        that.removeMarkup(ed);
      });

      ed.onBeforeExecCommand.add(function(ed, cmd) {
        if (cmd == 'mceFullScreen') {
          that.removeMarkup(ed);
        }
      });
      
      if (ed.settings.content_css !== false) {
        ed.contentCSS.push(Drupal.settings.basePath + Drupal.settings.accessibility_wysiwyg.accessibility_path + '/css/accessibility.css');
      }
    },
    
    checkContents : function(ed) {
      Drupal.accessibility.checkElement($(ed.dom.doc.activeElement), this.testFailed, function() {}, 'content');
    },

    testFailed : function(event) {
      Drupal.accessibility.highlightElement(event, function(event) {
        event.element.add(event.element.prev($('.accessibility-icon')))
                   .click(function(event) {
                      var tests = $(this).data('accessibility-tests');
                      var linkTests = [];
                      $.each(tests, function(index, test) {
                        linkTests.push(index);
                      });
                      tinyMCE.activeEditor.windowManager.open({
                         url : Drupal.settings.basePath + 'accessibility_wysiwyg/tinymce/view/' + linkTests.join(','),
                         width : 320,
                         height : 240
                      }, {
                         custom_param : 1
                      });
                   }); 
      });
    },
    
    removeMarkup : function(ed) {
      Drupal.accessibility.cleanUpHighlight($(ed.dom.doc.activeElement));
    },
    
    createControl : function(n, cm) {
      return null;
    },


    getInfo : function() {
      return {
        longname : 'Drupal accessibilty plugin',
        author : 'Kevin Miller',
        infourl : 'http://drupal.org/project/accessibility',
        version : "1.0"
      };
    }
  });
  
  tinymce.PluginManager.add('drupal_accessibility', tinymce.plugins.drupal_accessibility);
})(jQuery);