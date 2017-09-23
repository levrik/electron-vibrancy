var Vibrancy = require('bindings')('Vibrancy');

function enableVibrancy (buffer) {
	Vibrancy.SetVibrancy(true, buffer);
}
function disableVibrancy (buffer) {
	Vibrancy.SetVibrancy(false, buffer);
}

module.exports = {
	enableVibrancy: function (window, material) {
		if (window == null) return false;

		return enableVibrancy(window.getNativeWindowHandle());
	},
	disableVibrancy: function (window) {
		return disableVibrancy(window.getNativeWindowHandle());
	}
}
