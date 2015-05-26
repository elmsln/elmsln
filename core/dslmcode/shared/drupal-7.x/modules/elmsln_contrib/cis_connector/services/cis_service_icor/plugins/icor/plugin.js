/**
 * @file
 * icor plugin for CKEditor 4.x
 */
CKEDITOR.plugins.add('icor',   
  {    
    requires: ['dialog'],
    init:function(a) { 
  var b="icor";
  var c=a.addCommand(b,new CKEDITOR.dialogCommand(b));
    c.modes={wysiwyg:1,source:0};
    c.canUndo=false;
  a.ui.addButton("icor",{
          label:"Interactive Object",
          command:b,
          icon:this.path+"icor.png"
  });
  CKEDITOR.dialog.add(b,this.path+"dialogs/icor.js")}
});