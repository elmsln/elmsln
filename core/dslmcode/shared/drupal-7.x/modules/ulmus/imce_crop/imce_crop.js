
(function($) {
//implementation of imce.hookOpValidate
imce.cropOpValidate = function() {
  if (!imce.validateImage()) return false;
  var x = imce.el('edit-crop-x').value * 1, y = imce.el('edit-crop-y').value * 1;
  var w = imce.el('edit-crop-width').value * 1, h = imce.el('edit-crop-height').value * 1;
  for (var fid in imce.selected) {
    var row = imce.selected[fid], W = row.cells[2].innerHTML * 1, H = row.cells[3].innerHTML * 1;
    if (x < 0 || y < 0 || w < 1 || h < 1 || W < (x+w) || H < (y+h)) {
      return imce.setMessage(Drupal.t('Crop must be inside the image boundaries.'), 'error');
    }
  }
  return true;
};

//implementation of imce.hookOpSubmit
imce.cropOpSubmit = function(fop) {
  if (imce.fopValidate(fop)) {
    imce.fopLoading(fop, true);
    $.ajax($.extend(imce.fopSettings(fop), {success: imce.cropResponse}));
  }
};

//add hook.load
imce.hooks.load.push(function() {

  //set cropper layer
  imce.cropper = $('<div id="imce-cropper"></div>').mousedown(function(e) {
    var D = $(this), X = e.pageX, Y = e.pageY, oX = parseInt(D.css('left')), oY = parseInt(D.css('top'));
    var elX = imce.el('edit-crop-x'), elY = imce.el('edit-crop-y');
    $(document).mousemove(doDrag).mouseup(endDrag);
    function doDrag(e) {
      var fX = oX + e.pageX - X, fY = oY + e.pageY - Y;
      D.css('left', fX +'px');
      D.css('top', fY +'px');
      elX.value = fX + imce.cropperXextra;
      elY.value = fY + imce.cropperYextra;
      return false;
    }
    function endDrag(e) {
      $(document).unbind('mousemove', doDrag).unbind('mouseup', endDrag);
    }
    return false;
  });
  
  //cropper borders are not included in crop position and size
  imce.cropper.appendTo(document.body);//required to get the correct size
  imce.cropperXextra = parseInt(imce.cropper.css('borderLeftWidth')) || 0;
  imce.cropperYextra = parseInt(imce.cropper.css('borderTopWidth')) || 0;

  //update cropper dimension&position on input value change.
  $('#op-content-crop input:text').keyup(function(e) {
    var opt = ['width', this.value];
    switch (this.id.substr(10)) {
      case 'x': opt = ['left', opt[1] - imce.cropperXextra]; break;
      case 'y': opt = ['top', opt[1] - imce.cropperXextra]; break;
      case 'height': opt[0] = 'height'; break;
    }
    imce.cropper.css(opt[0], opt[1] +'px');
  });

  //alter preview function
  imce.cropPreview = imce.setPreview;
  imce.setPreview = function(fid) {
    imce.cropPreview(fid);
    imce.conf.perm.crop && imce.cropSettle(imce.vars.op == 'crop');
  };
  
  //set click function for crop tab to toggle crop UI
  imce.ops['crop'].func = imce.cropSettle;
  
  //IE fix. position:relative & scroll:auto
  $.browser.msie && parseFloat($.browser.version) < 8 && $('#preview-wrapper').css('position', 'relative');
});

//make previewed images croppable
imce.cropSettle = function(state) {
  var P = $(imce.el('file-preview')).removeClass('crop-preview');
  var I, A = P.find('a').unbind('mousedown', imce.cropDo), oA = A.get(0);
  if (oA && oA.onclick == imce.cropFalseClick) oA.onclick = imce.vars.cropclick;
  if (state && (I = A.find('img')).size()) {
    imce.vars.cropclick = oA.onclick;
    oA.onclick = imce.cropFalseClick;
    P.addClass('crop-preview');
    A.append(imce.cropper).width(I.width()).height(I.height()).bind('mousedown', imce.cropDo);
  }
};

//click replacer. prevents page sliding.
imce.cropFalseClick = function() {return false;};

//do crop
imce.cropDo = function(e) {
  var X = e.pageX, Y = e.pageY, IO = $(this.firstChild).offset();
  var elX = imce.el('edit-crop-x'), elY = imce.el('edit-crop-y');
  var elW = imce.el('edit-crop-width'), elH = imce.el('edit-crop-height');
  var iX = X - IO.left, iY = Y - IO.top;
  var D = imce.cropper.css({left: iX - imce.cropperXextra +'px', top: iY - imce.cropperYextra +'px', width: '1px', height: '1px'});
  elW.value = 1, elH.value = 1, elX.value = iX, elY.value = iY;
  $(document).mousemove(doDrag).mouseup(endDrag);
  function doDrag(e) {
    var nX = e.pageX, nY = e.pageY, fX = nX - IO.left, fY = nY - IO.top, W = (nX - X)||1, H = (nY - Y)||1;
    if (W < 0) D.css('left', fX +'px');
    if (H < 0) D.css('top', fY +'px');
    elX.value = (W < 0 ? fX : iX) + imce.cropperXextra;
    elY.value = (H < 0 ? fY : iY) + imce.cropperYextra;
    D.width(elW.value = Math.abs(W));
    D.height(elH.value = Math.abs(H));
    return false;
  }
  function endDrag(e) {
    $(document).unbind('mousemove', doDrag).unbind('mouseup', endDrag);
  }
  return false;
};

//fix browser cache showing the non-cropped image when filename is not changed.
imce.cropFids = {};

imce.cropGetURL = imce.getURL;
imce.getURL = function (fid) {
  var url = imce.cropGetURL(fid);
  return imce.cropFids[fid] ? (url +'?'+ imce.cropFids[fid]) : url;//add suffix to prevent caching.
};

imce.cropFileGet = imce.fileGet;
imce.fileGet = function (fid) {
  var file = imce.cropFileGet(fid);
  if (imce.cropFids[fid] && file) file.url = file.url.replace(/\?\d+$/, '');
  return file;
};

//custom response. keep track of overwritten files.
imce.cropResponse = function(response) {
  if (!imce.el('edit-crop-copy').checked && response.data && response.data.added) {
    var added = response.data.added;
    for (var i in added) {
      imce.cropFids[added[i].name] = (imce.cropFids[added[i].name]||0) + 1;
    }
  }
  imce.processResponse(response);
  imce.cropper.removeAttr('style');
};

})(jQuery);