#ifndef ITexture_h__
#define ITexture_h__

namespace DeviceInterface
{
	class ITexture : public Foundation::IObject
	{
	public:
		ITexture(void);
	public:
		virtual ~ITexture(void);
		virtual BOOL ReadyToDraw(int n) = 0;
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual int GetRawWidth() = 0;
		virtual int GetRawHeight() = 0;
		virtual int GetRawPositionX() = 0;
		virtual int GetRawPositionY() = 0;
		virtual void* GetTextureInterface()= 0;
	};
	SmartPointer(ITexture);
}
#endif // ITexture_h__