//This script will only be applied to the admin/content/book page
(function ($) {
/**
 * events to update interface
 */

/**
 * behaviors specific to the outline designer for overloading functions
 */
Drupal.behaviors.outline_designer_book = {
    attach: function (context, settings) {
  if (Drupal.settings.outline_designer.activeNid != '') {
    Drupal.outline_designer.set_active('node-' + Drupal.settings.outline_designer.activeNid);
  }
  // usability function to set active item to whatever tr is clicked
  $('#book-outline tbody tr', context).bind('click', function(e){
    if ($(this).children().children('img').length != 0) {
      // set active when you click
      Drupal.outline_designer.set_active($(this).children().children('img')[1]['id']);
    }
  });
  // hover state class so you can see what you are working on
  $('#book-outline tr', context).bind({
    mouseenter: function(e) {
      // Hover event handler
     $(this).addClass('od-hover');
    },
    mouseleave: function(e) {
      // Hover event handler
     $(this).removeClass('od-hover');
    }
  });
  //collapse / expand functionality
  $('.od-toggle-open', context).bind('click', function(e){
    if ($(this).attr('alt') == 'open') {
      $(this).attr('alt','closed');
      $(this).attr('src',$(this).attr('src').replace('images/open.png','images/closed.png'));
      Drupal.settings.outline_designer.collapseList.push($(this).attr('id'));
      Drupal.outline_designer.toggle_expand($(this).parent().parent(),$(this).attr('alt'));
    }
    else {
      $(this).attr('alt','open');
      $(this).attr('src',$(this).attr('src').replace('images/closed.png','images/open.png'));
      Drupal.settings.outline_designer.collapseList.splice($.inArray($(this).attr('id'), Drupal.settings.outline_designer.collapseList), 1);
      Drupal.outline_designer.toggle_expand($(this).parent().parent(),$(this).attr('alt'));
      //if we opened something and pop-ed an item off the array we need to clean up for nested elements potentially being rendered as open
      Drupal.outline_designer.collapseInit();
    }
  });
  //set the active node id everytime an edit icon is clicked on
  $('.outline_designer_edit_button', context).bind('click',function(e){
    Drupal.outline_designer.set_active($(this).attr('id'));    
  });
  //whenever you doubleclick on a title, switch it to the rename state
  $("#book-outline span.od_title_span", context).bind('dblclick',function(e){
    Drupal.settings.outline_designer.activeNid = $(this).attr('id').replace("edit-table-book-admin-","").replace("-title-span","");
    Drupal.outline_designer.form_render('rename');
    $(this).parent().prev().css('display', 'block');
  });
  //whenever you aren't active on a field, remove it
  $('#book-outline div.form-type-textfield input', context).blur(function(){
    $(this).next().children().css('display', 'block');
    $(this).val(Drupal.outline_designer_ops.active('span').html());
    $(this).css('display','none');
  });
  //if you hit enter, submit the title; if you hit esc then reset the field
  $('form').submit( function(){
   return false;
   } );
  $('#book-outline input').keydown(function(e){
    if(document.all) {
      e = event;
    }
      if(e.keyCode==13){  // Enter pressed
        Drupal.outline_designer_ops.rename_submit();
        return false;
      }  
      if(e.keyCode == 27){  // ESC pressed
        Drupal.outline_designer_ops.active('span').css('display','');
        Drupal.outline_designer_ops.active('input').val(Drupal.outline_designer_ops.active('span').html());
        Drupal.outline_designer_ops.active('input').blur();
      }
    });
    //bind the context menu and set it's properties
  var unavailableContextMenuItems = Drupal.settings.outline_designer.unavailableContextMenuItems;
  var ContextOperations = Drupal.settings.outline_designer.operations;
  Drupal.settings.outline_designer.context_menu = [];
  // loop through all buttons and build menu dynamically
  for (od_button in ContextOperations) {
    // special case for nid as thats disabled
    if ($.inArray(od_button, unavailableContextMenuItems) == -1) {
      var tmp = {}
      // stupid but we need to nest this way for lib to work, account for nid too
      if (od_button == 'nid') {
        tmp[ContextOperations[od_button]['title']] = {icon: Drupal.settings.basePath + ContextOperations[od_button]['icon'], disabled:true };
        Drupal.settings.outline_designer.context_menu.push(tmp,$.contextMenu.separator);
      }
      else {
        tmp[ContextOperations[od_button]['title']] = {onclick:function(menuItem,menu) {Drupal.outline_designer.form_render(Drupal.outline_designer.get_key(menuItem.textContent)); }, icon: Drupal.settings.basePath + ContextOperations[od_button]['icon'], disabled:false };
        Drupal.settings.outline_designer.context_menu.push(tmp);
      }
    }
  }
  //binding isn't working in Opera / IE correctly or at all
    $('.outline_designer_edit_button').contextMenu(Drupal.settings.outline_designer.context_menu, {
      theme: Drupal.settings.outline_designer.theme, 
      beforeShow: function () { 
      if ($.inArray("nid", unavailableContextMenuItems) == -1) { 
        $(this.menu).find('.context-menu-item-inner:first').css('backgroundImage','url(' + $("#node-" + Drupal.settings.outline_designer.activeNid +"-icon").attr('src') +')').empty().append("nid " + Drupal.settings.outline_designer.activeNid);
        }
      },
      useIframe: false,
      shadow: false
    });
    //whenever the screen gets altered, make sure we close everything that should be
    Drupal.outline_designer.collapseInit();
    }
  };

Drupal.outline_designer.get_active_title = function() {
  return Drupal.outline_designer_ops.active('span').html();
};

Drupal.outline_designer.get_active_type = function() {
  return $("#node-" + Drupal.settings.outline_designer.activeNid +"-icon").attr('alt');
};

// scaling functionality that overloads default
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
  if(Drupal.settings.outline_designer.factor == 1){
    $("#book-outline img").css('width','').css('height','');
    $("#book-outline").css('font-size','');
    $("#book-outline .form-item").css('margin-top','');
  }else{
    $("#book-outline img").css('width',Drupal.settings.outline_designer.factor + 'em').css('height',Drupal.settings.outline_designer.factor + 'em');
    $("#book-outline").css('font-size',Drupal.settings.outline_designer.factor + 'em');
    $("#book-outline .form-item").css('margin-top',(Drupal.settings.outline_designer.factor/4) + 'em');
  }
};

// quazi theme function for popup rendering
Drupal.outline_designer.render_popup = function(render_title) {
  var output = '';
  output+= '<img src="'+ Drupal.settings.basePath + Drupal.settings.outline_designer.operations[Drupal.settings.outline_designer.activeAction]['icon'] +'" class="od_statusbar_img" />';
  output+= Drupal.settings.outline_designer.operations[Drupal.settings.outline_designer.activeAction]['title'];
  // spec
  if (render_title == true) {
    if (Drupal.outline_designer.get_active_title().length > 20) {
      title = Drupal.outline_designer.get_active_title().substring(0,20) +'...';
    }
    else {
      title = Drupal.outline_designer.get_active_title();
    }
    output+= ' - <img src="'+  $("#node-" + Drupal.settings.outline_designer.activeNid +"-icon").attr('src') +'" class="od_statusbar_img" />'+ title + ' (nid:'+ Drupal.settings.outline_designer.activeNid +')';
  }
  else {
    output+= '<span class="tmpimage"></span><span class="tmptitle"></span>';
  }
  $('#od_'+ Drupal.settings.outline_designer.activeAction).appendTo('#od_popup .popup-content');
  $('#od_popup .popup-statusbar').html(output);
  $('#od_popup_overlay').addClass('od_show');
  $('#od_popup').addClass('od_show');
}
// define function for edit
  Drupal.outline_designer_ops.edit = function() {
    window.open(Drupal.settings.basePath + '?q=node/' + Drupal.settings.outline_designer.activeNid + '/edit','_blank');
  };
  // define function for view
  Drupal.outline_designer_ops.view = function() {
    window.open(Drupal.settings.basePath + '?q=node/' + Drupal.settings.outline_designer.activeNid,'_blank');
  };
  // define function for rename
  Drupal.outline_designer_ops.rename = function() {
    Drupal.outline_designer_ops.active('span').css('display','none');
    Drupal.outline_designer_ops.active('input').css('display','block');
    Drupal.outline_designer_ops.active('input').focus();
  };
  // define function for change_type
  Drupal.outline_designer_ops.change_type = function() {
    $(".od_submit_button").val('Change Type');
    // function call
    Drupal.outline_designer.render_popup(true);
    $("#od_change_type input.type_radio").val([Drupal.outline_designer.get_active_type()]);
    Drupal.settings.outline_designer.activeType = Drupal.outline_designer.get_active_type();
  };
  // define function for add_content
  Drupal.outline_designer_ops.add_content = function() {
    $(".od_submit_button").val('Add Content');
    // function call
    Drupal.outline_designer.render_popup(false);
    $("#od_add_content input.type_radio").val([Drupal.settings.outline_designer.defaultType]);
    $("#od_add_content_title").focus();
    Drupal.settings.outline_designer.activeType = Drupal.settings.outline_designer.defaultType;
  };
  // define function for delete
  Drupal.outline_designer_ops.delete = function() {
    $(".od_submit_button").val('Delete');
    // function call
    Drupal.outline_designer.render_popup(true);
  };
  // submit handlers
  Drupal.outline_designer_ops.edit_submit = function() {};
  Drupal.outline_designer_ops.view_submit = function() {};
  Drupal.outline_designer_ops.rename_submit = function() {
    Drupal.outline_designer_ops.active('span').css('display','');
    Drupal.outline_designer_ops.active('input').css('display','none');
    if (Drupal.outline_designer_ops.active('span').html() != Drupal.outline_designer_ops.active('input').val()) {
      var title = $.param(Drupal.outline_designer_ops.active('input'));
      var titleary = title.split('=',1);
      //need to remove the name space
      title = title.replace(titleary,'');
      title = title.substr(1);
      title = title.replace(/%2F/g,"@2@F@"); //weird escape for ajax with /
      title = title.replace(/%23/g,"@2@3@"); //weird escape for ajax with #
      title = title.replace(/%2B/g,"@2@B@"); //weird escape for ajax with +
      title = title.replace(/%26/g,"@2@6@"); // Fix ampersand issue &
      Drupal.outline_designer.ajax_call(Drupal.settings.outline_designer.type, 'rename', Drupal.settings.outline_designer.activeNid, title, null);
    }  
  };
  // submit handler for change type
  Drupal.outline_designer_ops.change_type_submit = function() {
    Drupal.outline_designer.ajax_call(Drupal.settings.outline_designer.type, 'change_type', Drupal.settings.outline_designer.activeNid, Drupal.settings.outline_designer.activeType, null, 'Drupal.outline_designer_ops.change_type_submit_success');
  };
  // callback function for change type submit
  Drupal.outline_designer_ops.change_type_submit_success = function(msg) {
    $("#reload_table").trigger('change');
  };
  Drupal.outline_designer_ops.add_content_submit = function() {
    var title = $.param($("#od_add_content_title"));
    title = title.replace(/%2F/g,"@2@F@"); //weird escape for ajax with /
    title = title.replace(/%23/g,"@2@3@"); //weird escape for ajax with #
    title = title.replace(/%2B/g,"@2@B@"); //weird escape for ajax with +
    title = title.substr(1);
    if (title == "") {
      alert(Drupal.t("You must enter a title in order to add content!"));
      return false;
    }
    else {
      Drupal.outline_designer.ajax_call(Drupal.settings.outline_designer.type, 'add_content', title, Drupal.settings.outline_designer.activeType, Drupal.settings.outline_designer.activeNid, 'Drupal.outline_designer_ops.add_content_submit_success');
    }
  };
  // callback function for add_content submit
  Drupal.outline_designer_ops.add_content_submit_success = function(msg) {
    $("#reload_table").trigger('change');
  };
  Drupal.outline_designer_ops.delete_submit = function() {
    Drupal.outline_designer.ajax_call(Drupal.settings.outline_designer.type, 'delete', Drupal.settings.outline_designer.activeNid, null, null);
  };
  // reset handlers
  Drupal.outline_designer_ops.edit_reset = function() {};
  Drupal.outline_designer_ops.view_reset = function() {};
  Drupal.outline_designer_ops.rename_reset = function() {};
  Drupal.outline_designer_ops.change_type_reset = function() {};
  Drupal.outline_designer_ops.delete_reset = function() {};
  Drupal.outline_designer_ops.add_content_reset = function() {
    $("#od_add_content_title").val('');
  };
  // special behaviors for the overlay
  Drupal.behaviors.outlineDesignerChangeType = {
    attach: function (context, settings) {
    $("#od_change_type input.type_radio", context).click(function(e){
      Drupal.settings.outline_designer.activeType = $(this).val();
});
    }
  };
  Drupal.behaviors.outlineDesignerAddContentTitle = {
    attach: function (context, settings) {
    $("#od_add_content_title", context).keyup(function(e){
      $(".popup-statusbar .tmptitle").empty().append($("#od_add_content_title").val());
});
    }
  };
  Drupal.behaviors.outlineDesignerAddContent = {
    attach: function (context, settings) {
    $("#od_add_content input.type_radio", context).click(function(e){
      Drupal.settings.outline_designer.activeType = $(this).val();
      $(".popup-statusbar .tmpimage", context).empty().append($(this).next().clone());
});
    }
  };
  // establish active item
  Drupal.outline_designer_ops.active = function(return_item) {
    var obj = $("input[name='table[book-admin-" + Drupal.settings.outline_designer.activeNid + "][title]']");
    if (return_item == 'input') {
      return obj;
    }
    else {
      return obj.next().children('span');
    }
  };
})(jQuery);