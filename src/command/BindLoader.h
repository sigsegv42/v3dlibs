#ifndef INCLUDED_V3D_BINDLOADER
#define INCLUDED_V3D_BINDLOADER

#include "CommandDirectory.h"

#include <boost/property_tree/ptree.hpp>

namespace v3D
{

	namespace utility
	{

		/**
		 * Load command bindings from config source
		 * Utility method used for loading command binds from a property tree.
		 * The relevant property tree section should take a form e.g.:
		 *
		 * \<keys>
		 *		\<bind key="w" scope="pong" command="leftPaddleUp" catch="any" param="cmd param" />
		 * \</keys>
		 * @param tree the property tree to load the bindings from
		 * @param directory the CommandDirectory to store the loaded bindings in
		 * @return whether loading was successful or not
		 */
		bool load_binds(const boost::property_tree::ptree & tree, CommandDirectory * directory);

	}; // end namespace utility

}; // end namespace v3D

#endif // INCLUDED_V3D_BINDLOADER
