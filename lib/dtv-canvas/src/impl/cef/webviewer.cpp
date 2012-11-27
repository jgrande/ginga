#include "webviewer.h"
#include "../../surface.h"
#include "../../canvas.h"
#include "../../system.h"
#include <util/log.h>
#include <util/registrator.h>
#include <boost/bind.hpp>
#include <assert.h>

#define REQUIRE_UI_THREAD()   assert(CefCurrentlyOn(TID_UI));
#define REQUIRE_IO_THREAD()   assert(CefCurrentlyOn(TID_IO));

namespace canvas {
namespace cef {

// Handler for off-screen rendering windows.
class WebHandler : public CefClient,
                         public CefLifeSpanHandler,
                         public CefRequestHandler,
                         public CefRenderHandler
{
public:
	WebHandler( WebViewer *view )
		: _view(view)
	{
	}

	virtual ~WebHandler() 
	{
	}

	// CefClient methods
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() { return this; }
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() { return this; }
	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() { return this; }

	// CefLifeSpanHandler methods
	virtual void OnAfterCreated( CefRefPtr<CefBrowser> browser ) {
		REQUIRE_UI_THREAD();
		_view->setupBrowser( browser );
	}

	//	CefRequestHandler methods
	virtual bool OnBeforeResourceLoad(
		CefRefPtr<CefBrowser> /*browser*/,
		CefRefPtr<CefRequest> request,
		CefString& /*redirectUrl*/,
		CefRefPtr<CefStreamReader>& /*resourceStream*/,
		CefRefPtr<CefResponse> /*response*/,
		int /*loadFlags*/ )
	{
		REQUIRE_IO_THREAD();
		std::string url = request->GetURL();
		LDEBUG("cef::WebViewer", "request url=%s", url.c_str() );
		return false;
	}

	//	CefRenderHandler methods
	virtual void OnPaint(
		CefRefPtr<CefBrowser> /*browser*/,
		PaintElementType /*type*/,
		const RectList& /*dirtyRects*/,
		const void* buffer)
	{
		REQUIRE_UI_THREAD();
		_view->paint( (const char *)buffer );
	}

private:
	WebViewer *_view;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(ClientOSRPlugin);
};

bool WebViewer::init() {
	// Initialize CEF.
	CefSettings settings;
	settings.multi_threaded_message_loop = true;
	settings.log_severity = LOGSEVERITY_ERROR;
	// settings.log_severity = LOGSEVERITY_VERBOSE;
	// CefString(&settings.log_file) = "chrome.log";
	CefRefPtr<CefApp> app;
	CefInitialize(settings, app);
	return true;
}

void WebViewer::fin() {
	// Shut down CEF.
	CefShutdown();
}

REGISTER_INIT( cef ) {
	WebViewer::init();
}

REGISTER_FIN( cef ) {
	WebViewer::fin();
}

WebViewer::WebViewer( System *sys, Surface *surface )
	: canvas::WebViewer( surface ), _sys(sys)
{
	_buf = NULL;
	_bufSize = 0;
	_valid = false;
}

WebViewer::~WebViewer( void )
{
	free(_buf);
}

void WebViewer::setupBrowser( const CefRefPtr<CefBrowser> &browser ) {
	_browser = browser;
	resize();
}

void WebViewer::resize() {
	_mutex.lock();
	_size = surface()->getSize();
	int tmp = bitmapSize();
	if (_bufSize < tmp) {
		free(_buf);
		_bufSize = tmp;
		_buf = (char *)malloc( _bufSize );
	}
	_valid = false;
	_mutex.unlock();
	_browser->SetSize( PET_VIEW, _size.w, _size.h );
}

int WebViewer::bitmapSize() const {
	return _size.w * _size.h * 4;
}

void WebViewer::paint( const char *buf ) {
	//	Copy memory
	_mutex.lock();
	memcpy( _buf, buf, bitmapSize() );
	_valid = true;
	_mutex.unlock();
	
	//	Enqueue paint
	_sys->enqueue( boost::bind(&WebViewer::draw,this) );	//	TODO: Validate pointer!
}

void WebViewer::draw() {
	_mutex.lock();
	if (_valid) {
		canvas::ImageData img;
		memset(&img,0,sizeof(canvas::ImageData));

		//	Setup data
		img.size = _size;
		img.length = bitmapSize();
		img.data = (unsigned char *)_buf;
		img.bitsPerPixel = 32;
		img.bytesPerPixel = 4;
		img.stride = _size.w*4;
		img.dataOffset = 0;	

		//	Create surface from data
		canvas::Surface *sur=_sys->canvas()->createSurface( &img );
		if (sur) {
			surface()->blit( canvas::Point(0,0), sur );
			_sys->canvas()->destroy( sur );
			_sys->canvas()->flush();
		}
	}
	_mutex.unlock();
}

void WebViewer::onResized() {
	resize();
}

bool WebViewer::load( const std::string &file ) {
	//	In player thread	
	LINFO("cef::WebViewer", "load: uri=%s", file.c_str());

	//	Create the off-screen rendering window.
	CefWindowInfo windowInfo;
	CefBrowserSettings settings;
	settings.history_disabled = true;
	settings.local_storage_disabled = true;
	settings.databases_disabled = true;
	settings.application_cache_disabled = true;
	windowInfo.SetAsOffScreen(NULL);
	windowInfo.SetTransparentPainting(TRUE);
	bool result=CefBrowser::CreateBrowser( 
		windowInfo, 
		new WebHandler( this ),
		file,
		settings );
	if (result) {
		return true;
	}
	return false;
}

void WebViewer::stop() {
	//	--	In player thread	   
	LINFO("cef::WebViewer", "stop");
	_browser->CloseBrowser();
	_browser = NULL;
}

}
}
