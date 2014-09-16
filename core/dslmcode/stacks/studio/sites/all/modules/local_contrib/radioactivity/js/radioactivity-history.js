(function ($) {
Drupal.behaviors.radioactivity_history = {

  attach: function (context, settings) {

    if ($.fn.sparkline) {
      $('.radioactivity-history').each(function (match) {
        var dataset = $.parseJSON($(this).text());
        $(this).sparkline(dataset.values, {
          type:'bar',
          height:'100%',
          width:'100%',
          chartRangeMin: dataset.cutoff,
          tooltipFormat: dataset.tooltipFormat,
          tooltipValueLookups: {
            tooltips: dataset.tooltips
          } 
        });
      });
    }
  }
};
})(jQuery);
