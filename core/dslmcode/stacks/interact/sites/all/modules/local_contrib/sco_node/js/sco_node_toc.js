// format the toc as a simple tree view
jQuery(document).ready(function($){
    $("#sco-node-toc li").each(function(index) {
        // only update parent li elements
        if ($(this).find('li').length > 0 ) {
            $(this).removeClass('sco-node-toc-item');
            $(this).addClass('sco-node-toc-expanded');
            // remove list marker from child elements
            $(this).find('li').addClass('sco-node-toc-item');
        }
    });
    $('#sco-node-toc li').each(function(index) {
        // only handle for parent li elements
        if ($(this).find('li').length > 0) {
            $(this).click(function(event){
            if (this == event.target) {
                    // sub-tree is collapsed
                    if ($(this).is('.sco-node-toc-collapsed')) {
                        // show children and update marker
                        $(this).find('li').show();
                        $(this).removeClass('sco-node-toc-collapsed');
                        $(this).addClass('sco-node-toc-expanded');
                    }
                    // sub-tree is expanded
                    else {
                        // only hide children li
                        $(this).find('li').hide();
                        // update marker
                        $(this).removeClass('sco-node-toc-expanded');
                        $(this).addClass('sco-node-toc-collapsed');
                    }
                }
            });
        }
    });
}); 

function sco_node_toc_set_active(id) {
    
  jQuery('#sco-node-toc').find('.sco-node-toc-active').removeClass('sco-node-toc-active');
  var linkid = '#sco-node-toc-link-' + id;
  jQuery('#sco-node-toc').find(linkid).addClass('sco-node-toc-active');
}

