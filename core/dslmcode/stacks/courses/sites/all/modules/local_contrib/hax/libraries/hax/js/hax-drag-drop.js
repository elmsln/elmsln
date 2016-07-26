/**
 * HAX drag and drop functionality.
 * This is based on http://www.sitepoint.com/accessible-drag-drop
 */
(function ($) {
Hax = { functions: {} };

// dictionary for storing the selections data
// comprising an array of the currently selected Hax.dragitems
// a reference to the selected Hax.dragitems' owning container
// and a refernce to the current drop target container
Hax.selections = {
  activeitems: [],
  owner: null,
  droptarget: null,
  related: null
};

// generate a GUID
Hax.getGUID = function() {
  var guid = 'yxx-xyx-xxy-yyx-xyy-yyy';
  guid = guid.replace(/[xy]/g, function(c) {
    var r = crypto.getRandomValues(new Uint8Array(1))[0]%16|0, v = c == 'x' ? r : (r&0x3|0x8);
    return v.toString(16);
  });
  return guid;
};

// apply dropping properties to an object
Hax.applyCKEditor = function(obj) {
  obj.setAttribute('contenteditable', true);
  CKEDITOR.inline( obj, {
    extraAllowedContent: 'a(documentation);abbr[title];code',
    mathJaxLib : '//cdn.mathjax.org/mathjax/2.2-latest/MathJax.js?config=TeX-AMS_HTML',
    // Show toolbar on startup (optional).
    startupFocus: true
  } );
};

// apply dropping properties to an object
Hax.applyDrop = function(obj) {
  obj.setAttribute('aria-dropeffect', 'none');
  obj.setAttribute('data-hax-processed', 'true');
  obj.setAttribute('data-guid', Hax.getGUID());
  obj.setAttribute('data-draggable', 'target');
};

// apply dragging capability to item
Hax.applyDrag = function(obj) {
  obj.setAttribute('draggable', 'true');
  obj.setAttribute('aria-grabbed', 'false');
  obj.setAttribute('tabindex', '0');
  obj.setAttribute('data-hax-processed', 'true');
  obj.setAttribute('data-guid', Hax.getGUID());
  obj.setAttribute('data-draggable', 'item');
};

// resetting all selections
Hax.clearSelections = function() {
  // if we have any selected Hax.dragitems
  if (Hax.selections.activeitems.length) {
    //reset the owner reference
    Hax.selections.owner = null;
    //reset the grabbed state on every selected item
    for (var len = Hax.selections.activeitems.length, i = 0; i < len; i++) {
      Hax.selections.activeitems[i].setAttribute('aria-grabbed', 'false');
    }
    //then reset the Hax.dragitems array
    Hax.selections.activeitems = [];
  }
};

// removing dropeffect from the target containers
Hax.clearDropeffects = function() {
  //if we have any selected Hax.dragitems
  if (Hax.selections.activeitems.length) {
    //reset aria-dropeffect and remove tabindex from all Hax.targets
    for (var len = Hax.targets.length, i = 0; i < len; i++) {
      if (Hax.targets[i].getAttribute('aria-dropeffect') != 'none') {
        Hax.targets[i].setAttribute('aria-dropeffect', 'none');
        Hax.targets[i].removeAttribute('tabindex');
      }
    }
    //restore aria-grabbed and tabindex to all selectable Hax.dragitems 
    //without changing the grabbed value of any existing selected Hax.dragitems
    for (var len = Hax.dragitems.length, i = 0; i < len; i++) {
      if (!Hax.dragitems[i].getAttribute('aria-grabbed')) {
        Hax.dragitems[i].setAttribute('aria-grabbed', 'false');
        Hax.dragitems[i].setAttribute('tabindex', '0');
      } else if (Hax.dragitems[i].getAttribute('aria-grabbed') == 'true') {
        Hax.dragitems[i].setAttribute('tabindex', '0');
      }
    }
  }
};

// shortcut function for identifying an event element's target container
Hax.getContainer = function(element) {
  do {
    if (element.nodeType == 1 && element.getAttribute('aria-dropeffect')) {
      return element;
    }
  }
  while (element = element.parentNode);

  return null;
};

// selecting an item
Hax.addSelection = function (item) {
  //if the owner reference is still null, set it to this item's parent
  //so that further selection is only allowed within the same container
  if (!Hax.selections.owner) {
    Hax.selections.owner = item.parentNode;
  }

  //or if that's already happened then compare it with this item's parent
  //and if they're not the same container, return to prevent selection
  else if (Hax.selections.owner != item.parentNode) {
    return;
  }

  //set this item's grabbed state
  item.setAttribute('aria-grabbed', 'true');

  //add it to the Hax.dragitems array
  Hax.selections.activeitems.push(item);
};

// unselecting an item
Hax.removeSelection = function (item) {
  //reset this item's grabbed state
  item.setAttribute('aria-grabbed', 'false');

  //then find and remove this item from the existing Hax.dragitems array
  for (var len = Hax.selections.activeitems.length, i = 0; i < len; i++) {
    if (Hax.selections.activeitems[i] == item) {
      Hax.selections.activeitems.splice(i, 1);
      break;
    }
  }
};

//shorctut function for testing whether a selection modifier is pressed
Hax.hasModifier = function (e) {
  return (e.ctrlKey || e.metaKey || e.shiftKey);
};

// applying dropeffect to the target containers
Hax.addDropeffects = function () {
  //apply aria-dropeffect and tabindex to all Hax.targets apart from the owner
  for (var len = Hax.targets.length, i = 0; i < len; i++) {
    if (
      Hax.targets[i] != Hax.selections.owner &&
      Hax.targets[i].getAttribute('aria-dropeffect') == 'none'
    ) {
      Hax.targets[i].setAttribute('aria-dropeffect', 'move');
      Hax.targets[i].setAttribute('tabindex', '0');
    }
  }

  //remove aria-grabbed and tabindex from all Hax.dragitems inside those containers
  for (var len = Hax.dragitems.length, i = 0; i < len; i++) {
    if (
      Hax.dragitems[i].parentNode != Hax.selections.owner &&
      Hax.dragitems[i].getAttribute('aria-grabbed')
    ) {
      Hax.dragitems[i].removeAttribute('aria-grabbed');
      Hax.dragitems[i].removeAttribute('tabindex');
    }
  }
};

// mousedown event to implement single selection
Hax.eventMouseDown = function (e) {
  //if the element is a draggable item
  if (e.target.getAttribute('draggable')) {
    //clear dropeffect from the target containers
    Hax.clearDropeffects();
    //if the multiple selection modifier is not pressed
    //and the item's grabbed state is currently false
    if (!Hax.hasModifier(e) && e.target.getAttribute('aria-grabbed') == 'false') {
      //clear all existing selections
      Hax.clearSelections();
      //then add this new selection
      Hax.addSelection(e.target);
    }
  }
  // @todo need to ignore clicks on the toolbar axing the process
  /*else if (e.target.hasClass('hax-toolbar') || e.target.hasClass('hax-toolbar-groupname') || e.target.hasClass('hax-toolbar-tool')) {
    console.log(Hax.selections);
  }*/
  //else [if the element is anything else]
  //and the selection modifier is not pressed
  else if (!Hax.hasModifier(e)) {
    //clear dropeffect from the target containers
    Hax.clearDropeffects();
    //clear all existing selections
    //Hax.clearSelections();
  }
  //else [if the element is anything else and the modifier is pressed]
  else {
    //clear dropeffect from the target containers
    // allow clicking in the toolbar
    Hax.clearDropeffects();
  }
};

// mouseup event to implement multiple selection
Hax.eventMouseUp = function (e) {
  //if the element is a draggable item
  //and the multipler selection modifier is pressed
  if (e.target.getAttribute('draggable') && Hax.hasModifier(e)) {
    //if the item's grabbed state is currently true
    if (e.target.getAttribute('aria-grabbed') == 'true') {
      //unselect this item
      Hax.removeSelection(e.target);
      //if that was the only selected item
      //then reset the owner container reference
      if (!Hax.selections.activeitems.length) {
        Hax.selections.owner = null;
      }
    }
    //else [if the item's grabbed state is false]
    else {
      //add this additional selection
      Hax.addSelection(e.target);
    }
  }
};

// dragstart event to initiate mouse dragging
Hax.eventDragStart = function (e) {
  //if the element's parent is not the owner, then block this event
  if (Hax.selections.owner != e.target.parentNode) {
    e.preventDefault();
    return;
  }
  //[else] if the multiple selection modifier is pressed
  //and the item's grabbed state is currently false
  if (
    Hax.hasModifier(e) &&
    e.target.getAttribute('aria-grabbed') == 'false'
  ) {
    //add this additional selection
    Hax.addSelection(e.target);
  }
  //we don't need the transfer data, but we have to define something
  //otherwise the drop action won't work at all in firefox
  //most browsers support the proper mime-type syntax, eg. "text/plain"
  //but we have to use this incorrect syntax for the benefit of IE10+
  e.dataTransfer.setData('text', '');
  //apply dropeffect to the target containers
  Hax.addDropeffects();
};

// dragenter event to set that variable
Hax.eventDragEnter = function(e) {
  Hax.selections.related = e.target;
};

// dragleave event to maintain target highlighting using that variable
Hax.eventDragLeave = function (e) {
  //get a drop target reference from the Hax.selections.related Target
  var droptarget = Hax.getContainer(Hax.selections.related);
  //if the target is the owner then it's not a valid drop target
  if (droptarget == Hax.selections.owner) {
    droptarget = null;
  }
  //if the drop target is different from the last stored reference
  //(or we have one of those references but not the other one)
  if (droptarget != Hax.selections.droptarget) {
    //if we have a saved reference, clear its existing dragover class
    if (Hax.selections.droptarget) {
      Hax.selections.droptarget.className =
        Hax.selections.droptarget.className.replace(/ dragover/g, '');
    }
    //apply the dragover class to the new drop target reference
    if (droptarget) {
      droptarget.className += ' dragover';
    }
    //then save that reference for next time
    Hax.selections.droptarget = droptarget;
  }
};

// dragover event to allow the drag by preventing its default
Hax.eventDragOver = function(e) {
  // if we have any selected Hax.dragitems, allow them to be dragged
  if (Hax.selections.activeitems.length) {
    e.preventDefault();
  }
};

// event for the end of the drag event
Hax.eventDragEnd = function(e) {
  //if the element is a drop target container
  if (e.target.getAttribute('aria-dropeffect')) {
    //Enter or Modifier + M is the drop keystroke
    if (e.keyCode == 13 || (e.keyCode == 77 && Hax.hasModifier(e))) {
      //append the selected Hax.dragitems to the end of the target container
      for (var len = Hax.selections.activeitems.length, i = 0; i < len; i++) {
        e.target.appendChild(Hax.selections.activeitems[i]);
      }
      //clear dropeffect from the target containers
      Hax.clearDropeffects();
      //then set focus back on the last item that was selected, which is
      //necessary because we've removed tabindex from the current focus
      Hax.selections.activeitems[Hax.selections.activeitems.length - 1].focus();
      //reset the selections array
      Hax.clearSelections();
      //prevent default to to avoid any conflict with native actions
      e.preventDefault();
      // Reflow foundation for equal height adjustments
      $(document).foundation('equalizer', 'reflow');
    }
  }
  //if we have a valid drop target reference
  //(which implies that we have some selected Hax.dragitems)
  if (Hax.selections.droptarget) {
    //append the selected Hax.dragitems to the end of the target container
    for (var len = Hax.selections.activeitems.length, i = 0; i < len; i++) {
      Hax.selections.droptarget.appendChild(Hax.selections.activeitems[i]);
    }

    //prevent default to allow the action
    e.preventDefault();

    // Reflow foundation for equal height adjustments
    // @todo assumes foundation
    $(document).foundation('equalizer', 'reflow');
  }
  // if we have any selected Hax.dragitems
  if (Hax.selections.activeitems.length) {
    //clear dropeffect from the target containers
    Hax.clearDropeffects();

    //if we have a valid drop target reference
    if (Hax.selections.droptarget) {
      //reset the selections array
      Hax.clearSelections();

      //reset the target's dragover class
      Hax.selections.droptarget.className =
        Hax.selections.droptarget.className.replace(/ dragover/g, '');

      //reset the target reference
      Hax.selections.droptarget = null;
    }
  }
};

// keydown event to implement selection and abort
Hax.eventKeyDown = function (e) {
  //if the element is a grabbable item
  if (e.target.getAttribute('aria-grabbed')) {
    //Space is the selection or unselection keystroke
    if (e.keyCode == 32) {
      //if the multiple selection modifier is pressed
      if (Hax.hasModifier(e)) {
        //if the item's grabbed state is currently true
        if (e.target.getAttribute('aria-grabbed') == 'true') {
          //if this is the only selected item, clear dropeffect
          //from the target containers, which we must do first
          //in case subsequent unselection sets owner to null
          if (Hax.selections.activeitems.length == 1) {
            Hax.clearDropeffects();
          }
          //unselect this item
          Hax.removeSelection(e.target);
          //if we have any selections
          //apply dropeffect to the target containers,
          //in case earlier selections were made by mouse
          if (Hax.selections.activeitems.length) {
            Hax.addDropeffects();
          }
          //if that was the only selected item
          //then reset the owner container reference
          if (!Hax.selections.activeitems.length) {
            Hax.selections.owner = null;
          }
        }
        //else [if its grabbed state is currently false]
        else {
          //add this additional selection
          Hax.addSelection(e.target);
          //apply dropeffect to the target containers
          Hax.addDropeffects();
        }
      }
      // else [if the multiple selection modifier is not pressed]
      // and the item's grabbed state is currently false
      else if (e.target.getAttribute('aria-grabbed') == 'false') {
        //clear dropeffect from the target containers
        Hax.clearDropeffects();
        //clear all existing selections
        Hax.clearSelections();
        //add this new selection
        Hax.addSelection(e.target);
        //apply dropeffect to the target containers
        Hax.addDropeffects();
      }
      // else [if modifier is not pressed and grabbed is already true]
      else {
        // apply dropeffect to the target containers
        Hax.addDropeffects();
      }
      // then prevent default to avoid any conflict with native actions
      e.preventDefault();
    }
    // Modifier + M is the end-of-selection keystroke
    if (e.keyCode == 77 && Hax.hasModifier(e)) {
      // if we have any selected Hax.dragitems
      if (Hax.selections.activeitems.length) {
        // apply dropeffect to the target containers
        // in case earlier selections were made by mouse
        Hax.addDropeffects();
        // if the owner container is the last one, focus the first one
        if (Hax.selections.owner == Hax.targets[Hax.targets.length - 1]) {
          Hax.targets[0].focus();
        }
        // else [if it's not the last one], find and focus the next one
        else {
          for (var len = Hax.targets.length, i = 0; i < len; i++) {
            if (Hax.selections.owner == Hax.targets[i]) {
              Hax.targets[i + 1].focus();
              break;
            }
          }
        }
      }
      //then prevent default to avoid any conflict with native actions
      e.preventDefault();
    }
  }
  //Escape is the abort keystroke (for any target element)
  if (e.keyCode == 27) {
    //if we have any selected Hax.dragitems
    if (Hax.selections.activeitems.length) {
      //clear dropeffect from the target containers
      Hax.clearDropeffects();
      //then set focus back on the last item that was selected, which is
      //necessary because we've removed tabindex from the current focus
      Hax.selections.activeitems[Hax.selections.activeitems.length - 1].focus();
      //clear all existing selections
      Hax.clearSelections();
      //but don't prevent default so that native actions can still occur
    }
  }
};

// setup and activate HAX on an interface
Hax.applyHax = function() {
  //exclude older browsers by the features we need them to support
  //and legacy opera explicitly so we don't waste time on a dead browser
  if (!document.querySelectorAll ||
    !('draggable' in document.createElement('span')) ||
    window.opera
  ) {
    return;
  }
  //get the collection of draggable Hax.targets and add their draggable attribute
  for (
      Hax.targets = document.querySelectorAll('[data-draggable="target"]'),
      len = Hax.targets.length,
      i = 0; i < len; i++) {
    Hax.applyDrop(Hax.targets[i]);
  }

  //get the collection of draggable Hax.dragitems and add their draggable attributes
  for (Hax.dragitems = document.querySelectorAll('[data-draggable="item"]'),
      len = Hax.dragitems.length,
      i = 0; i < len; i++) {
    Hax.applyDrag(Hax.dragitems[i]);
    // all draggable items get ckeditor inline atm
    Hax.applyCKEditor(Hax.dragitems[i]);
  }
};

// activate the event listeners for an object
Hax.applyEventListeners = function (obj) {
  // mouseup event to implement multiple selection
  obj.addEventListener('mouseup', function (e) { Hax.eventMouseUp(e); }, false);
  // mousedown event to implement single selection
  obj.addEventListener('mousedown', function (e) { Hax.eventMouseDown(e); }, false);
  // dragstart event to initiate mouse dragging
  obj.addEventListener('dragstart', function (e) { Hax.eventDragStart(e); }, false);
  // dragenter event to set that variable
  obj.addEventListener('dragenter', function (e) { Hax.eventDragEnter(e); }, false);
  // dragover event to allow the drag by preventing its default
  obj.addEventListener('dragover', function (e) { Hax.eventDragOver(e); }, false);
  // dragleave event to maintain target highlighting using that variable
  obj.addEventListener('dragleave', function (e) { Hax.eventDragLeave(e); }, false);
  // dragend event to implement Hax.dragitems being validly dropped into Hax.targets,
  // or invalidly dropped elsewhere, and to clean-up the interface either way
  obj.addEventListener('dragend', function (e) { Hax.eventDragEnd(e); }, false);
  // keydown event to implement Hax.dragitems being dropped into Hax.targets
  obj.addEventListener('keydown', function (e) { Hax.eventKeyDown(e); }, false);
};

$(document).ready(function() {
  Hax.applyHax();
  Hax.applyEventListeners(document);
});

})(jQuery);