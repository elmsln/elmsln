/**
 * Google Chart Tools javascript
 *
 */

// Load the Visualization API and the chart package.
google.load("visualization", "1", {packages:["corechart", "gauge", "orgchart", "geochart"]});

(function($) {
  Drupal.behaviors.googleChart = {
    attach: function(context, settings) {
      google.setOnLoadCallback(drawChart);
      // Callback that creates and populates a data table,
      // instantiates the chart, passes in the data and
      // draws it.
      function drawChart() {
        // Loop on the charts in the settings.
        for (var chartId in settings.chart) {
          // Create the data table.
          var data = new google.visualization.DataTable();
          // OrgChart charts need a different format data table.
          if (settings.chart[chartId].chartType == "OrgChart") {
            data.addColumn('string', 'Title');
            data.addColumn('string', 'Parent');
            data.addColumn('string', 'ToolTip');
            for ( var i in settings.chart[chartId].rows ) {
              var row = new Array();
              row = [{v:settings.chart[chartId].rows[i][0], f:settings.chart[chartId].rows[i][1]}, settings.chart[chartId].rows[i][2], settings.chart[chartId].rows[i][3]];
              data.addRows([row]);
              i = parseInt(i);
              data.setRowProperty(i, 'style', settings.chart[chartId].rows[i][4]);
              data.setRowProperty(i, 'selectedStyle', settings.chart[chartId].rows[i][5]);
            }
          } 
          else {
            data.addColumn('string', 'Label');

            // Adding the colomns. 
            // These are graphs titles.
            for (var col in settings.chart[chartId].columns) {
              data.addColumn('number', settings.chart[chartId].columns[col]);
            }

            // Adding the headers.
            // The rows titles.
            for (var i in settings.chart[chartId].header) {
              var row = new Array();
              // Adding the rows.
              // The points of the column for each row.
              for (var j in settings.chart[chartId].rows) {
                row[j] = parseFloat(settings.chart[chartId].rows[j][i]);
              } 
              row.unshift(settings.chart[chartId].header[i]);
              data.addRows([row])
            };
          }

          // Set chart options
          var options = settings.chart[chartId].options;

          // Instantiate and draw our chart, passing in some options.
          var chart = new Object;
          var element = document.getElementById(settings.chart[chartId].containerId);
          if (element) {
            chart[settings.chart[chartId]] = new google.visualization[settings.chart[chartId].chartType](element);
            chart[settings.chart[chartId]].draw(data, options);
          }
        }
      }   
    }
  };
})(jQuery);

