(function ($) {
    function update_label(node_type) {
        return function() { 
            var exclude_type = $('#edit-exclude-node-title-content-type-value-' + node_type).find(':selected').val();

            if (exclude_type != 'none') {
                $("label[for='edit-exclude-node-title-content-type-modes-" + node_type + "']")
                .text('Exclude title from ' + (exclude_type == 'all' ? 'all ' : 'user defined')
                      + ' nodes in the following view modes:');
            }
        };
    }

    Drupal.behaviors.exclude_node_title =  {
        attach: function(context, settings) {
            for (type in Drupal.settings.exclude_node_title.content_types) {
                var type_label = Drupal.settings.exclude_node_title.content_types[type]; 
                $('#edit-exclude-node-title-content-type-value-' + type).change(update_label(type));
            }
        }
    };
})(jQuery);
