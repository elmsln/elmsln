/*
 Copyright (c) 2003-2014, CKSource - Frederico Knabben. All rights reserved.
 For licensing, see LICENSE.md or http://ckeditor.com/license
*/
CKEDITOR.dialog.add("ccmssourcedialog",function(b){var a=CKEDITOR.document.getWindow().getViewPaneSize(),d=Math.min(a.width-70,800),a=a.height/1.5,c;return{title:b.lang.ccmssourcedialog.title,minWidth:100,minHeight:100,onShow:function(){this.setValueOf("main","data",c=b.getData());CKEDITOR.dialog.getCurrent().parts.dialog.$.disabled=!0},onOk:function(){return function(){var a=this;if(this.getValueOf("main","data").replace(/\r/g,"")===c)return!0;setTimeout(function(){a.hide();b.focus()});return!1}}(),
contents:[{id:"main",label:b.lang.ccmssourcedialog.title,elements:[{type:"textarea",id:"data",dir:"ltr",inputStyle:"cursor:auto;width:"+d+"px;height:"+a+"px;tab-size:4;text-align:left;","class":"cke_source"}]}],buttons:[CKEDITOR.dialog.okButton]}});