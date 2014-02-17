/**
 * Sponsored by: Senter for IKT i utdanningen
 * Code: paalj
 *
 * @file
 * Drag and drop with lines quiz question type implemented using the Raphaël 
 * javascript library (http://raphaeljs.com/)
 * 
 */

/**
 * Implementation of the connection between a hotspot and the label
 */
Raphael.fn.connection = function (obj1, obj2, line, bg) {
    if (obj1.line && obj1.from && obj1.to && obj1.bg) {
        line = obj1;
        obj1 = line.from;
        obj2 = line.to;
    }
    
    var bb1 = obj1.getBBox(),
        bb2 = obj2.getBBox(),
        p = [{x: bb1.x + bb1.width / 2, y: bb1.y - 1},
        {x: bb1.x + bb1.width / 2, y: bb1.y + bb1.height + 1},
        {x: bb1.x - 1, y: bb1.y + bb1.height / 2},
        {x: bb1.x + bb1.width + 1, y: bb1.y + bb1.height / 2},
        {x: bb2.x + bb2.width / 2, y: bb2.y - 1},
        {x: bb2.x + bb2.width / 2, y: bb2.y + bb2.height + 1},
        {x: bb2.x - 1, y: bb2.y + bb2.height / 2},
        {x: bb2.x + bb2.width + 1, y: bb2.y + bb2.height / 2}],
        d = {}, dis = [];
    for (var i = 0; i < 4; i++) {
        for (var j = 4; j < 8; j++) {
            var dx = Math.abs(p[i].x - p[j].x),
                dy = Math.abs(p[i].y - p[j].y);
            if ((i == j - 4) || (((i != 3 && j != 6) || p[i].x < p[j].x) && ((i != 2 && j != 7) || p[i].x > p[j].x) && ((i != 0 && j != 5) || p[i].y > p[j].y) && ((i != 1 && j != 4) || p[i].y < p[j].y))) {
                dis.push(dx + dy);
                d[dis[dis.length - 1]] = [i, j];
            }
        }
    }
    if (dis.length == 0) {
        var res = [0, 4];
    } else {
        res = d[Math.min.apply(Math, dis)];
    }
    var x1 = p[res[0]].x,
        y1 = p[res[0]].y,
        x4 = p[res[1]].x,
        y4 = p[res[1]].y;
    dx = Math.max(Math.abs(x1 - x4) / 2, 10);
    dy = Math.max(Math.abs(y1 - y4) / 2, 10);
    var x2 = [x1, x1, x1 - dx, x1 + dx][res[0]].toFixed(3),
        y2 = [y1 - dy, y1 + dy, y1, y1][res[0]].toFixed(3),
        x3 = [0, 0, 0, 0, x4, x4, x4 - dx, x4 + dx][res[1]].toFixed(3),
        y3 = [0, 0, 0, 0, y1 + dy, y1 - dy, y4, y4][res[1]].toFixed(3);
    var path = ["M", x1.toFixed(3), y1.toFixed(3), "C", x2, y2, x3, y3, x4.toFixed(3), y4.toFixed(3)].join(",");
    if (line && line.line) {
        line.bg && line.bg.attr({path: path});
        line.line.attr({path: path});
    } else {
        var color = typeof line == "string" ? line : "#000";
        return {
            bg: bg && bg.split && this.path(path).attr({stroke: bg.split("|")[0], fill: "none", "stroke-width": bg.split("|")[1] || 3})/*.toBack()*/,
            line: this.path(path).attr({stroke: color, fill: "none", "stroke-width":3}),
            from: obj1,
            to: obj2
        };
    }
};

(function ($) {
var QuizUtil = {
    // The minimum width of the label
    LABEL_MIN_WIDTH: 40,
    
    CANVAS_PADDING: 10,
  
    // The glow implementation should be moved into a class, 
    // but will do for now 
    current_glow: null,
    
    current_editor: null,
    
    drag_mode: false,
    
    imageChanged: false,

    defined: function (a) {
      return (typeof a !== 'undefined');
    },
    
    bboxUnion: function(bbox1, bbox2) {
      bbox1.x = bbox1.x < bbox2.x ? bbox1.x : bbox2.x; 
      bbox1.y = bbox1.y < bbox2.y ? bbox1.y : bbox2.y;
      bbox1.x2 = bbox1.x2 > bbox2.x2 ? bbox1.x2 : bbox2.x2;
      bbox1.y2 = bbox1.y2 > bbox2.y2 ? bbox1.y2 : bbox2.y2;
      
      return bbox1;
    }
};
/**
 * A list of quiz ddlines elements.
 * 
 * Responsible for: 
 * - Holding the elements in-memory 
 * - Creating/Parsing the jsondata 
 * - Making the form input field being in-sync
 */
var QuizElementList = {
  elements: [],
  engine: null,
  add: function(element) {
    this.elements.push(element);
    this.updateForm();
  },
  remove: function(element) {
    // Remove from list:
    for(var i=0; i<this.elements.length; i++) {
      if(element == this.elements[i]) {
        this.elements.splice(i,1);
      }
    }   
    // Update form cache:
    this.updateForm();
  },
  clear: function() {
    this.elements = [];
    
    // Update form cache:
    this.updateForm();
  },
  updateForm: function() {
    if(this.engine.isEditMode()) {
      // Set the value of the hidden form field (ddlines_elements)
      $('input[name=ddlines_elements]').val(this.toJson());
    }
  },
  load: function(engine, display_answers, id) {
    
    QuizElementList.engine = engine;
    
    var obj=null;
    if(engine.isResultMode()) {
      obj = display_answers ? engine.conf["answers-"+id] : engine.conf["correct-"+id];
    }
    else {
      json = $('input[name=ddlines_elements]').val();
      
      if(!json || json.length == 0) {
        return;
      }
      
      obj = $.parseJSON(json);
    }
    
    // Set canvas size:
    engine.resizePaper(obj.canvas.width, obj.canvas.height);
    
    // Set image position:
    if(!QuizUtil.imageChanged) {
      engine.image.setBounds(obj.image.left, obj.image.top, obj.image.width, obj.image.height);
    }
    
    // Add elements:
    if(QuizUtil.defined(obj.elements)) {
      for (var i = 0; i < obj.elements.length; i++) {
        this.add(QuizElement.fromJson(obj.elements[i], engine));
      }
    }
    
    // Update connecting lines between each pair if hotspot 
    // and label: 
    engine.redrawConnections();
  },
  toJson: function() {
    // Get image location:
    var elements='';
    var json = '{' + this.engine.image.toJson() + ',' + this.engine.toJson();
    for (var i = 0; i < this.elements.length; i++) {      
      elements += this.elements[i].toJson() + (i<this.elements.length-1 ? ',' : '');
    }
    
    if(this.elements.length>0) {
      json += ',"elements":['+elements+']';
    }
    
    return json+'}';
  },
  size: function() {
    return this.elements.length;
  },
  updateHotspotRadius: function(radius) {
    radius = parseInt(radius);
    
    this.engine.conf.hotspot.radius = radius;
    
    // Update radius for all elements:
    for(var i=0; i<this.elements.length; i++) {
      this.elements[i].uiHotspot.updateHotspotRadius(radius);
      this.elements[i].redrawConnection();
    }   
  },
  adjustCanvasSize: function() {
    
    var moveLeft = moveUp = 0;
    var bbox = this.engine.image.getBBox();
    var maxElementWidth = 0;
    
    /* Auto adjust canvas size */
    for (var i = 0; i < this.elements.length; i++) {
      bbox2 = this.elements[i].getBBox();
      maxElementWidth = maxElementWidth < bbox2.width ? bbox2.width : maxElementWidth; 
      
      bbox = QuizUtil.bboxUnion(bbox, bbox2);
    }
    
    var horizontalPadding = this.engine.executionModeLines() ? QuizUtil.CANVAS_PADDING : maxElementWidth * 0.6;    
    horizontalPadding = horizontalPadding > QuizUtil.CANVAS_PADDING ? horizontalPadding : QuizUtil.CANVAS_PADDING; 
    
    moveLeft = -bbox.x + horizontalPadding;
    moveUp = -bbox.y + QuizUtil.CANVAS_PADDING;
    
    /* Update all elements */
    for (var i = 0; i < this.elements.length; i++) {
      this.elements[i].move(moveLeft, moveUp);      
    }
    
    // Update image:
    this.engine.image.move(moveLeft, moveUp);
    
    // Update canvas-size
    this.engine.setSize(bbox.x2-bbox.x+(horizontalPadding*2),bbox.y2-bbox.y+(QuizUtil.CANVAS_PADDING*2));
    
    this.updateForm();
  }
};

/*
 * A user's answers
 */
var Answers = {
  elements: [],  
  setAnswer: function(label_id, hotspot_id) {
    this.elements[label_id] = hotspot_id ;
    this.updateForm();
  },
  removeAnswer: function(label_id) {
    delete this.elements[label_id];
    this.updateForm();
  },
  toJson: function() {
    var json = '';
    var count=0;
    for (var key in this.elements) {    
      json += (count>0 ? ',' : '') + '{"label_id":'+key+',"hotspot_id":'+this.elements[key]+'}';
      count++;
    }
    
    if(count===0) {
      return '';
    }
    else {
      return '['+json+']';
    }
  },
  updateForm: function() {
    $('input[name=tries]').val(this.toJson());
  }
};

Drupal.behaviors.quiz_ddlines = {
  initialized: false,
  attach: function(context) {
    /* Auto adjust canvas size */
    $('.node-quiz_ddlines-form #edit-submit:not(.canvas-adjusted)').click(function() {
      QuizElementList.adjustCanvasSize();
      $(this).addClass('canvas-adjusted');
    });
    
    // Make hotspot radius only accept numbers:
    $('input#edit-hotspot-radius').keypress(function(e) {
      var key_codes = [48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 0, 8];
    
      if (!($.inArray(e.which, key_codes) >= 0)) {
        e.preventDefault();
      }
    });
    
    // Initializing the result page; the correct answer part
    $('.quiz-ddlines-correct-answers', context).each(function() {
      // Id is the node id of the question node
      // Will be overwritten in engine.init
      var id = $(this).attr('id');

      var engine = new Engine();
      engine.init(this, id);
        
      // Load elements if they exists:
      QuizElementList.load(engine, false, id);
    });
    
    // Initializing the result page; the user answer part
    $('.quiz-ddlines-user-answers', context).each(function() {
      // Id is the node id of the question node
      // Will be overwritten in engine.init
      var id = $(this).attr('id');
      
      var engine = new Engine();
      engine.init(this, id);
        
      // Load elements if they exists:
      QuizElementList.load(engine, true, id);
    });
    
    $('.image-preview', context).each(function() {
      if(this.initialized) {
        return;
      }
      var self = this;
      this.initialized = true;
      
      // Initialize
      var engine = new Engine();
      
      // Need to wait for IE to make image beeing displayed
      // This is not a great solution, but it does work.
      setTimeout( function() {
        engine.init(self);
        
        // Load elements if they exists:
        QuizElementList.load(engine);
        
        // Show helptext if no alternatives have been added:
        if(engine.isNew()) {
          engine.addHelpText();
        }
      }, ($.browser.msie ? 1000 : 0));
    });           
  }
};

// generic functions for dragging of sets:
function set_drag_start(x, y, event, set) {
  set = QuizUtil.defined(set) ? set : this.set;
  
  QuizUtil.drag_mode = false;
  
  set.ox = x;
  set.oy = y;
}
function set_drag_move(dx, dy, x, y, event, set) {
  QuizUtil.drag_mode = true;
  
  set = QuizUtil.defined(set) ? set : this.set;
  
  if(QuizElementList.engine.isEditMode()) {
    var inside = true;
    // Do not allow dragging outside canvas:
    set.forEach(function(elm){
      var elm_x,elm_y,elm_width,elm_height;
      if(elm.type === "circle") {      
        var radius = elm.attr("r");
        elm_x = elm.attr("cx")+(x - elm.set.ox)-radius;
        elm_y = elm.attr("cy")+(y - elm.set.oy)-radius;
        elm_width = elm_height = radius*2;
      }
      else {
        elm_x = elm.attr("x")+(x - elm.set.ox);
        elm_y = elm.attr("y")+(y - elm.set.oy);
        var elm_bbox = elm.getBBox();
        elm_width = elm_bbox.width;
        elm_height = elm_bbox.height;
      }
      
      var going_left = (x - elm.set.ox) < 0;
      var going_up = (y - elm.set.oy) < 0;
      
      if((elm_x<-10 && going_left)
          || (elm_y<-10 && going_up) 
          || ((elm_x + elm_width)>QuizElementList.engine.getCanvasWidth()+30 && !going_left)
          || (elm_y + elm_height)>QuizElementList.engine.getCanvasHeight()+10 && !going_up) {
        inside = false;
        return false;
      }
    });
    
    
    if(!inside) {
      return false;
    }
  }
  
  set.forEach(function(elm){
    if(elm.type === "circle") {
      elm.attr({cx: elm.attr("cx")+(x - elm.set.ox),cy: elm.attr("cy")+(y - elm.set.oy)});
    }
    else {
      elm.attr({x: elm.attr("x")+(x - elm.set.ox),y: elm.attr("y")+(y - elm.set.oy)});
    }
  });

  set.ox = x;
  set.oy = y;

  if(QuizUtil.defined(set.parent)) {
    set.parent.redrawConnection();
  }
  
  return true;
};
function set_drag_finished(event) {
  // Update form:
  QuizElementList.updateForm();
};


/*
 * The main class. Representing the canvas.
 * */
function Engine() {
  var self = this;
  this.id = null;
  this.r = null;    
  this.conf = null; 
  this.node_id = null;
  this.helptext = null;
  
  this.getSelector = function() {
    return "#"+this.id;
  };
  
  this.init = function (container_class, node_id) {
  
    if(!QuizUtil.defined(Engine.counter)) {
      Engine.counter = 0;
    }
    Engine.counter++;
    this.id = "ddlines-container-"+Engine.counter;
    this.node_id = QuizUtil.defined(node_id) ? node_id : null;
    
    // Add a specific ID and class to div, so CSS may be set only
    // for our case:
    $(container_class).attr("id",this.id);
    $(container_class).addClass("ddlines-container");
    
    this.conf = Drupal.settings.quiz_ddlines;
    
    if(this.isEditMode()) {
      this.conf.feedback.enabled = $('#edit-feedback-enabled').is(':checked') ? "1" : "0";    
      $('#edit-feedback-enabled').change(function(){
        // Set the conf variable:
        self.conf.feedback.enabled = $('#edit-feedback-enabled').is(':checked') ? "1" : "0";
        $('#feedback-disabled').css({'display': (self.feedbackEnabled() ? 'none' : 'block')});
      });
      
      // Listen to change events on hotspot radius input:
      $('input#edit-hotspot-radius').change(function(e) {
        QuizElementList.updateHotspotRadius($(this).val());
      });
      
      // Add click-handler to add elements when clicking in canvas:
      $(this.getSelector()).click(function(event) {
        
        var targetIsSVG = (event.target.nodeName === 'svg' || event.target.nodeName === 'DIV'); 
        var targetIsImage = (event.target.nodeName === 'image' || event.target.nodeName === 'shape');
        
        if(!targetIsSVG && QuizUtil.drag_mode){
          return;
        }
        
        // Don't create new element when focus is on inputbox
        if(QuizUtil.current_editor != null && (targetIsSVG || targetIsImage)) {
          QuizUtil.current_editor.editingDone();
          return;
        }
        
        if(targetIsSVG || targetIsImage ||
          (self.helptext != null && event.target.nodeName === 'tspan')) {
          
          // Remove help text:
          if(self.helptext != null) {
            self.helptext.remove();
            self.helptext = null;
          }
          
          // Add element:
          self.createNewElement(event);
        }
      });
      
      $(this.getSelector()).resizable({
         stop: function(event, ui) {
           // Update size!
           var height=$(self.getSelector()).height();
           var width=$(self.getSelector()).width();
           self.setSize(width,height);
         }
         /*minHeight: 300,
         minWidth: 450*/
      });
      
      // Add delete handler:
      $(document).keydown(function(event) {
        // Check if the deletion did not take place within an input field
        // 46 is the delete button        
        if(event.target.nodeName != 'INPUT' && event.which === 46) {
          // The glow represents the current selected object
          if(QuizUtil.current_glow != null) {
            QuizUtil.current_glow.set.parent.remove();
            QuizUtil.current_glow = null;
            $("#quiz-ddlines-toolpane").fadeOut();
          }
        }
      });
      
      // Add clearing of data when image is removed
      $('form.node-quiz_ddlines-form #edit-field-image-und-0-remove-button').mousedown(function() {
        QuizElementList.clear();
        
        QuizUtil.imageChanged = true;
      });
    }
    
    // Set size of canvas
    $(this.getSelector()).height(this.getCanvasHeight()).width(this.getCanvasWidth());    
    
    // Create paper
    this.r = Raphael(this.id, this.getCanvasWidth(), this.getCanvasHeight());

    // Get image attributes:
    var img_width = $(this.getSelector() + ' > img').attr("width");
    var img_height = $(this.getSelector() + ' > img').attr("height");   
    var img_uri=$(this.getSelector() + ' > img').attr("src");   
    this.image = new QuizImage(this, img_uri, img_width, img_height);
  };
  
  this.addHelpText = function() {
    if(this.isEditMode()) {
      // Add help text:
      // Only if this
      self.helptext = this.r.text(this.getCanvasWidth()/2,this.getCanvasHeight()/2,Drupal.t("Click anywhere in\nthe canvas to\nadd an alternative"));
      self.helptext.attr({'font-size': 50, 'fill': '#FFF', stroke:'#000', 'font-weight': 'bold'});
      
      self.helptext.mousedown(function(){
        QuizUtil.drag_mode = false;
      });
    }
  };
  
  
  this.getCanvasHeight = function() {
    if(this.isResultMode()) {
      return this.conf["correct-"+this.node_id].canvas.height;
    }
    else {
      return parseInt(this.conf.canvas.height);
    }
  };
  
  this.getCanvasWidth = function() {
    if(this.isResultMode()) {
      return this.conf["correct-"+this.node_id].canvas.width;
    }
    else {      
      return parseInt(this.conf.canvas.width);
    }
  };
  
  this.resizePaper = function(width, height) {
    this.setSize(width,height);
    $(this.getSelector()).height(height).width(width);
  };
  
  this.setSize = function(width,height) {
    if(this.isEditMode()) {
      this.conf.canvas.width=width;
      this.conf.canvas.height=height;
    }
    this.r.setSize(width,height);
  };
   
  this.redrawConnections = function() {
    for (var i = QuizElementList.elements.length; i--;) {
      QuizElementList.elements[i].redrawConnection();
    }
    this.r.safari();
  };
    
  this.createNewElement = function (event) {
    // Create a new element    
    var x = this.getRelativeX(event.pageX);
    var y = this.getRelativeY(event.pageY);    
    var element = new QuizElement(self, Raphael.getColor(0.9), "", undefined, x > 20 ? x-20 : x, y > 80 ? y-80 : y, undefined, x, y);
    // Add to list
    QuizElementList.add(element);
    
    element.gotoEditMode();
  };
  
  this.toJson = function() {     
    return '"canvas":{"width":'+this.conf.canvas.width+',"height":'+this.conf.canvas.height+'}';
  };
    
  this.getPosition = function() {
    return $(this.getSelector()).offset();
  };
    
  this.getRelativeX = function(x) {
    return (x-this.getPosition().left);
  };
  
  this.getRelativeY = function(y) {
    return (y-this.getPosition().top);
  };
  
  this.isNew = function() {
    return (this.conf.editmode === 'add');
  };
  
  this.isEditMode = function() {
    return (this.conf.mode === 'edit');
  };
  
  this.executionModeLines = function() {
    return (this.conf.execution_mode === '0');
  };
  
  this.isResultMode = function() {
    return (this.conf.mode === 'result');
  };
  
  this.isTakeMode = function() {
    return (this.conf.mode === 'take');
  };
  
  this.feedbackEnabled = function() {
    return (this.conf.feedback.enabled === '1');
  };
  
  this.pointInsideCanvas = function(x,y) {
    x = this.getRelativeX(x);
    y = this.getRelativeY(y);
    return (x>5 && y>5 && x<this.conf.canvas.width-5 && y<this.conf.canvas.height-5);
  };
  
  this.showInfoPopup = function(text, border_color) {
    if(text) {
      // Show feedback:
      // Create a div, since shapes in raphael need a value for height, width,
      // and we don't know how much space we need at this point.
      
      // Calculate the displaytime for the message based on the length of the text:
      var displaytime = 1800 + (text.length*30);
      
      var $feedback = $('<div id="quiz-ddlines-feedback">'+text+'</div>');
      $feedback.css({'border-color': border_color, 'display': 'none'});
      $(this.getSelector()).append($feedback);
      $feedback.fadeIn();
      setTimeout(function() { $feedback.fadeOut(); }, displaytime);
    }
  };
};

/**
 * The image class
 */
function QuizImage(engine, uri, width, height) {
  
  /*var self = this;*/
  
  this.engine = engine;
  this.image = this.engine.r.image(uri, 0, 0, width, height);
  this.image.toFront();
  
  if(this.engine.isEditMode()) {
    
    // Center image when added:
    if(this.engine.isNew()) {
      this.image.attr({"x": (engine.getCanvasWidth()/2)-(width/2) ,"y": (engine.getCanvasHeight()/2)-(height/2)});
    }
    
    /*
    var bbox = this.image.getBBox();
    this.image.resizer = this.engine.r.rect(bbox.x2-20,bbox.y2-20,20,20);
    this.image.resizer.attr({color: "#00bb27", "fill": "#00bb27", "fill-opacity": 0.9, opacity:0.9, cursor: "se-resize"});
    */
    
    this.image.attr({cursor:'move'});
    /*
    rstart = function () {
      this.ox = this.attr("x");
      this.oy = this.attr("y");
      
      self.image.ow = self.image.attr("width");
      self.image.oh = self.image.attr("height");        
    },
    rmove = function (dx, dy) {
        this.attr({x: this.ox + dx, y: this.oy + dy});
        self.image.attr({width: self.image.ow + dx, height: self.image.oh + dy});
    };
    this.image.resizer.drag(rmove, rstart);*/
    
    // Setup image dragging handling
    function image_drag_move(dx, dy, x, y, event) {
      if(set_drag_move(dx, dy, x, y, event, this.set)) {
        // Move all hotspots accordingly:
        for (var i = QuizElementList.elements.length; i--;) {
          set_drag_move(dx, dy, x, y, event, QuizElementList.elements[i].uiHotspot.set);
        }
      }
    }

    function image_drag_start(x, y, event) {
      set_drag_start(x, y, event, this.set);
      
      // Make all hotspots readu to be moved:
      for (var i = QuizElementList.elements.length; i--;) {
        set_drag_start(x, y, event, QuizElementList.elements[i].uiHotspot.set);
      }
    }
    
    var set = this.engine.r.set();
    set.push(this.image);
    //set.push(this.image.resizer);
    this.image.set = set;
    //this.image.resizer.set = set;
    set.drag(image_drag_move, image_drag_start, set_drag_finished);
  }
  
  this.toJson = function() {    
    return '"image":{"left":'+this.image.attr("x")+',"top":'+this.image.attr("y")+',"width":'+this.image.attr("width")+',"height":'+this.image.attr("height")+'}';
  };
  
  this.setBounds = function(x,y,width,height) {
    this.image.attr({"x":x, "y":y, "width":width, "height":height});
  };
  
  this.getBBox = function() {
    return this.image.getBBox();
  };
  
  this.move = function(deltax, deltay) {
    this.image.attr({"x":this.image.attr("x")+deltax, "y":this.image.attr("y")+deltay});
  };
}

/**
 * The label UI element class
 */
function QuizLabel(parent, color, id, text, x, y) {
  
  var self = this;
  
  this.parent = parent;
  this.color = color;
  this.text = text;
  
  this.setText = function(text) {
    
    self.label.text.hide();
    
    // Set the new text
    self.label.text.attr({text: text});
    
    // Recalculate rectangle size.
    var bbox = self.label.text.getBBox();
    self.label.text.attr({
      x: self.label.attr("x")+bbox.width/2+10,
      y: self.label.attr("y")+10});
    
    // Set new width of parent rectangle:
    var rect_width = bbox.width+20;
    self.label.attr({width: rect_width < QuizUtil.LABEL_MIN_WIDTH ? QuizUtil.LABEL_MIN_WIDTH : rect_width});
    self.label.fg.attr({width: rect_width < QuizUtil.LABEL_MIN_WIDTH ? QuizUtil.LABEL_MIN_WIDTH : rect_width});
    
    // Set size of glow if it exists
    if(QuizUtil.defined(self.glow)) {
      self.glow.attr({width: rect_width+8 < QuizUtil.LABEL_MIN_WIDTH+8 ? QuizUtil.LABEL_MIN_WIDTH+8 : rect_width+8});
    }
    
    self.label.text.show();
  };
  
  this.updateTextPosition = function() {
    this.setText(this.text);
    
    // Update position of foreground object:
    var bbox = self.label.getBBox();
    self.label.fg.attr({x:bbox.x, y:bbox.y, width:bbox.width, height: bbox.height});
    self.label.fg.show();
  };
  
  // Create Raphael objects:
  this.label = this.parent.engine.r.rect(x, y, 100, 20);
  this.label.parent = this;
  
  // Use same id as previous if this is set
  if(QuizUtil.defined(id)) {
    this.label.id = id;
  }
  
  this.label.text = this.parent.engine.r.text(-200,y+10,""); // initially hide the text;
  this.label.fg = this.parent.engine.r.rect(x-5, y-5, 110, 30); // Foreground object
  
  // Set attributes:
  this.label.attr({fill: "#fff", stroke: this.color, "fill-opacity": 1, "stroke-width": 3, cursor: (!this.parent.engine.isResultMode() ? "move" : "default")});
  this.label.text.attr({"font-size": 12, cursor: (!this.parent.engine.isResultMode() ? "move" : "default")});
  this.label.fg.attr({fill: "#fff", "fill-opacity": 0, "stroke-width": 0, "stroke-opacity":0, cursor: (!this.parent.engine.isResultMode() ? "move" : "default")});
  this.label.fg.toFront();
  
  // Create a set so they can be treated as one:
  this.set = this.parent.engine.r.set();
  this.set.parent = parent;
  this.set.push(this.label, this.label.text, this.label.fg);
  
  // Create backreference from elements to the set:
  this.label.set = this.label.text.set = this.label.fg.set = this.set;
  
  // Set text if value set:
  this.setText(text);
  
  // Move it to center of hotspot if resultpage
  // and execution modes without lines:
  if(!this.parent.engine.executionModeLines() && this.parent.engine.isResultMode() && QuizUtil.defined(this.parent.uiHotspot)) {
    // Get hotspot:
    var center = this.parent.uiHotspot.getCenter();
    if (center != null) {
      this.set.forEach(function(element) {
        element.attr({x: center.x-(element.attr('width')/2), y:center.y-(element.attr('height')/2)});
      });
    }
  }
  
  this.toJson = function(){
    return '"label":{"id":'+this.label.id+',"x":'+this.label.attr("x")+',"y":'+this.label.attr("y")+',"text":"'+this.label.text.attr("text")+'"}';
  };
  
  this.setColor = function(color) {
    this.color = color;
    this.label.attr({stroke: this.color});
  };
  
  if(this.parent.engine.isEditMode()) {
    this.set.drag(set_drag_move,set_drag_start,set_drag_finished);
  }
  
  var edit_mode = function (event) {
    // Add an inputbox as overlay:
    // Get dimensions of rect
    
    if(QuizUtil.drag_mode) {
      return false;
    }
    
    if(event !== null) {
      event.stopPropagation();
    }
    
    if(QuizUtil.current_editor != null) {
      QuizUtil.current_editor.editingDone();
    }
    
    var me = QuizUtil.current_editor = this;
    
    var topleft=self.label.attr("x")-2;
    var topright=self.label.attr("y")-2;
    var bbox=self.label.getBBox();
    
    var $editButton = $('<input type="text" id="quiz-ddlines-edit" value="'+self.label.text.attr("text")+'"></input>');
    $editButton.css({
      'position': 'absolute',
      'left': topleft+'px',
      'top': topright+'px',
      'z-index': 99999,
      'border': '2px dashed '+self.color,
      'height': (bbox.height+4)+'px',
      'width': (bbox.width+4)+'px'
    });
    
    
    this.editingDone = function() {
      // Save the text
      self.parent.setText($editButton.val());
      // Remove the input field
      $editButton.remove();
      self.parent.redrawConnection();
      
      QuizUtil.current_editor = null;
    };
    
    // Listen on editing finished:    
    $editButton.keypress(function(event) {
      // 13 is enter
      if(event.which === 13) {
        me.editingDone();
      }
    });
    $editButton.keyup(function(event) {
      // Update toolpane:
      $('#quiz-ddlines-toolpane label > em').html($editButton.val());
    });
    
    $(self.parent.engine.getSelector()).append($editButton);
    setTimeout( function() {
      $editButton.focus();
    }, 100);
    
    return false;
  };
  
  var focus_mode = function () {
    if($('#quiz-ddlines-toolpane').length != 0) {
      $('#quiz-ddlines-toolpane').remove();
    }
    
    if(QuizUtil.current_glow != null) {
      if(QuizUtil.current_glow.set) {
        QuizUtil.current_glow.set.exclude(QuizUtil.current_glow);
      }
      QuizUtil.current_glow.remove();
      QuizUtil.current_glow = null;
    }
    
    QuizUtil.current_glow = self.parent.engine.r.rect(self.label.attr('x')-4, self.label.attr('y')-4, self.label.attr('width')+8, self.label.attr('height')+8, 5);
    QuizUtil.current_glow.attr({"fill-opacity": 0, "stroke": self.color, "stroke-width": 4, "stroke-opacity": 0.3});
    QuizUtil.current_glow.parent_id = self.label.id;
    
    self.glow = QuizUtil.current_glow;
    self.set.push(QuizUtil.current_glow);
    QuizUtil.current_glow.set = self.set;
    
    /*var topleft=self.label.attr("x")-2;
    var topright=self.label.attr("y")-2;
    var bbox=self.label.getBBox();*/
    var selected_text=self.label.text.attr("text");
    
    var $toolPane = $('<div id="quiz-ddlines-toolpane"></div>');
    var $buttonPane = $('<div id="quiz-ddlines-buttonpane"></div>');
    var $feedbackPane = $('<div id="quiz-ddlines-feedback-pane"></div>');
    var $feedbackCorrect = $('<input type="text" class="form-text feedback correct" value="'+self.parent.feedback_correct+'"></input>');
    var $feedbackWrong = $('<input type="text" class="form-text feedback wrong" value="'+self.parent.feedback_wrong+'"></input>');
    var $feedbackLabel = $('<div class="form-item"><label id="settings-for">'+Drupal.t('Settings for')+' <em>'+selected_text+'</em></label></div>');
    var $deleteButton = $('<input id="ddlines-delete-element" type="button" class="form-submit" tabindex="-1" value="'+Drupal.t('delete')+'">');
    var $colorButton = $('<input id="ddlines-change-color" class="form-submit" type="button" value="'+Drupal.t('color')+'">');
    var $closeButton = $('<input id="ddlines-close-panel" class="form-submit" type="button" value="'+Drupal.t('save')+'">');
    
    $toolPane.css({
      'z-index': 10001,
      'border-color': self.color
    });
    
    $(self.parent.engine.getSelector()).append($toolPane);
    $toolPane.append($feedbackPane);
    $toolPane.append($buttonPane);
    
    $feedbackPane.append($feedbackLabel);
    $feedbackPane.append($('<span id="feedback-correct">'+Drupal.t('Feedback when correct')+'</span>'));
    $feedbackPane.append($('<span id="feedback-wrong">'+Drupal.t('Feedback when wrong')+'</span>'));
    $feedbackPane.append($feedbackCorrect);
    $feedbackPane.append($feedbackWrong);
    
    var updateFeedback = function(){
      self.parent.setFeedback($feedbackCorrect.val(), $feedbackWrong.val());
    };      
    $feedbackCorrect.keyup(updateFeedback);
    $feedbackWrong.keyup(updateFeedback);
    
    // Add feedback disabled:
    var $feedbackDisabled = $('<div id="feedback-disabled"><p>'+Drupal.t('Feedback disabled')+'</p></div>');
    $feedbackDisabled.css({'display': self.parent.engine.feedbackEnabled() ? 'none' : 'block'});
    $feedbackPane.append($feedbackDisabled);
    
    $buttonPane.append($colorButton);
    $buttonPane.append($closeButton);
    $buttonPane.append($deleteButton);
    
    // Create container:
    var $colorContainer = $('<div id="colorwheel-container"></div>').css({'width':'150px','height':'150px'});
    $toolPane.append($colorContainer);
    var cw = Raphael.colorwheel($('#colorwheel-container'), 150);
    cw.color(self.color);
    cw.onchange(function(color) {
      $toolPane.css({'border-color': color.hex});
      $colorContainer.css({'border-color': color.hex});
      self.parent.setColor(color.hex);
    });
    
    // Colorbutton clicked
    $colorButton.click(function() {
      
      // If color container is visible, close it
      if ( $colorContainer.is(":visible") ) {
        $colorContainer.hide();
      }
      else {
      
        /*var position = $toolPane.position();
        var pos_left = (position.left + 300) + "px";
        var pos_top = (position.top - 150) + "px";*/
        
        // Set position of container:
        $colorContainer.css({'border-color': self.color}).show();
      }      
    });
        
    $deleteButton.click(function() {      
      $("#quiz-ddlines-toolpane").fadeOut();
      if(QuizUtil.current_editor != null) {
        QuizUtil.current_editor.editingDone();
      }
      self.parent.remove();
    });    
  
    $('#ddlines-close-panel').click(function() {
      // Hide colorwheel:
      $colorContainer.hide();
      
      // Update form for saving
      QuizElementList.updateForm();    
      
      $("#quiz-ddlines-toolpane").fadeOut();
    });
  };
  
  if(this.parent.engine.isEditMode()) {
    this.set.click(edit_mode);
    this.set.mousedown(focus_mode);
  }
  
  this.gotoEditMode = function() {
    focus_mode();
    edit_mode(null);
  };
  
  this.remove = function() {
    this.set.remove();
  };
  
  this.getBBox = function() {
    return this.label.getBBox();
  };
  
  this.move = function(deltax,deltay) {
    this.label.attr({"x": this.label.attr("x") + deltax}); 
    this.label.attr({"y": this.label.attr("y") + deltay});
  };
}

function QuizLabelDrag(parent, label, color) {
  var self = this;
  
  this.initial_x = label.attr('x');
  this.initial_y = label.attr('y');
  
  this.label = label;
  this.parent = parent;
  this.color = color;
  this.ox = this.oy = null;
  
  var drag_start = function(x,y) {
    self.ox = x;
    self.oy = y;
    self.label.set.toFront();
  };
  
  var drag_move = function(dx,dy,x,y) {
    
    /*if(!self.parent.engine.pointInsideCanvas(x,y)) {
      return;
    }*/
    
    self.label.set.forEach(function(elm){
      elm.attr({x: elm.attr("x")+(x - self.ox), y: elm.attr("y")+(y - self.oy)});
    });
    
    self.ox = x;
    self.oy = y;
    
    // Hover on hits:
    x = self.label.attr('x')+(self.label.attr('width')/2);
    y = self.label.attr('y')+(self.label.attr('height')/2);
    var hit_hotspot = false;
    for (var i = QuizElementList.elements.length; i--;) {
      // Check if x,y is within BBox:
      var id = QuizElementList.elements[i].uiHotspot.hotspot.id;
      if(QuizElementList.elements[i].uiHotspot.hotspot.margin.isPointInside(x,y)) {
        
        hit_hotspot = true;
        
        if(QuizUtil.current_glow === null || QuizUtil.current_glow.parent_id != id) {
          if(QuizUtil.current_glow != null) {
            QuizUtil.current_glow.remove();
            QuizUtil.current_glow = null;
          }
          QuizUtil.current_glow = QuizElementList.elements[i].uiHotspot.hotspot.glow({"color": self.color, width: self.label.attr('width'), fill: true, opacity: 1.0});
          QuizUtil.current_glow.parent_id = id;
        }
        
        break;
      }
    }
    
    if(!hit_hotspot && QuizUtil.current_glow != null) {
      QuizUtil.current_glow.remove();
      QuizUtil.current_glow = null;
    }
  };
  
  var drag_finish = function(event) {
    
    if(QuizUtil.current_glow != null) {
      QuizUtil.current_glow.remove();
    }
    
    var x = self.label.attr("x") + (self.label.attr("width")/2);
    var y = self.label.attr("y") + (self.label.attr("height")/2);
    
    // Inside any hotspot at all?
    var targets = self.parent.engine.r.getElementsByPoint(x, y);
    var selected_hotspot=null;
    
    targets.forEach(function(e){
      if(e.isHotspotMargin) {
        selected_hotspot = e.hotspot;
        // Makes callback stop (like break if this was a for loop)
        return false; 
      }
    });
    
    var correct_answer = selected_hotspot === null ? false : (self.parent.uiHotspot.hotspot === selected_hotspot);
    var feedback_enabled = self.parent.engine.feedbackEnabled();
    
    if((!feedback_enabled && selected_hotspot !== null) || (feedback_enabled && correct_answer)) {
      // Glue it to the center of the selected hotspot,
      // and make it smaller:
      self.label.text.hide();
      self.label.fg.hide();
      self.label.animate({
        x: selected_hotspot.attr("cx")-(self.label.attr('width')/2), 
        y: selected_hotspot.attr("cy")-(self.label.attr('height')/2),
        "stroke-opacity": 0.3,
        "fill-opacity": 0.95},
        500, 
        "bounce", function() {
          self.label.parent.updateTextPosition();          
        });        
    }
    
    if(selected_hotspot === null || (feedback_enabled && !correct_answer)) {
      // Animate back to source!      
      // Do the animation of the label:
      self.label.text.hide();
      self.label.fg.hide();
      self.label.animate({
        "stroke-opacity": 1,
        "fill-opacity": 1,
        x: self.initial_x, 
        y: self.initial_y}, 500, "bounce", function() {
          self.label.parent.updateTextPosition();          
        });
      
      if(selected_hotspot != null && feedback_enabled && !correct_answer){
        self.parent.engine.showInfoPopup(self.parent.feedback_wrong, self.color);
      }
      
      Answers.removeAnswer(self.label.id);
    }
    else if(feedback_enabled && correct_answer) {
      self.parent.engine.showInfoPopup(self.parent.feedback_correct, self.color);     
      // Save answer:
      Answers.setAnswer(self.label.id, selected_hotspot.id);
    }
    else if(!feedback_enabled && selected_hotspot !== null) {
      // Save answer:     
      Answers.setAnswer(self.label.id, selected_hotspot.id);
    }
  };
  
  label.set.drag(drag_move, drag_start, drag_finish);
}

/**
 * The pointer class, the UI element dragged while taking
 * a test.
 * 
 */
function QuizPointer(parent, label, color) {
  var self = this;
  
  this.color = color;
  this.parent = parent;
  this.label = label;
  this.radius = parseInt(parent.engine.conf.pointer.radius);
  
  this.connect = function() {
    return this.ie_fix;
  };
  
  this.createVisual = function(x,y) {
    this.pointer = this.parent.engine.r.circle(x,y,this.radius);
    this.pointer.attr({fill: this.color, stroke: this.color, "fill-opacity": 0.9, "stroke-opacity": 1, "stroke-width": 2, cursor: "move"});
    this.border = this.parent.engine.r.circle(x,y,this.radius+2);
    this.border.attr({stroke: "#fff", "stroke-width": 2, "stroke-opacity": 1});
    this.ie_fix = this.parent.engine.r.rect(x-this.radius, y-this.radius, this.radius*2, this.radius*2);    
    this.ie_fix.attr({opacity:0});
    
    this.set = this.parent.engine.r.set();
    this.set.push(this.pointer, this.border);
  };
  
  this.updateVisual = function(cx, cy, updatePointer) {
    updatePointer = QuizUtil.defined(updatePointer) ? updatePointer : false;
    
    if(updatePointer) {
      self.pointer.attr({cx: cx, cy: cy, r:self.radius});
    }
    else {
      self.radius = parseInt(self.pointer.attr("r"));
    }
    
    self.ie_fix.attr({x: cx-self.radius, y:cy-self.radius, width: self.radius*2, height: self.radius*2});
    self.border.attr({cx: cx, cy: cy, r:(self.radius+2)});
    
    self.parent.redrawConnection();
  };
  
  // Start dragging pointer 
  this.pointer_drag_start = function(x,y) {
    if(!self.pointer) {
      self.createVisual(self.parent.engine.getRelativeX(x), self.parent.engine.getRelativeY(y));
      
      if(!self.parent.connection) {
        self.parent.createConnection();
      }
  
      self.pointer.drag(self.pointer_move, self.pointer_drag_start, self.pointer_up);
    }
  };  
  
  // Dragging of pointer
  this.pointer_move = function(dx,dy,x,y) {
    /*if(!self.parent.engine.pointInsideCanvas(x,y)) {
      return;
    }*/
    x = self.parent.engine.getRelativeX(x);
    y = self.parent.engine.getRelativeY(y);
    
    self.updateVisual(x,y,true);
    
    // Check if hotspot is hit, for hovering:
    // Tried using onDragOver, but that did not work. See comment here:
    // http://dashasalo.com/2011/08/15/raphaeljs-2-0-ondragover-limitation/
    var hit_hotspot = false;
    for (var i = QuizElementList.elements.length; i--;) {
      // Check if x,y is within BBox:
      var id = QuizElementList.elements[i].uiHotspot.hotspot.id;
      if(QuizElementList.elements[i].uiHotspot.hotspot.isPointInside(x,y)) {
        
        hit_hotspot = true;
        
        if(QuizUtil.current_glow === null || QuizUtil.current_glow.parent_id !== id) {
          if(QuizUtil.current_glow !== null) {
            QuizUtil.current_glow.remove();
            QuizUtil.current_glow = null;
          }          
          QuizUtil.current_glow = QuizElementList.elements[i].uiHotspot.hotspot.glow({"color": self.color, width: 20, fill: true, opacity: 1.0});
          QuizUtil.current_glow.parent_id = id;
        }
        
        break;
      }
    }
    
    if(!hit_hotspot && QuizUtil.current_glow !== null) {
      QuizUtil.current_glow.remove();
      QuizUtil.current_glow = null;
    }
  };
      
  this.pointer_up = function(event) {
    
    if(QuizUtil.current_glow !== null) {
      QuizUtil.current_glow.remove();
    }
    
    var x = self.pointer.attr("cx");
    var y = self.pointer.attr("cy");
    
    // Inside any hotspot at all?
    var targets = self.parent.engine.r.getElementsByPoint(x, y);
    var selected_hotspot=null;
    
    targets.forEach(function(e){
      if(e !== self.pointer && e.isHotspot) {
        // Hit one
        // Check if correct hotspot hit.
        //correct_answer = (self.parent.uiHotspot.hotspot == e);
        selected_hotspot = e;
        
        // Makes callback stop (like break if this was a for loop)
        return false; 
      }
    });
    
    var correct_answer = selected_hotspot===null ? false : (self.parent.uiHotspot.hotspot == selected_hotspot);
    var feedback_enabled = self.parent.engine.feedbackEnabled();
    
    if((!feedback_enabled && selected_hotspot !== null) || (feedback_enabled && correct_answer)) {
      // Remove connecting line:
      self.parent.hideConnection();
      
      // Glue it to the center of the selected hotspot:
      self.set.animate({cx: selected_hotspot.attr("cx"), cy: selected_hotspot.attr("cy"), r: selected_hotspot.attr("r")}, 500, "bounce", function() {
        self.updateVisual(self.pointer.attr("cx"), self.pointer.attr("cy"), false);        
      });
    }
    
    if(selected_hotspot === null || (feedback_enabled && !correct_answer)) {
      // Animate back to source!      
      // Remove connecting line:
      self.parent.hideConnection();      
      
      // Do the animation of the pointer
      var bbox = self.label.getBBox();
      self.set.animate({cx: self.label.attr("x")+(bbox.width/2), cy: self.label.attr("y")+50, r: self.parent.engine.conf.pointer.radius}, 500, "bounce", function() {
        self.updateVisual(self.pointer.attr("cx"), self.pointer.attr("cy"), false);
      });
      
      if(selected_hotspot !== null && feedback_enabled && !correct_answer){
        self.parent.engine.showInfoPopup(self.parent.feedback_wrong, self.color);
      }
      
      Answers.removeAnswer(self.label.id);
    }
    else if(feedback_enabled && correct_answer) {
      self.parent.engine.showInfoPopup(self.parent.feedback_correct, self.color);     
      // Save answer:
      Answers.setAnswer(self.label.id, selected_hotspot.id);
    }
    else if(!feedback_enabled && selected_hotspot !== null) {
      // Save answer:     
      Answers.setAnswer(self.label.id, selected_hotspot.id);
    }
  };
  
}

/**
 * The hotspot UI element class
 */
function QuizHotspot(parent, color, id, x, y, radius) {
  var self = this;  
  this.parent = parent;
  this.color = color;
  
  this.radius = parseInt(self.parent.engine.conf.hotspot.radius);
  
  this.hotspot = self.parent.engine.r.circle(x, y, this.radius);  
  this.hotspot.attr({fill: "#fff", stroke: "#000", "fill-opacity": 0.4, "stroke-opacity": 1, "stroke-width": 2});
  this.hotspot.isHotspot=true;
  
  this.hotspot.margin = self.parent.engine.r.circle(x, y, this.radius+20);
  this.hotspot.margin.isHotspotMargin = true;
  this.hotspot.margin.hotspot = this.hotspot; 
  this.hotspot.margin.hide();
  
  this.border = self.parent.engine.r.circle(x, y, this.radius+2);
  this.border.attr({stroke: "#fff", "stroke-width": 2, "stroke-opacity": 1});
  
  this.ie_fix = self.parent.engine.r.rect(x-this.radius, y-this.radius, this.radius*2, this.radius*2);
  this.ie_fix.attr({opacity:0});
  this.ie_fix.toFront();
  
  if(self.parent.engine.isEditMode()) {
    this.hotspot.attr({cursor: "move", stroke: this.color});
  }
  
  if(QuizUtil.defined(id)) {
    this.hotspot.id = id;
  }
  
  if(self.parent.engine.isEditMode()) { 
    this.set = self.parent.engine.r.set();
    this.set.parent = parent;
    this.set.push(this.hotspot, this.border, this.ie_fix);
    this.hotspot.set = this.set;
    this.border.set = this.set;
    this.ie_fix.set = this.set;
    
    this.hotspot.set.drag(set_drag_move,set_drag_start,set_drag_finished);
  } 
  
  this.connect = function() {
    return this.ie_fix;
  };
  
  this.toJson = function() {
    return '"hotspot":{"id":'+this.hotspot.id+',"x":'+this.hotspot.attr("cx")+',"y":'+this.hotspot.attr("cy")+'}';
  };
  
  this.remove = function() {    
    this.hotspot.remove();
    this.border.remove();
  };
  
  this.setColor = function(color) {
    this.color = color;
    this.hotspot.attr({stroke: this.color});
  };
  
  this.updateHotspotRadius = function(radius) {
    var previous_radius = this.radius;
    var diff = radius-previous_radius;
    this.radius = radius;
    
    this.hotspot.attr({r: radius});
    this.border.attr({r: radius+2});
    this.ie_fix.attr({x: this.ie_fix.attr('x')-diff, y: this.ie_fix.attr('y')-diff, width: radius*2, height: radius*2});
  };
  
  this.getCenter = function() {
    if(this.hotspot) {
      return {x: this.hotspot.attr('cx'), y:this.hotspot.attr('cy')};
    }
    else {
      return null;
    }
  };
  
  this.getBBox = function() {
    return this.hotspot.getBBox();
  };
  
  this.move = function(deltax,deltay) {
    this.hotspot.attr({"cx": this.hotspot.attr("cx") + deltax}); 
    this.hotspot.attr({"cy": this.hotspot.attr("cy") + deltay});
  };
}


/**
 * The quiz ddlines element.
 * 
 * It contains the metadata needed to draw the label, hotspot, pointer 
 * and connecting lines
 * 
 */
function QuizElement (engine, color, text, label_id, label_x, label_y, hotspot_id, hotspot_x, hotspot_y, feedback_correct, feedback_wrong, correct_answer) {  
  
  var self = this;
  this.engine = engine;
  
  text = QuizUtil.defined(text) ? text : "";
  label_x = QuizUtil.defined(label_x) ? label_x : 5;
  label_y = QuizUtil.defined(label_y) ? label_y : 5;
  hotspot_x = QuizUtil.defined(hotspot_x) ? hotspot_x : 55;
  hotspot_y = QuizUtil.defined(hotspot_y) ? hotspot_y : 100;  
  this.feedback_wrong = QuizUtil.defined(feedback_wrong)  ? feedback_wrong : engine.conf.feedback.wrong;
  this.feedback_correct = QuizUtil.defined(feedback_correct) ? feedback_correct : engine.conf.feedback.correct;
  correct_answer = QuizUtil.defined(correct_answer) ? correct_answer : null;
  
  // Create default hotspot and label
  this.color = color;
  
  if((correct_answer !== null || hotspot_id !== null) && hotspot_x !== null) {
    this.uiHotspot = new QuizHotspot(this, color, hotspot_id, hotspot_x, hotspot_y);
  }
  
  if(correct_answer !== null || label_id !== null) {
    this.uiLabel = new QuizLabel(this, color, label_id, text, label_x, label_y);
  }
  
  if(this.engine.isTakeMode()) {
    if(this.engine.executionModeLines()) {
      this.pointer = new QuizPointer(this, this.uiLabel.label, color);
      this.uiLabel.set.drag(this.pointer.pointer_move, this.pointer.pointer_drag_start, this.pointer.pointer_up);
    }
    else {
      // Make label beeing draggable
      new QuizLabelDrag(this, this.uiLabel.label, color);
    }
  }
  
  this.createConnection = function() {
    if(self.engine.isEditMode() || self.engine.executionModeLines()) {
      this.connection = this.engine.r.connection(this.uiLabel.label, (this.engine.isTakeMode() ? this.pointer.connect() : this.uiHotspot.connect()), this.color, "#FFF|5");
    }
  };
  
  this.hideConnection = function() {
    if(self.engine.isEditMode() || self.engine.executionModeLines()) {
      this.connection.bg.hide();
      this.connection.line.hide();
    }
  };
  
  if(this.engine.isEditMode() || (this.engine.isResultMode() && hotspot_id !== null && label_id !== null)) {
    this.createConnection();
  }
  
  if(this.engine.isResultMode() && (correct_answer != null || (label_id === null || hotspot_id === null))) {
    
    //var settings = {color: (correct_answer ? '#00bb27' : '#fe2020'), width: 20, fill: true, opacity: 1};
    
    var imagepath = this.engine.conf.quiz_imagepath + (correct_answer ? "icon_ok" : "icon_wrong") + ".gif";
    
    // Set glow color:
    if(QuizUtil.defined(this.uiLabel)) {
      // Create Image:
      var bbox = this.uiLabel.getBBox();
      this.engine.r.image(imagepath, bbox.x-8, bbox.y-8, 20, 20);
      //this.engine.r.image.attr({'width': 16, 'height': 16});
      
      //this.uiLabel.label.glow(settings);
    }
    /*if(QuizUtil.defined(this.uiHotspot) && this.engine.executionModeLines()) {
      //this.uiHotspot.hotspot.glow(settings);
      var bbox = this.uiHotspot.getBBox();
      this.engine.r.image(imagepath, bbox.x, bbox.y, 16, 16);
    }*/
  }
  
  this.redrawConnection = function() {
    if(this.connection) {
      this.connection.bg.show();
      this.connection.line.show();
      this.engine.r.connection(this.connection);
    }
    this.engine.r.safari();
  };
  
  this.gotoEditMode = function() {
    this.uiLabel.gotoEditMode();
  };
      
  this.toJson = function() {
    // Generates JSON
    return '{"feedback_wrong":"'+this.feedback_wrong+'",'+'"feedback_correct":"'+this.feedback_correct+'","color":"'+this.color+'",'+this.uiLabel.toJson()+','+this.uiHotspot.toJson()+'}';
  };
  
  this.setFeedback = function(correct, wrong) {
    this.feedback_correct = correct;
    this.feedback_wrong = wrong;
    
    // Update list:
    QuizElementList.updateForm();
  };
  
  this.setText = function(text) {
    // Set the new text
    this.uiLabel.setText(text);
    
    // Update form element, so it is ready to be saved
    QuizElementList.updateForm();
  };
  
  this.setColor = function(color) {
    this.color = color;
    
    this.uiLabel.setColor(this.color);
    this.uiHotspot.setColor(this.color);
    
    // Set glow if it exists:
    if(QuizUtil.current_glow != null) {
      QuizUtil.current_glow.attr({stroke: this.color});
    }
    
    // Set connection color:
    this.connection.line.attr({stroke: this.color});
  };
  
  this.remove = function() {    
    // Remove from list:
    QuizElementList.remove(this);
    
    // Remove from canvas:
    this.uiHotspot.remove();
    this.uiLabel.remove();
    this.connection.bg.remove();
    this.connection.line.remove();
  };
  
  this.getBBox = function() {
    var bbox = this.uiLabel.getBBox();
    
    if(QuizUtil.defined(this.uiHotspot)) {
      var bboxHotSpot = this.uiHotspot.getBBox();
      bbox = QuizUtil.bboxUnion(bbox, bboxHotSpot);
    }
    
    return bbox;
  };
  
  this.move = function(deltax,deltay) {
    this.uiLabel.move(deltax,deltay);
    this.uiHotspot.move(deltax,deltay);
  };
}

QuizElement.fromJson = function(json, engine) {
  return new QuizElement(
       engine, 
       json.color, 
       QuizUtil.defined(json.label) ? json.label.text : null, 
       QuizUtil.defined(json.label) ? json.label.id : null, 
       QuizUtil.defined(json.label) ? json.label.x : null, 
       QuizUtil.defined(json.label) ? json.label.y : null, 
       QuizUtil.defined(json.hotspot) ? json.hotspot.id : null, 
       QuizUtil.defined(json.hotspot) ? json.hotspot.x : null, 
       QuizUtil.defined(json.hotspot) ? json.hotspot.y : null, 
       json.feedback_correct, 
       json.feedback_wrong, 
       QuizUtil.defined(json.correct) ? json.correct : null);
};
/*
var Glow = {
    instance: null,
    glow: function(elem, color) {
      this.remove();
      
      var settings = {};
      
      if(elem.type='circle') {
        settings = {}
      }
      else {
        
      }
      
      this.instance = elem.glow({"color": color, width: 20, fill: true, opacity: 1.0});
      
      Engine.r.rect(self.label.attr('x')-4, self.label.attr('y')-4, self.label.attr('width')+8, self.label.attr('height')+8, 5);
      
      
    },
    remove: function() {
      this.instance.remove();
      this.instance = null;
    },
    isGlowing(): function() {
      return (set != null);
    }
};*/





}(jQuery));