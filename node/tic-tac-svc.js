// Require CGDV library
var cgdv = require('bindings')('cgdvV8');
// var cgdv = require('./build/Release/cgdvV8');
// var cgdv = require('./bin/win32-x64-54/cgdvV8');

// Test CGDV status object
//cgdvStatus = new cgdv.v8CgdvStatus();
//console.log(cgdvStatus);

// CGDV update timer
const UPDATE_TIME_MS = 500;
var cgdvTimer = null;

// User status delegate
var userStatusDelegate = null;


// ********* MODULE EXPORTS ***********

// Export CGDV for use by consuming apps
// exports.cgdv = cgdv;

// Startup CGDV
exports.Startup = function Startup(statusDelegate)
{
    // Remember user status delegate
	userStatusDelegate = statusDelegate;

    // Set status delegate
    cgdv.Startup(cgdvStatusDelegate);

    // Start update timer
    startUpdateTimer();
}

// Shutdown CGDV
exports.Shutdown = function Shutdown()
{
    // Kill update timer
    stopUpdateTimer();

    // Shutdown CGDV
    cgdv.Shutdown();
}

// Revalidate CGDV
exports.Validate = function Validate()
{
    // Revalidate CGDV
    cgdv.Validate();
}

// Suspend CGDV
exports.Suspend = function Suspend()
{
    // Pause update timer
    stopUpdateTimer();

    // Suspend CGDV
    cgdv.Suspend();
}

// Resume CGDV
exports.Resume = function Resume()
{
    // Resume CGDV
    cgdv.Resume();

    // Resume update timer
    startUpdateTimer();
}

// CGDV update timer must be on main thread because it calls back into Javascript
function updateCgdv()
{
	// Update CGDV on main UI thread
	cgdv.Update();
}

// Start update timer
function startUpdateTimer()
{
    if (cgdvTimer == null)
        cgdvTimer = setInterval(updateCgdv, UPDATE_TIME_MS);
}

// Stop update timer
function stopUpdateTimer()
{
    if (cgdvTimer != null)
	{
        clearInterval(cgdvTimer);
		cgdvTimer = null;
    }
}

// CGDV Status Delegate
function cgdvStatusDelegate(status)
{
    // Do any preemptive status processing here (only pass to user when necessary)
	console.log("******** cgdv-lib.js cgdvStatusDelegate ********");
	console.log(Object.getOwnPropertyNames(status));

    // Pass CGDV status to user
    userStatusDelegate(status);
}
