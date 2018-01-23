/* global PDFJS, URL */

'use strict';

(function(window, undefined) {
  var Reader = function(el) {
    this.element = el;
    this.reader = Polymer.dom(el.root).querySelector('.pdf-viewer');
    this.viewportOut = this.reader.querySelector('.pdf-viewport-out');
    this.element = this.reader.querySelector('.pdf-element');
    this.container = this.reader.querySelector('.sidebar');
    this.toolbar = this.reader.querySelector('.pdf-toolbar');
    this.card = Polymer.dom(el.root).querySelector('.style-scope');
    this.toolbarHeight = 0;
    this.title = this.toolbar.querySelector('.title');
    this.enableTextSelection = el.enableTextSelection;
    this.fitWidth = el.fitWidth;
    this.HEIGHT = el.getAttribute('height');
    this.WIDTH = el.getAttribute('width');

    this.viewport = this.reader.querySelector('.pdf-viewport');

    if (this.enableTextSelection){
      this.textLayerDiv = this.reader.querySelector(".textLayer");
      this.textLayerDivStyle = this.textLayerDiv.style;
    }

    this.spinner = this.reader.querySelector(".spinner");
    this.totalPages = this.reader.querySelector('#totalPages');
    this.viewportStyle = this.viewport.style;
    this.viewportOutStyle = this.viewportOut.style;

    this.ctx = this.viewport.getContext('2d');

    this.SRC = el.src;

    // this.loadPDF();
    // this.renderPages();
    this.pageRendering = false;
    this.pageNumPending = null;

  };

  Reader.prototype.setSize = function(attrName, newVal) {
    if(!this.WIDTH){
      this.WIDTH = this.viewportOut.offsetWidth;
    }
    //this.width = 100;
    if (!this.HEIGHT){
      this.HEIGHT = this.viewportOut.offsetHeight;
    }


    var width = this.WIDTH,
      height = this.HEIGHT;

    if (attrName === 'width') {
      width = newVal;
    }

    if (attrName === 'height') {
      height = newVal;
    }

    this.viewportOutStyle.height = height + 'px';
    this.spinner.style.top = (height - this.toolbarHeight) / 2 + 'px';
  };

  Reader.prototype.setSrc = function(src) {
    this.SRC = src;
  };

  Reader.prototype.setFitWidth = function(fitWidth) {
    this.fitWidth = fitWidth;
  };

  Reader.prototype.queueRenderPage = function(num) {
    this.pdfExists = true;
    if (this.pageRendering) {
      this.pageNumPending = num;
    } else {
      this.renderPDF(num);
    }
  };

  Reader.prototype.loadPDF = function(pageNum) {
    this.setSize();
    pageNum = 1;
    var self = this;
    PDFJS.getDocument(this.SRC).then(function(pdf) {
      self.PDF = pdf;
      self.queueRenderPage(pageNum);

      self.currentPage = pageNum;
      self.totalPages.innerHTML = self.PDF.numPages;
      self.totalPagesNum = self.PDF.numPages;
      self.currentZoomVal = self.fitZoomVal = self.widthZoomVal = 0;
      self.createDownloadLink();
    }).catch((ex) => {
      this.pdfExists = false;
    });
  };

  Reader.prototype.renderPages = function(pdf) {
    var self = this;
    self.viewportOut.innerHTML="";
    PDFJS.getDocument(this.SRC).then(function(pdf) {
      self.PDF = pdf;

      for(var num = 1; num <= self.PDF.numPages; num++){
        pdf.getPage(num).then(self.renderPDF(num, null, true));
      }

      self.currentPage = 1;
      self.totalPages.innerHTML = self.PDF.numPages;
      self.totalPagesNum = self.PDF.numPages;
      if (!self.currentZoomVal)
        self.currentZoomVal = self.fitZoomVal = self.widthZoomVal = 0;
      self.createDownloadLink();
    });
  };

  Reader.prototype.sidebarSetup = function(currentThis){
    var self = this;
    var pdfName = currentThis.src;
    var currPage = 1; //Pages are 1-based not 0-based
    var numPages = 0;
    var pdfObj = null;

    //If there is already a sidebar loaded
    if(self.container.innerHTML.length != 0){
      if(currentThis.changedSideBar){   //Check if the pdf has been changed
        self.container.innerHTML = "";
        // Asynchronous download PDF
        PDFJS.getDocument(this.SRC).then(function(pdf) {

          //Set PDFJS global object (so we can easily access in our page functions
          pdfObj = pdf;

          //How many pages it has
          numPages = pdfObj.numPages;

          // Get div#container and cache it for later use
          var container = self.container;
          var counter = 0;

          pdf.getPage( 1 ).then( handlePages );
        });
        self.setViewportPos(false);
      }
    }


      //Else sidebar has not been loaded for first time
      else{
        self.container.innerHTML = "";
        // Asynchronous download PDF
        PDFJS.getDocument(this.SRC).then(function(pdf) {

          //Set PDFJS global object (so we can easily access in our page functions
          pdfObj = pdf;

          //How many pages it has
          numPages = pdfObj.numPages;

          // Get div#container and cache it for later use
          var container = self.container;
          var counter = 0;

          pdf.getPage( 1 ).then( handlePages );
        });
        self.setViewportPos(true);
      }
    
      function handlePages(page){
        var scale = 0.14;
        var scaleWidth = 0;
        var container = self.container;
        if(currentThis.sidebarOpen){
          scaleWidth = self.WIDTH;
        }
        else{
          scaleWidth = self.WIDTH;
        }
        scale = scaleWidth * .00035;
        var viewport = page.getViewport(scale);
        var div = document.createElement("div");

        // Set id attribute with page-#{pdf_page_number} format
        var pageString = (page.pageIndex + 1).toString();
        var parsedFileName = pdfName.split('/').pop();
        //div.setAttribute("id", "page-" + pageString + "-" + parsedFileName);


        // This will keep positions of child elements as per our needs
        div.style.backgroundColor = "gray";

        var click = document.querySelector('pdf-element');

        // Create a new Canvas element
        var canvas = document.createElement("canvas");
        // Append Canvas within div#page-#{pdf_page_number}
        div.appendChild(canvas);

        // Append div within div#container
        container.appendChild(div);

        //Add event listener for selecting that page.
        var addPage = Polymer.dom(self.container).childNodes[page.pageIndex];
        addPage.addEventListener('click',function(){
          var testPage = page.pageIndex + 1;
          click.sideBarClick(testPage, currentThis.instance, currentThis);
        });

        var context = canvas.getContext('2d');
        canvas.height = viewport.height;
        canvas.width = viewport.width;

        var renderContext = {
          canvasContext: context,
          viewport: viewport
        };

        // Render PDF page
        page.render(renderContext);
          
        //Move to next page
        currPage++;
        if ( pdfObj !== null && currPage <= numPages )
        {
            pdfObj.getPage( currPage ).then( handlePages );
        }
      }
  };

  Reader.prototype.renderPDF = function(pageNum, resize, isFull) {
    var self = this;
    self.pageRendering = true;
    self.spinner.active = true;
    this.PDF.getPage(pageNum).then(function(page) {
    var scaleW, scaleH, viewerViewport, scale, radians;
    radians = page.pageInfo.rotate * Math.PI / 180;

    self.pageW = Math.abs((page.view[2]*Math.cos(radians)) + (page.view[3]*Math.sin(radians)));
    self.pageH = Math.abs((page.view[3]*Math.cos(radians)) + (page.view[2]*Math.sin(radians)));

      if (self.currentZoomVal === 0 || !!resize) {
        scaleW = Math.round((self.WIDTH / self.pageW) * 100) / 100,
          scaleH = Math.round(((self.HEIGHT - self.toolbarHeight) / self.pageH) * 100) / 100,
          scale = Math.min(scaleH, scaleW);
        self.fitZoomVal = scale;
        self.widthZoomVal = self.WIDTH / self.pageW;
        self.currentZoomVal = self.fitWidth ? self.widthZoomVal : self.fitZoomVal;
      }
      if (!!resize) {
        self.zoomPage({
          target: self.zoomLvl
        });
      } else {
        scale = self.currentZoomVal;

        viewerViewport = page.getViewport(scale);

        self.ctx.height = viewerViewport.height;
        self.ctx.width = viewerViewport.width;

        self.pageW = self.pageW * scale;
        self.pageH = self.pageH * scale;

        if(self.WIDTH == self.currentWidth || self.currentWidth == null){
          self.setViewportPos(false);

        }
        else{
          self.setViewportPos(true);
        }

        self.viewport.width = self.pageW;
        self.viewport.height = self.pageH;
        self.viewportStyle.width = self.pageW + 'px';
        self.viewportStyle.height = self.pageH + 'px';

        if (self.enableTextSelection){
          self.textLayerDivStyle.width = self.pageW + 'px';
          self.textLayerDivStyle.height = self.pageH + 'px';
        }
        self.ctx.clearRect(0, 0, self.viewport.width, self.viewport.height);

        if (isFull){
          var wrapper = document.createElement('div');
          wrapper.setAttribute("style", "position: relative");
          var canvas = document.createElement('canvas');
          var textLayer = document.createElement('div');
          textLayer.setAttribute("style", "left: " + self.viewportStyle.left)

          textLayer.className = "textLayer";

          var ctx = canvas.getContext('2d');

          // canvas.height = viewerViewport.height;
          // canvas.width = viewerViewport.width;

          textLayer.height = viewerViewport.height;
          textLayer.width = viewerViewport.width;

          self.viewportOut.appendChild(wrapper);
          wrapper.appendChild(canvas);
          wrapper.appendChild(textLayer);

          page.render({
            canvasContext: ctx,
            viewport: viewerViewport
          });

          if (self.enableTextSelection){
            self.textLayerDiv.innerHTML="";
            page.getTextContent().then(function(textContent) {
              PDFJS.renderTextLayer({
                textContent: textContent,
                container: textLayer,
                pageIndex : pageNum,
                viewport: viewerViewport,
                textDivs: []
              });
            });
          }

        } else{
          var renderTask = page.render({
            canvasContext: self.ctx,
            viewport: viewerViewport
          });

          renderTask.promise.then(function () {
            self.pageRendering = false;
            self.spinner.active = false;
            if (self.pageNumPending !== null) {
              // New page rendering is pending
              self.renderPDF(self.pageNumPending);
              self.pageNumPending = null;
            }
          });
        }

        if (self.enableTextSelection){
          self.textLayerDiv.innerHTML="";
          page.getTextContent().then(function(textContent) {
            PDFJS.renderTextLayer({
              textContent: textContent,
              container: self.textLayerDiv,
              pageIndex : pageNum,
              viewport: viewerViewport,
              textDivs: []
            });
          });
        }
      }
    });
  };

  Reader.prototype.setViewportPos = function(sidebarAdjust) {
    if(sidebarAdjust){
      this.currentWidth = this.WIDTH * 0.75;
    }
    else{
      this.currentWidth = this.WIDTH;
    }
    if (this.pageW < this.currentWidth){
      this.viewportStyle.left = (this.currentWidth - this.pageW) / 2 + 'px';
    }
    else
      this.viewportStyle.left = 0;
    if (this.pageH < this.HEIGHT) {
      this.viewportStyle.top = (this.HEIGHT - this.pageH - this.toolbarHeight) / 2 + 'px';
      this.viewportStyle.topNum = Math.floor((this.HEIGHT - this.pageH - this.toolbarHeight) / 2) + this.toolbarHeight;
      if (this.enableTextSelection){
        this.textLayerDivStyle.topNum = Math.floor((this.HEIGHT - this.pageH - this.toolbarHeight) / 2) + this.toolbarHeight;
      }
    } else {
      this.viewportStyle.top = 0;
    }

    if (this.enableTextSelection) {
      this.textLayerDivStyle.left = this.viewportStyle.left;
      this.textLayerDivStyle.top = this.viewportStyle.top;
    }
  };

  Reader.prototype.changePDFSource = function(newSrc) {
    this.setSrc(newSrc);
    this.loadPDF(1);
  };

  Reader.prototype.zoomInOut = function(step) {
    // var step = 0.1;
    this.currentZoomVal = Math.round((Math.round(this.currentZoomVal * 10) / 10 + step) * 10) / 10;
    this.queueRenderPage(this.currentPage);
    // this.renderPages();
  };

  Reader.prototype.zoomIn = function() {
    var step = 0.1;
    this.currentZoomVal = Math.round((Math.round(this.currentZoomVal * 10) / 10 + step) * 10) / 10;
    this.queueRenderPage(this.currentPage);
    // this.renderPages();
  };

  Reader.prototype.zoomOut = function() {
    var step = -0.1;
    this.currentZoomVal = Math.round((Math.round(this.currentZoomVal * 10) / 10 + step) * 10) / 10;
    this.queueRenderPage(this.currentPage);
  };

  Reader.prototype.zoomPageFit = function() {
    this.currentZoomVal = this.fitZoomVal;
    this.queueRenderPage(this.currentPage);
  };

  Reader.prototype.zoomWidthFit = function() {
    this.currentZoomVal = this.widthZoomVal;
    this.queueRenderPage(this.currentPage);
  };

  Reader.prototype.getPageNum = function() {
    return this.PDF.numPages;
  };

  Reader.prototype.createDownloadLink = function() {
    var self = this;

    this.PDF.getData().then(function(data) {
      var blob = PDFJS.createBlob(data, 'application/pdf');

      self.downloadLink = URL.createObjectURL(blob);
    });
  };

  Reader.prototype.download = function(context) {
    var a = document.createElement('a'),
      filename = this.SRC.split('/');

    a.href = this.downloadLink;
    a.target = '_parent';

    if ('download' in a) {
      a.download = decodeURIComponent(filename[filename.length - 1]);
    }

    this.reader.appendChild(a);
    a.click();
    a.parentNode.removeChild(a);
  };

  window.Polymer.Reader = Reader;
})(window); 
