/**
 * HAX drag and drop functionality.
 * This is based on http://www.sitepoint.com/accessible-drag-drop
 */
(function ($) {
// extend the drupal js object by adding in an hax name-space
Drupal.hax = Drupal.hax || { functions: {} };

// dictionary for storing the selections data
// comprising an array of the currently selected Drupal.hax.dragitems
// a reference to the selected Drupal.hax.dragitems' owning container
// and a refernce to the current drop target container
Drupal.hax.selections = {
  activeitems: [],
  owner: null,
  droptarget: null,
  related: null
};

// generate a GUID
Drupal.hax.getGUID = function() {
  var guid = 'yxx-xyx-xxy-yyx-xyy-yyy';
  guid = guid.replace(/[xy]/g, function(c) {
    var r = crypto.getRandomValues(new Uint8Array(1))[0]%16|0, v = c == 'x' ? r : (r&0x3|0x8);
    return v.toString(16);
  });
  return guid;
};

// apply dropping properties to an object
Drupal.hax.applyCKEditor = function(obj) {
  obj.setAttribute('contenteditable', true);
  CKEDITOR.inline( obj, {
    extraPlugins: 'sourcedialog',
    extraAllowedContent: 'a(documentation);abbr[title];code',
    // Show toolbar on startup (optional).
    startupFocus: true
  } );
};

// apply dropping properties to an object
Drupal.hax.applyDrop = function(obj) {
  obj.setAttribute('aria-dropeffect', 'none');
  obj.setAttribute('data-hax-processed', 'true');
  obj.setAttribute('data-guid', Drupal.hax.getGUID());
  obj.setAttribute('data-draggable', 'target');
};

// apply dragging capability to item
Drupal.hax.applyDrag = function(obj) {
  obj.setAttribute('draggable', 'true');
  obj.setAttribute('aria-grabbed', 'false');
  obj.setAttribute('tabindex', '0');
  obj.setAttribute('data-hax-processed', 'true');
  obj.setAttribute('data-guid', Drupal.hax.getGUID());
  obj.setAttribute('data-draggable', 'item');
};

// resetting all selections
Drupal.hax.clearSelections = function() {
  // if we have any selected Drupal.hax.dragitems
  if (Drupal.hax.selections.activeitems.length) {
    //reset the owner reference
    Drupal.hax.selections.owner = null;
    //reset the grabbed state on every selected item
    for (var len = Drupal.hax.selections.activeitems.length, i = 0; i < len; i++) {
      Drupal.hax.selections.activeitems[i].setAttribute('aria-grabbed', 'false');
    }
    //then reset the Drupal.hax.dragitems array
    Drupal.hax.selections.activeitems = [];
  }
};

// removing dropeffect from the target containers
Drupal.hax.clearDropeffects = function() {
  //if we have any selected Drupal.hax.dragitems
  if (Drupal.hax.selections.activeitems.length) {
    //reset aria-dropeffect and remove tabindex from all Drupal.hax.targets
    for (var len = Drupal.hax.targets.length, i = 0; i < len; i++) {
      if (Drupal.hax.targets[i].getAttribute('aria-dropeffect') != 'none') {
        Drupal.hax.targets[i].setAttribute('aria-dropeffect', 'none');
        Drupal.hax.targets[i].removeAttribute('tabindex');
      }
    }
    //restore aria-grabbed and tabindex to all selectable Drupal.hax.dragitems 
    //without changing the grabbed value of any existing selected Drupal.hax.dragitems
    for (var len = Drupal.hax.dragitems.length, i = 0; i < len; i++) {
      if (!Drupal.hax.dragitems[i].getAttribute('aria-grabbed')) {
        Drupal.hax.dragitems[i].setAttribute('aria-grabbed', 'false');
        Drupal.hax.dragitems[i].setAttribute('tabindex', '0');
      } else if (Drupal.hax.dragitems[i].getAttribute('aria-grabbed') == 'true') {
        Drupal.hax.dragitems[i].setAttribute('tabindex', '0');
      }
    }
  }
};

// shortcut function for identifying an event element's target container
Drupal.hax.getContainer = function(element) {
  do {
    if (element.nodeType == 1 && element.getAttribute('aria-dropeffect')) {
      return element;
    }
  }
  while (element = element.parentNode);

  return null;
};

// selecting an item
Drupal.hax.addSelection = function (item) {
  //if the owner reference is still null, set it to this item's parent
  //so that further selection is only allowed within the same container
  if (!Drupal.hax.selections.owner) {
    Drupal.hax.selections.owner = item.parentNode;
  }

  //or if that's already happened then compare it with this item's parent
  //and if they're not the same container, return to prevent selection
  else if (Drupal.hax.selections.owner != item.parentNode) {
    return;
  }

  //set this item's grabbed state
  item.setAttribute('aria-grabbed', 'true');

  //add it to the Drupal.hax.dragitems array
  Drupal.hax.selections.activeitems.push(item);
};

// unselecting an item
Drupal.hax.removeSelection = function (item) {
  //reset this item's grabbed state
  item.setAttribute('aria-grabbed', 'false');

  //then find and remove this item from the existing Drupal.hax.dragitems array
  for (var len = Drupal.hax.selections.activeitems.length, i = 0; i < len; i++) {
    if (Drupal.hax.selections.activeitems[i] == item) {
      Drupal.hax.selections.activeitems.splice(i, 1);
      break;
    }
  }
};

//shorctut function for testing whether a selection modifier is pressed
Drupal.hax.hasModifier = function (e) {
  return (e.ctrlKey || e.metaKey || e.shiftKey);
};

// applying dropeffect to the target containers
Drupal.hax.addDropeffects = function () {
  //apply aria-dropeffect and tabindex to all Drupal.hax.targets apart from the owner
  for (var len = Drupal.hax.targets.length, i = 0; i < len; i++) {
    if (
      Drupal.hax.targets[i] != Drupal.hax.selections.owner &&
      Drupal.hax.targets[i].getAttribute('aria-dropeffect') == 'none'
    ) {
      Drupal.hax.targets[i].setAttribute('aria-dropeffect', 'move');
      Drupal.hax.targets[i].setAttribute('tabindex', '0');
    }
  }

  //remove aria-grabbed and tabindex from all Drupal.hax.dragitems inside those containers
  for (var len = Drupal.hax.dragitems.length, i = 0; i < len; i++) {
    if (
      Drupal.hax.dragitems[i].parentNode != Drupal.hax.selections.owner &&
      Drupal.hax.dragitems[i].getAttribute('aria-grabbed')
    ) {
      Drupal.hax.dragitems[i].removeAttribute('aria-grabbed');
      Drupal.hax.dragitems[i].removeAttribute('tabindex');
    }
  }
};

// mousedown event to implement single selection
Drupal.hax.eventMouseDown = function (e) {
  //if the element is a draggable item
  if (e.target.getAttribute('draggable')) {
    //clear dropeffect from the target containers
    Drupal.hax.clearDropeffects();
    //if the multiple selection modifier is not pressed
    //and the item's grabbed state is currently false
    if (!Drupal.hax.hasModifier(e) && e.target.getAttribute('aria-grabbed') == 'false') {
      //clear all existing selections
      Drupal.hax.clearSelections();
      //then add this new selection
      Drupal.hax.addSelection(e.target);
    }
  }
  // @todo need to ignore clicks on the toolbar axing the process
  /*else if (e.target.hasClass('hax-toolbar') || e.target.hasClass('hax-toolbar-groupname') || e.target.hasClass('hax-toolbar-tool')) {
    console.log(Drupal.hax.selections);
  }*/
  //else [if the element is anything else]
  //and the selection modifier is not pressed
  else if (!Drupal.hax.hasModifier(e)) {
    //clear dropeffect from the target containers
    Drupal.hax.clearDropeffects();
    //clear all existing selections
    //Drupal.hax.clearSelections();
  }
  //else [if the element is anything else and the modifier is pressed]
  else {
    //clear dropeffect from the target containers
    // allow clicking in the toolbar
    Drupal.hax.clearDropeffects();
  }
};

// mouseup event to implement multiple selection
Drupal.hax.eventMouseUp = function (e) {
  //if the element is a draggable item
  //and the multipler selection modifier is pressed
  if (e.target.getAttribute('draggable') && Drupal.hax.hasModifier(e)) {
    //if the item's grabbed state is currently true
    if (e.target.getAttribute('aria-grabbed') == 'true') {
      //unselect this item
      Drupal.hax.removeSelection(e.target);
      //if that was the only selected item
      //then reset the owner container reference
      if (!Drupal.hax.selections.activeitems.length) {
        Drupal.hax.selections.owner = null;
      }
    }
    //else [if the item's grabbed state is false]
    else {
      //add this additional selection
      Drupal.hax.addSelection(e.target);
    }
  }
};

// dragstart event to initiate mouse dragging
Drupal.hax.eventDragStart = function (e) {
  //if the element's parent is not the owner, then block this event
  if (Drupal.hax.selections.owner != e.target.parentNode) {
    e.preventDefault();
    return;
  }
  //[else] if the multiple selection modifier is pressed
  //and the item's grabbed state is currently false
  if (
    Drupal.hax.hasModifier(e) &&
    e.target.getAttribute('aria-grabbed') == 'false'
  ) {
    //add this additional selection
    Drupal.hax.addSelection(e.target);
  }
  //we don't need the transfer data, but we have to define something
  //otherwise the drop action won't work at all in firefox
  //most browsers support the proper mime-type syntax, eg. "text/plain"
  //but we have to use this incorrect syntax for the benefit of IE10+
  e.dataTransfer.setData('text', '');
  //apply dropeffect to the target containers
  Drupal.hax.addDropeffects();
};

// dragenter event to set that variable
Drupal.hax.eventDragEnter = function(e) {
  Drupal.hax.selections.related = e.target;
};

// dragleave event to maintain target highlighting using that variable
Drupal.hax.eventDragLeave = function (e) {
  //get a drop target reference from the Drupal.hax.selections.related Target
  var droptarget = Drupal.hax.getContainer(Drupal.hax.selections.related);
  //if the target is the owner then it's not a valid drop target
  if (droptarget == Drupal.hax.selections.owner) {
    droptarget = null;
  }
  //if the drop target is different from the last stored reference
  //(or we have one of those references but not the other one)
  if (droptarget != Drupal.hax.selections.droptarget) {
    //if we have a saved reference, clear its existing dragover class
    if (Drupal.hax.selections.droptarget) {
      Drupal.hax.selections.droptarget.className =
        Drupal.hax.selections.droptarget.className.replace(/ dragover/g, '');
    }
    //apply the dragover class to the new drop target reference
    if (droptarget) {
      droptarget.className += ' dragover';
    }
    //then save that reference for next time
    Drupal.hax.selections.droptarget = droptarget;
  }
};

// dragover event to allow the drag by preventing its default
Drupal.hax.eventDragOver = function(e) {
  // if we have any selected Drupal.hax.dragitems, allow them to be dragged
  if (Drupal.hax.selections.activeitems.length) {
    e.preventDefault();
  }
};

// event for the end of the drag event
Drupal.hax.eventDragEnd = function(e) {
  //if the element is a drop target container
  if (e.target.getAttribute('aria-dropeffect')) {
    //Enter or Modifier + M is the drop keystroke
    if (e.keyCode == 13 || (e.keyCode == 77 && Drupal.hax.hasModifier(e))) {
      //append the selected Drupal.hax.dragitems to the end of the target container
      for (var len = Drupal.hax.selections.activeitems.length, i = 0; i < len; i++) {
        e.target.appendChild(Drupal.hax.selections.activeitems[i]);
      }
      //clear dropeffect from the target containers
      Drupal.hax.clearDropeffects();
      //then set focus back on the last item that was selected, which is
      //necessary because we've removed tabindex from the current focus
      Drupal.hax.selections.activeitems[Drupal.hax.selections.activeitems.length - 1].focus();
      //reset the selections array
      Drupal.hax.clearSelections();
      //prevent default to to avoid any conflict with native actions
      e.preventDefault();
      // Reflow foundation for equal height adjustments
      $(document).foundation('equalizer', 'reflow');
    }
  }
  //if we have a valid drop target reference
  //(which implies that we have some selected Drupal.hax.dragitems)
  if (Drupal.hax.selections.droptarget) {
    //append the selected Drupal.hax.dragitems to the end of the target container
    for (var len = Drupal.hax.selections.activeitems.length, i = 0; i < len; i++) {
      Drupal.hax.selections.droptarget.appendChild(Drupal.hax.selections.activeitems[i]);
    }

    //prevent default to allow the action
    e.preventDefault();

    // Reflow foundation for equal height adjustments
    // @todo assumes foundation
    $(document).foundation('equalizer', 'reflow');
  }
  // if we have any selected Drupal.hax.dragitems
  if (Drupal.hax.selections.activeitems.length) {
    //clear dropeffect from the target containers
    Drupal.hax.clearDropeffects();

    //if we have a valid drop target reference
    if (Drupal.hax.selections.droptarget) {
      //reset the selections array
      Drupal.hax.clearSelections();

      //reset the target's dragover class
      Drupal.hax.selections.droptarget.className =
        Drupal.hax.selections.droptarget.className.replace(/ dragover/g, '');

      //reset the target reference
      Drupal.hax.selections.droptarget = null;
    }
  }
};

// keydown event to implement selection and abort
Drupal.hax.eventKeyDown = function (e) {
  //if the element is a grabbable item
  if (e.target.getAttribute('aria-grabbed')) {
    //Space is the selection or unselection keystroke
    if (e.keyCode == 32) {
      //if the multiple selection modifier is pressed
      if (Drupal.hax.hasModifier(e)) {
        //if the item's grabbed state is currently true
        if (e.target.getAttribute('aria-grabbed') == 'true') {
          //if this is the only selected item, clear dropeffect
          //from the target containers, which we must do first
          //in case subsequent unselection sets owner to null
          if (Drupal.hax.selections.activeitems.length == 1) {
            Drupal.hax.clearDropeffects();
          }
          //unselect this item
          Drupal.hax.removeSelection(e.target);
          //if we have any selections
          //apply dropeffect to the target containers,
          //in case earlier selections were made by mouse
          if (Drupal.hax.selections.activeitems.length) {
            Drupal.hax.addDropeffects();
          }
          //if that was the only selected item
          //then reset the owner container reference
          if (!Drupal.hax.selections.activeitems.length) {
            Drupal.hax.selections.owner = null;
          }
        }
        //else [if its grabbed state is currently false]
        else {
          //add this additional selection
          Drupal.hax.addSelection(e.target);
          //apply dropeffect to the target containers
          Drupal.hax.addDropeffects();
        }
      }
      // else [if the multiple selection modifier is not pressed]
      // and the item's grabbed state is currently false
      else if (e.target.getAttribute('aria-grabbed') == 'false') {
        //clear dropeffect from the target containers
        Drupal.hax.clearDropeffects();
        //clear all existing selections
        Drupal.hax.clearSelections();
        //add this new selection
        Drupal.hax.addSelection(e.target);
        //apply dropeffect to the target containers
        Drupal.hax.addDropeffects();
      }
      // else [if modifier is not pressed and grabbed is already true]
      else {
        // apply dropeffect to the target containers
        Drupal.hax.addDropeffects();
      }
      // then prevent default to avoid any conflict with native actions
      e.preventDefault();
    }
    // Modifier + M is the end-of-selection keystroke
    if (e.keyCode == 77 && Drupal.hax.hasModifier(e)) {
      // if we have any selected Drupal.hax.dragitems
      if (Drupal.hax.selections.activeitems.length) {
        // apply dropeffect to the target containers
        // in case earlier selections were made by mouse
        Drupal.hax.addDropeffects();
        // if the owner container is the last one, focus the first one
        if (Drupal.hax.selections.owner == Drupal.hax.targets[Drupal.hax.targets.length - 1]) {
          Drupal.hax.targets[0].focus();
        }
        // else [if it's not the last one], find and focus the next one
        else {
          for (var len = Drupal.hax.targets.length, i = 0; i < len; i++) {
            if (Drupal.hax.selections.owner == Drupal.hax.targets[i]) {
              Drupal.hax.targets[i + 1].focus();
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
    //if we have any selected Drupal.hax.dragitems
    if (Drupal.hax.selections.activeitems.length) {
      //clear dropeffect from the target containers
      Drupal.hax.clearDropeffects();
      //then set focus back on the last item that was selected, which is
      //necessary because we've removed tabindex from the current focus
      Drupal.hax.selections.activeitems[Drupal.hax.selections.activeitems.length - 1].focus();
      //clear all existing selections
      Drupal.hax.clearSelections();
      //but don't prevent default so that native actions can still occur
    }
  }
};

// setup and activate HAX on an interface
Drupal.hax.applyHax = function() {
  //exclude older browsers by the features we need them to support
  //and legacy opera explicitly so we don't waste time on a dead browser
  if (!document.querySelectorAll ||
    !('draggable' in document.createElement('span')) ||
    window.opera
  ) {
    return;
  }
  //get the collection of draggable Drupal.hax.targets and add their draggable attribute
  for (
      Drupal.hax.targets = document.querySelectorAll('[data-draggable="target"]'),
      len = Drupal.hax.targets.length,
      i = 0; i < len; i++) {
    Drupal.hax.applyDrop(Drupal.hax.targets[i]);
  }

  //get the collection of draggable Drupal.hax.dragitems and add their draggable attributes
  for (Drupal.hax.dragitems = document.querySelectorAll('[data-draggable="item"]'),
      len = Drupal.hax.dragitems.length,
      i = 0; i < len; i++) {
    Drupal.hax.applyDrag(Drupal.hax.dragitems[i]);
    // all draggable items get ckeditor inline atm
    Drupal.hax.applyCKEditor(Drupal.hax.dragitems[i]);
  }
};

// activate the event listeners for an object
Drupal.hax.applyEventListeners = function (obj) {
  // mouseup event to implement multiple selection
  obj.addEventListener('mouseup', function (e) { Drupal.hax.eventMouseUp(e); }, false);
  // mousedown event to implement single selection
  obj.addEventListener('mousedown', function (e) { Drupal.hax.eventMouseDown(e); }, false);
  // dragstart event to initiate mouse dragging
  obj.addEventListener('dragstart', function (e) { Drupal.hax.eventDragStart(e); }, false);
  // dragenter event to set that variable
  obj.addEventListener('dragenter', function (e) { Drupal.hax.eventDragEnter(e); }, false);
  // dragover event to allow the drag by preventing its default
  obj.addEventListener('dragover', function (e) { Drupal.hax.eventDragOver(e); }, false);
  // dragleave event to maintain target highlighting using that variable
  obj.addEventListener('dragleave', function (e) { Drupal.hax.eventDragLeave(e); }, false);
  // dragend event to implement Drupal.hax.dragitems being validly dropped into Drupal.hax.targets,
  // or invalidly dropped elsewhere, and to clean-up the interface either way
  obj.addEventListener('dragend', function (e) { Drupal.hax.eventDragEnd(e); }, false);
  // keydown event to implement Drupal.hax.dragitems being dropped into Drupal.hax.targets
  obj.addEventListener('keydown', function (e) { Drupal.hax.eventKeyDown(e); }, false);
};

$(document).ready(function() {
  Drupal.hax.applyHax();
  Drupal.hax.applyEventListeners(document);
});

})(jQuery);