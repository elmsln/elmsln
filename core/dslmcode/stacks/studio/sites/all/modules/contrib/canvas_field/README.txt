Thanks to the creators of the Silk Icon Set
_________________________________________
Mark James
http://www.famfamfam.com/lab/icons/silk/
_________________________________________

Extending canvas_field:

TOOLS:

All tools should extend CanvasField.Tools.baseTool
and use prototypes of the base functions to react
to canvas events.  The events are:

- start:  The tool is active, and the canvas has been clicked.
- move:   The tool is active, canvas has been clicked, and the
  cursor is in motion.
- pause:  The tool is active and the canvas has been clicked, but
  the tool has left the canvas.  For path-based tools,
  this is an opportunity to reset and wait for the cursor
  to re-enter the canvas.
- stop:   The tool is active, but a mouseUp event has occurred,
  meaning that the tools should stop acting on the canvas.
- config: Currently not implemented, but will probably allow
  the tool to define a configuration form.

The pen tool is a good example of a tool template.