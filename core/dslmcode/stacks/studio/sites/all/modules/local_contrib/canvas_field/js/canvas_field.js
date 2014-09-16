Drupal.canvas_fields = {};


(function ($) {

  Drupal.behaviors.canvas_field = {
    attach: function(context, settings) {
      $('input.canvas-field:not(".canvas-field-processed")', context).each(function(context) {
        var field_settings = settings.canvas_field[this.id];
        Drupal.canvas_fields[this.id] = new CanvasField(this, field_settings);
        $(this).addClass('canvas-field-processed');

        if($(this).val()) {
          Drupal.canvas_fields[this.id].setImage($(this).val());
        }

      });

    }
  };

  CanvasField = function(selector, settings) {
    this.field = $(selector),
    this.canvas = $('<canvas>');
    this.context = this.canvas[0].getContext("2d");
    this.state = 'inactive';
    this.settings = $.extend(true, {
      'style' : {
        'height'  : 150,
        'width'   : 300
      },
      'default_tool' : 'Pen'
    }, settings);
    this.getButtons();
    this.tool = this.switchTool();

    this.attach();
    this.render();

    return this;
  };

  CanvasField.prototype.attach = function () {
    var self = this;
    $(this.canvas).bind('mousedown touchstart', function (event) {
      self.resetOrigin();

      var y = event.pageY - self.origin['top'];
      var x = event.pageX - self.origin['left'];
      self.state = 'active';

      self.tool.start(x, y, self.context);
    })
      .bind('mousemove touchmove', function (event) {
        if (self.state == 'active') {
          var y = event.pageY - self.origin['top'];
          var x = event.pageX - self.origin['left'];

          self.tool.move(x, y, self.context);
          event.preventDefault();
        }
      })
      .bind('mouseup mouseleave touchend, touchcancel', function (event) {
        if (self.state == 'active') {
          var y = event.pageY - self.origin['top'];
          var x = event.pageX - self.origin['left'];

          self.tool.pause(x, y, self.context);
        }
      });

    $(document).mouseup(function (event) {
      if (self.state == 'active') {
        var y = event.pageY - self.origin['top'];
        var x = event.pageX - self.origin['left'];
        self.state = 'inactive';
        self.tool.stop(x, y, self.context);
        self.save();
      }
    });
  };

  CanvasField.prototype.switchTool = function(newTool) {
    if (!newTool) {
      newTool = this.settings.default_tool;
    }
    if (typeof newTool == 'string') {
      if (typeof window["CanvasField"]["Tools"][newTool] == 'function') {
        this.activateButton(newTool);
        this.tool = new window["CanvasField"]["Tools"][newTool]();
        return this.tool;
      }
    }
    else if (typeof newTool == 'function') {
      //@todo: Figure out how to activate the button in this case.
      this.tool = new newTool();
      return this.tool;
    }
    alert(Drupal.t('Couldn\'t find ' + newTool + ' tool.'));
  };

  CanvasField.prototype.resetOrigin = function() {
    this.origin = this.canvas.offset();
  };

  CanvasField.prototype.render = function() {
    var output = $('<div class="canvas-outer-wrapper">');
    if (this.buttons) {
      var buttons = Drupal.theme('canvasButtonSet', this.buttons);

      if(this.settings.style['border-color']) {
        buttons.css('background-color', this.settings.style['border-color']);
      }
      output.append(buttons);
    }
    if (this.settings.style.height || this.settings.style.width) {
      //Resize canvas, not wrappers.
      this.resize(this.settings.style.height, this.settings.style.width);
      this.settings.style.height = this.settings.style.width = null;
    }
    var innerwrapper = $('<div class="canvas-inner-wrapper">').css(this.settings.style);
    innerwrapper.append(this.canvas);
    output.append(innerwrapper);
    this.field.after(output);
  };

  CanvasField.prototype.save = function() {
    this.field.val(this.canvas[0].toDataURL());
  };

  CanvasField.prototype.reset = function() {
    this.context.clearRect(0, 0, this.context.canvas.width, this.context.canvas.height);
    this.field.val('');
  };

  CanvasField.prototype.resize = function(height, width) {
    this.canvas.attr('height', height).attr('width', width);
  };

  CanvasField.prototype.getButtons = function() {
    this.buttons = {};

    if (CanvasField.Buttons) {
      for (var key in CanvasField.Buttons) {
        if (this.settings.buttons[key.toLowerCase()] == 1) {
          this.buttons[key] = new CanvasField.Buttons[key](this);
        }
      }
    }
  };

  CanvasField.prototype.activateButton = function(name) {
    for (var key in this.buttons) {
      if (key == name) {
        $(this.buttons[name]).addClass('active');
      }
      else {
        $(this.buttons[key]).removeClass('active');
      }
    }
  };

  CanvasField.prototype.setImage = function(data) {
    var self = this;
    var img = new Image();
    img.src = data;
    img.onload = function() {
      self.resize(img.height, img.width);
      self.context.drawImage(img, 0, 0);
    };
  };


  CanvasField.Tools = {};
/**
 * Tools base object.
 */
  CanvasField.baseTool = function() {};
  CanvasField.baseTool.prototype.start = function() {};
  CanvasField.baseTool.prototype.move = function() {};
  CanvasField.baseTool.prototype.pause = function() {};
  CanvasField.baseTool.prototype.stop =  function() {};
  CanvasField.baseTool.prototype.config = function( wrapper ) {};


})(jQuery);

