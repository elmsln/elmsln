
(function($) {

/**
 * Attach behaviors.
 */
Drupal.behaviors.fieldUIFieldsFormsOverview = {
  attach: function (context, settings) {
    $('table#field-overview', context).once('field-field-overview', function() {
      Drupal.fieldUIOverview.attach(this, settings.fieldUIRowsData, Drupal.fieldUIFieldOverview);
    });
  }
};

/**
 * Row handlers for the 'Manage fields' screen.
 */
Drupal.fieldUIFieldOverview = Drupal.fieldUIFieldOverview || {};

Drupal.fieldUIFieldOverview.ds = function (row, data) {

  this.row = row;
  this.name = data.name;
  this.region = data.region;
  this.tableDrag = data.tableDrag;

  this.$regionSelect = $('select.ds-field-region', row);
  this.$regionSelect.change(Drupal.fieldUIOverview.onChange);

  return this;
};

Drupal.fieldUIFieldOverview.ds.prototype = {

  /**
   * Returns the region corresponding to the current form values of the row.
   */
  getRegion: function () {
    return this.$regionSelect.val();
  },

  /**
   * Reacts to a row being changed regions.
   *
   * This function is called when the row is moved to a different region, as a
   * result of either :
   * - a drag-and-drop action 
   * - user input in one of the form elements watched by the
   *   Drupal.fieldUIOverview.onChange change listener.
   *
   * @param region
   *   The name of the new region for the row.
   * @return
   *   A hash object indicating which rows should be AJAX-updated as a result
   *   of the change, in the format expected by
   *   Drupal.fieldOverview.AJAXRefreshRows().
   */
  regionChange: function (region, recurse) {
	  	  	  
     // Replace dashes with underscores.
     region = region.replace('-', '_');

     // Set the region of the select list.
     this.$regionSelect.val(region);

     // Prepare rows to be refreshed in the form.
     var refreshRows = {};
     refreshRows[this.name] = this.$regionSelect.get(0);
     
     // If a row is handled by field_group module, loop through the children.
     if ($(this.row).hasClass('field-group') && $.isFunction(Drupal.fieldUIFieldOverview.group.prototype.regionChangeFields)) {
       Drupal.fieldUIFieldOverview.group.prototype.regionChangeFields(region, this, refreshRows);
     }

     return refreshRows;
  }
};

})(jQuery);