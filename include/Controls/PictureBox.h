#ifndef XAGUI_PICTURE_BOX_H
#define XAGUI_PICTURE_BOX_H

XAGUI_EXPORT class PictureBox : public Button
{
	public:

		PictureBox();

		virtual void Render();

		virtual void DeleteTexture();

		virtual inline Texture* GetImage() const { return _image; }
		
		virtual void SetImage(Texture* image);


	protected:

		Texture* _image;
};

#endif