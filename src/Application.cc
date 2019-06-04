#include "Application.h"

#include "NodeConfiguration.h"

using namespace reflex;

Application::Application(Pool& pool) :
	  actTimeoutRed(*this)
	, actTimeoutGreen(*this)
	, actTimeoutBlue(*this)
	, timerRed(VirtualTimer::PERIODIC)
	, timerGreen(VirtualTimer::PERIODIC)
	, timerBlue(VirtualTimer::PERIODIC)
	, pool(pool)
{

	timerRed.set(100);
	timerGreen.set(500);
	timerBlue.set(1000);
	eventRed.init(&actTimeoutRed);
	eventGreen.init(&actTimeoutGreen);
	eventBlue.init(&actTimeoutBlue);
	timerRed.connect_output(&eventRed);
	timerGreen.connect_output(&eventGreen);
	timerBlue.connect_output(&eventBlue);

	led.turnOnAll();

}

void Application::timeoutRed()
{
	led.toggleColor(LED::red);
}

void Application::timeoutGreen()
{
	led.toggleColor(LED::green);
}

void Application::timeoutBlue()
{
	led.toggleColor(LED::blue);
}
