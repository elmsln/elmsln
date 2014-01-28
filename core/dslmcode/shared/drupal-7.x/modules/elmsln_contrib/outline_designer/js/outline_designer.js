(function ($) {
//extend the drupal js object by adding in an outline_designer name-space
Drupal.outline_designer = Drupal.outline_designer || { functions: {} };
// ensure that od object for ops is set
Drupal.outline_designer_ops = Drupal.outline_designer_ops || { functions: {} };

/**
 * Get rid of tabledrag messages about needing to save
 */ 
Drupal.theme.tableDragChangedWarning = function () { 
  return '<div></div>';
};
  
/**
 * events to update interface
 */
$(document).ready(function() {
  //if everything's been told to close, close it all
  if (Drupal.settings.outline_designer.collapseToggle == 1) {
    Drupal.outline_designer.collapseAll();
  }
  document.onkeyup = function(e) {
    if(document.all) {
      e = event;
    }
    if(e.keyCode==27){  // ESC pressed
      Drupal.outline_designer.ui_reset();
    }
  };
 });
// standard function to get / set results via AJAX
Drupal.outline_designer.ajax_call = function(type, action, param1, param2, param3, callback) {
  // establish the two parameters that we know will be there
  // burden is on the function calling ajax_call to provide others
  var query = '/'+ type +'/' + action +'/'+ param1 +'/'+ param2;
  if (param3 != null) {
     query = query +'/'+ param3;
  }
  // make standard ajax call
  $.ajax({
    type: "POST",
    url: Drupal.settings.outline_designer.ajaxPath + Drupal.settings.outline_designer.token + query,    
    success: function(msg){
      // make sure this is a valid callback
      if (callback != null && callback != 'none') {
        Drupal.outline_designer.executeFunctionByName(callback, window, msg);
      }
      else {
        // allow definition of doing nothing
        if (callback != 'none') {
          if(msg == 0) {
          }
          else {
            $("#reload_table").trigger('change');
          }
        }
      }
    }
  });
}
// popup event listeners
Drupal.behaviors.outlineDesignerCancelButton = {
    attach: function (context, settings) {
      $('.od_cancel_button', context).click(function(){ 
        Drupal.outline_designer.ui_reset();
      });
    }
  };
Drupal.behaviors.outlineDesignerSubmitButton = {
    attach: function (context, settings) {
      $('.od_submit_button', context).click(function(){
        Drupal.outline_designer.form_submit(Drupal.settings.outline_designer.activeAction);
      });
    }
  };
Drupal.behaviors.outlineDesignerCloseOverlay = {
    attach: function (context, settings) {
      //things for when the popup is active to give ways of closing it
      $('#od_popup_overlay', context).click(function(){
        Drupal.outline_designer.ui_reset();
      });
    }
  };
Drupal.behaviors.outlineDesignerEscapeOverlay = {
    attach: function (context, settings) {
    $('#od_popup', context).keydown(function(e){
      if(document.all) {
        e = event;
      }
      if(e.keyCode == 13){  // Enter pressed
        Drupal.outline_designer.form_submit(Drupal.settings.outline_designer.activeAction);
        return false;
      }
    });
    }
  };

// handle rendering of the form
Drupal.outline_designer.form_render = function(render_item) {
  // capture the active action
  Drupal.settings.outline_designer.activeAction = render_item;
  // build function call based on API
  var functionName = 'Drupal.outline_designer_ops.'+ Drupal.settings.outline_designer.activeAction;
  // call "user defined" function
  Drupal.outline_designer.executeFunctionByName(functionName, window);
};

// handle submission of any of the forms, most likely via ajax
Drupal.outline_designer.form_submit = function(submit_item) {
  // build function call based on API
  var functionName = 'Drupal.outline_designer_ops.'+ Drupal.settings.outline_designer.activeAction +'_submit';
  // call "user defined" function
  Drupal.outline_designer.executeFunctionByName(functionName, window);
  Drupal.outline_designer.ui_reset();
};

// remove the interface and get it set for the next action
Drupal.outline_designer.ui_reset = function() {
  $('#od_popup').removeClass('od_show');
  $('#od_popup_overlay').removeClass('od_show');
  // remove focus on any potential operations
  if (Drupal.settings.outline_designer.activeNid != '') {
    $('#node-' + Drupal.settings.outline_designer.activeNid).prev().prev().blur();
    $('#node-' + Drupal.settings.outline_designer.activeNid).prev().prev().removeClass('od_has_focus');
  }
  $('#od_popup .popup-statusbar').html('');
  $('#od_popup .popup-content .od_uiscreen').appendTo('#od_popup_toolbox');
  //reset default settings for all input fields
  $("#od_popup_toolbox input.type_radio").attr('checked',false);
  //reset button names
  $(".od_submit_button").val('Save');
  // allow hooked in items to reset themselves
  var functionName = 'Drupal.outline_designer_ops.'+ Drupal.settings.outline_designer.activeAction +'_reset';
  // ensure one is set
  if ( typeof functionName == 'function' ) { 
    // call "user defined" function
    Drupal.outline_designer.executeFunctionByName(functionName, window);
  }
};

Drupal.outline_designer.get_active_title = function() {
  // stub
};

Drupal.outline_designer.get_active_type = function() {
  // stub
};

//scaling functionality
Drupal.outline_designer.scale = function(scale){
  if(scale == 1 && Drupal.settings.outline_designer.factor != 2){
  Drupal.settings.outline_designer.factor = Drupal.settings.outline_designer.factor + 0.25;
  }else if(scale == -1 && Drupal.settings.outline_designer.factor != 1){
    Drupal.settings.outline_designer.factor = Drupal.settings.outline_designer.factor - 0.25;
  }else if(scale == 0){
    Drupal.settings.outline_designer.factor = 1;
  }
  //account for initial page load, stupid IE thing
  if(Drupal.settings.outline_designer.factor == null && scale == -2) {
    Drupal.settings.outline_designer.factor = 1;
  }
};
//expand / collapse functionality
Drupal.outline_designer.toggle_expand = function(obj,state) {
  var depth = obj.children().children('div.indentation').size();
  var traveldepth = 100;
  var tmpobj = obj;
  while (depth < traveldepth){
    tmpobj = tmpobj.next();
    traveldepth = tmpobj.children().children('div.indentation').size();
    if (depth < traveldepth) {
      if(state == 'closed') {
        tmpobj.css('display','none');
      }
      else {
        tmpobj.css('display','block');
        //if something's marked closed we want to flip that to open too to make things easier. Init is then run after the fact to make sure everything's closed that should be
        if (tmpobj.children().children('img.od-toggle-open').attr('alt') == 'closed') {
          tmpobj.children().children('img.od-toggle-open').attr('alt','open');
          tmpobj.children().children('img.od-toggle-open').attr('src',tmpobj.children().children('img.od-toggle-open').attr('src').replace('images/closed.png','images/open.png'));
        }
      }
    }
  }
};

//everything will get returned as open by default so go through and collapse things that have been collapsed
Drupal.outline_designer.collapseInit = function() {
  for(var i in Drupal.settings.outline_designer.collapseList) {
    if ($('#'+ Drupal.settings.outline_designer.collapseList[i]).length == 1) {
      $('#'+ Drupal.settings.outline_designer.collapseList[i]).attr('alt','closed');
      $('#'+ Drupal.settings.outline_designer.collapseList[i]).attr('src',$('#'+ Drupal.settings.outline_designer.collapseList[i]).attr('src').replace('images/open.png','images/closed.png'));
      Drupal.outline_designer.toggle_expand($('#'+ Drupal.settings.outline_designer.collapseList[i]).parent().parent(),$('#'+ Drupal.settings.outline_designer.collapseList[i]).attr('alt'));
    }
  }
  //scale interface here as well. -2 is so that it ignores the scale and keeps the current global
  Drupal.outline_designer.scale(-2);
};

//Collapse all branches
Drupal.outline_designer.collapseAll = function() {
  $('.od-toggle-open').each(function(){
    $(this).attr('alt','closed');
    $(this).attr('src',$(this).attr('src').replace('images/open.png','images/closed.png'));
    //only push if it's not in the list already
    if ($.inArray($(this).attr('id'), Drupal.settings.outline_designer.collapseList) == -1) {
      Drupal.settings.outline_designer.collapseList.push($(this).attr('id'));
    }
    Drupal.outline_designer.toggle_expand($(this).parent().parent(),$(this).attr('alt'));
  });
};

// Open all branches
Drupal.outline_designer.openAll = function() {
  $('.od-toggle-open').each(function(){
    $(this).attr('alt','open');
    $(this).attr('src',$(this).attr('src').replace('images/closed.png','images/open.png'));
    Drupal.settings.outline_designer.collapseList = new Array();
    Drupal.outline_designer.toggle_expand($(this).parent().parent(),$(this).attr('alt'));
  });
};

// get key associated to the text passed
Drupal.outline_designer.get_key = function(text_name) {
  for (key in Drupal.settings.outline_designer.operations) {
    if (Drupal.settings.outline_designer.operations[key]['title'] == text_name) {
      return key;
    }
  }
};
// convert user input to function call
Drupal.outline_designer.executeFunctionByName = function(functionName, context /*, args */) {
  var args = Array.prototype.slice.call(arguments).splice(2);
  var namespaces = functionName.split(".");
  var func = namespaces.pop();
  for(var i = 0; i < namespaces.length; i++) {
    context = context[namespaces[i]];
  }
  return context[func].apply(this, args);
};

// quazi theme function for popup rendering
Drupal.outline_designer.render_popup = function(render_title) {
  // stub
}

// helper function to set the active item
Drupal.outline_designer.set_active = function(id) {
  // routine to set new focus id
  $('.tabledrag-processed tr').removeClass('od-selected');
  Drupal.settings.outline_designer.activeNid = id.replace('node-', '');
  $('#' + id).parent().parent().addClass('od-selected');
};

})(jQuery);