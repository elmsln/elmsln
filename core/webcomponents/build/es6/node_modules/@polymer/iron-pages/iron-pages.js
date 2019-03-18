import"../polymer/polymer-legacy.js";import{IronResizableBehavior}from"../iron-resizable-behavior/iron-resizable-behavior.js";import{IronSelectableBehavior}from"../iron-selector/iron-selectable.js";import{Polymer}from"../polymer/lib/legacy/polymer-fn.js";import{html}from"../polymer/lib/utils/html-tag.js";Polymer({_template:html`
    <style>
      :host {
        display: block;
      }

      :host > ::slotted(:not(slot):not(.iron-selected)) {
        display: none !important;
      }
    </style>

    <slot></slot>
`,is:"iron-pages",behaviors:[IronResizableBehavior,IronSelectableBehavior],properties:{activateEvent:{type:String,value:null}},observers:["_selectedPageChanged(selected)"],_selectedPageChanged:function(){this.async(this.notifyResize)}});