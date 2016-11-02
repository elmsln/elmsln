/*! Leaflet.widget - v0.1.0 - 2012-11-02
* Copyright (c) 2012 Affinity Bridge - Tom Nightingale <tom@affinitybridge.com> (http://affinitybridge.com)
* Licensed BSD */

L.GeoJSONUtil = {
    featureCollection: function (features) {
        return {
            type: 'FeatureCollection',
            features: features || []
        };
    },

    feature: function (geometry, properties) {
        return {
            "type": "Feature",
            "geometry": geometry,
            "properties": properties || {}
        };
    },

    latLngsToCoords: function (latlngs) {
        var coords = [],
            coord;

        for (var i = 0, len = latlngs.length; i < len; i++) {
            coord = L.GeoJSONUtil.latLngToCoord(latlngs[i]);
            coords.push(coord);
        }

        return coords;
    },

    latLngToCoord: function (latlng) {
        return [latlng.lng, latlng.lat];
    }
};

L.WidgetFeatureGroup = L.LayerGroup.extend({
    initialize: function (layers) {
        L.LayerGroup.prototype.initialize.call(this, layers);
        this._size = layers ? layers.length : 0;
    },

    addLayer: function (layer) {
        this._size += 1;
        L.LayerGroup.prototype.addLayer.call(this, layer);
    },

    removeLayer: function (layer) {
        this._size -= 1;
        L.LayerGroup.prototype.removeLayer.call(this, layer);
    },

    clearLayers: function () {
        this._size = 0;
        L.LayerGroup.prototype.clearLayers.call(this);
    },

    toGeoJSON: function () {
        var features = [];
        this.eachLayer(function (layer) {
            features.push(layer.toGeoJSON());
        });

        return L.GeoJSONUtil.featureCollection(features);
    },

    size: function () {
        return this._size;
    },

    /**
     * Borrowing from L.FeatureGroup.
     */
    getBounds: L.FeatureGroup.prototype.getBounds
});

L.widgetFeatureGroup = function (layers) {
    return new L.WidgetFeatureGroup(layers);
};

L.Path.include({
    toGeoJSON: function () {
        return L.GeoJSONUtil.feature(this.toGeometry());
    }
});

L.FeatureGroup.include({
    toGeometry: function () {
        var coords = [];
        this.eachLayer(function (layer) {
            var geom = layer.toGeometry();
            if (geom.type !== "Point") {
                // We're assuming a FeatureGroup only contains Points
                // (currently no support for 'GeometryCollections').
                return;
            }
            coords.push(geom.coordinates);
        });

        return {
            type: "MultiPoint",
            coordinates: coords
        };
    },

    // TODO: Refactor this so we don't require two passes.
    isCollection: function () {
        var is_collection = false,
            geoms = [];

        this.eachLayer(function (layer) {
            if (!is_collection && layer.toGeometry().type !== "Point") {
                is_collection = true;
            }
        });

        return is_collection;
    },

    toGeoJSON: function () {
        if (this.isCollection()) {
            var geoms = [];
            this.eachLayer(function (layer) {
                geoms.push(layer.toGeometry());
            });
            return {
                type: "GeometryCollection",
                geometries: geoms
            };
        }
        else {
            return L.GeoJSONUtil.feature(this.toGeometry());
        }
    }
});

L.Marker.include({
    toGeometry: function () {
        return {
            type: "Point",
            coordinates: L.GeoJSONUtil.latLngToCoord(this.getLatLng())
        };
    },
    toGeoJSON: function () {
        return L.GeoJSONUtil.feature(this.toGeometry());
    }
});

L.Polyline.include({
    toGeometry: function () {
        return {
            type: "LineString",
            coordinates: L.GeoJSONUtil.latLngsToCoords(this.getLatLngs())
        };
    }
});

L.Polygon.include({
    toGeometry: function () {
        var latlngs = this.getLatLngs();
        // Close the polygon to create a LinearRing as per GeoJSON spec.
        // - http://www.geojson.org/geojson-spec.html#polygon
        latlngs.push(latlngs[0]);

        // TODO: add support for 'holes'.

        return {
            type: "Polygon",
            coordinates: [L.GeoJSONUtil.latLngsToCoords(latlngs)]
        };
    }
});

L.MultiPolyline.include({
    toGeometry: function () {
        var coords = [];

        this.eachLayer(function (layer) {
            coords.push(layer.toGeometry().coordinates);
        });

        return {
            type: "MultiLineString",
            coordinates: coords
        };
    }
});

L.MultiPolygon.include({
    toGeometry: function () {
        var coords = [];

        this.eachLayer(function (layer) {
            coords.push(layer.toGeometry().coordinates);
        });

        return {
            type: "MultiPolygon",
            coordinates: coords
        };
    }
});

L.Control.Draw.mergeOptions({
    select: {
        title: 'Select items'
    }
});

// TODO: Remove hack to 'open' object.
var onAdd = L.Control.Draw.prototype.onAdd;

L.Control.Draw.include({
    onAdd: function (map) {
        var className = 'leaflet-control-draw',
            container = onAdd.call(this, map);

        if (this.options.select) {
            this.handlers.select = new L.Handler.Select(map, this.options.select);
            this._createButton(
                    this.options.select.title,
                    className + '-select',
                    container,
                    this.handlers.select.enable,
                    this.handlers.select
            );
            this.handlers.select.on('activated', this._disableInactiveModes, this);
        }

        return container;
    }
});

L.Handler.Select = L.Handler.extend({
    includes: L.Mixin.Events,

    options: {},

    initialize: function (map, options) {
        L.Util.setOptions(this, options);
        L.Handler.prototype.initialize.call(this, map);
    },

    enable: function () {
        this.fire('activated');
        L.Handler.prototype.enable.call(this);
    },

    // Called when handler is enabled.
    addHooks: function () {
        if (this._map && this.options.selectable) {
            this._selected = L.layerGroup();
            this._selectable = this.options.selectable;

            this._selectable.eachLayer(function (layer) {
                this._bind(layer);
            }, this);

            this._map.on({
                // TODO: Determine whether this is necessary: can layers be
                //       added while this handler is enabled?
                layeradd: this._bind,
                layerremove: this._unbind
            }, this);
        }
    },

    // Called when handler is disabled.
    removeHooks: function () {
        if (this._map && this._selectable) {
            // Clean up selected layers.
            this._selectable.eachLayer(function (layer) {
                this._unbind(layer);
            }, this);
            delete this._selected;

            this._map.off({
                layeradd: this._bind,
                layerremove: this._unbind
            }, this);
        }
    },

    select: function (e) {
        var layer = e.layer || e.target || e;
        layer.off('click', this.select);
        layer.on('click', this.deselect, this);
        this._selected.addLayer(layer);
        this._map.fire('selected', { layer: layer });
    },

    deselect: function (e, permanent) {
        var layer = e.layer || e.target || e;
        layer.off('click', this.deselect);
        this._selected.removeLayer(layer);
        this._map.fire('deselected', { layer: layer });

        if (!permanent) {
            layer.on('click', this.select, this);
        }
    },

    applyToSelected: function (callback, context) {
        this._selected.eachLayer(callback, context);
    },

    _bind: function (e) {
        var layer = e.layer ? e.layer : e;
        if (this._selectable.hasLayer(layer)) {
            layer.on('click', this.select, this);
        }
    },

    _unbind: function (e) {
        var layer = e.layer ? e.layer : e;
        if (this._selectable.hasLayer(layer)) {
            if (this._selected.hasLayer(layer)) {
                this.deselect(layer, true);
            }
        }
    }
});

L.LayerGroup.include({
    hasLayer: function (layer) {
        return !!this._layers[L.Util.stamp(layer)];
    }
});

L.Control.Select = L.Control.extend({
    options: {
        title: 'Remove selected features',
        position: 'bottomright',
        remove: true
    },

    onAdd: function (map) {
        this._map = map;

        var class_name = 'leaflet-select-control',
            container = L.DomUtil.create('div', class_name);

        if (this.options.remove) {
            this._createButton(
                    this.options.remove.title,
                    class_name + '-remove',
                    container,
                    this._delete,
                    this
            );
        }

        return container;
    },

    _delete: function () {
        this._map.drawControl.handlers.select.applyToSelected(function (layer) {
            this._map.removeLayer(layer);
        }, this);
    },

    _createButton: function (title, className, container, fn, context) {
        var link = L.DomUtil.create('a', className, container);
        link.href = '#';
        link.title = title;

        L.DomEvent
                .on(link, 'click', L.DomEvent.stopPropagation)
                .on(link, 'mousedown', L.DomEvent.stopPropagation)
                .on(link, 'dblclick', L.DomEvent.stopPropagation)
                .on(link, 'click', L.DomEvent.preventDefault)
                .on(link, 'click', fn, context);

        return link;
    }
});

L.Map.addInitHook(function () {
    if (this.options.drawControl.select) {
        this.selectControl = L.Control.select(this.options.drawControl.select);
        this.addControl(this.selectControl);
    }
});

L.Control.select = function (options) {
    return new L.Control.Select(options);
};

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
