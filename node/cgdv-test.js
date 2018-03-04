
// Require CGDV library
var cgdv = require('bindings')('cgdvV8');

// Test CGDV status object
//cgdvStatus = new cgdv.v8CgdvStatus();
//console.log(cgdvStatus);

// Startup CGDV
console.log(cgdv.Startup(cgdvStatusDelegate));

// Main Loop
var mainLoop = setInterval(updateCgdv, 500);
function updateCgdv()
{
	// Update CGDV on main UI thread
	cgdv.Update();
}

// CGDV Status Delegate
function cgdvStatusDelegate(status)
{
	console.log("******** cgdv-test cgdvStatusDelegate ********");
	console.log(status);
//	console.log(Object.getOwnPropertyNames(status));
}
