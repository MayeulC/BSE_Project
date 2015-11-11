# BSE_Project
School work

What works
==========
Everything more or less works, but we didn't have time to completely debug some functionalities : 

* The Send_String function sometimes returns without completing. A check has been added to be able to use the UART correctly.
* There might be some other bugs that we didn't find about yet, unfortunately. Also, we might have forgotten to merge bugfixes between branches.

Compilation warning : 
A function has been excluded from the overlay analysis. Be sure to add the `LIB_BSE_linker_command.lin` file as the linker script.

What works : 

* The ADC works
* When recieving R, correct status information is sent trough the UART
* The external interrupt works
* Every error is displayed trough the UART
* The RTC and its associated functions (reset...) works
* The correct information is sent to the printer
* Packages are correctly detected and identified
* Weighing works
* Pulses to activate pistons works


Program architecture
====================
The main program initializes the device, then launches an infinite loop, waiting for instructions from the UART, or for strings to send to the UART.

Then, everything happens in the Timer 2 ISR, which is triggered every 5ms. This ISR keeps a RTC, and calls the central brain of the program, which is the event dispatcher. This one can be thought as a scheduler, bearing some similarities in structure with some RT kernels. 

The scheduler first checks inputs, also calling a package management subsystems. This subsystem detects incoming packages, and adds event to the queue depending on the detected package.
Then, the event dispatcher checks if the queued items can be acomplished, and does so if possible.

An other source of async event is the INT1, which adds an event to the queue.

If the system is in error mode, it just refuses to add events to the queue. We could have just filtered out the events depending on whether they could be processed safely, but chose to go this way for a bit of extra safety.

Comments for the corrector
==========================
Feel free to consult statistics included in the stats/ dir, or to make your own.
I also included both git shortlog and git log outputs into logs.txt in case you can't use git.
This is on the branch complete, which is the most advanced as of now. Phase 1,2,3,4 branches are here to demonstrate some functionalities.

If you prefer github's interface, the project is there too, just send me an email so that I can give you access to it. The goal is of course to open up the repository once cleaned up a bit.

We decided early to go on and write everything in English to avoid mixing French with English keywords, etc. With that came the choice to write detailled comments for each function we wrote, as well as adding a LICENSE header to each of our files. Since the program is to be publicly released, we opted for the GPLv3 license.

Sorry for the delay. As of writing this line, it is 20:18, but I corrected a few mistakes in the code which were worth it.

