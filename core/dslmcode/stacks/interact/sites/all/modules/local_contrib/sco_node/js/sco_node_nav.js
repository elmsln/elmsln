// add event handlers for nav buttons
jQuery(document).ready(function($){

  sco_node_nav_disable();
  $("#sco-node-nav-first").click(function(event){
    sco_node_nav_move_first();
  });
  $("#sco-node-nav-prev").click(function(event){
    sco_node_nav_move_prev();
  });
  $("#sco-node-nav-next").click(function(event){
    sco_node_nav_move_next();
  });
  $("#sco-node-nav-last").click(function(event){
    sco_node_nav_move_last();
  });
});

function sco_node_nav_to(id, url) {

  sco_node_toc_set_active(id);
  sco_node_nav_set_active(id);

  var obj = jQuery('#sco-node-iframe');
  if (obj.length) {
    obj.attr('src', url);
  }
  else {
    // changing the data attribute doesn't work
    // replace the object with an object with the new url
    obj = jQuery('#sco-node-object');
    var container = obj.parent();
    obj2 = jQuery('<object id="sco-node-object" type="text/html" data="' + url + '"></object>');
    obj.remove();
    container.append(obj2);
  }
}

// disable all nav buttons
function sco_node_nav_disable() {

  jQuery("#sco-node-nav-first").attr("disabled", "disabled");
  jQuery("#sco-node-nav-prev").attr("disabled", "disabled");
  jQuery("#sco-node-nav-next").attr("disabled", "disabled");
  jQuery("#sco-node-nav-last").attr("disabled", "disabled");
}

// set active item in nav list
function sco_node_nav_set_active(id) {

  if (sco_node_nav_list.length > 0) {

    sco_node_nav_set_inactive();

    // find index of item with matching id
    var index = 0;
    var found = false;
    var obj;
    while (index < sco_node_nav_list.length) {
      obj = sco_node_nav_list[index];
      if (obj.id == id) {
        obj.active = true;
        found = true;
        break;
      }
      index++;
    }

    if (found) {
      if (cmi && cmi.hasOwnProperty("launch_data")) {
        cmi.launch_data = obj.lmsdata;
      }
      sco_node_nav_enable(index);
    }
    else {
      sco_node_nav_disable();
    }
  }
}

// set all items inactive
function sco_node_nav_set_inactive() {

  for (var i=0; i<sco_node_nav_list.length; i++) {
    var obj = sco_node_nav_list[i];
    obj.active = false;
  }
}

// set button states based on index
function sco_node_nav_enable(index) {

  if (index == 0) {
    jQuery("#sco-node-nav-first").attr("disabled", true);
    jQuery("#sco-node-nav-prev").attr("disabled", true);
  }
  else {
    jQuery("#sco-node-nav-first").removeAttr("disabled");
    jQuery("#sco-node-nav-prev").removeAttr("disabled");
  }

  if (index == sco_node_nav_list.length-1) {
    jQuery("#sco-node-nav-last").attr("disabled", true);
    jQuery("#sco-node-nav-next").attr("disabled", true);
  }
  else {
    jQuery("#sco-node-nav-last").removeAttr("disabled");
    jQuery("#sco-node-nav-next").removeAttr("disabled");
  }
}

// move to first nav item
function sco_node_nav_move_first() {

  if (sco_node_nav_list.length > 0) {
    var item = sco_node_nav_list[0];
    sco_node_nav_to(item.id, decodeURIComponent(item.url));
  }
}

// move to last nav item
function sco_node_nav_move_last() {

  if (sco_node_nav_list.length > 0) {
    i = sco_node_nav_list.length - 1;
    var item = sco_node_nav_list[i];
    sco_node_nav_to(item.id, decodeURIComponent(item.url));
  }
}

// move to next nav item
function sco_node_nav_move_next() {

  if (sco_node_nav_list.length > 0) {
    i = sco_node_nav_get_active_index();
    if (i > -1 && i < sco_node_nav_list.length - 1) {
      var item = sco_node_nav_list[i+1];
      sco_node_nav_to(item.id, decodeURIComponent(item.url));
    }
  }
}

// return true if can nav to the next item
function sco_node_nav_can_move_next() {

  result = false;

  if (sco_node_nav_list.length > 0) {
    i = sco_node_nav_get_active_index();
    if (i > -1 && i < sco_node_nav_list.length - 1) {
      result = true;
    }
  }

  return result;
}

// move to previous nav item
function sco_node_nav_move_prev() {

  if (sco_node_nav_list.length > 0) {
    i = sco_node_nav_get_active_index();
    if (i > 0) {
      var item = sco_node_nav_list[i-1];
      sco_node_nav_to(item.id, decodeURIComponent(item.url));
    }
  }

  return result;
}

// return true if can nav to the previous item
function sco_node_nav_can_move_prev() {

  result = false;

  if (sco_node_nav_list.length > 0) {
    i = sco_node_nav_get_active_index();
    if (i > 0) {
      result = true;
    }
  }

  return result;
}


// return the index of the active item in the nav list
function sco_node_nav_get_active_index() {

  var index = -1;

  for (var i=0; i<sco_node_nav_list.length; i++) {
    if (sco_node_nav_list[i].active) {
      index = i;
      break;
    }
  }

  return index;
}

