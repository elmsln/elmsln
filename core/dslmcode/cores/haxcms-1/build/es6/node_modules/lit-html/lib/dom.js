/**
 * @license
 * Copyright (c) 2017 The Polymer Project Authors. All rights reserved.
 * This code may only be used under the BSD style license found at
 * http://polymer.github.io/LICENSE.txt
 * The complete set of authors may be found at
 * http://polymer.github.io/AUTHORS.txt
 * The complete set of contributors may be found at
 * http://polymer.github.io/CONTRIBUTORS.txt
 * Code distributed by Google as part of the polymer project is also
 * subject to an additional IP rights grant found at
 * http://polymer.github.io/PATENTS.txt
 */
export const isCEPolyfill=void 0!==window.customElements&&void 0!==window.customElements.polyfillWrapFlushCallback;export const reparentNodes=(o,e,l=null,n=null)=>{for(;e!==l;){const l=e.nextSibling;o.insertBefore(e,n),e=l}};export const removeNodes=(o,e,l=null)=>{for(;e!==l;){const l=e.nextSibling;o.removeChild(e),e=l}};