# Webcomponents Token module
In order to use this you'll need the cms-token element. You can find it here: https://github.com/LRNWebComponents/cms-hax

Or to install via bower with other workflows you're lookign for from this project:

```
cd DRUPAL/sites/all/libraries/webcomponents/polymer/
bower install --save LRNWebComponents/cms-hax
```

Then you'll want to enable the webcomponents token filter on any text areas you plan on using this with. It will then automatically convert these into web components. This can offer a lazy loading effect for any token that drupal is going to render to help with performance. It also establishes a deeper point of integration with HAX as a result -- https://drupal.org/project/hax