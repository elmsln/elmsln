<?php
/**
 * @file
 * Template to display a view as a calendar day, grouped by time with overlapping items
 * 
 * @see template_preprocess_calendar_day.
 *
 * $rows: The rendered data for this day.
 * $rows['date'] - the date for this day, formatted as YYYY-MM-DD.
 * $rows['datebox'] - the formatted datebox for this day.
 * $rows['empty'] - empty text for this day, if no items were found.
 * $rows['all_day'] - an array of formatted all day items.
 * $rows['items'] - an array of timed items for the day.
 * $rows['items'][$time_period]['hour'] - the formatted hour for a time period.
 * $rows['items'][$time_period]['ampm'] - the formatted ampm value, if any for a time period.
 * $rows['items'][$time_period][$column]['values'] - An array of formatted 
 *   items for a time period and field column.
 * 
 * $view: The view.
 * $columns: an array of column names.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * 
 * The width of the columns is dynamically set using <col></col> 
 * based on the number of columns presented. The values passed in will
 * work to set the 'hour' column to 10% and split the remaining columns 
 * evenly over the remaining 90% of the table.
 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
?>
<div class="calendar-calendar"><div class="day-view">
<div id="multi-day-container">
  <table class="full">
    <tbody>
      <tr class="holder">
        <td class="calendar-time-holder"></td>
        <td class="calendar-day-holder"></td>
      </tr>
      <tr>
        <td class="<?php print $agenda_hour_class ?> first">
           <span class="calendar-hour"><?php print t('All day', array(), array('context' => 'datetime')) ?></span>
        </td>
        <td class="calendar-agenda-items multi-day last">
          <?php foreach ($columns as $column): ?>
          <div class="calendar">
            <div class="inner">
             <?php print isset($rows['all_day'][$column]) ? implode($rows['all_day'][$column]) : '&nbsp;';?>
            </div>
          </div>
          <?php endforeach; ?>   
        </td>
      </tr>
    </tbody>
  </table>
</div>
<div class="header-body-divider">&nbsp;</div>
<div id="single-day-container">
  <?php if (!empty($scroll_content)) : ?>
  <script>
    try {
  	  // Hide container while it renders...  Degrade w/o javascript support
      jQuery('#single-day-container').css('visibility','hidden');
    }catch(e){ 
      // swallow 
    }
  </script>
  <?php endif; ?>
  <table class="full">
    <tbody>
      <tr class="holder">
        <td class="calendar-time-holder"></td>
        <td class="calendar-day-holder"></td>
      </tr>
      <tr>
        <td class="first">
          <?php $is_first = TRUE; ?>
          <?php foreach ($rows['items'] as $time_cnt => $hour): ?>
            <?php 
              if ($time_cnt == 0) {
                $class = 'first ';
              }
              elseif ($time_cnt == count($start_times) - 1) {
                $class = 'last ';
              }
              else {
                $class = '';
              } ?>
            <div class="<?php print $class?>calendar-agenda-hour">
              <span class="calendar-hour"><?php print $hour['hour']; ?></span><span class="calendar-ampm"><?php print $hour['ampm']; ?></span>
            </div>
          <?php endforeach; ?>   
        </td>
        <td class="last">
          <?php foreach ($rows['items'] as $time_cnt => $hour): ?>
            <?php 
              if ($time_cnt == 0) {
                $class = 'first ';
              }
              elseif ($time_cnt == count($start_times) - 1) {
                $class = 'last ';
              }
              else {
                $class = '';
              } ?>
          <div class="<?php print $class?>calendar-agenda-items single-day">
            <div class="half-hour">&nbsp;</div>
            <?php if ($is_first && isset($hour['values'][$column])) :?>
            <div class="calendar item-wrapper first_item">
            <?php $is_first = FALSE; ?>
            <?php else : ?>
            <div class="calendar item-wrapper">
            <?php endif; ?>
              <div class="inner">
               <?php if (!empty($hour['values']) && is_array($hour['values']) && array_key_exists($column, $hour['values'])): ?>
                 <?php foreach ($hour['values'][$column] as $item): ?>
                   <?php print $item; ?>
                 <?php endforeach; ?>
               <?php else: ?>
                 <?php print '&nbsp;'; ?>
               <?php endif; ?>
              </div>
            </div>
          </div>
          <?php endforeach; ?>   
        </td>
      </tr>
    </tbody>
  </table>
</div>
<div class="single-day-footer">&nbsp;</div>
</div></div>
<?php if (!empty($scroll_content)) : ?>
<script>
try {
  // Size and position the viewport inline so there are no delays
  calendar_resizeViewport(jQuery);
  calendar_scrollToFirst(jQuery);
  jQuery('#single-day-container').css('visibility','visible');
}catch(e){ 
  // swallow 
}
</script>
<?php endif; ?>
