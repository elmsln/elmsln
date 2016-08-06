/**
 * @file
 * Required functions to use the EIM module.
 */
(function($){Drupal.behaviors.initEim={attach:function(context,settings){$("#edit-instance-settings-alt-field").click(function(){if(!$("#edit-instance-settings-alt-field:checked").val()){if($("#edit-instance-settings-alt-field-required:checked").val()==1){$("#edit-instance-settings-alt-field-required:checked").attr("checked",false)}}});$("#edit-instance-settings-title-field").click(function(){if(!$("#edit-instance-settings-title-field:checked").val()){if($("#edit-instance-settings-title-field-required:checked").val()==1){$("#edit-instance-settings-title-field-required:checked").attr("checked",false)}}})}}})(jQuery);