
(function ($) {

  $(document).ready(function () {
    lastObj = false;
    strs = Drupal.settings.thmrStrings;
    $('body').addClass("thmr_call").attr("id", "thmr_" + Drupal.settings.page_id);

    var themerEnabled = 0;
    var themerToggle = function () {
      themerEnabled = 1 - themerEnabled;
      $('#themer-toggle :checkbox').attr('checked', themerEnabled ? 'checked' : '');
      $('#themer-popup').css('display', themerEnabled ? 'block' : 'none');
      if (themerEnabled) {
        document.onclick = themerEvent;
        if (lastObj != false) {
          $(lastObj).css('outline', '3px solid #999');
        }
        $('[data-thmr]').hover(
          function () {
            if (this.parentNode.nodeName != 'BODY' && $(this).attr('thmr_curr') != 1) {
              $(this).css('outline', 'red solid 1px');
            }
          },
          function () {
            if ($(this).attr('thmr_curr') != 1) {
              $(this).css('outline', 'none');
            }
          }
        );
      }
      else {
        document.onclick = null;
        if (lastObj != false) {
          $(lastObj).css('outline', 'none');
        }
        $('[data-thmr]').unbind('mouseenter mouseleave');
      }
    };
    $(Drupal.settings.thmr_popup)
      .appendTo($('body'));

    $('<div id="themer-toggle"><input type="checkbox" />'+ strs.themer_info +'</div>')
      .appendTo($('body'))
      .click(themerToggle);
    $('#themer-popup').resizable();
    $('#themer-popup')
       .draggable({
               opacity: .6,
               handle: $('#themer-popup .topper')
             })
      .prepend(strs.toggle_throbber)
    ;

    // close box
    $('#themer-popup .topper .close').click(function() {
      themerToggle();
    });
  });

  /**
   * Known issue: IE does NOT support outline css property.
   * Solution: use another browser
   */
  function themerHilight(obj) {
    // hilight the current object (and un-highlight the last)
    if (lastObj != false) {
      $(lastObj).css('outline', 'none').attr('thmr_curr', 0);
    }
    $(obj).css('outline', '#999 solid 3px').attr('thmr_curr', 1);
    lastObj = obj;
  }

  function themerDoIt(obj) {
    if (thmrInPop(obj)) {
      return true;
    }
    // start throbber
    //$('#themer-popup img.throbber').show();
    var objs = thmrFindParents(obj);
    if (objs.length) {
      themerHilight(objs[0]);
      thmrRebuildPopup(objs);
    }
    return false;
  }

  function thmrInPop(obj) {
    //is the element in either the popup box or the toggle div?
    if (obj.id == "themer-popup" || obj.id == "themer-toggle") return true;
    if (obj.parentNode) {
      while (obj = obj.parentNode) {
        if (obj.id=="themer-popup" || obj.id == "themer-toggle") return true;
      }
    }
    return false;
  }

  function themerEvent(e) {
    if (!e) {
      var e = window.event;
    };
    if (e.target) var tg = e.target;
    else if (e.srcElement) var tg = e.srcElement;
    return themerDoIt(tg);
  }

  /**
   * Find all parents with @data-thmr"
   */
  function thmrFindParents(obj) {
    var parents = new Array();
    if ($(obj).attr('data-thmr') != undefined) {
      parents[parents.length] = obj;
    }
    if (obj && obj.parentNode) {
      while ((obj = obj.parentNode) && (obj.nodeType != 9)) {
        if ($(obj).attr('data-thmr') != undefined) {
          parents[parents.length] = obj;
        }
      }
    }
    return parents;
  }

  /**
   * Check to see if object is a block element
   */
  function thmrIsBlock(obj) {
    if (obj.style.display == 'block') {
      return true;
    }
    else if (obj.style.display == 'inline' || obj.style.display == 'none') {
      return false;
    }
    if (obj.tagName != undefined) {
      var i = blocks.length;
      if (i > 0) {
        do {
          if (blocks[i] === obj.tagName) {
            return true;
          }
        } while (i--);
      }
    }
    return false;
  }

  function thmrRefreshCollapse() {
    $('#themer-popup .devel-obj-output dt').each(function() {
        $(this).toggle(function() {
              $(this).parent().children('dd').show();
            }, function() {
              $(this).parent().children('dd').hide();
            });
      });
  }

  /**
   * Rebuild the popup
   *
   * @param objs
   *   The array of the current object and its parents. Current object is first element of the array
   */
  function thmrRebuildPopup(objs) {
    // rebuild the popup box
    var id = objs[0].getAttribute('data-thmr').split(' ').reverse()[0];
    // vars is the settings array element for this theme item
    var vars = Drupal.settings[id];
    // strs is the translatable strings
    var strs = Drupal.settings.thmrStrings;
    var type = vars.type;
    var key = vars.used;

    // clear out the initial "click on any element" starter text
    $('#themer-popup div.starter').empty();

    $('#themer-popup dd.key').empty().prepend('<a href="'+ strs.api_site +'api/search/'+ strs.drupal_version +'/'+ vars.search +'" title="'+ strs.drupal_api_docs +'">'+ key + '</a>');
    $('#themer-popup dt.key-type').empty().prepend((type == 'function') ? strs.function_called : strs.template_called);

    // parents
    var parents = '';
    var parents = strs.parents +' <span class="parents">';
    var isFirst = true;
    for (i = 0; i < objs.length; i++) {
      thmr_ids = objs[i].getAttribute('data-thmr').split(' ').reverse();
      for (j = (i==0?1:0); j < thmr_ids.length; j++) {
        var thmrid = thmr_ids[j];
        var pvars = Drupal.settings[thmrid];
        parents += (isFirst) ? '' : '&lt; ';
        // populate the parents
        // each parent is wrapped with a span containing a 'trig' attribute with the id of the element it represents
        parents += '<span class="parent" trig="'+ objs[i].getAttribute('data-thmr') +'">'+ pvars.name +'</span> ';
        isFirst = false;
      }
    }
    parents += '</span>';
    // stick the parents spans in the #parents div
    $('#themer-popup #parents').empty().prepend(parents);
    $('#themer-popup span.parent')
      .click(function() {
        var thmr_id = $(this).attr('trig');
        var thmr_obj = $('[data-thmr = "' + thmr_id + '"]')[0];
        themerDoIt(thmr_obj);
      })
      .hover(
        function() {
          // make them highlight their element on mouseover
          $('#'+ $(this).attr('trig')).trigger('mouseover');
        },
        function() {
          // and unhilight on mouseout
          $('#'+ $(this).attr('trig')).trigger('mouseout');
        }
      );

    if (vars == undefined) {
      // if there's no item in the settings array for this element
      $('#themer-popup dd.candidates').empty();
      $('#themer-popup dd.preprocessors').empty();
      $('#themer-popup div.attributes').empty();
      $('#themer-popup div.used').empty();
      $('#themer-popup div.duration').empty();
    }
    else {
      $('#themer-popup div.duration').empty().prepend('<span class="dt">' + strs.duration + '</span>' + vars.duration + ' ms');
 
      if (vars.candidates.length > 0) {
        $('#themer-popup dd.candidates').show().empty().prepend(vars.candidates.join('<span class="delimiter"> < </span>'));
  
        if (type == 'function') {
          // populate the candidates
          $('#themer-popup dt.candidates-type').show().empty().prepend(strs.candidate_functions);
        }
        else {
          $('#themer-popup dt.candidates-type').show().empty().prepend(strs.candidate_files);
        }
      }
      else {
        $('#themer-popup dt.candidates-type, #themer-popup dd.candidates').hide();
      }

      if (vars.preprocessors.length > 0) {
        $('#themer-popup dd.preprocessors').show().empty().prepend(vars.preprocessors.join('<span class="delimiter"> + </span>'));
        $('#themer-popup dt.preprocessors-type').show().empty().prepend(strs.preprocessors);
      }
      else {
        $('#themer-popup dd.preprocessors, #themer-popup dt.preprocessors-type').hide();
      }

      if (vars.processors.length > 0) {
        $('#themer-popup dd.processors').show().empty().prepend(vars.processors.join('<span class="delimiter"> + </span>'));
        $('#themer-popup dt.processors-type').show().empty().prepend(strs.processors);
      }
      else {
        $('#themer-popup dd.processors, #themer-popup dt.processors-type').hide();
      }

      // Use drupal ajax to do what we need 
      vars_div_array = $('div.themer-variables');
      vars_div = vars_div_array[0];
      var uri = Drupal.settings.devel_themer_uri + '/' + vars['variables'];
      // Programatically using the drupal ajax things is tricky, so cheat.
      dummy_link = $('<a href="'+uri+'" class="use-ajax">Loading Vars</a>');
      $(vars_div).append(dummy_link);
      Drupal.attachBehaviors(vars_div);
      dummy_link.click();
      
      thmrRefreshCollapse();
    }
    // stop throbber
    //$('#themer-popup img.throbber').hide();
  }

})(jQuery);
