(function ($) {

Drupal.NodejsBuddylist = Drupal.NodejsBuddyList || {'chats': {}};

Drupal.Nodejs.presenceCallbacks.buddyList = {
  callback: function (message) {
    if (message.presenceNotification.event == 'offline') {
      $('#nodejs-buddylist-uid-' + message.presenceNotification.uid)
        .removeClass('nodejs-buddylist-online')
        .addClass('nodejs-buddylist-offline');
      $('#nodejs-chatbar-uid-' + message.presenceNotification.uid)
        .removeClass('nodejs-buddylist-online')
        .addClass('nodejs-buddylist-offline');
      $('#nodejs-chatbar-uid-' + message.presenceNotification.uid).children('.chat-link-wrapper').first()
        .removeClass('chat-link-wrapper-online')
        .addClass('chat-link-wrapper-offline');
    }
    else {
      $('#nodejs-buddylist-uid-' + message.presenceNotification.uid)
        .addClass('nodejs-buddylist-online')
        .removeClass('nodejs-buddylist-offline');
      $('#nodejs-chatbar-uid-' + message.presenceNotification.uid)
        .addClass('nodejs-buddylist-online')
        .removeClass('nodejs-buddylist-offline');
      $('#nodejs-chatbar-uid-' + message.presenceNotification.uid).children('.chat-link-wrapper').first()
        .addClass('chat-link-wrapper-online')
        .removeClass('chat-link-wrapper-offline');
    }
  }
};

Drupal.Nodejs.callbacks.nodejsBuddyListStartChat = {
  callback: function (message) {
    if ($('#nodejs-buddylist-chat-' + message.data.chatId).length == 0) {
      Drupal.NodejsBuddylist.createChat(message);
    }
  }
};

Drupal.Nodejs.callbacks.nodejsBuddyAddMessage = {
  callback: function (message) {
    if ($('#nodejs-buddylist-chat-' + message.data.chatId).length == 0) {
      Drupal.NodejsBuddylist.createChat(message);
    }
    Drupal.NodejsBuddylist.updateChat(message);
  }
};

Drupal.NodejsBuddylist.createChat = function (message) {
  Drupal.NodejsBuddylist.chats[message.data.chatId] = {buddyUid: message.data.buddyUid};

  var html = '<div id="nodejs-buddylist-chat-' + message.data.chatId + '" class="section-container">';
  html += '<a class="tab-button">' + message.data.buddyUsername + '</a>'; 
  html += '<div class="chatbar-pane chatbar-chat"><h2>Chat with ' + message.data.buddyUsername + '</h2>';
  html += '<div id="nodejs-buddylist-message-board-' + message.data.chatId + '" class="chatbar-message-board"></div>';
  html += '<div class="chatbar-message-box"><input id="nodejs-buddylist-message-box-' + message.data.chatId + '" type="text" name="' + message.data.chatId + '" /></div>';
  html += '</div></div>';
  $('#chatbar').append(html);

  $('#nodejs-buddylist-message-box-' + message.data.chatId).keyup(function(e) {

    var messageText = $(this).val().replace(/^\s+|\s+$/g, '');
    var matches = this.id.match(/nodejs-buddylist-message-box-(\d+)/);

    if (messageText && e.keyCode == 13 && !e.shiftKey && !e.ctrlKey) {
      Drupal.NodejsBuddylist.postMessage(messageText, matches[1]);
      $(this).val('').focus();
    }
    else {
      return true;
    }
  });

  Drupal.NodejsBuddylist.popupChat(message.data.chatId);
  if (message.data.creatorUid > 0) {
    $('#nodejs-buddylist-message-box-' + message.data.chatId).focus();
  }
};

Drupal.NodejsBuddylist.updateChat = function (message) {
  Drupal.NodejsBuddylist.popupChat(message.data.chatId);
  $(message.data.html).hide().appendTo('#nodejs-buddylist-message-board-' + message.data.chatId).fadeIn(200);
  $('#nodejs-buddylist-message-board-' + message.data.chatId).animate({ scrollTop: $('#nodejs-buddylist-message-board-' + message.data.chatId).attr("scrollHeight") }, 200);
};

Drupal.NodejsBuddylist.chatWithBuddyExists = function (buddyUid) {
  for (var i in Drupal.NodejsBuddylist.chats) {
    if (Drupal.NodejsBuddylist.chats[i].buddyUid == buddyUid) {
      return true;
    }
  }
  return false;
};

Drupal.NodejsBuddylist.getChatIdFromBuddyId = function (buddyUid) {
  for (var i in Drupal.NodejsBuddylist.chats) {
    if (Drupal.NodejsBuddylist.chats[i].buddyUid == buddyUid) {
      return i;
    }
  }
  return false;
};

Drupal.NodejsBuddylist.popupChat = function (chatId) {
  var container = $('#nodejs-buddylist-chat-' + chatId);
  if (container.children('.chatbar-pane').css('display') == 'none') {
    container.children('.tab-button').first().click();
  }
};

/**
 * Add behaviours to buddylist elements.
 */
Drupal.behaviors.buddyList = {
  attach: function (context, settings) {
    $('body').append(Drupal.settings.chatbar_settings);
    $('#chatbar .tab-button').live('click', function () {
      Drupal.NodejsBuddylist.clickChat(this);
    });
    $('.nodejs-buddylist-start-chat-link').click(function (e) {
      e.preventDefault();
      e.stopPropagation();
      var matches = this.href.match(/start-chat-(\d+)/);
      if (Drupal.NodejsBuddylist.chatWithBuddyExists(matches[1])) {
        var chatId = Drupal.NodejsBuddylist.getChatIdFromBuddyId(matches[1]);
        Drupal.NodejsBuddylist.popupChat(chatId);
        $('#nodejs-buddylist-message-box-' + chatId).focus();
      }
      else {
        $.ajax({
          type: 'POST',
          url: Drupal.settings.basePath + 'nodejs-buddylist/start-chat',
          dataType: 'json',
          success: function () {},
          data: {uid: matches[1]}
        });
      }
    });
  }
};

Drupal.NodejsBuddylist.postMessage = function(message, chatId) {
  $.ajax({
    type: 'POST',
    url: Drupal.settings.basePath + 'nodejs-buddylist/post-message/' + chatId,
    dataType: 'json',
    success: function () {},
    data: {
      message: message,
      anonName: '',
      formId: 'nodejs_buddylist_chat_' + chatId
    }
  })
}

Drupal.NodejsBuddylist.clickChat = function (button) {
  var sibling_pane = $(button).siblings('.chatbar-pane');
  var container = $(button).parent();

  if (container.width() > sibling_pane.width()) {
    sibling_pane.width(container.width());
  }
  else {
    container.width(sibling_pane.width());
  }
  sibling_pane.width(container.width());

  // reposition all the chats
  $('#chatbar').children().each(function(index, chatContainer) {
    var chatbarPane = $(chatContainer).children('.chatbar-pane');
    chatbarPane.offset({'left' : $(chatContainer).offset().left});
  });

  sibling_pane.slideToggle(100, function() {
    if ($(this).css('display') == 'none') {
      container.width('auto');

      // reposition all the chats... again... really? Come on...
      $('#chatbar').children().each(function(index, chatContainer) {
        var chatbarPane = $(chatContainer).children('.chatbar-pane');
        chatbarPane.offset({'left' : $(chatContainer).offset().left});
      });

    }
  });
};

})(jQuery);

// vi:ai:expandtab:sw=2 ts=2

