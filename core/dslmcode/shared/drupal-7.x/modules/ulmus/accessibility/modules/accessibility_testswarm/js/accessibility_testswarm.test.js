(function ($) {
  Drupal.behaviors.accessibility_testswarm_test = {
    
    tests : {},
    
    attach: function (context) {
      var that = this;
      $.ajax({ url : Drupal.settings.basePath + 'js/accessibility/tests.json',
                     async : false,
                     dataType : 'json',
                     success : function(data) {
                       that.tests = data;
                    }
                   });
      module('Accessibility testing', {
        setup : function() {
           
        },
        teardown : function() {
        
        }
      });
      $.each(this.tests.tests, function(testName, testItem) {
        test(testItem.readableName, function() {
          expect(1);
          var result = true;
          $('body').quail({ accessibilityTests : that.tests.tests,
                            guideline : [ testName ],
                            testFailed : function(event) {
                              result = false;
                            }});
           equal(result, true, testItem.readableName);
          
        });
      });
    }
  };
})(jQuery);