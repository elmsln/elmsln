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
