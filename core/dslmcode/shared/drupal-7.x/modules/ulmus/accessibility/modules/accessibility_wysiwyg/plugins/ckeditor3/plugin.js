(function($) {
  CKEDITOR.plugins.add( 'drupal_accessibility',
  {
    
    icons : '',

    active : false,

    editor : { },
    
    init: function( editor ) {
      var that = this;
      that.editor = editor;

      editor.addCss(Drupal.settings.accessibility_wysiwyg.css);

      editor.addCommand( 'accessibilityDialog', new CKEDITOR.dialogCommand( 'accessibilityDialog' ));

      editor.addCommand( 'checkContent',
        {
          exec : function( editor ) {
            if (that.active) {
              that.removeMarkup(editor);
              that.active = false;
            }
            else {
              that.checkContent(editor);
              that.active = true;
            }
          }
        });
      
      editor.ui.addButton( 'drupal_accessibility',
      {
        label: 'Check content for accessibility',
        command: 'checkContent',
        icon: Drupal.settings.basePath + Drupal.settings.accessibility_wysiwyg.path + '/plugins/ckeditor3/img/button.png'
      });

      CKEDITOR.on('instanceReady', function (ev) {
        ev.editor.dataProcessor.htmlFilter.addRules( {
          elements : {
              $ : function( element ) {
                if(typeof element.attributes !== 'undefined') {
                  if(typeof element.attributes.class === 'string') {
                    element.attributes.class = element.attributes.class.replace(/(_(severe|moderate|suggestion)|accessibility-result|bt-active)/gi, '').trim();
                    if(element.attributes.class.search('accessibility-icon') > -1) {
                      delete element.name;
                    }
                  }
                }
                return element;
              }
          }
        });
      });

        CKEDITOR.dialog.add( 'accessibilityDialog', function( editor ) {
          return {
              title: 'Accessibility',
              minWidth: 400,
              minHeight: 200,
              contents: [
                  {
                      id: 'tab1',
                      label: 'Accessibility feedback',
                      elements: [
                          {
                              type: 'html',
                              id : 'accessibility-dialog-content',
                              html: '<div class="accessibility-dialog-content"></div>'
                          }
                      ]
                  }
              ],

              buttons : []
          };
      });
    },

    removeMarkup : function(editor) {
      $(editor.document.getDocumentElement().$).find('.accessibility-result, .accessibility-icon').unbind('click');
      Drupal.accessibility.cleanUpHighlight($(editor.document.getDocumentElement().$));
    },
    
    checkContent : function(editor) {
      Drupal.settings.accessibility_wysiwyg.currentContext = $(editor.container.$).find('iframe').first();
      Drupal.accessibility.checkElement($(editor.document.getDocumentElement().$), this.testFailed, function() {}, 'content');
    },

    testFailed : function(event) {
      var editor = CKEDITOR.currentInstance;
      Drupal.accessibility.highlightElement(event, function(event) {
        event.element.add(event.element.prev($('.accessibility-icon')))
                   .click(function(event) {
                      var tests = $(this).data('accessibility-tests');

                      editor.execCommand( 'accessibilityDialog', $content );
                      var dialog = CKEDITOR.dialog.getCurrent();
                      var $content = $('<div class="accessibility-wysiwyg-popup">');
                      $.each(tests, function(index, test) {
                        $content.append('<h3 class="title">' + Drupal.accessibility.messages[test].title + '</h3>');
                        $content.append(Drupal.accessibility.messages[test].content);
                      });
                      $(dialog.getContentElement( 'tab1', 'accessibility-dialog-content' ).getElement().$).html($content.html());
                   }); 
      });
    }
  });
})(jQuery);