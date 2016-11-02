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
