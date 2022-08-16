// forcibly disable sounds and darkmode
if (window.localStorage) {
  try {
    localStorage.setItem('app-hax-soundStatus', "false");
    localStorage.setItem('app-hax-darkMode', "false");  
  }
  catch(e) {
    // do nothing, in a secure context
  }
}
/**
 * behavior to make sure select lists are applied every time we do an ajax reload.
 */
Drupal.behaviors.haxCmsMoocBridgeOldContent = {
  attach: function (context, settings) {
    document.querySelectorAll("a[data-imagelightbox]").forEach((item) => {
      item.addEventListener("click", (e) => {
        e.preventDefault();
        e.stopImmediatePropagation();
        e.stopPropagation();
        let target = e.target;
        // move up to a tag if we are on an image tag
        if (target.tagName === "IMG") {
          target = target.parentNode;
        }
        const content = document.createElement("img");
        content.src = target.getAttribute("href");
        content.style.margin = "0 auto";
        content.style.display = "block";
        const evt = new CustomEvent("simple-modal-show", {
          bubbles: true,
          cancelable: true,
          detail: {
            title: e.target.getAttribute('alt'),
            elements: {
              content: content,
            },
            styles: {
              "--simple-modal-z-index": "100000000",
            },
            invokedBy: target,
            clone: false,
          },
        });
        window.dispatchEvent(evt);
      });
    });
  }
};
 