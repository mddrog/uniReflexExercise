#include "Application.h"

#include "NodeConfiguration.h"

using namespace reflex;

Application::Application(Pool& pool) :
	  actTimeout(*this)
	, timer(VirtualTimer::PERIODIC)
	, pool(pool)
{
	timer.set(1000);
	event.init(&actTimeout);
	timer.connect_output(&event);

}

void Application::timeout()
{

}
