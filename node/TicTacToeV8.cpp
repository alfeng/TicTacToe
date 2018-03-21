#ifdef THIS_FILE
#undef THIS_FILE
#endif
#define THIS_FILE "TicTacToeV8.cpp"

#include <nan.h>

#include "CTicTacToe.h"


// ********************************************************************
//   TicTacToe interface
// ********************************************************************

// App interface for CGDV
CgdvApp* cgdvApp = NULL;

// Javascript status delegate
Nan::Callback jsStatusDelegate;


// Send status to Javascript
void sendStatus(v8CgdvStatus* status)
{
	// Create callback parameters
	const int argc = 1;
	v8::Local<v8::Value> args[argc];

	// Create JSON object for status
	v8::Local<v8::Object> jsonObject = Nan::New<v8::Object>();
	v8::Local<v8::String> propName = Nan::New("statusCode").ToLocalChecked();
	v8::Local<v8::Value> propValue = Nan::New(status->statusCode);
	Nan::Set(jsonObject, propName, propValue);
	propName = Nan::New("statusAction").ToLocalChecked();
	propValue = Nan::New(status->statusAction);
	Nan::Set(jsonObject, propName, propValue);
	propName = Nan::New("deviceID").ToLocalChecked();
	propValue = Nan::New(status->deviceID).ToLocalChecked();
	Nan::Set(jsonObject, propName, propValue);
	propName = Nan::New("sessionID").ToLocalChecked();
	propValue = Nan::New(status->sessionID).ToLocalChecked();
	Nan::Set(jsonObject, propName, propValue);
	propName = Nan::New("propertyCode").ToLocalChecked();
	propValue = Nan::New(status->propertyCode).ToLocalChecked();
	Nan::Set(jsonObject, propName, propValue);
	propName = Nan::New("statusMessage").ToLocalChecked();
	propValue = Nan::New(status->statusMessage).ToLocalChecked();
	Nan::Set(jsonObject, propName, propValue);
	propName = Nan::New("statusDetails").ToLocalChecked();
	propValue = Nan::New(status->statusDetails).ToLocalChecked();
	Nan::Set(jsonObject, propName, propValue);
	propName = Nan::New("actionURL").ToLocalChecked();
	propValue = Nan::New(status->actionURL).ToLocalChecked();
	Nan::Set(jsonObject, propName, propValue);

	// Set parameter to JSON object
	args[0] = jsonObject;

	CGDV_TRACE("=========== Calling Javascript Delegate");

	// Pass status to Javascript
	v8::Local<v8::Value> jsReturnValue = jsStatusDelegate.Call(argc, args);
}

// CGDV status delegate
void cgdvStatusHandler(CgdvStatus &cgdvStatus)
{
	// Print status
	CGDV_TRACE("................ cgdv_v8.cpp -- cgdvStatusHandler()");
	string dbgStr = "Status Code: " + to_string(cgdvStatus.statusCode);
	CGDV_TRACE(dbgStr);
	dbgStr = "Status Action: " + to_string(cgdvStatus.statusAction);
	CGDV_TRACE(dbgStr);
	dbgStr = "Device ID: " + cgdvStatus.deviceID;
	CGDV_TRACE(dbgStr);
	dbgStr = "Session ID: " + cgdvStatus.sessionID;
	CGDV_TRACE(dbgStr);
	dbgStr = "Property Code: " + cgdvStatus.propertyCode;
	CGDV_TRACE(dbgStr);
	dbgStr = "Status Message: " + cgdvStatus.statusMessage;
	CGDV_TRACE(dbgStr);
	dbgStr = "Status Details: " + cgdvStatus.statusDetails;
	CGDV_TRACE(dbgStr);
	dbgStr = "Action URL: " + cgdvStatus.actionURL;
	CGDV_TRACE(dbgStr);

	// Copy native status to Javascript status
	v8CgdvStatus* status = new v8CgdvStatus();
	status->statusCode = cgdvStatus.statusCode;
	status->statusAction = cgdvStatus.statusAction;
	status->deviceID = cgdvStatus.deviceID;
	status->sessionID = cgdvStatus.sessionID;
	status->propertyCode = cgdvStatus.propertyCode;
	status->statusMessage = cgdvStatus.statusMessage;
	status->statusDetails = cgdvStatus.statusDetails;
	status->actionURL = cgdvStatus.actionURL;

	// Send status to Javascript
	sendStatus(status);
}


// ********************************************************************
//   Javascript interface
// ********************************************************************

// NAN_METHOD is a Nan macro enabling convenient way of creating native node functions.
// It takes a method's name as a param. By C++ convention, I used the Capital cased name.
NAN_METHOD(Startup)
{
	// Create an instance of V8's String type
	auto message = Nan::New("Calling Startup.").ToLocalChecked();

	// Start CGDV
	if (cgdvApp != NULL)
		cgdvApp->Startup(cgdvStatusHandler);

	// Set Javascript status delegate
	// assume info[0]->IsFunction()
	jsStatusDelegate.Reset(info[0].As<v8::Function>());

	// 'info' is a macro's "implicit" parameter - it's a bridge object between C++ and JavaScript runtimes
	// You would use info to both extract the parameters passed to a function as well as set the return value.
	info.GetReturnValue().Set(message);
}

// Update CGDV on Main UI thread
NAN_METHOD(Update)
{
	// Start CGDV
	if (cgdvApp != NULL)
		cgdvApp->Update();
}

// Revalidate CGDV on Main UI thread
NAN_METHOD(Validate)
{
	// Start CGDV
	if (cgdvApp != NULL)
		cgdvApp->Revalidate();
}

// Shutdown CGDV on Main UI thread
NAN_METHOD(Shutdown)
{
	// Start CGDV
	if (cgdvApp != NULL)
		cgdvApp->Shutdown();
}

// Suspend CGDV on Main UI thread
NAN_METHOD(Suspend)
{
	// Start CGDV
	if (cgdvApp != NULL)
		cgdvApp->Suspend();
}

// Resume CGDV on Main UI thread
NAN_METHOD(Resume)
{
	// Start CGDV
	if (cgdvApp != NULL)
		cgdvApp->Resume();
}

// Module initialization logic
NAN_MODULE_INIT(Initialize)
{
	// Export CGDV methods
	NAN_EXPORT(target, Startup);
	NAN_EXPORT(target, Update);
	NAN_EXPORT(target, Validate);
	NAN_EXPORT(target, Shutdown);
	NAN_EXPORT(target, Suspend);
	NAN_EXPORT(target, Resume);

	// Create CGDV App Helper
	cgdvApp = CgdvApp::GetSingleton();

	// Init CGDV status class so Javascript can use it
	v8CgdvStatus::Init(target);
}

// Create the add-on module and initialize it (created with NAN_MODULE_INIT macro)
NODE_MODULE(cgdv_v8, Initialize);
