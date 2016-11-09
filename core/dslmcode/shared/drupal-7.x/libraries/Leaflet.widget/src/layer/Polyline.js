L.Polyline.include({
    toGeometry: function () {
        return {
            type: "LineString",
            coordinates: L.GeoJSONUtil.latLngsToCoords(this.getLatLngs())
        };
    }
});
