CKEDITOR.plugins.add('collapse_text',
{
  init: function(editor)
  {
    /* COMMAND */
    editor.addCommand('cmdCollapseTextDialog', new CKEDITOR.dialogCommand('collapseTextDialog'));

    /* BUTTON */
    editor.ui.addButton('collapse_text',
    {
      label: 'Insert collapsible text',
      command: 'cmdCollapseTextDialog',
      icon: this.path + 'button.png'
    });

    /* DIALOG */
    CKEDITOR.dialog.add('collapseTextDialog', function (editor)
    {
      //TODO: Labels below could be replaced with linkLang.labelName.
      return {
        title : 'Collapsible text settings',
        minWidth : 300,
        minHeight : 200,
        contents :
        [{
          id : 'tab1',
          label : 'Settings',
          elements :
          [{
            type : 'text',
            id : 'title',
            label : 'Collapsible text title',
            validate : CKEDITOR.dialog.validate.notEmpty("Collapsible text title should be provided")
          }, {
            type : 'textarea',
            id : 'content',
            label : 'Collapsible text content',
            validate : CKEDITOR.dialog.validate.notEmpty("Collapsible text content should be provided")
          }, {
            type : 'checkbox',
            id : 'state',
            label : 'Initially expanded (not collapsed)'
          },{
            type : 'text',
            id : 'classes',
            label : 'Optional class'
          }]
        }],
        onOk : function()
               {
                 var dialog = this;
                 var title = dialog.getValueOf('tab1', 'title');
                 var content = dialog.getValueOf('tab1', 'content');
                 var classes = dialog.getValueOf('tab1', 'classes');
                 var state = !dialog.getValueOf('tab1', 'state') ? 'collapsed' : 'collapse';

                 var openTag = '[' + state + ' title="' + title + '"' + ((classes != "") ? ' class="' + classes + '"' : "") + ']';
                 var closeTag = '[/' + state + ']';
                 var inplaceTag = openTag + content + closeTag;

                 var S = editor.getSelection();

                 if(S == null)
                 {
                   editor.insertHtml(inplaceTag);
                   return;
                 }

                 var R = S.getRanges();
                 R = R[0];

                 if(R == null)
                 {
                   editor.insertHtml(inplaceTag);
                   return;
                 }

                 var startPos = Math.min(R.startOffset, R.endOffset);
                 var endPos = Math.max(R.startOffset, R.endOffset);

                 if(startPos == endPos)
                 {
                   editor.insertHtml(inplaceTag);
                   return;
                 }

                 var container = new CKEDITOR.dom.element('p');
                 var fragment = R.extractContents();

                 container.appendText(openTag);
                 fragment.appendTo(container);
                 container.appendText(closeTag);

                 editor.insertElement(container);
               }
      };
      // End CKEDITOR.dialog.add.
    });
  }// End init.
  // End CKEDITOR.plugins.add.
});
