
#include "stdafx.h"

extern "C"
{
   #include "libjpeg-turbo\jpeglib.h"
}


#define DSVNCLIBRARY_API __declspec(dllexport)



extern "C"
{
	class DSVncViewerAdapter : protected CoreEventsAdapter
	{
	public:

		DSVncViewerAdapter();
		~DSVncViewerAdapter();

		TCHAR* m_ip;//��Ҫ������IP

		int width();
		int height();
		int bitsPerPixel();

		void start();
		void stop();
		void refresh();

	protected:
		//
		// Bell event has been received from the server.
		//
		virtual void onBell();

		//
		// New cut text (clipboard) contents has been received from the server.
		//
		virtual void onCutText(const StringStorage *cutText);

		//
		// Connection has been established.
		//
		virtual void onEstablished();

		//
		// Protocol has entered the normal interactive phase (in other words,
		// protocol initialization has been completed).
		//
		// FIXME: document it.
		// Output need for capability, e.g. FT.
		virtual void onConnected(RfbOutputGate *output);

		//
		// RemoteViewerCore has been disconnected by calling stop()
		// or connection with server is disconnected.
		//
		// FIXME: now, onDisconnect not called after onError().
		// FIXME: change documentation or call onDisconnect() after onError().
		virtual void onDisconnect(const StringStorage *message);

		//
		// Authentication has been failed.
		// By default, onAuthError() call onError(exception).
		//
		virtual void onAuthError(const AuthException *exception);

		//
		// Error has been occured.
		//
		virtual void onError(const Exception *exception);

		// this event after update of frame buffer "fb" in rectangle "update".
		// guaranteed correct of frame buffer's area in rectangle "update".
		//
		// Frame buffer contents has been changed. During this callback,
		// the frame buffer is locked, and the rectangle is guaranteed to be valid
		// (no guarantees about other areas of the frame buffer).
		//
		virtual void onFrameBufferUpdate(const FrameBuffer *fb, const Rect *update);

		// changed properties of frame buffer.
		// In this moment frame buffer area is dirty and may be contained incorrect data
		//
		// Some properties of the frame buffer have been changed. Assume that new
		// frame buffer has been created and the old one has been destroyed. This
		// notification will be called on initial frame buffer allocation as well.
		//
		virtual void onFrameBufferPropChange(const FrameBuffer *fb);

	private:
		int m_buttonMask;
		RemoteViewerCore *m_viewerCore;
		LocalMutex m_bufferLock;
		FrameBuffer m_framebuffer;

		int m_width;
		int m_height;
		int m_bitsPerPixel;

	};
};

typedef void *CPPCallback_DEBUG(char* tick);//һ���ı���Ϣ�ص�����ָ��,��������debugʱʹ��
EXTERN_C DSVNCLIBRARY_API void SetCallback_DEBUG(CPPCallback_DEBUG callback);//���ú���ָ�뷽��

typedef void *CPPCallback(char* tick);//����vnc�ͻ�������״̬�ص�����ָ��
EXTERN_C DSVNCLIBRARY_API void SetCallback(CPPCallback callback);//���ú���ָ�뷽��

typedef void *CPPUpdateCallback(UCHAR* data, int length, int w, int h, int left, int top, int right, int bottom);//����ָ��
EXTERN_C DSVNCLIBRARY_API void SetUpdateCallback(CPPUpdateCallback callback);//���ú���ָ�뷽��

EXTERN_C DSVNCLIBRARY_API void StartVNCClient();//����VNC�ͻ���
EXTERN_C DSVNCLIBRARY_API void CloseVNCClient();//�ر�VNC�ͻ���
EXTERN_C DSVNCLIBRARY_API void SetIP(TCHAR * ip);//������Ҫ������IP������֮ǰ����Ҫ���ݽ��룩