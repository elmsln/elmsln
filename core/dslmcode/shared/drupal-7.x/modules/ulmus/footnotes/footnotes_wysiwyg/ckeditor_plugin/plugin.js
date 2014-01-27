/**
 * A CKeditor plugin to insert footnotes as in-place <fn> elements (consumed by Footnotes module in Drupal).
 *
 * This is a rather sophisticated plugin to show a dialog to insert
 * <fn> footnotes or edit existing ones. It produces and understands
 * the <fn>angle bracket</fn> variant and uses the fakeObjects API to
 * show a nice icon to the user, while producing proper <fn> tags when 
 * the text is saved or View Source is pressed. 
 *
 * If a text contains footnotes of the [fn]square bracket[/fn] variant, 
 * they will be visible in the text and this plugin will not react to them.
 *
 * This plugin uses Drupal.t() to translate strings and will not as such
 * work outside of Drupal. (But removing those functions would be the only
 * change needed.) While being part of a Wysiwyg compatible module, it could 
 * also be used together with the CKEditor module.
 * 
 * Drupal Wysiwyg requirement: The first argument to CKEDITOR.plugins.add() 
 * must be equal to the key used in $plugins[] in hook_wysiwyg_plugin().
 */
CKEDITOR.plugins.add( 'footnotes',
{
    requires : [ 'fakeobjects', 'htmlwriter' ],
    init: function( editor )
    {
      CKEDITOR.addCss(
      'img.cke_footnote' +
      '{' +
        'background-image: url(' + CKEDITOR.getUrl( this.path + 'images/fn_icon2.png' ) + ');' +
        'background-position: center center;' +
        'background-repeat: no-repeat;' +
//        'border: 1px solid #a9a9a9;' +
        'width: 16px;' +
        'height: 16px;' +
   '}'
      );
      CKEDITOR.dialog.add('footnotesDialog', function( editor ) {
       var loadElements = function( editor, selection, element )
       {
          var content = null;
          var attr_value = null;

          element.editMode = true;
          content = element.getText();
          attr_value = element.getAttribute('value');

        if ( content.length > 0 )
         this.setValueOf( 'info','footnote', content );
        else
         this.setValueOf( 'info','footnote', "" );
        if ( attr_value && attr_value.length > 0 )
         this.setValueOf( 'info','value', attr_value );
        else
         this.setValueOf( 'info','value', "" );
       };
        return {
          title : Drupal.t('Footnotes Dialog'),
          minWidth : 500,
          minHeight : 50,
          contents : [
            {
              id : 'info',
              label : Drupal.t('Add a footnote'),
              title : Drupal.t('Add a footnote'),
              elements :
              [
                {
                  id : 'footnote',
                  type : 'text',
                  label : Drupal.t('Footnote text :'),
                },
                {
                  id : 'value',
                  type : 'text',
                  label : Drupal.t('Value :'),
                  labelLayout : 'horizontal',
                  style : 'float:left;width:100px;',
                }
              ]
            }
          ],
        onShow : function()
        {
         this.editObj = false;
         this.fakeObj = false;
         this.editMode = false;

         var selection = editor.getSelection();
         var ranges = selection.getRanges();
         var element = selection.getSelectedElement();
         var seltype = selection.getType();
         
         if ( seltype == CKEDITOR.SELECTION_ELEMENT && element.getAttribute( 'data-cke-real-element-type' ) && element.getAttribute( 'data-cke-real-element-type' ) == 'fn' )
         {
          this.fakeObj = element;
          element = editor.restoreRealElement( this.fakeObj );
          loadElements.apply( this, [ editor, selection, element ] );
          selection.selectElement( this.fakeObj );
         }
         else if ( seltype == CKEDITOR.SELECTION_TEXT )
         {
           this.setValueOf( 'info','footnote', selection.getNative() );
         }
         this.getContentElement( 'info', 'footnote' ).focus();
        },
          onOk : function()
          {
            var editor = this.getParentEditor();
            var content = this.getValueOf( 'info', 'footnote' );
            var value = this.getValueOf( 'info', 'value' );
            if ( content.length > 0 || value.length > 0 ) {
              var realElement = CKEDITOR.dom.element.createFromHtml('<fn></fn>');
              if ( content.length > 0 )
                realElement.setText(content);
              if ( value.length > 0 )
                realElement.setAttribute('value',value);
              var fakeElement = editor.createFakeElement( realElement , 'cke_footnote', 'fn', false );
              editor.insertElement(fakeElement);
            }
          }
        };
      });
      editor.addCommand('footnotes', new CKEDITOR.dialogCommand('footnotesDialog'));
      // Drupal Wysiwyg requirement: The first argument to editor.ui.addButton() 
      // must be equal to the key used in $plugins[<pluginName>]['buttons'][<key>]
      // in hook_wysiwyg_plugin().
      editor.ui.addButton('footnotes',
        {
            label : Drupal.t('Add a footnote'),
            icon : this.path + 'images/footnotes.png',
            command : 'footnotes'
        });
      if ( editor.addMenuGroup )
      {
        editor.addMenuGroup('footnotes');
      }
      if ( editor.addMenuItems )
      {
        editor.addMenuItems(
          {
            footnotes :
              {
                label : Drupal.t('Edit footnote'),  
                command : 'footnotes',
                icon : this.path + 'images/footnotes.png',
                group : 'footnotes'
              }
          });
      }
      if ( editor.contextMenu )
      {
        editor.contextMenu.addListener(function(element, selection)
          {
            if(element.is( 'img' ) &&element.getAttribute( 'data-cke-real-element-type' ) == 'fn')
              return { footnotes : CKEDITOR.TRISTATE_OFF };
            else
              return null;
          });
      }
    },
    afterInit : function( editor )
    {
      var dataProcessor = editor.dataProcessor,
        dataFilter = dataProcessor && dataProcessor.dataFilter;

      if ( dataFilter )
      {
        dataFilter.addRules(
          {
            elements :
              {
                'fn' : function( element )
                  {
                      var fakeElement = editor.createFakeParserElement(element, 'cke_footnote', 'fn', false );
                      return fakeElement;  
                  }
              }
          },
          5);
      }
    }
});
