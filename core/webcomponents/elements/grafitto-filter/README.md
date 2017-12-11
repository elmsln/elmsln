[![Published on webcomponents.org](https://img.shields.io/badge/webcomponents.org-published-blue.svg?style=flat-square)](https://www.webcomponents.org/element/grafitto/grafitto-filter)
[![Published on github pages](https://img.shields.io/badge/github.io-demo-blue.svg?style=flat-square)](https://grafitto.github.io/grafitto-filter/components/grafitto-filter/)

# grafitto-filter

A polymer compatible reusable web element providing a solution for filtering a list of items before displaying them. This component also supports use of custom filter functions using the `f` property. 

Install:   
```bash
bower install --save grafitto/grafitto-filter
```

View the API and Demo [Here](https://grafitto.github.io/grafitto-filter/components/grafitto-filter)
<!---
```
<custom-element-demo>
  <template>
    <script src="../webcomponentsjs/webcomponents-lite.js"></script>
    <link rel="import" href="grafitto-filter.html">
    <link rel="import" href="../iron-list/iron-list.html">
    <link rel="import" href="../paper-input/paper-input.html">
    <link rel="import" href="../paper-checkbox/paper-checkbox.html">
    <link rel="import" href="../paper-item/paper-item.html">
    <style>
    	#like{
     	  padding: 5px; 
          width: 95%;
          border:none;
          border-bottom: 1px solid #555;
      	}
        paper-checkbox.styled {
          width: 92%;
          align-self: center;
          border: 1px solid #ddd;
          padding: 8px 16px;
          --paper-checkbox-checked-color: #0f0;
          --paper-checkbox-checked-ink-color: #0f0;
          --paper-checkbox-unchecked-color: white;
          --paper-checkbox-unchecked-ink-color: black;
          --paper-checkbox-label-color: black;
          --paper-checkbox-label-spacing: 0;
          --paper-checkbox-margin: 8px 16px 8px 0;
          --paper-checkbox-vertical-align: top;
        }

        paper-checkbox .subtitle {
          display: block;
          font-size: 0.8em;
          margin-top: 2px;
          max-width: 150px;
        }
        .small{
          font-size: 0.7em;
          color: darkgrey;
        }
        .wrapper{
          width: 33%;
          margin-left: 33%;
        }
        @media only screen and (max-width: 768px) {
            .wrapper{
                width: 100%;
                margin: 0px;
                padding: 5px;
            }
            #like{
              width: 99%
            }
        }
    </style>
    <next-code-block></next-code-block>
  </template>
</custom-element-demo>
```
-->
```html
<h3>GRAFITTO-FILTER DEMO</h3>
    <paper-input label="Filter" id="like"></paper-input>
        <paper-checkbox class="styled" id="i" raised>
          Case
          <span class="subtitle">
            Enable case sensitivity
          </span>
        </paper-checkbox>
        <grafitto-filter where="name" like="" as="vitu">
          <template>
            <iron-list items=[[vitu]] as="item">
              <template>
                <paper-item>
                  <paper-item-body two-line>
                    <div>{{item.name}}</div>
                    <div class="small" secondary>{{item.code}}</div>
                  </paper-item-body>
                </paper-item>
              </template>
            </iron-list>
          </template>
        </grafitto-filter>
  </body>
  <script>
    var items = [
                    {"code": "+678","name": "Vanuatu"},
                    {"code": "+58","name": "Venezuela"},
                    {"code": "+84","name": "Vietnam"},
                    {"code": "+1 808","name": "Wake Island"},
                    {"code": "+681","name": "Wallis and Futuna"},
                    {"code": "+967","name": "Yemen"},
                    {"code": "+260","name": "Zambia"}
                ];
    
    var f = document.querySelector("grafitto-filter");
    f.items = items;

      //Set case sensitivity event handler
    document.getElementById("i").addEventListener("checked-changed", function(e){
      f.caseSensitive = e.detail.value;
    })

    //Listen for value changed
    document.getElementById("like").addEventListener("value-changed", function(from, to){
      f.like = from.detail.value;
    });
  </script>
```
`array`:
```javascript
var array = ["one", "two", "three", "four", "five", "six", "seven"];
```
```html
<grafitto-filter item=[[array]] like="o" as="vitu">
  <template>
    <iron-list items=[[vitu]] as="item">
      <template>
        <div>{{item}}</div>
      </template>
    </iron-list>
  </template> </grafitto-filter>
```
### Arrays of Objects   
`data`:
```javascript
var data = [
  {
    name:"John",
    home: "Thika"
  },
  {
    name: "Doe",
    home: "Nairobi"
  }
]
```
Example using `dom-repeat`:

```html
<grafitto-filter items='[[data]]' where="name" like="Doe" as="vitu">
  <template>
    <template is="dom-repeat" items=[[vitu]] as="item">
      <div>{{item.name}}</div>
    </template>
  </template>
</grafitto-filter>
```

Example using `iron-list`:

```html
<grafitto-filter items=[[data]] where="name" like="Doe" as="vitu">
  <template>
    <iron-list items=[[vitu]] as="item">
      <template>
        <div>{{item.name}}</div>
      </template>
    </iron-list>
  </template>
</grafitto-filter>
```
Just incase you are wondering, `vitu` means `items` in Swahili :-)

_Note_: When a simple array E.g `["one","two","three","four"]` is provided, the `where` attribute is ignored and filtering done on the array items themselves.
Also an array of numbers behave like an array of strings when filtering.


`grafitto-filter` also supports complex objects. consider:


```javascript
var complexObj = [
  {
    name: {
      first: "Thomas",
      second: "Kimtu"
    },
    home: "Thika"
  },
  {
    name: {
      first: "John",
      second: "Doe"
    },
    home: "Othaya"
  },
  {
    name: {
      first: "Clement",
      second: "Wainaina"
    },
    home: "Nakuru"
  }
]
``` 

Here is an example using the `complexObj` object above

```html
<grafitto-filter items=[[complexObj]] where="name.first" like="tho" as="vitu">
  <template>
    <iron-list items=[[vitu]] as="item">
      <template>
        <div>{{item.name.first}} {{item.name.second}}, {{item.home}}</div>
      </template>
    </iron-list>
  </template>
</grafitto-filter>
```

You can also use your custom function to filter the items provided.
The function receives a single `item` of the items provided and should return a `boolean` 

```html
<dom-module id="your-element">
  <template>
    <grafitto-filter items=[[data]] id="filter" as="vitu">
      <template>
        <iron-list items=[[vitu]] as="item">
          <template>
            <div>{{item.name}}, {{item.home}}</div>
          </template>
        </iron-list>
      </template>
    </grafitto-filter>
    <script>
      Polymer({
        is: "your-element",
        properties: {
          data: {
            type: Array,
            value: [
                    {
                      "name":"John",
                      "home": "Thika"
                    },
                    {
                      "name": "Doe",
                      "home": "Nairobi"
                    }
                  ]
          }
        },
        ready: function(){
          this.$.filter.f = function(item){
            return item.name == "Doe";
          };
        }
       //Then you can call filter() function to trigger filter
      })
    </script>
  </template>
</dom-module>
```
### Rule of thumb   
`like` is taken as a regular expression so remember to escape any characters that you don't want interpreted by the regular expression engine.