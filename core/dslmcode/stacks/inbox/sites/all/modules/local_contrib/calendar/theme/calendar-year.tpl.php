<?php
/**
 * @file
 * Template to display a view as a calendar year.
 * 
 * @see template_preprocess_calendar_year.
 *
 * $view: The view.
 * $months: An array with a formatted month calendar for each month of the year.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * 
 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
?>

<div class="calendar-calendar"><div class="year-view">
<table <?php if ($mini): ?> class="mini"<?php endif; ?>>
  <tbody>
    <tr><td><?php print $months[1] ?></td><td><?php print $months[2] ?></td><td><?php print $months[3] ?></td></tr>  
    <tr><td><?php print $months[4] ?></td><td><?php print $months[5] ?></td><td><?php print $months[6] ?></td></tr>  
    <tr><td><?php print $months[7] ?></td><td><?php print $months[8] ?></td><td><?php print $months[9] ?></td></tr>  
    <tr><td><?php print $months[10] ?></td><td><?php print $months[11] ?></td><td><?php print $months[12] ?></td></tr>  
  </tbody>
</table>
</div></div>