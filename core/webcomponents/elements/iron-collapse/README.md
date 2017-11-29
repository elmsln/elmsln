[![Build status](https://travis-ci.org/PolymerElements/iron-collapse.svg?branch=master)](https://travis-ci.org/PolymerElements/iron-collapse)

_[Demo and API docs](https://elements.polymer-project.org/elements/iron-collapse)_


## &lt;iron-collapse&gt;

`iron-collapse` creates a collapsible block of content.  By default, the content
will be collapsed.  Use `opened` or `toggle()` to show/hide the content.

```html
<button on-click="toggle">toggle collapse</button>

<iron-collapse id="collapse">
  <div>Content goes here...</div>
</iron-collapse>

...

toggle: function() {
  this.$.collapse.toggle();
}
```

`iron-collapse` adjusts the max-height/max-width of the collapsible element to show/hide
the content.  So avoid putting padding/margin/border on the collapsible directly,
and instead put a div inside and style that.

```html
<style>
  .collapse-content {
    padding: 15px;
    border: 1px solid #dedede;
  }
</style>

<iron-collapse>
  <div class="collapse-content">
    <div>Content goes here...</div>
  </div>
</iron-collapse>
```

### Styling

The following custom properties and mixins are available for styling:

| Custom property | Description | Default |
| --- | --- | --- |
| `--iron-collapse-transition-duration` | Animation transition duration | `300ms` |


