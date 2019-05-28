/*
 *	REFLEX - Real-time Event FLow EXecutive
 *
 *	A lightweight operating system for deeply embedded systems.
 *
 *
 *	Class(ses):	main
  
 *	Author:		Karsten Walther
 *
 *	Description:
 */
#include "NodeConfiguration.h"


namespace reflex {
	NodeConfiguration system;
}

int main()
{
	reflex::system.scheduler.start();
	return 0;
}
