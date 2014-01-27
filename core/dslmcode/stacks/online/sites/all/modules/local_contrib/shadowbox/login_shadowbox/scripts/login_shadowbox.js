(function($) {
	Drupal.behaviors.shadowboxLogin = {

		attach:function() {

			Shadowbox.ctrlPressed = false;
			var settings = Drupal.settings.shadowboxLogin;

			Shadowbox.showLogin = function() {
				Shadowbox.open([{
					content: settings.login_content,
					player: 'iframe',
					gallery: 'shadowbox_login',
					width: settings.login_width,
					height: settings.login_height,
					options: {
						modal: settings.modal,
						enableKeys: false,
						displayCounter: false,
						displayNav: false,
						onOpen: function() {
							$("#sb-wrapper-inner").addClass("shadowbox-login");
						},
						onClose: function() {
							$("#sb-wrapper-inner").removeClass("shadowbox-login");
						},
						onFinish: function(gallery) {
							$('#sb-player').load(function() {
								$('#sb-player').contents().find("a[href*='" + settings.register_path + "']").click(function(event) {
									parent.Shadowbox.change(1);
									return false;
								});
								$('#sb-player').contents().find("a[href*='" + settings.password_path + "']").click(function(event) {
									parent.Shadowbox.change(2);
									return false;
								});
								$('#sb-player').contents().find('#shadowbox_login #edit-name').focus();
								if (settings.modal) {
									$('#sb-player').contents().find(".shadowbox_login_close_button").click(function() {
										parent.Shadowbox.close();
									});
								} else {
									$('#sb-player').contents().find(".shadowbox_login_close_button").hide();
								}
							});
						}

					}

				}, {
					content: settings.register_content,
					player: 'iframe',
					gallery: 'shadowbox_login',
					width: settings.register_width,
					height: settings.register_height,
					options: {
						modal: settings.modal,
						enableKeys: false,
						displayCounter: false,
						displayNav: false,
						onFinish: function() {
							$('#sb-player').load(function() {
								$('#sb-player').contents().find("#shadowbox_register .username").focus();
								if (settings.modal) {
									$('#sb-player').contents().find(".shadowbox_login_close_button").click(function() {
										parent.Shadowbox.close();
									});
								} else {
									$('#sb-player').contents().find(".shadowbox_login_close_button").hide();
								}
							});
						}
					}

				}, {
					content: settings.password_content,
					player: 'iframe',
					gallery: 'shadowbox_login',
					width: settings.password_width,
					height: settings.password_height,
					options: {
						modal: settings.modal,
						enableKeys: false,
						displayCounter: false,
						displayNav: false,
						onOpen: function() {
							$("#sb-wrapper-inner").addClass("shadowbox-login");
						},
						onClose: function() {
							$("#sb-wrapper-inner").removeClass("shadowbox-login");
						},
						onFinish: function() {
							$('#sb-player').load(function() {
								$('#sb-player').contents().find("#shadowbox_password #edit-name").focus();
								if (settings.modal) {
									$('#sb-player').contents().find(".shadowbox_login_close_button").click(function() {
										parent.Shadowbox.close();
									});
								} else {
									$('#sb-player').contents().find(".shadowbox_login_close_button").hide();
								}
							});
						}
					}
				}]);
			};

			if(!$.browser.msie || $.browser.version > 6 || window.XMLHttpRequest) {
				$("a[href*='" + settings.login_path + "']").each(function() {
					$(this).click(function() {
						Shadowbox.showLogin();
						return false;
					});
				});
				$("a[href*='" + settings.register_path + "']").each(function() {
					$(this).click(function() {
						Shadowbox.open({
							content: settings.register_content,
							player: 'iframe',
							width: settings.register_width,
							height: settings.register_height,
							options: {
								modal: settings.modal,
								enableKeys: false,
								displayCounter: false,
								displayNav: false,
								onOpen: function() {
									$("#sb-wrapper-inner").addClass("shadowbox-login");
								},
								onClose: function() {
									$("#sb-wrapper-inner").removeClass("shadowbox-login");
								},
								onFinish: function() {
									$('#sb-player').load(function() {
										$('#sb-player').contents().find("#shadowbox_register .username").focus();
										if (settings.modal) {
											$('#sb-player').contents().find(".shadowbox_login_close_button").click(function() {
												parent.Shadowbox.close();
											});
										} else {
											$('#sb-player').contents().find(".shadowbox_login_close_button").hide();
										}
									});
								}
							}
						});
						return false;
					});
				});
				$("a[href*='" + settings.password_path + "']").each(function() {
					$(this).click(function() {
						Shadowbox.open({
							content: settings.password_content,
							player: 'iframe',
							width: settings.password_width,
							height: settings.password_height,
							options: {
								modal: settings.modal,
								enableKeys: false,
								displayCounter: false,
								displayNav: false,
								onOpen: function() {
									$("#sb-wrapper-inner").addClass("shadowbox-login");
								},
								onClose: function() {
									$("#sb-wrapper-inner").removeClass("shadowbox-login");
								},
								onFinish: function() {
									$('#sb-player').load(function() {
										$('#sb-player').contents().find("#shadowbox_password #edit-name").focus();
										if (settings.modal) {
											$('#sb-player').contents().find(".shadowbox_login_close_button").click(function() {
												parent.Shadowbox.close();
											});
										} else {
											$('#sb-player').contents().find(".shadowbox_login_close_button").hide();
										}
									});
								}
							}
						});
						return false;
					});
				});
				$(document).keyup(function(e) {
					if(e.keyCode === 17) {
						Shadowbox.ctrlPressed = false;
					}
				});
				$(document).keydown(function(e) {
					if(e.keyCode === 17) {
						Shadowbox.ctrlPressed = true;
					}
					if(Shadowbox.ctrlPressed === true && e.keyCode === 190) {
						Shadowbox.ctrlPressed = false;
						if(Shadowbox.isOpen()) {
							Shadowbox.close();
						} else {
							Shadowbox.showLogin();
						}
					}
				});
			}
		}
	};
}(jQuery));
