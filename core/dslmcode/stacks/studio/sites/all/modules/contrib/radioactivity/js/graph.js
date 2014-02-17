(function ($) {
  Drupal.behaviors.radioactivity = {

    attach: function (context, settings) {

      $("#edit-half-life, #edit-granularity").bind("change", function() {
        Drupal.behaviors.radioactivity.vp.scene.graph =
          Drupal.behaviors.radioactivity.precalculate();
      });

      this.vp = new RViewport(this.createGraphElement());
      this.vp.setScene({
        graph: Array(),
        draw: function(vp, td) {
          var c = vp.context;
          this.renderGraph(c);
        },

        renderGraph: function(c) {
          if (this.graph.length == 0)
            return;
          c.beginPath();
          c.lineWidth = 1;
          c.strokeStyle = "#000";
          c.moveTo(0, this.graph[0]);
          for (var i in this.graph) {
            y = this.graph[i];
            c.lineTo(i, y);
          }
          c.stroke();

          var hl = $("#edit-half-life").val();
          var s = hl;
          var str = "";
          var m = Math.floor(s / 60);
          var h = Math.floor(m / 60);
          s -= m * 60;
          m -= h * 60;
          str = "" + h + " h " + m + " m " + s + " s ";
          c.font = " 12px sans-serif";
          c.strokeStyle = "#000";
          c.fillText("Half life: " + str, 0, 0);
          c.beginPath();
          c.strokeStyle = "#f00";
          var td = c.canvas.width / 10;
          var t = - c.canvas.height + 20;
          c.moveTo(0, -14);
          c.lineTo(td, -14);
          c.lineTo(td, t);
          c.stroke();

          var td = Math.round(c.canvas.width / 2);
          str = "Incident: +10%";
          c.strokeStyle = "#000";
          c.fillText(str, td, t + 14);

          c.beginPath();
          c.strokeStyle = "#f00";
          c.moveTo(td + 40, t + 20);
          c.lineTo(td, t + 20);
          c.lineTo(td, -14);
          c.stroke();

        }
      });

      this.vp.origin = new Point(this.vp.canvas.width / 2 - 10, -(this.vp.canvas.height / 2) + 10);
      this.vp.setFPS(4);
      this.vp.scene.graph = this.precalculate();
    },

    createGraphElement: function () {
      var element = document.createElement('canvas');
      var canvas = $(element);
      var width = 500;
      var height = 300;

      canvas.attr({
        id: "radioactivity-graph",
        width: width,
        height: height,
      });

      canvas.css({backgroundColor:"#EEE", width:width, height:height, padding:"0", margin:"5px"});

      $('#ctools-export-ui-edit-item-form .form-item-half-life').append(canvas);
      return element;
    },

    precalculate: function() {
      var precalculated = Array();
      var e = -100;
      var scale = (this.vp.canvas.height - 20) / -e;
      var granularity = $("#edit-granularity").val();
      var half_life = $("#edit-half-life").val();
      var g = granularity / 3600;
      var hl = half_life / 3600;
      var half = Math.round(this.vp.canvas.width / 2);
      var t = 0; // time
      var td = hl / this.vp.canvas.width; // time delta
      g /= td;
      td *= 10;
      for (var i = 0; i < this.vp.canvas.width - 20; i++) {
        var pi = i - 1;
        var tt = pi - (pi % g) + g;
        if (i >= tt) {
          e = e * Math.pow(2, (-t / hl));
          t = 0;
        }
        t += td;
        precalculated[i] = e * scale;
        if (i == half) {
          e -= 10;
        }
      }
      return precalculated;
    }
  };

})(jQuery);
