#ifndef IMAGESURFACE_HPP
#define IMAGESURFACE_HPP

#include "surface/Surface.hpp"


namespace conrast { namespace surface {

class ImageSurface : public Surface
{
public:
	enum class ImageFormat {
		BMP,
		PNG
	};

	ImageSurface(utils::Vec2i resolution, ImageFormat imageFormat = ImageFormat::BMP);
    virtual void display(const render::RenderTarget& renderTarget) const override;

private:
	ImageFormat m_imageFormat;
};

} }
#endif // CONSOLESURFACE_HPP
