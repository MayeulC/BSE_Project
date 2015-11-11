# BSE_Project
School work

What works
==========
Everything more or less works, but we didn't have time to completely debug some functionalities : 

* The Send_String function sometimes returns without completing. A check has been added to be able to use the UART correctly.
* There might be some other bugs that we didn't find about yet, unfortunately.

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
