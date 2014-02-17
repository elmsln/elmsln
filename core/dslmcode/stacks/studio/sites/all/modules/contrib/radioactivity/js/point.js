/**
 * Point class
 */
function Point(a, b) {
  if (a != null) {
    if (b != null) {
      this.x = a;
      this.y = b;
    } else {
      this.x = a.x;
      this.y = a.y;
    }
  } else {
    this.x = 0;
    this.y = 0;
  }
}

Point.prototype = {

  add: function (other) {
    if (typeof other == "number") {
      return new Point(this.x + other, this.y + other);
    }
    return new Point(this.x + other.x, this.y + other.y);
  },

  sub: function (other) {
    if (typeof other == "number") {
      return new Point(this.x - other, this.y - other);
    }
    return new Point(this.x - other.x, this.y - other.y);
  },

  mul: function (other) {
    if (typeof other == "number") {
      return new Point(this.x * other, this.y * other);
    }
    return new Point(this.x * other.x, this.y * other.y);
  },

  div: function (other) {
    if (typeof other == "number") {
      return new Point(this.x / other, this.y / other);
    }
    return new Point(this.x / other.x, this.y / other.y);
  },

  normalize: function () {
    var l = this.length();
    this.x /= l;
    this.y /= l;
  },

  normalized: function () {
    var l = this.length();
    return new Point(this.x / l, this.y / l);
  },

  dot: function (other) {
    return (this.x * other.x + this.y * other.y);
  },

  length: function () {
    return Math.sqrt((this.x * this.x) + (this.y * this.y));
  },

  lengthSquared: function () {
    return (this.x * this.x) + (this.y * this.y);
  },

  cap: function (min, max) {
    if (this.x < min.x)
      this.x = min.x;
    else if (this.x > max.x)
      this.x = max.x;
    if (this.y < min.y)
      this.y = min.y;
    else if (this.y > max.y)
      this.y = max.y;
  }

}
