Google Chart Tools - Drupal module
Display live data on your site using Google Chart Tools (http://code.google.com/apis/chart/).
Google Chart Tools provides a simple API to Build custom charts, useing your Drupal module.

The module contain an example module which demonstrate how this module can be use.

 
  $settings['chart']['chartOne'] = array(  
    'header' => array('Apple', 'Banana', 'Mango'),
    'rows' => array(array(12, 6, 8)),
    'columns' => array('Fruit count'),
    'chartType' => 'PieChart',
    'containerId' =>  'content',
    'options' => array( 
      'forceIFrame' => FALSE, 
      'title' => 'Fruit count',
      'width' => 800,
      'height' => 400  
    )   
  );

  // Draw it.
  draw_chart($settings); 

* The 'containterId' is optional and if it's not set the 'containerId' will be taken from chart ID ($settings['chart']['chart_id']).
* The 'options' are optional as well.

* The draw_chart() function returns an array which contains:
  'title' - Title of the chart, 
  'id' - the chart ID, 
  'weight' - A weight can be add to the chart array (default to 0),
  'markup' - The HTML markup, which can be use.

For Views integration instruction, see the README.txt in the "Google Chart Tools Views" module.