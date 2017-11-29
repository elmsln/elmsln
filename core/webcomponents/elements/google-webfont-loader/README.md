# &lt;google-webfont-loader&gt;
===============================
[![Build Status](https://travis-ci.org/printminion/google-webfont-loader.svg?branch=master)](https://travis-ci.org/printminion/google-webfont-loader)
[![Published on webcomponents.org](https://img.shields.io/badge/webcomponents.org-published-blue.svg)](https://www.webcomponents.org/element/printminion/google-webfont-loader)

See the [component page](http://printminion.github.io/google-webfont-loader) for more information.


## Getting Started
Add it via bower
  "dependencies": {
    "google-webfont-loader": "git@github.com:printminion/google-webfont-loader.git#~1.6.24"
  }
  

## Using
 
 ## Usage
 
 <!--
 ```
 <custom-element-demo>
   <template>
     <script src="../webcomponentsjs/webcomponents-lite.js"></script>
     <link rel="import" href="google-webfont-loader.html">
      <google-webfont-loader id="loader1" loading="{{loading}}" fonts="Droid Sans, Bangers, Pacifico, Fredoka One, Lobster"></google-webfont-loader>

    <div id="fonts">
        <p id="Droid-Sans" style="font-family: Droid Sans, sans-serif;">Droid Sans: Grumpy wizards make toxic brew for the
            evil Queen and Jack.</p>
        <p id="Bangers" style="font-family: Bangers, sans-serif;">Oswald: Grumpy wizards make toxic brew for the evil Queen
            and Jack.</p>
        <p id="Pacifico" style="font-family: Pacifico, sans-serif;">Pacifico: Grumpy wizards make toxic brew for the evil
            Queen and Jack.</p>
        <p id="Fredoka-One" style="font-family: Fredoka One, sans-serif;">Fredoka One: Grumpy wizards make toxic brew for
            the evil Queen and Jack.</p>
        <p id="Lobster" style="font-family: Lobster, sans-serif;">Lobster: Grumpy wizards make toxic brew for the evil Queen
            and Jack.</p>
    </div>
   </template>
 </custom-element-demo>
 ```
 -->
 ```html
 <google-webfont-loader fonts="Droid Sans,Droid Serif"></google-webfont-loader>
 ```


    document.querySelector('google-webfont-loader').addEventListener('fonts-active', function(e) {
        console.log('fonts-active', e.detail.fonts);
    });
    

## Dependencies

Element dependencies are managed via [Bower](http://bower.io/). You can
install that via:

    npm install -g bower

Then, go ahead and download the element's dependencies:

    bower install


## Playing With Your Element

If you wish to work on your element in isolation, we recommend that you use
[Polyserve](https://github.com/PolymerLabs/polyserve) to keep your element's
bower dependencies in line. You can install it via:

    npm install -g polyserve

And you can run it via:

    polyserve

Once running, you can preview your element at
`http://localhost:8080/components/google-webfont-loader/`, where `google-webfont-loader` is the name of the directory containing it.


## Testing Your Element

Simply navigate to the `/test` directory of your element to run its tests. If
you are using Polyserve: `http://localhost:8080/components/google-webfont-loader/test/`

### web-component-tester

The tests are compatible with [web-component-tester](https://github.com/Polymer/web-component-tester).
Install it via:

    npm install -g web-component-tester

Then, you can run your tests on _all_ of your local browsers via:

    wct

#### WCT Tips

`wct -l chrome` will only run tests in chrome.

`wct -p` will keep the browsers alive after test runs (refresh to re-run).

`wct test/some-file.html` will test only the files you specify.
