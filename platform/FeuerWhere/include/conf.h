#ifndef Configuration_h
#define Configuration_h
/*
 *	REFLEX - Real-time Event FLow EXecutive
 *
 *	A lightweight operating system for deeply embedded systems.
 *
 *	Class(ses):
 *
 *	Author:		 Karsten Walther
 *
 *	Description: Definitions needed by classes used for the application.
 *
 *
 *    This file is part of REFLEX.
 *
 *    Copyright 2010 BTU Cottbus, Department for Distributed Systems and 
 *    Operating Systems. All rights reserved.
 *    
 *    Redistribution and use in source and binary forms, with or without 
 *    modification, are permitted provided that the following conditions
 *    are met:
 *    
 *       1. Redistributions of source code must retain the above copyright 
 *          notice, this list of conditions and the following disclaimer.
 * 
 *       2. Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in
 *          the documentation and/or other materials provided with the 
 *          distribution.
 * 
 *    THIS SOFTWARE IS PROVIDED BY BTU COTTBUS, DEPARTMENT FOR DISTRIBUTED 
 *    SYSTEMS AND OPERATING SYSTEMS ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 *    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 *    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 *    NO EVENT SHALL BTU COTTBUS, DEPARTMENT FOR DISTRIBUTED SYSTEMS AND 
 *    OPERATING SYSTEMS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *    The views and conclusions contained in the software and documentation 
 *    are those of the authors and should not be interpreted as representing 
 *    official policies, either expressed or implied, of BTU Cottbus, 
 *    Department for Distributed Systems and Operating Systems.
 *
 * */

// different system constants
enum { 	IOBufferSize = 100,   	//used for OutputChannel
		NrOfStdOutBuffers = 20,
		MaxPoolCount = 1};	//amount of buffers in OutputChannel


// Defines the speed of the system clock
#define TICK_PERIOD_MSEC 1

// Defines the duration of a whole cycle in clockticks
#ifdef TIME_TRIGGERED_SCHEDULING
#define MAXTIME 60
#endif

#ifndef NODEID
#define NODEID 1
#endif


#endif
