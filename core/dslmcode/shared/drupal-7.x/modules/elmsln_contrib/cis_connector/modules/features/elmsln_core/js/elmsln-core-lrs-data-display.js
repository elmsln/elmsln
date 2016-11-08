(function ($) {
  Drupal.prettyJson = {
   replacer: function(match, pIndent, pKey, pVal, pEnd) {
      var key = '<span class="json-key blue-text text-darken-4">';
      var val = '<span class="json-value green-text text-darken-4">';
      var str = '<span class="json-string red-text text-darken-4">';
      var r = pIndent || '';
      if (pKey)
         r = r + key + pKey.replace(/[": ]/g, '') + '</span>: ';
      if (pVal)
         r = r + (pVal[0] == '"' ? str : val) + pVal + '</span>';
      return r + (pEnd || '');
      },
   prettyPrint: function(obj) {
      var jsonLine = /^( *)("[\w]+": )?("[^"]*"|[\w.+-]*)?([,[{])?$/mg;
      return JSON.stringify(obj, null, 3)
         .replace(/&/g, '&amp;').replace(/\\"/g, '&quot;')
         .replace(/</g, '&lt;').replace(/>/g, '&gt;')
         .replace(jsonLine, Drupal.prettyJson.replacer);
      }
  };
  $(document).ready(function(){
    // when an xapi statement is expanded, make it more readable
    $('.elmsln-core-lrs-data-display .xapi-statement-raw').click(function(){
      if (!$(this).hasClass('xapi-colorization')) {
        $(this).addClass('xapi-colorization');
        var json = jQuery.parseJSON($(this).siblings('.collapsible-body').children('pre').html());
        $(this).siblings('.collapsible-body').children('pre').html(Drupal.prettyJson.prettyPrint(json));
      }
    });
    // tee up the chart data
    var ctx = document.getElementById("lrs-data-chart");
    var myChart = new Chart(ctx, {
      type: Drupal.settings.elmslnCore.chart.style.type,
      data: {
        labels: Drupal.settings.elmslnCore.chart.data.labels,
        datasets: [{
          label: Drupal.settings.elmslnCore.chart.style.label,
          data: Drupal.settings.elmslnCore.chart.data.values,
          borderWidth: Drupal.settings.elmslnCore.chart.style.borderWidth,
          borderColor: Drupal.settings.elmslnCore.chart.style.colors,
          backgroundColor: Drupal.settings.elmslnCore.chart.style.colors
        }]
      },
      options: {
        scales: {
          yAxes: [{
            ticks: {
              beginAtZero:true
            }
          }]
        }
      }
    });
  });
})(jQuery);


