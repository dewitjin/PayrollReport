## Synopsis

This console application helps small business owners to produce a Payroll Report.  

<img src="https://raw.githubusercontent.com/dewitjin/PayRollReport/master/images/report.png" width="250">

Essentially, this is a template to read and write text files using C++.  Each line in the text file called EmployeePayInput.txt contains a set of employee data, and each data is separated by a null (space).  After each data is read in, it is validated and assign to the appropriate variables, such that we have data for social insurance number, gross pay, net pay, pension and deduction.

Each data gets validated according to a set of parameters:

Social insurance number has to be 9 digits.
Hours worked has to range from 40 to 54 hours.
Hours are calculated with the first 40 hours with regular pay. 
Hours between 40 to 54 hours are calculated with time and a half pay rate.
The pay rate has to be $99.99 or lower.
Exemption has to range from 0 to 19.
Deduction has to incorporate both the federal and provincial constants.
Pension has to be 7.7% of gross pay or $16.50, whichever is lower.
Net pay has to be calculated such that deduction and pension pay is subtracted from gross.

After data is validated, a report will be generated in a txt file called EmployeePayOutput.txt. If data is invalid, then the console will output error messages.

## Code Example

The key to making the code in this project is reusable is using a lot of constant variables listed at the very top.  This allows any programmer to modify the value right away.  If you don't like the name of the report, then change the value of HEADER.

![alt tag]()  

## Motivation

This project is a modified lab assignment I had to do for a C++ course.  The Instructor provided us with the bones of the codes, in terms of how to read and write to the text documents.

This assignment turned out to be very useful because I can modify the content in so many different ways to produce customized business reports and I hope it helps many others.

## Installation

This project was built using Visual Studio 2015 (VS) and uses the C++ compiler that comes with VS. In order for the application to run smoothly the EmployeePayInput.txt has to be included at solution level.

![alt tag]()

There are many things you could do to expand this project.  This console application, however, will help you produce a pretty neat Payroll Report right now without modifications.

## API Reference

None right now.

## Tests

If data is invalid, then the console will output error messages.

## Contributors

The best way to reach me is via my Email at dewi.tjin@gmail.com

If you would like to contribute please fork the repo and I will review code.


## License

The MIT License (MIT)

Copyright (c) 2016 DEWI TJIN

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

