# emoji-selector

👋`emoji-selector` is a Polymer custom element that acts as a `paper-input` suffix (see [Polymer.PaperInput](https://github.com/polymerelements/paper-input)) to help you with your emoji shenanigans.

Since you probably don't remember where each emoji is, it ships with a search-for-emoji-keywords feature! 🚀🎉

![selector](https://cloud.githubusercontent.com/assets/1369170/9456986/2bfca090-4a93-11e5-9787-b4c04fbe55db.gif)

Example:
```html
    <paper-input label="needs moar emoji">
      <emoji-selector suffix></emoji-selector>
    </paper-input>
```

Also works with non `<paper-input>`s, provided you manually wire up the input:
```html
    <paper-input-container>
      <emoji-selector suffix id="s1"></emoji-selector>
      <label>whoa! textareas!</label>
      <iron-autogrow-textarea class="paper-input-input" id="a1"></iron-autogrow-textarea>
    </paper-input-container>
    
    <script>
      document.getElementById('s1').inputTarget = document.getElementById('a1');
    </script>

```
💖
