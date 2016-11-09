/**
 * Special widget feature group to maintain seperation from L.FeatureGroup.
 */
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
