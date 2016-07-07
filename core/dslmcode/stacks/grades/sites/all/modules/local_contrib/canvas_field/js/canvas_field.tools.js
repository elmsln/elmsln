
(function ($) {
 /**
 * Pen tool.
 */
  //Pen constructor
  CanvasField.Tools.Pen = function() {
    this.lastX = 0;
    this.lastY = 0;
  };

  //Extends the baseTool object
  CanvasField.Tools.Pen.prototype = new CanvasField.baseTool();

  //Start prototype (get the start coords)
  CanvasField.Tools.Pen.prototype.start = function(x, y, context) {
    this.lastX = x;
    this.lastY = y;
  };

  //Move prototype (create the path as we go).
  CanvasField.Tools.Pen.prototype.move = function(x, y, context) {
    //If lastX is not set, we must be resuming from a pause.
    if (!this.lastX) {
      this.lastX = x;
      this.lastY = y;
    }

    context.beginPath();
    context.moveTo(x,y);
    context.lineTo(this.lastX,this.lastY);
    context.stroke();
    this.lastX = x;
    this.lastY = y;
  };

  //Pause prototype (temporarily stop drawing).
  CanvasField.Tools.Pen.prototype.pause = function(x, y, context) {
    this.lastX = 0;
    this.lastY = 0;
  };

  /**
 * Canvas Paint Tool
 */
  CanvasField.Tools.Paint = function() {};
  CanvasField.Tools.Paint.prototype = new CanvasField.baseTool();
  CanvasField.Tools.Paint.prototype.start = function(x, y, context) {
    context.fillRect(0, 0, context.canvas.width, context.canvas.height);
  };

  /**
 * ConfigForm Callback for configure button callback.
 */

  CanvasField.ConfigForm = function(context) {

    $('<div id="canvasfield-color" class="colorpicker"></div>').dialog({
      title: Drupal.t('Configure')
      })
    .before(Drupal.t('Stroke') + '<input type="radio" name="cfSet" value="stroke" checked="checked" />')
    .before(Drupal.t('Fill') + '<input type="radio" name="cfSet" value="fill" />')
    .farbtastic(function(color) {
      context[$('input[name=cfSet]:checked').val() + 'Style'] = color;
    });
  };

  })(jQuery);
