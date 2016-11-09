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
