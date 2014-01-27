tinyMCEPopup.requireLangPack();

var FootnoteDialog = {
	init : function() {
		var f = document.getElementById('fntext').value, ed = tinyMCEPopup.editor;
		e = ed.dom.getParent(ed.selection.getNode(), 'fn');
  
	},

	update : function() {
		var f = document.getElementById('fntext').value;
		tinyMCEPopup.execCommand("mceInsertContent", false, '[fn]' + f + '[/fn]');
		tinyMCEPopup.close();
	}
 
};

tinyMCEPopup.onInit.add(FootnoteDialog.init, FootnoteDialog);
