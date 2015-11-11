# BSE_Project
School work

What works
==========
Everything more or less works, but we didn't have time to completely debug some functionalities : 

* The equation used to calculate the weigth might not be valid
* The deadline for pushng the packages seems not to be computed correctly
* The Send_String function sometimes returns without completing. A check has been added to be able to use the UART correctly.

What works : 

* The ADC works
* When recieving R, correct status information is sent trough the UART
* The external interrupt works
* Every error is displayed trough the UART
* The RTC and its associated functions (reset...) works
* The correct information is sent to the printer
* Packages are correctly detected and identified.
