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
    var counter = 0;
    // tee up the chart data
    $('.lrs-data-chart').each(function(){
      var myChart = new Chart(this, {
        type: Drupal.settings.elmslnCore.charts[counter].style.type,
        data: {
          labels: Drupal.settings.elmslnCore.charts[counter].data.labels,
          datasets: [{
            label: Drupal.settings.elmslnCore.charts[counter].style.label,
            data: Drupal.settings.elmslnCore.charts[counter].data.values,
            borderWidth: Drupal.settings.elmslnCore.charts[counter].style.borderWidth,
            borderColor: Drupal.settings.elmslnCore.charts[counter].style.colors,
            backgroundColor: Drupal.settings.elmslnCore.charts[counter].style.colors
          }]
        },
        options: {
          title: {
            display: true,
            text: Drupal.settings.elmslnCore.charts[counter].title
          },
          scales: {
            yAxes: [{
              ticks: {
                beginAtZero:true
              }
            }],
            xAxes: [{
              ticks: {
                beginAtZero:true
              }
            }],
          }
        }
      });
      counter++;
    });
  });
})(jQuery);


