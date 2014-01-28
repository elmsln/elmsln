(function ($) {
  $(document).ready(function(){
  //allow user menu to slide into focus
  $('regions_top_nav_notifications .regions_block_title').click(function(){
    $('#regions_top_nav_notifications .regions_block_content').slideToggle('fast', 'linear');
  });
  $('#regions_top_nav_notifications .regions_block_title').click(function(){
    $('#regions_top_nav_notifications .regions_block_content').slideToggle('fast', 'linear');
    //class to retain the hover state
    if ($(this).hasClass('regions_top_nav_open')) {
      $(this).removeClass('regions_top_nav_open');
    }
    else {
      $(this).addClass('regions_top_nav_open');
    }
  });
  
  //extend the drupal js object by adding in an regions_top_nav name-space
  Drupal.regions_top_nav = Drupal.regions_top_nav || { functions: {} };
  //allow for adding messages after page load
  Drupal.regions_top_nav.add_message = function (type, message) {
  try {
    if (Drupal.settings.regions_top_nav.icon_map) {
      var map = Drupal.settings.regions_top_nav.icon_map;
    }
  }
  catch(e) {
     var map = '';
  }
  //make sure this isn't a parent'ed item
  var map_title, map_bar_icon, title_type;
  if (typeof map[type]['parent'] != 'undefined') {
    map_title = map[map[type]['parent']]['title'];
    map_bar_icon = map[map[type]['parent']]['bar_icon'];
    title_type = map[type]['parent'];
  }
  else {
    map_title = map[type]['title'];
    map_bar_icon = map[type]['bar_icon'];
    title_type = type;
  }
  //add to the title container or increment a count
  if ($('#regions_top_nav_notifications .regions_block_title .'+ title_type).length == 0) {
    var title = '<a name="notification" title="'+ title_type +', click for more details"><div class="regions_top_nav_msg_bar_icon '+ title_type +'" style="background-image:url('+ map_bar_icon +')" title="'+ map_title +', click for more details" alt="'+ map_title +', click for more details"><div class="regions_top_nav_msg_bar_icon_count"></div></div></a>';
    $('#regions_top_nav_notifications .regions_block_title').append(title);
    Drupal.settings.regions_top_nav_top.msg_count[title_type] = 1;
  }
  else {
    Drupal.settings.regions_top_nav_top.msg_count[title_type]++;
    $('#regions_top_nav_notifications .regions_block_title .'+ title_type + ' .regions_top_nav_msg_bar_icon_count').html(Drupal.settings.regions_top_nav_top.msg_count[title_type]);
  }
  //add to the content container
  var content = '<div class="regions_top_nav_row"><img src="'+ map[type]['icon'] +'" title="'+ map[type]['title'] +', click for more details" alt="'+ map[type]['title'] +', click for more details" class="regions_top_nav_icon"/><div class="regions_top_nav_msg"><div class="regions_top_nav_msg_title">'+ map[type]['title'] +'</div><div class="regions_top_nav_msg_text">'+ message +'</div></div></div>';
  $('#regions_top_nav_notifications .regions_block_content').append(content);
  };
  $('#regions_top_nav_notifications .regions_block_title').click();
});
})(jQuery);