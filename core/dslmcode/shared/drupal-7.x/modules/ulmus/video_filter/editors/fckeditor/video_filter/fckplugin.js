var path = Drupal.settings.video_filter.url.wysiwyg_fckeditor;
var basePath =  Drupal.settings.basePath;
var modulePath = Drupal.settings.video_filter.modulepath;

FCKCommands.RegisterCommand('video_filter', new FCKDialogCommand('video_filter', '&nbsp;', path, 580, 480));

var oVideoFilterItem = new FCKToolbarButton('video_filter', 'video_filter');
oVideoFilterItem.IconPath = basePath + modulePath + '/editors/fckeditor/video_filter/video_filter.png';
FCKToolbarItems.RegisterItem('video_filter', oVideoFilterItem);
