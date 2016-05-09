$template = array();
$template['title'] = 'MOOC Table Responsive';
$template['description'] = 'This is the HTML baseline for MOOC tables that are responsive.';
$template['weight'] = '0';
$template['fid'] = '0';
$template['body'] = '<!DOCTYPE html>
<html >
  <head>
    <meta charset="UTF-8">
    <title>Responsive Table (with Hover)</title>
    <!--Import Google Icon Font-->
      <link href="http://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
      <!--Import materialize.css-->
      <link type="text/css" rel="stylesheet" href="css/materialize.min.css"  media="screen,projection"/>
    <link rel=\'stylesheet prefetch\' href=\'https://cdnjs.cloudflare.com/ajax/libs/materialize/0.97.6/css/materialize.css\'>
        <link rel="stylesheet" href="css/style.css">
  </head>
  <body>
     <table class="responsive-table">
  <caption class="title">Issue Tracker</caption>
  <tr class="headingTr">
    <th>Reference #</th>
    <th>Date Issued</th>
    <th>Description</th>
    <th>Status</th>
  </tr>
  <tr>
    <td>#2331212</td>
    <td>Feb 21,2013</td>
    <td>White Out</td>
    <td>Paid</td>
  </tr>
  <tr>
    <td>#2331212</td>
    <td>Feb 21,2013</td>
    <td>White Out</td>
    <td>Paid</td>
  </tr>
  <tr>
    <td>#2331212</td>
    <td>Feb 21,2013</td>
    <td>White Out</td>
    <td>Paid</td>
  </tr>
  <tr>
    <td>#2331212</td>
    <td>Feb 21,2013</td>
    <td>White Out</td>
    <td>Paid</td>
  </tr>
  <tr>
    <td>#2331212</td>
    <td>Feb 21,2013</td>
    <td>White Out</td>
    <td>Paid</td>
  </tr>
</table>
    <script src=\'https://cdnjs.cloudflare.com/ajax/libs/materialize/0.97.6/js/materialize.min.js\'></script>
  </body>
</html>';
$template['format'] = 'textbook_editor';
$template['name'] = 'mooc_table_responsive';
$template['content_types'] = array (
);