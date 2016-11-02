L.Map.mergeOptions({
    widget: false
});

L.Handler.Widget = L.Handler.extend({
    includes: L.Mixin.Events,

    options: {
        multiple: true,
        cardinality: 0, // Unlimited if multiple === true.
        autoCenter: true,
        defaultVectorStyle: {
            color: '#0033ff'
        },
        selectedVectorStyle: {
            color: '#F00'
        },
        drawVectorStyle: {
            color: '#F0F',
            clickable: true
        }
    },

    initialize: function (map, options) {
        L.Util.setOptions(this, options);
        L.Handler.prototype.initialize.call(this, map);

        if (!this._map.drawControl) {
            this._initDraw();
        }
    },

    addHooks: function () {
        if (this._map && this.options.attach) {
            this.vectors = L.widgetFeatureGroup().addTo(this._map);
            this._attach = L.DomUtil.get(this.options.attach);
            this._full = false;
            this._cardinality = this.options.multiple ? this.options.cardinality : 1;

            this.load(this._attach.value);

            this._map.drawControl.handlers.select.options.selectable = this.vectors;

            // Map event handlers.
            this._map.on({
                'draw:poly-created draw:marker-created': this._onCreated,
                'selected': this._onSelected,
                'deselected': this._onDeselected,
                'layerremove': this._unbind
            }, this);

            if (this.vectors.size() > 0 && this.options.autoCenter) {
                this._map.fitBounds(this.vectors.getBounds());
            }
        }
    },

    removeHooks: function () {
        if (this._map) {
            this._map.removeLayer(this.vectors);
            delete this.vectors;

            this._map.off({
                'draw:poly-created draw:marker-created': this._onCreated,
                'selected': this._onSelected,
                'deselected': this._onDeselected,
                'layerremove': this._unbind
            }, this);
        }
    },

    _initDraw: function () {
        this._map.drawControl = new L.Control.Draw({
            position: 'topright',
            polyline: { shapeOptions: this.options.drawVectorStyle },
            polygon: { shapeOptions: this.options.drawVectorStyle },
            circle: false,
            rectangle: false
        }).addTo(this._map);

        this._map.selectControl = L.Control.select().addTo(this._map);
    },

    // Add vector layers.
    _addVector: function (feature) {
        this.vectors.addLayer(feature);

        if (this._cardinality > 0 && this._cardinality <= this.vectors.size()) {
            this._full = true;
        }
    },

    // Handle features drawn by user.
    _onCreated: function (e) {
        var key = /(?!:)[a-z]+(?=-)/.exec(e.type)[0],
            vector = e[key] || false;

        if (vector && !this._full) {
            this._addVector(vector);
        }
    },

    _onSelected: function (e) {
        var layer = e.layer;

        if (layer.setStyle) {
            layer.setStyle(this.options.selectedVectorStyle);
        }
        else {
            var icon = layer.options.icon;
            icon.options.className = 'marker-selected';
            layer.setIcon(icon);
            icon.options.className = '';
        }
    },

    _onDeselected: function (e) {
        var layer = e.layer;

        if (layer.setStyle) {
            layer.setStyle(this.options.defaultVectorStyle);
        }
        else {
            layer.setIcon(layer.options.icon);
        }
    },

    _unbind: function (e) {
        var layer = e.layer;
        if (this.vectors.hasLayer(layer)) {
            this.vectors.removeLayer(layer);

            if (this._cardinality > this.vectors.size()) {
                this._full = false;
            }
        }
    },

    // Read GeoJSON features into widget vector layers.
    load: function (geojson) {
        var data,
            on_each = function (feature, layer) {
                this._addVector(layer);
            };

        // Empty data isn't an exceptional scenario.
        if (!geojson) {
            // Return like nothing happened.
            return;
        }

        // Invalid GeoJSON is and an exception will be thrown.
        data = typeof geojson === 'string' ? JSON.parse(geojson) : geojson;

        return L.geoJson(data, {
            onEachFeature: L.Util.bind(on_each, this)
        });
    },

    // Write widget vector layers to GeoJSON.
    write: function () {
        var obj = this.vectors.toGeoJSON();
        this._attach.value = JSON.stringify(obj);
    }
});

L.Map.addInitHook(function () {
    if (this.options.widget) {
        var options = this.options.widget;
        this.widget = new L.Handler.Widget(this, options);
    }
});
