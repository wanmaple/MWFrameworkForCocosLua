/******************************
Description: Make the class uninheritable, just let your class inherit the Uninheritable<T>
Author: M.Wan
Date: 1/28/2014
******************************/

#ifndef __BASE_IUNINHERITABLE__
#define __BASE_IUNINHERITABLE__

namespace mwframework
{
	template<typename T>
	class IUninheritable;

	template<typename T>
	class Sealed
	{
		friend T;
		friend IUninheritable<T>;
	private:
		Sealed() {}
	};

    
	/**
     * Make class inheritable.
     */
	template<typename T>
	class IUninheritable : public virtual Sealed<T>		// use virtual inherit is to ensure the derived class of a sealed class must call the Sealed's constructor at first.
	{
	protected:
		IUninheritable() {}
	};
}

#endif