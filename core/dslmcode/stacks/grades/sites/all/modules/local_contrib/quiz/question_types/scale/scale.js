/**
 * @file
 * Javascript functions for the scale question type.
 */

/**
 * Refreshes alternatives when a preset is selected.
 *
 * @param selection
 *  The select item used to select answer collection
 */
function refreshAlternatives(selection) {
  clearAlternatives();
  var colId = selection.options[selection.selectedIndex].value;
  var numberOfOptions = scaleCollections[colId].length;
  for(var i = 0; i<numberOfOptions;i++){
	jQuery('#edit-alternative' + (i)).val(scaleCollections[colId][i]);
  }
}

/**
 * Clears all the alternatives on the scale node form
 */
function clearAlternatives() {
  for ( var i = 0; i < scale_max_num_of_alts; i++) {
	jQuery('#edit-alternative' + (i)).val('');
  }
}
