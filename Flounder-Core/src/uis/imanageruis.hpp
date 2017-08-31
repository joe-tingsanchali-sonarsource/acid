#pragma once

#include "../maths/colour.hpp"

namespace Flounder
{
	/// <summary>
	/// A interface used to manage a main UI system.
	/// </summary>
	class imanageruis
	{
	public:
		/// <summary>
		/// Creates a new ui manager.
		/// </summary>
		imanageruis()
		{
		}

		/// <summary>
		/// Deconstructor for the ui manager.
		/// </summary>
		virtual ~imanageruis()
		{
		}

		/// <summary>
		/// Run when updating the ui manager.
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// Gets if the main menu is open.
		/// </summary>
		/// <returns> If the main menu is open. </returns>
		virtual bool isGamePaused() = 0;

		/// <summary>
		/// Gets the main menu's blur factor.
		/// </summary>
		/// <returns> The main menu's blur factor. </returns>
		virtual float getBlurFactor() = 0;

		/// <summary>
		/// The primary colour to be used in UI elements.
		/// </summary>
		/// <returns> The primary colour. </returns>
		virtual colour *getPrimaryColour() = 0;
	};
}
