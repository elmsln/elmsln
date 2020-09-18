define(["exports", "./boot.js", "./resolve-url.js"], function (_exports, _boot, _resolveUrl) {
  "use strict";

  Object.defineProperty(_exports, "__esModule", {
    value: true
  });
  _exports.setUseAdoptedStyleSheetsWithBuiltCSS = _exports.useAdoptedStyleSheetsWithBuiltCSS = _exports.setLegacyNoObservedAttributes = _exports.legacyNoObservedAttributes = _exports.setSuppressTemplateNotifications = _exports.suppressTemplateNotifications = _exports.setFastDomIf = _exports.fastDomIf = _exports.setRemoveNestedTemplates = _exports.removeNestedTemplates = _exports.setCancelSyntheticClickEvents = _exports.cancelSyntheticClickEvents = _exports.setOrderedComputed = _exports.orderedComputed = _exports.setLegacyUndefined = _exports.legacyUndefined = _exports.setSyncInitialRender = _exports.syncInitialRender = _exports.setLegacyWarnings = _exports.legacyWarnings = _exports.setLegacyOptimizations = _exports.legacyOptimizations = _exports.setAllowTemplateFromDomModule = _exports.allowTemplateFromDomModule = _exports.setStrictTemplatePolicy = _exports.strictTemplatePolicy = _exports.setPassiveTouchGestures = _exports.passiveTouchGestures = _exports.getSanitizeDOMValue = _exports.setSanitizeDOMValue = _exports.sanitizeDOMValue = _exports.setRootPath = _exports.rootPath = _exports.supportsAdoptingStyleSheets = _exports.useNativeCustomElements = _exports.useNativeCSSProperties = _exports.useShadow = void 0;

  /**
  @license
  Copyright (c) 2017 The Polymer Project Authors. All rights reserved.
  This code may only be used under the BSD style license found at http://polymer.github.io/LICENSE.txt
  The complete set of authors may be found at http://polymer.github.io/AUTHORS.txt
  The complete set of contributors may be found at http://polymer.github.io/CONTRIBUTORS.txt
  Code distributed by Google as part of the polymer project is also
  subject to an additional IP rights grant found at http://polymer.github.io/PATENTS.txt
  */
  const useShadow = !window.ShadyDOM || !window.ShadyDOM.inUse;
  _exports.useShadow = useShadow;
  const useNativeCSSProperties = Boolean(!window.ShadyCSS || window.ShadyCSS.nativeCss);
  _exports.useNativeCSSProperties = useNativeCSSProperties;
  const useNativeCustomElements = !window.customElements.polyfillWrapFlushCallback;
  _exports.useNativeCustomElements = useNativeCustomElements;

  const supportsAdoptingStyleSheets = useShadow && 'adoptedStyleSheets' in Document.prototype && 'replaceSync' in CSSStyleSheet.prototype && // Since spec may change, feature detect exact API we need
  (() => {
    try {
      const sheet = new CSSStyleSheet();
      sheet.replaceSync('');
      const host = document.createElement('div');
      host.attachShadow({
        mode: 'open'
      });
      host.shadowRoot.adoptedStyleSheets = [sheet];
      return host.shadowRoot.adoptedStyleSheets[0] === sheet;
    } catch (e) {
      return false;
    }
  })();
  /**
   * Globally settable property that is automatically assigned to
   * `ElementMixin` instances, useful for binding in templates to
   * make URL's relative to an application's root.  Defaults to the main
   * document URL, but can be overridden by users.  It may be useful to set
   * `rootPath` to provide a stable application mount path when
   * using client side routing.
   */


  _exports.supportsAdoptingStyleSheets = supportsAdoptingStyleSheets;
  let rootPath = window.Polymer && window.Polymer.rootPath || (0, _resolveUrl.pathFromUrl)(document.baseURI || window.location.href);
  /**
   * Sets the global rootPath property used by `ElementMixin` and
   * available via `rootPath`.
   *
   * @param {string} path The new root path
   * @return {void}
   */

  _exports.rootPath = rootPath;

  const setRootPath = function (path) {
    _exports.rootPath = rootPath = path;
  };
  /**
   * A global callback used to sanitize any value before inserting it into the DOM.
   * The callback signature is:
   *
   *  function sanitizeDOMValue(value, name, type, node) { ... }
   *
   * Where:
   *
   * `value` is the value to sanitize.
   * `name` is the name of an attribute or property (for example, href).
   * `type` indicates where the value is being inserted: one of property, attribute, or text.
   * `node` is the node where the value is being inserted.
   *
   * @type {(function(*,string,string,?Node):*)|undefined}
   */


  _exports.setRootPath = setRootPath;
  let sanitizeDOMValue = window.Polymer && window.Polymer.sanitizeDOMValue || undefined;
  /**
   * Sets the global sanitizeDOMValue available via this module's exported
   * `sanitizeDOMValue` variable.
   *
   * @param {(function(*,string,string,?Node):*)|undefined} newSanitizeDOMValue the global sanitizeDOMValue callback
   * @return {void}
   */

  _exports.sanitizeDOMValue = sanitizeDOMValue;

  const setSanitizeDOMValue = function (newSanitizeDOMValue) {
    _exports.sanitizeDOMValue = sanitizeDOMValue = newSanitizeDOMValue;
  };
  /**
   * Gets sanitizeDOMValue, for environments that don't well support `export let`.
   *
   * @return {(function(*,string,string,?Node):*)|undefined} sanitizeDOMValue
   */


  _exports.setSanitizeDOMValue = setSanitizeDOMValue;

  const getSanitizeDOMValue = function () {
    return sanitizeDOMValue;
  };
  /**
   * Globally settable property to make Polymer Gestures use passive TouchEvent listeners when recognizing gestures.
   * When set to `true`, gestures made from touch will not be able to prevent scrolling, allowing for smoother
   * scrolling performance.
   * Defaults to `false` for backwards compatibility.
   */


  _exports.getSanitizeDOMValue = getSanitizeDOMValue;
  let passiveTouchGestures = window.Polymer && window.Polymer.setPassiveTouchGestures || false;
  /**
   * Sets `passiveTouchGestures` globally for all elements using Polymer Gestures.
   *
   * @param {boolean} usePassive enable or disable passive touch gestures globally
   * @return {void}
   */

  _exports.passiveTouchGestures = passiveTouchGestures;

  const setPassiveTouchGestures = function (usePassive) {
    _exports.passiveTouchGestures = passiveTouchGestures = usePassive;
  };
  /**
   * Setting to ensure Polymer template evaluation only occurs based on tempates
   * defined in trusted script.  When true, `<dom-module>` re-registration is
   * disallowed, `<dom-bind>` is disabled, and `<dom-if>`/`<dom-repeat>`
   * templates will only evaluate in the context of a trusted element template.
   */


  _exports.setPassiveTouchGestures = setPassiveTouchGestures;
  let strictTemplatePolicy = window.Polymer && window.Polymer.strictTemplatePolicy || false;
  /**
   * Sets `strictTemplatePolicy` globally for all elements
   *
   * @param {boolean} useStrictPolicy enable or disable strict template policy
   *   globally
   * @return {void}
   */

  _exports.strictTemplatePolicy = strictTemplatePolicy;

  const setStrictTemplatePolicy = function (useStrictPolicy) {
    _exports.strictTemplatePolicy = strictTemplatePolicy = useStrictPolicy;
  };
  /**
   * Setting to enable dom-module lookup from Polymer.Element.  By default,
   * templates must be defined in script using the `static get template()`
   * getter and the `html` tag function.  To enable legacy loading of templates
   * via dom-module, set this flag to true.
   */


  _exports.setStrictTemplatePolicy = setStrictTemplatePolicy;
  let allowTemplateFromDomModule = window.Polymer && window.Polymer.allowTemplateFromDomModule || false;
  /**
   * Sets `lookupTemplateFromDomModule` globally for all elements
   *
   * @param {boolean} allowDomModule enable or disable template lookup
   *   globally
   * @return {void}
   */

  _exports.allowTemplateFromDomModule = allowTemplateFromDomModule;

  const setAllowTemplateFromDomModule = function (allowDomModule) {
    _exports.allowTemplateFromDomModule = allowTemplateFromDomModule = allowDomModule;
  };
  /**
   * Setting to skip processing style includes and re-writing urls in css styles.
   * Normally "included" styles are pulled into the element and all urls in styles
   * are re-written to be relative to the containing script url.
   * If no includes or relative urls are used in styles, these steps can be
   * skipped as an optimization.
   */


  _exports.setAllowTemplateFromDomModule = setAllowTemplateFromDomModule;
  let legacyOptimizations = window.Polymer && window.Polymer.legacyOptimizations || false;
  /**
   * Sets `legacyOptimizations` globally for all elements to enable optimizations
   * when only legacy based elements are used.
   *
   * @param {boolean} useLegacyOptimizations enable or disable legacy optimizations
   * includes and url rewriting
   * @return {void}
   */

  _exports.legacyOptimizations = legacyOptimizations;

  const setLegacyOptimizations = function (useLegacyOptimizations) {
    _exports.legacyOptimizations = legacyOptimizations = useLegacyOptimizations;
  };
  /**
   * Setting to add warnings useful when migrating from Polymer 1.x to 2.x.
   */


  _exports.setLegacyOptimizations = setLegacyOptimizations;
  let legacyWarnings = window.Polymer && window.Polymer.legacyWarnings || false;
  /**
   * Sets `legacyWarnings` globally for all elements to migration warnings.
   *
   * @param {boolean} useLegacyWarnings enable or disable warnings
   * @return {void}
   */

  _exports.legacyWarnings = legacyWarnings;

  const setLegacyWarnings = function (useLegacyWarnings) {
    _exports.legacyWarnings = legacyWarnings = useLegacyWarnings;
  };
  /**
   * Setting to perform initial rendering synchronously when running under ShadyDOM.
   * This matches the behavior of Polymer 1.
   */


  _exports.setLegacyWarnings = setLegacyWarnings;
  let syncInitialRender = window.Polymer && window.Polymer.syncInitialRender || false;
  /**
   * Sets `syncInitialRender` globally for all elements to enable synchronous
   * initial rendering.
   *
   * @param {boolean} useSyncInitialRender enable or disable synchronous initial
   * rendering globally.
   * @return {void}
   */

  _exports.syncInitialRender = syncInitialRender;

  const setSyncInitialRender = function (useSyncInitialRender) {
    _exports.syncInitialRender = syncInitialRender = useSyncInitialRender;
  };
  /**
   * Setting to retain the legacy Polymer 1 behavior for multi-property
   * observers around undefined values. Observers and computed property methods
   * are not called until no argument is undefined.
   */


  _exports.setSyncInitialRender = setSyncInitialRender;
  let legacyUndefined = window.Polymer && window.Polymer.legacyUndefined || false;
  /**
   * Sets `legacyUndefined` globally for all elements to enable legacy
   * multi-property behavior for undefined values.
   *
   * @param {boolean} useLegacyUndefined enable or disable legacy
   * multi-property behavior for undefined.
   * @return {void}
   */

  _exports.legacyUndefined = legacyUndefined;

  const setLegacyUndefined = function (useLegacyUndefined) {
    _exports.legacyUndefined = legacyUndefined = useLegacyUndefined;
  };
  /**
   * Setting to ensure computed properties are computed in order to ensure
   * re-computation never occurs in a given turn.
   */


  _exports.setLegacyUndefined = setLegacyUndefined;
  let orderedComputed = window.Polymer && window.Polymer.orderedComputed || false;
  /**
   * Sets `orderedComputed` globally for all elements to enable ordered computed
   * property computation.
   *
   * @param {boolean} useOrderedComputed enable or disable ordered computed effects
   * @return {void}
   */

  _exports.orderedComputed = orderedComputed;

  const setOrderedComputed = function (useOrderedComputed) {
    _exports.orderedComputed = orderedComputed = useOrderedComputed;
  };
  /**
   * Setting to cancel synthetic click events fired by older mobile browsers. Modern browsers
   * no longer fire synthetic click events, and the cancellation behavior can interfere
   * when programmatically clicking on elements.
   */


  _exports.setOrderedComputed = setOrderedComputed;
  let cancelSyntheticClickEvents = true;
  /**
   * Sets `setCancelSyntheticEvents` globally for all elements to cancel synthetic click events.
   *
   * @param {boolean} useCancelSyntheticClickEvents enable or disable cancelling synthetic
   * events
   * @return {void}
   */

  _exports.cancelSyntheticClickEvents = cancelSyntheticClickEvents;

  const setCancelSyntheticClickEvents = function (useCancelSyntheticClickEvents) {
    _exports.cancelSyntheticClickEvents = cancelSyntheticClickEvents = useCancelSyntheticClickEvents;
  };
  /**
   * Setting to remove nested templates inside `dom-if` and `dom-repeat` as
   * part of element template parsing.  This is a performance optimization that
   * eliminates most of the tax of needing two elements due to the loss of
   * type-extended templates as a result of the V1 specification changes.
   */


  _exports.setCancelSyntheticClickEvents = setCancelSyntheticClickEvents;
  let removeNestedTemplates = window.Polymer && window.Polymer.removeNestedTemplates || false;
  /**
   * Sets `removeNestedTemplates` globally, to eliminate nested templates
   * inside `dom-if` and `dom-repeat` as part of template parsing.
   *
   * @param {boolean} useRemoveNestedTemplates enable or disable removing nested
   *   templates during parsing
   * @return {void}
   */

  _exports.removeNestedTemplates = removeNestedTemplates;

  const setRemoveNestedTemplates = function (useRemoveNestedTemplates) {
    _exports.removeNestedTemplates = removeNestedTemplates = useRemoveNestedTemplates;
  };
  /**
   * Setting to place `dom-if` elements in a performance-optimized mode that takes
   * advantage of lighter-weight host runtime template stamping to eliminate the
   * need for an intermediate Templatizer `TemplateInstance` to mange the nodes
   * stamped by `dom-if`.  Under this setting, any Templatizer-provided API's
   * such as `modelForElement` will not be available for nodes stamped by
   * `dom-if`.
   */


  _exports.setRemoveNestedTemplates = setRemoveNestedTemplates;
  let fastDomIf = window.Polymer && window.Polymer.fastDomIf || false;
  /**
   * Sets `fastDomIf` globally, to put `dom-if` in a performance-optimized mode.
   *
   * @param {boolean} useFastDomIf enable or disable `dom-if` fast-mode
   * @return {void}
   */

  _exports.fastDomIf = fastDomIf;

  const setFastDomIf = function (useFastDomIf) {
    _exports.fastDomIf = fastDomIf = useFastDomIf;
  };
  /**
   * Setting to disable `dom-change` and `rendered-item-count` events from
   * `dom-if` and `dom-repeat`. Users can opt back into `dom-change` events by
   * setting the `notify-dom-change` attribute (`notifyDomChange: true` property)
   * to `dom-if`/`don-repeat` instances.
   */


  _exports.setFastDomIf = setFastDomIf;
  let suppressTemplateNotifications = window.Polymer && window.Polymer.suppressTemplateNotifications || false;
  /**
   * Sets `suppressTemplateNotifications` globally, to disable `dom-change` and
   * `rendered-item-count` events from `dom-if` and `dom-repeat`.
   *
   * @param {boolean} suppress enable or disable `suppressTemplateNotifications`
   * @return {void}
   */

  _exports.suppressTemplateNotifications = suppressTemplateNotifications;

  const setSuppressTemplateNotifications = function (suppress) {
    _exports.suppressTemplateNotifications = suppressTemplateNotifications = suppress;
  };
  /**
   * Setting to disable use of dynamic attributes. This is an optimization
   * to avoid setting `observedAttributes`. Instead attributes are read
   * once at create time and set/removeAttribute are patched.
   */


  _exports.setSuppressTemplateNotifications = setSuppressTemplateNotifications;
  let legacyNoObservedAttributes = window.Polymer && window.Polymer.legacyNoObservedAttributes || false;
  /**
   * Sets `legacyNoObservedAttributes` globally, to disable `observedAttributes`.
   *
   * @param {boolean} noObservedAttributes enable or disable `legacyNoObservedAttributes`
   * @return {void}
   */

  _exports.legacyNoObservedAttributes = legacyNoObservedAttributes;

  const setLegacyNoObservedAttributes = function (noObservedAttributes) {
    _exports.legacyNoObservedAttributes = legacyNoObservedAttributes = noObservedAttributes;
  };
  /**
   * Setting to enable use of `adoptedStyleSheets` for sharing style sheets
   * between component instances' shadow roots, if the app uses built Shady CSS
   * styles.
   */


  _exports.setLegacyNoObservedAttributes = setLegacyNoObservedAttributes;
  let useAdoptedStyleSheetsWithBuiltCSS = window.Polymer && window.Polymer.useAdoptedStyleSheetsWithBuiltCSS || false;
  /**
   * Sets `useAdoptedStyleSheetsWithBuiltCSS` globally.
   *
   * @param {boolean} value enable or disable `useAdoptedStyleSheetsWithBuiltCSS`
   * @return {void}
   */

  _exports.useAdoptedStyleSheetsWithBuiltCSS = useAdoptedStyleSheetsWithBuiltCSS;

  const setUseAdoptedStyleSheetsWithBuiltCSS = function (value) {
    _exports.useAdoptedStyleSheetsWithBuiltCSS = useAdoptedStyleSheetsWithBuiltCSS = value;
  };

  _exports.setUseAdoptedStyleSheetsWithBuiltCSS = setUseAdoptedStyleSheetsWithBuiltCSS;
});