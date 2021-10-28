Drupal.behaviors.h5pContentHubPublish = {
  attach: function (context, settings) {
    const publish = document.getElementById('h5p-publish');
    if (!publish.classList.contains('processed')) {
      publish.classList.add('processed');
      H5PHub.createSharingUI(publish, settings.h5pContentHubPublish);
    }
  }
};
