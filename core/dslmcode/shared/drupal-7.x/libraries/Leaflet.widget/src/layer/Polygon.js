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
