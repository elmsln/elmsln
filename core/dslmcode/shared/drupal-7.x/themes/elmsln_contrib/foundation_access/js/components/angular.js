module.exports = function() {
  angular
    .module('Fa',['ngMaterial', 'ngMessages'])
    .controller('FaHeaderOptionsCtrl', function DemoCtrl($mdDialog) {
      var originatorEv;
      this.openMenu = function($mdOpenMenu, ev) {
        originatorEv = ev;
        $mdOpenMenu(ev);
      };
    });
};