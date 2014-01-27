(function($) {
	
	Drupal.behaviors.accessibilityReporting = {

		results : { results : [ ] },

		attach : function() {
			if ($('body').hasClass('accessibility-reporting-done')) {
				return;
			}
			var that = this;
			$('body').addClass('accessibility-reporting-done');
			var totalElements = $('.accessibility-report-field').length - 1;
			$('.accessibility-report-field').each(function(index, item) {
				var $element = $(this);
				var total = { };
				Drupal.accessibility.checkElement($element, function(e) { }, function(event) {
					$.each(event.results, function(testName, result) {
						var testId = Drupal.accessibility.settings.tests[testName].testId;
						total[testId] = result.length;
					});
					that.results.results.push({
							entity_type : $element.data('entity-type'),
							entity_id   : $element.data('entity-id'),
							bundle      : $element.data('bundle'),
							field 		  : $element.data('field'),
							total       : total
						});
					if (index == totalElements) {
						$.post(Drupal.settings.basePath + 'accessibility/reporting/report', that.results);
					}
				});
			});
		}
	}
})(jQuery);