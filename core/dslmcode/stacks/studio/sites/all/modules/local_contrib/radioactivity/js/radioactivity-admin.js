(function ($) {
  Drupal.behaviors.radioactivity_admin = {

    attach: function (context, settings) {

      $("#edit-half-life, #edit-granularity").bind("change", function() {
        Drupal.behaviors.radioactivity_admin.plot();
      });
      var div = $(document.createElement('div'));
      div.attr({
        id: "radioactivity-graph",
      });
      $('#ctools-export-ui-edit-item-form .form-item-granularity').append(div);

      $('#ctools-export-ui-edit-item-form .form-item-granularity').append("<p>" + Drupal.t('Above is a rough mockup on how the granularity and half life interacts. In the middle of the graph you see an emit.') + "</p>");

      this.plot();
    },

    plot: function() {
      data = this.precalculate();
      $('#radioactivity-graph').sparkline(data, {
        type:'bar',
        height:'100%',
        width:'100%',
        tooltipFormat: '<span style="color:{{color}}">&#9679;</span> {{value}} | {{offset:tooltips}}',
      });
    },

    precalculate: function() {
      var precalculated = Array();
      var e = 100;
      var resolution = 100;
      var granularity = $("#edit-granularity").val();
      var half_life = $("#edit-half-life").val();
      var g = granularity / 3600;
      var hl = half_life / 3600;
      var half = Math.round(resolution / 2);
      var t = 0; // time
      var td = hl / resolution; // time delta
      g /= td;
      td *= 10;
      for (var i = 0; i < resolution; i++) {
        var pi = i - 1;
        var tt = pi - (pi % g) + g;
        if (i >= tt) {
          e = e * Math.pow(2, (-t / hl));
          t = 0;
        }
        t += td;
        precalculated[i] = Math.round(e * 100) / 100;
        if (i == half) {
          e += 10;
        }
      }
      return precalculated;
    }
  };

})(jQuery);

