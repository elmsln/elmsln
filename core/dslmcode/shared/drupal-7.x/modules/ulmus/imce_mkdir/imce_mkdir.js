
(function($) {
//add hook:load. process mkdir form 
imce.hooks.load.push(function () {
  if (!(imce.mkdirForm = imce.el('imce-mkdir-form'))) return;
  var form = $(imce.mkdirForm);
  //clean up fieldsets
  form.find('fieldset').each(function() {
    this.removeChild(this.firstChild);
    $(this).after(this.childNodes);
  }).remove();
  imce.mkdirOps = {};
  form.find('input:submit').each(function(i) {
    var dop = this.id.substr(5);
    $(imce.mkdirOps[dop] = this).click(function() {imce.dopSubmit(dop); return false;});
  });
  imce.opAdd({name: 'mngdir', title: Drupal.t('Directory'), content: form});
  imce.mkdirRefreshOps();
  //add hook:navigate. set dirops visibility
  imce.hooks.navigate.push(function (data, olddir, cached) {
    imce.mkdirRefreshOps();
  });
  // add subdir selector
  imce.mkdirSubSelector();
});

//change dirops states.
imce.mkdirRefreshOps = function () {
  var perm, func = 'opDisable';
  for (var op in imce.mkdirOps) {
    if (perm = imce.conf.perm[op]) func = 'opEnable';
    $(imce.mkdirOps[op])[perm ? 'show' : 'hide']();
  }
  imce[func]('mngdir');
};

//successful mkdir
imce.mkdirSuccess = function (response) {
  if (response.data) {
    if (response.data.diradded) imce.dirSubdirs(imce.conf.dir, response.data.diradded);
    if (response.data.dirremoved) imce.rmdirSubdirs(imce.conf.dir, response.data.dirremoved);
    imce.mkdirSSBuild && imce.mkdirSSBuild();
  }
  if (response.messages) imce.resMsgs(response.messages);
};

//validate default dops(mkdir, rmdir)
imce.dopValidate = function(dop) {
  var dirname = imce.el('edit-dirname').value, dir = imce.conf.dir, branch = imce.tree[dir], newdir = (dir == '.' ? '' : dir +'/') + dirname;
  switch (dop) {
    case 'mkdir':
      if (imce.conf.mkdirnum && branch.ul && branch.ul.childNodes.length >= imce.conf.mkdirnum) {
        return imce.setMessage(Drupal.t('You are not alllowed to create more than %num directories.', {'%num': imce.conf.mkdirnum}), 'error');
      }
      if (dirname.search(/^[A-Za-z0-9_\-]+$/) == -1) {
        return imce.setMessage(Drupal.t('%dirname is not a valid directory name. It should contain only alphanumeric characters, hyphen and underscore.', {'%dirname': dirname}), 'error');
      }
      if (imce.tree[newdir]) {
        return imce.setMessage(Drupal.t('Subdirectory %dir already exists.', {'%dir': dirname}), 'error');
      }
      return true;
    case 'rmdir':
      if (!imce.tree[newdir]) {
        return imce.setMessage(Drupal.t('Subdirectory %dir does not exist.', {'%dir': dirname}), 'error');
      }
      return confirm(Drupal.t('Are you sure want to delete this subdirectory with all directories and files in it?'));
  }

  var func = dop +'DopValidate';
  if (imce[func]) return imce[func](dop);
  return true;
};

//submit directory operations
imce.dopSubmit = function(dop) {
  if (!imce.dopValidate(dop)) return false;
  var func = dop +'DopSubmit';
  if (imce[func]) return imce[func](dop);
  imce.fopLoading(dop, true);
  $.ajax(imce.dopSettings(dop));
};

//ajax settings for directory operations
imce.dopSettings = function (dop) {
  return {url: imce.ajaxURL(dop), type: 'POST', dataType: 'json', success: imce.mkdirSuccess, complete: function (response) {imce.fopLoading(dop, false); imce.mkdirForm.reset();}, data: $(imce.mkdirForm).serialize()};
};

//remove subdirectories
imce.rmdirSubdirs = function(dir, subdirs) {
  var branch = imce.tree[dir];
  if (branch.ul && subdirs && subdirs.length) {
    var prefix = dir == '.' ? '' : dir +'/';
    for (var i in subdirs) {
      var subdir = prefix + subdirs[i];
      if (imce.tree[subdir]) {
        $(imce.tree[subdir].li).remove();
        delete imce.tree[subdir];
        if (imce.cache[subdir]) {
          $(imce.cache[subdir].files).remove();
          delete imce.cache[subdir];
        }
      }
    }
    if (!$('li', branch.ul).size()) {
      $(branch.ul).remove();
      $(branch.li).removeClass('expanded').addClass('leaf');
      delete branch.ul;
    }
  }
};

// visual sub directory selector
imce.mkdirSubSelector = function () {
  var ie7 = $('html').is('.ie-7');
  var $inp = $(imce.el('edit-dirname'));
  // create selector
  var $subsel = $(imce.newEl('div')).attr({id: 'subdir-selector'}).css('display', 'none').appendTo(document.body);
  // create selector button
  var $button = $(imce.newEl('a')).attr({id: 'subdir-selector-button', href: '#'}).click(function() {
    var offset = $inp.offset();
    offset.top += $inp.outerHeight();
    $subsel.css(offset).slideDown('normal', itemfocus);
    $(document).mouseup(hide);
    ie7 && $subsel.css('width', 'auto') && $subsel.width($subsel[0].offsetWidth);
    return false;
  }).insertAfter($inp[0]);
  // focus on first subdir item
  var itemfocus = function(){$subsel.children().eq(0).focus()};
  // hide selector
  var hide = function(e){
    if (e.target != $subsel[0]) {
      $subsel.hide();
      $(document).unbind('mouseup', hide);
    }
  };
  // adjust newdir input
  var newdir = imce.el('edit-newdirname');
  newdir && $(newdir).css('marginRight', parseFloat($(newdir).css('marginRight')) + parseFloat($button.css('width')));
  // subdir click
  var subclick = function() {
    $inp.val(this.title.substr(this.title.lastIndexOf('/') + 1)).focus();
    $subsel.hide();
    return false;
  };
  // subdir process
  var subproc = function(i, a) {
    $(imce.newEl('a')).attr({href: '#', title: a.title}).html(a.innerHTML).click(subclick).appendTo($subsel[0]);
  };
  // navigation hook
  var navhook = imce.mkdirSSBuild = function() {
    var branch = imce.tree[imce.conf.dir];
    $subsel.empty();
    if (branch.ul && branch.ul.firstChild) {
      $(branch.ul).children('li').children('a').each(subproc);
      $button.css('visibility', 'visible');
    }
    else {
      $button.css('visibility', 'hidden');
    }
  };
  imce.hooks.navigate.push(navhook);
  navhook();
};

})(jQuery);