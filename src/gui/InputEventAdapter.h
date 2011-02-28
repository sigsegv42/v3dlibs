#ifndef INCLUDED_V3D_INPUTEVENTADAPTER
#define INCLUDED_V3D_INPUTEVENTADAPTER

#include "../input/MouseDevice.h"
#include "../input/KeyboardDevice.h"
#include "../input/MouseEventListener.h"
#include "../input/KeyboardEventListener.h"
#include "../command/EventListener.h"

#include <boost/shared_ptr.hpp>

/**
 * The InputEventAdapter provides the glue between libv3dcommand and libv3dinput, connecting the input device events to
 * the command library's generic event listener object type.
 */
class InputEventAdapter :
	public v3D::MouseEventListener,
	public v3D::KeyboardEventListener
{
	public:
		InputEventAdapter(boost::shared_ptr<v3D::KeyboardDevice> kb, boost::shared_ptr<v3D::MouseDevice> mouse);

		void connect(v3D::EventListener * target);

		// overrides from MouseEventListener
		void motion(unsigned int x, unsigned int y);
		void buttonPressed(unsigned int button);
		void buttonReleased(unsigned int button);
		// overrides from KeyboardEventListener base
		void keyPressed(const std::string & key);
		void keyReleased(const std::string & key);

	protected:
		void dispatch(const v3D::EventInfo & info) const;

	private:
		std::vector< v3D::EventListener * > targets_;
};



#endif // INCLUDED_V3D_INPUTEVENTADAPTER
