/**
 * @file
 * icor plugin for CKEditor 4.x
 */
CKEDITOR.dialog.add("icor",function(e){  
  return{
    title:"Interactive object",
    resizable : CKEDITOR.DIALOG_RESIZE_BOTH,
    minWidth:925,
    minHeight:525,
    buttons:[CKEDITOR.dialog.okButton, CKEDITOR.dialog.cancelButton],
    onShow:function(){ 
  
    },
    onLoad:function(){ 
      dialog = this; 
      this.setupContent();
    },
    onOk:function(){
      var val = window.frames['icor-frame'].document.getElementById('asset-clicked').value;
      if (val != 0) {
        // build the iframe object
        var embed;
        embed = new CKEDITOR.dom.element( 'iframe' );
        embed.setAttribute('src', Drupal.settings.icorPath +'entity_iframe/node/' + val);
        embed.setAttribute('width', '98%');
        embed.setAttribute('height', '400');
        embed.setAttribute('frameborder', '0');
        embed.setAttribute('id', 'entity_iframe_node_'+ val);
        embed.setAttribute('class', 'entity_iframe entity_iframe_node');
        // reset window clicked status to account for multiple embedding
        window.frames['icor-frame'].document.getElementById('asset-clicked').value = 0;
        e.insertElement(embed);
      }
    },
    contents:[
      {  id:"info",
        name:'info',
        label:'Info',
        elements:[{
         type:'vbox',
         padding:0,
         children:[
          {type:'html',
          html: '<iframe src="' + Drupal.settings.basePath + 'ciscon/interactive-objects" id="icor-frame" style="width:925px;height:525px;overflow-x:hidden"></iframe>'
          }]
        }]
      }
    ]
  };
});
