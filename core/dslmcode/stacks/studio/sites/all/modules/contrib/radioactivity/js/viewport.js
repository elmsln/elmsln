/**
 * viewport class
 */

/**
 * Constructor
 */
function RViewport(element) {

  this.canvas = element;
  this.context = element.getContext('2d');
  this.origin = new Point(0, 0);

  this.size = new Point(this.canvas.width, this.canvas.height);
  this.halfSize = new Point(this.size.mul(new Point(0.5, 0.5)));

}

/**
 * viewport prototype class
 */
RViewport.prototype = {

  drawInterval: null,
  FPS: 25,
  SPF: 0,
  scale: 1,
  origin: null,
  update: null,
  scene: null,

  click: function (point) {
    if (this.scene && this.scene.click) {
      this.scene.click(this, point);
    }
  },

  wheel: function (delta) {
    if (this.scene && this.scene.wheel) {
      this.scene.wheel(this, delta);
    }
  },

  keyDown: function (key) {
    if (this.scene && this.scene.keyDown) {
      this.scene.keyDown(this, key);
    }
  },

  setFPS: function (fps) {
    if (this.FPS != fps && this.drawInterval != null) {
      clearInterval(this.drawInterval);
    }
    this.FPS = fps;
    this.SPF = 1.0 / this.FPS;
    if (this.FPS != null) {
      this.drawInterval = setInterval(function (vp) {
        vp.draw();
      }, this.SPF * 1000, this);
    }
  },

  setScale: function (scale) {
    this.scale = scale;
  },

  setScene: function (scene) {
    this.scene = scene;
    scene.viewport = this;
  },

  screenToWorld: function (point) {
    return point.sub(this.halfSize)
      .div(this.scale)
      .add(this.origin);
  },

  worldToScreen: function (point) {
    return point.sub(this.origin)
      .mul(this.scale)
      .add(this.halfSize);
  },

  draw: function () {

    this.context.clearRect(0, 0, this.size.x, this.size.y);

    if (this.scene) {
      this.context.save();
      this.context.translate(this.halfSize.x, this.halfSize.y);
      this.context.scale(this.scale, this.scale);
      this.context.translate(-this.origin.x, -this.origin.y);

      // draw
      this.scene.draw(this, this.SPF);

      this.context.restore();
    }
  },

  drawImage: function (img, position, scale, rotation) {
    this.context.save();
    this.context.translate(position.x, position.y);
    this.context.scale(scale.x, scale.y);
    this.context.rotate(rotation);
    this.context.translate(-img.width * 0.5, -img.height * 0.5);
    this.context.drawImage(img, 0, 0);
    this.context.restore();
  }

}
