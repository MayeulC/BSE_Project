# BSE_Project
This project was some school work done at CPE Lyon. We had a specification to follow, as well as checkpoints to validate our work (hence the different phase branches). Please note that code in these branches may not work, since we may have used other means to validate these checkpoints.
BSE stands for "Base des Systèmes Embarqués", or introduction to embedded systems, and is one of the modules of the fourth year at CPE Lyon in our speciality. You can find the complete specification (albeit in French) in the corresponding folder. We tried our best to write everything in English, but some French must have slipped here and there. As of now, the files that were provided to us are not translated yet.

The whole project is available under the GPL.V3 License, excepted the specification, which is released as CC BY-NC-ND 4.0, since we are not the crators. If you want to create derivative works from the specification, please contact either us or CPE Lyon, explaining your request. If you contact us, we will forward your request to the right person.

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
