/**
 * @file
 * Javascript for creating the regions on an image_target_question question
 *
 * Uses a modified version of the Boxer plugin for jQuery
 * ref: http://jsbin.com/aqowa
 */

(function($) {

var boxer_instance;

$.widget("ui.boxer", $.ui.mouse, {

  _init: function() {
    this.element.addClass("ui-boxer");
    this.dragged = false;
    this._mouseInit();
    this.region_templates = new Array();
    this.helper = $(document.createElement('div'))
      .css({border:'1px dotted black'})
      .addClass("ui-boxer-helper");
    boxer_instance  = this;
    this.options.appendTo = '#image_target_question_image';
    this.options.distance = 0;
    this.options.selected_region = 0;
    var options = this.options;
    var reg = /edit-alternatives-targets-([0-9]*)-region/;
    $('.image_target_question-region').each(function() {
      var id = $(this).attr('id').replace(reg, "$1");
      var positions = $(this).val().split(',');
      if (positions.length == 4) {
        boxer_instance.region_templates[id] = $(document.createElement('div'))
          .css({
              background: 'orange',
              "z-index": 100,
              "position": "absolute",
              "top": positions[0] + "px",
              "left": positions[1] + "px",
              "width": positions[2] + "px",
              "height": positions[3] + "px"
           })
          .append(id)
          .appendTo(options.appendTo);
      }
    });
  },

destroy: function() {
this.element
.removeClass("ui-boxer ui-boxer-disabled")
.removeData("boxer")
.unbind(".selectable");
this._mouseDestroy();

return this;
         },

_mouseStart: function(event) {
  if (this.options.selected_region > 0) {
    var self = this;

    if (this.region_templates[this.options.selected_region] != null) {
      $(this.region_templates[this.options.selected_region]).remove();
    }

    this.opos = [event.pageX, event.pageY];

    if (this.options.disabled)
      return;

    this._trigger("start", event);

    $('body').append(this.helper);

    this.helper.css({
        "z-index": 100,
        "position": "absolute",
        "left": event.clientX,
        "top": event.clientY,
        "width": 0,
        "height": 0
        });
  }
},

  _mouseDrag: function(event) {
    if (this.options.selected_region > 0) {
      var self = this;
      this.dragged = true;

      if (this.options.disabled)
        return;

      var x1 = this.opos[0], y1 = this.opos[1], x2 = event.pageX, y2 = event.pageY;
      if (x1 > x2) { var tmp = x2; x2 = x1; x1 = tmp; }
      if (y1 > y2) { var tmp = y2; y2 = y1; y1 = tmp; }
      this.helper.css({left: x1, top: y1, width: x2-x1, height: y2-y1});

      this._trigger("drag", event);
    }

    return false;
  },

  _mouseStop: function(event) {
    if (this.options.selected_region > 0) {
      var self = this;
      this.dragged = false;
      var clone = this.helper.clone()
        .removeClass('ui-boxer-helper').appendTo(this.options.appendTo);
      this.region_templates[this.options.selected_region] = clone;
      clone.css({ background: 'orange'}).append(this.options.selected_region);

      var left = this.helper.offset().left - $('#image_target_question_image > img').offset().left;
      var top = this.helper.offset().top - $('#image_target_question_image > img').offset().top;
      var width = clone.width();
      var height = clone.height();

      clone.css({
        "left": left + "px",
        "top": top + "px"
        });

      $('#edit-alternatives-targets-' + this.options.selected_region + '-region').val(top + ',' + left + ',' + width + ',' + height);

      this.helper.remove();
      this.options.selected_region = 0;
    }
    return false;
  }

});

  function image_target_question_setup_creation_form() {

    // Using the boxer plugin
    $('#image_target_question_image').boxer();
    $('.image_target_question-select-region').unbind();
    $('.image_target_question-select-region').click(function(e) {
      boxer_instance.options.selected_region = this.value.replace('Set region ','');
      e.preventDefault();
      return false;
    });
  }

  // Setup the JS form elements on submission
  $(document).ready(function() {
    image_target_question_setup_creation_form();
  });

  // Setup the JS form elements after an AHAH event to change or add the image
  $(document).ajaxComplete(function(e, xhr, settings) {
    if (settings.url.indexOf("/node/add/image_target_question/upload_image_ahah") != -1) {
      image_target_question_setup_creation_form();
    }
  });

}(jQuery));
